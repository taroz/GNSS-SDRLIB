/*------------------------------------------------------------------------------
* sdrlex.c : QZSS LEX signal functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

static fftwf_plan  plan=NULL;
static fftwf_plan iplan=NULL; 

/* LEX correlation function ----------------------------------------------------
* compute LEX message based on FFT 
* args   : sdrch_t *sdr     I   sdr channel struct
*          char   *data     I   input 4ms IF data
*          int    dtype     I   sampling data type (1:real,2:complex)
*          double ti        I   sampling interval (s)
*          int    n         I   number of samples
*          double freq      I   doppler frequency computed by L1 signal (Hz)
*          double crate     I   code chip rate (chip/s)
*          int    m         I   number of FFT points
*          cpx_t  codex     I   frequency domain code
*          double *cn       O   estimated C/N0
* return : uint8_t              LEX message word
* note : LEX message uses CSK modulation and it can be solve by FFT correlation
*        LEX(E6) doppler shift and code phase are estimated by L1 signal
*-----------------------------------------------------------------------------*/
uint8_t lexcorr_fft(sdrch_t *sdr, const char *data, int dtype, double ti, int n,
                    double freq, double crate, int m, cpx_t* codex, double *cn)
{
    int codei,codei2,corri,exinds,exinde;
    cpx_t *datax;
    short *dataI,*dataQ;
    char *dataR;
    double peakr,*P,maxP,maxP2,meanP;

    /* memory allocation */
    if (!(P=(double*)calloc(m,sizeof(double))) ||
        !(dataR=(char  *)sdrmalloc(sizeof(char )*m*dtype))||
        !(dataI=(short *)sdrmalloc(sizeof(short)*m))||
        !(dataQ=(short *)sdrmalloc(sizeof(short)*m))||
        !(datax=cpxmalloc(m))) return -1;

    /* zero padding */
    memset(dataR,0,m*dtype);
    memcpy(dataR,data,n*dtype);

    /* mix local carrier */
    mixcarr(dataR,dtype,ti,m,freq,0.0,dataI,dataQ);

    /* to complex */
    cpxcpx(dataI,dataQ,(1.0/32)/m,m,datax);

    /* convolution */
    if (plan==NULL||iplan==NULL) {
        fftwf_plan_with_nthreads(NFFTTHREAD); /* fft execute in multi threads */
        plan=fftwf_plan_dft_1d(n,datax,datax,FFTW_FORWARD,FFTW_ESTIMATE);
        
        fftwf_plan_with_nthreads(NFFTTHREAD); /* fft execute in multi threads */
        iplan=fftwf_plan_dft_1d(n,datax,datax,FFTW_BACKWARD,FFTW_ESTIMATE);
    }
    cpxconv(plan,iplan,datax,codex,m,m,0,P);

    /* maximum index */
    maxP=maxvd(P,m,-1,-1,&codei);
    corri=(int)((double)(n-codei)/n*sdr->clen/2);
    if (corri==(int)(sdr->clen/2)) corri=0;

    /* C/N0 calculation */
    exinds=codei-sdr->nsampchip; if(exinds<0) exinds+=n; /* excluded index */
    exinde=codei+sdr->nsampchip; if(exinde>=n) exinde-=n;
    meanP=meanvd(P,n,exinds,exinde); /* mean of correlation */
    (*cn)=10*log10(maxP/meanP/sdr->ctime);

    maxP2=maxvd(P,m,exinds,exinde,&codei2);
    peakr=maxP/maxP2;
    
    if (peakr<1.5)
        SDRPRINTF("error: peakr=%.1f\n",peakr);

    /* message must be 0-255 */
    if (corri>255)
        SDRPRINTF("error: corri=%05d codei=%06d cn0=%.1f\n",corri,codei,cn);

    free(P); sdrfree(dataR); sdrfree(dataI); sdrfree(dataQ); cpxfree(datax);
    return (uint8_t)corri;
}
/* LEX thread ------------------------------------------------------------------
* LEX message thread (called every 4ms from sdr channel thread)  
* args   : void * arg       I   sdr channel struct
* return : none
* note : Reed-Solomon error correction is used
*-----------------------------------------------------------------------------*/
#ifdef WIN32
void lexthread(void * arg)
#else
void *lexthread(void * arg)
#endif
{
    sdrch_t *sdr=(sdrch_t*)arg;
    int cnt=0,lexch=0,state,i,nerr,errloc[LENLEXRS],time=0,dt,mid;
    uint64_t buffloc;
    double dfreq,cn0;
    char *data;
    uint8_t corri,sendbuf[LENLEXRCV],rsmsg[LENLEXRS];
    uint8_t lexpre[LENLEXPRE]={0x1A,0xCF,0xFC,0x1D}; /* preamble */
    sdrlex_t sdrlex={{0}};
    sdrout_t out={0};
    unsigned long tick=0;
    FILE *fplexlog=NULL,*fplexbin=NULL;
    short *rcode;
    cpx_t *xcode;

    if (sdrini.log) {
        fplexlog=fopen("LEXLOG.csv","w");
        fplexbin=fopen("LEXBIN.bin","wb");
        fprintf(fplexlog,"Tow,CN0,Time(ms),Error\n");
    }

    /* start tcp server (lex) */
    if (sdrini.lex) {
        out.soc_lex.port=sdrini.lexport;
        tcpsvrstart(&out.soc_lex);
    }

    data=(char*)sdrmalloc(sizeof(char)*sdr->nsamp*sdr->dtype);

    /* lex channel is last */
    lexch=sdrini.nch;

    /* FFT code generation */
    if (!(rcode=(short *)sdrmalloc(sizeof(short)*sdr->nsamp)) || 
        !(xcode=cpxmalloc(sdr->nsamp))) {
            SDRPRINTF("error: initsdrch memory alocation\n");
            return THRETVAL;
    }
    rescode(sdr->code,sdr->clen,0,0,sdr->ci,sdr->nsamp,rcode); /* resampled code */
    cpxcpx(rcode,NULL,1.0,sdr->nsamp,xcode); /* FFT code */
    cpxfft(NULL,xcode,sdr->nsamp);
    sdrfree(rcode);

    sleepms(3000*sdrini.nch);
    SDRPRINTF("**** LEX sdr thread start! ****\n");
    do {
        /* wait event */
        mlock(hlexmtx);
        waitevent(hlexeve,hlexmtx);
        unmlock(hlexmtx);
        
        /* assist from L1CA */
        buffloc=sdrch[lexch].trk.codei[1]+sdrch[lexch].currnsamp+DSAMPLEX;
        dfreq=-sdrch[lexch].trk.D[1]*(FREQ6/FREQ1);

        /* get current data */
        rcvgetbuff(&sdrini,buffloc,sdr->nsamp,sdr->ftype,sdr->dtype,data);

        tick=tickgetus();
        /* LEX correlation */
        corri=lexcorr_fft(sdr,data,sdr->dtype,sdr->ti,sdr->nsamp,dfreq,sdr->crate,
            sdr->nsamp,xcode,&cn0);
        dt=tickgetus()-tick;
        time+=dt;

        if (dt>4000) 
            SDRPRINTF("error: dt=%.1fms(must be < 4ms)\n",(double)dt/1000);

        /* check computation time */
        if (cnt%250==0) {
            //SDRPRINTF("time=%.2fms doppler=%.1f\n",(double)time/250000,dfreq);
            time=0;
        }

        shiftdata(&sdrlex.msg[0],&sdrlex.msg[1],1,LENLEXMSG-1); /* shift to left */
        sdrlex.msg[LENLEXMSG-1]=corri; /* add last */

        /* preamble search */
        state=0;
        for (i=0;i<LENLEXPRE;i++) state+=abs(sdrlex.msg[i]-lexpre[i]);

        if (state==0) {
            /* reed solomon */
            memset(rsmsg,0,LENLEXRS);
            memcpy(&rsmsg[9],&sdrlex.msg[LENLEXPRE],LENLEXRS-9);

            /* RS decode */
            nerr=decode_rs_ccsds(rsmsg,errloc,0,0);
            if (nerr!=0)
                SDRPRINTF("RS correct %d symbols!\n",nerr);

            if (sdrini.log) {
                fprintf(fplexlog,"%f,%f,%d,%d\n",
                    sdrch[lexch].trk.tow[0],cn0,time,nerr);
                fwrite(sdrlex.msg,1,LENLEXMSG,fplexbin);
            }

            if (nerr<0) { cnt++; continue; } /* <0 means failed to RS decode */

            /* correct lex message */
            memcpy(&sdrlex.msg[LENLEXPRE],&rsmsg[9],LENLEXRSK-9);

            mid=getbitu(sdrlex.msg,5*8,8);
            SDRPRINTF("LEX Message Type ID=%d\n",mid);

            /* generate send buffer */
            sendbuf[0]=0xAA; /* sync code1 (see rcvlex.c) */
            sendbuf[1]=0x55; /* sync code2 (see rcvlex.c) */

            /* set tow (LEX message does not contain tow information...) */
            setbitu(sendbuf,2*8,4*8,ROUND(sdrch[lexch].trk.tow[0]*1000));
            
            /*  set week ()*/
            setbitu(sendbuf,6*8,2*8,sdrch[lexch].nav.sdreph.eph.week);
            memcpy(&sendbuf[8],sdrlex.msg,LENLEXMSG-LENLEXRSP); /* LEX message */

            /* send LEX message */
            if (sdrini.lex&&out.soc_lex.flag) 
                send(out.soc_lex.c_soc,(char*)sendbuf,LENLEXRCV,0);
        }
        cnt++;
    } while (!sdrstat.stopflag);

    if (sdrini.log) {
        fclose(fplexlog);
        fclose(fplexbin);
    }

    if (out.soc_lex.flag) tcpsvrclose(&out.soc_lex);

    cpxfree(xcode);
    return THRETVAL;
}
