/*------------------------------------------------------------------------------
* sdrspec.c : SDR spectrum analyzer functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

/* initialize spectrum analyzer ------------------------------------------------
* create spectrum analyzer thread
* args   : sdrspec_t* sdrspecgui I   sdr spectrum struct
* return : none
* note : this function is only called from GUI application
*-----------------------------------------------------------------------------*/
extern void initsdrspecgui(sdrspec_t *sdrspecgui)
{
    memcpy(&sdrspec,sdrspecgui,sizeof(sdrspec_t)); /* copy setting from GUI */

    /* start specthread */
    cratethread(hspecthread,specthread,&sdrspec);
}
/* spectrum analyzer thread ----------------------------------------------------
* spectrum analyzer thread
* args   : void * arg       I   sdr spectrum struct
* return : none
*-----------------------------------------------------------------------------*/
#ifdef WIN32
extern void specthread(void * arg) 
#else
extern void *specthread(void * arg) 
#endif
{
    sdrspec_t *spec=(sdrspec_t*)arg;
    char *data;
    uint64_t buffloc;
    double *xI,*yI,*xQ,*yQ,*freq,*pspec;

    /* check front end */
    if (sdrini.fend==FEND_FILE) {
        if (spec->ftype==FTYPE2&&(!sdrini.useif2)) {
            SDRPRINTF("error: spectrum analysis FE2 doesn't exist\n");
            return THRETVAL;
        }
    }
    if (sdrini.fend==FEND_GN3SV2||sdrini.fend==FEND_GN3SV3) {
        if (spec->ftype==FTYPE2) {
            SDRPRINTF("error: spectrum analysis FE2 doesn't exist\n");
            return THRETVAL;
        }
    }
    /* memory allocation */
    if (!(data=(char*)malloc(sizeof(char)*spec->nsamp*spec->dtype*SPEC_LEN)) ||
        !(freq=(double*)malloc(sizeof(double)*SPEC_NFFT*spec->dtype)) ||
        !(pspec=(double*)malloc(sizeof(double)*SPEC_NFFT*spec->dtype)) ||
        !(xI=(double*)malloc(sizeof(double)*SPEC_BITN)) ||
        !(yI=(double*)malloc(sizeof(double)*SPEC_BITN)) ||
        !(xQ=(double*)malloc(sizeof(double)*SPEC_BITN)) ||
        !(yQ=(double*)malloc(sizeof(double)*SPEC_BITN))) {
            SDRPRINTF("error: specthread memory allocation\n");
            return THRETVAL;
    }
    /* initiarize plot structs */
    if (initspecpltstruct(spec)<0) {
        sdrstat.stopflag=ON;
    }
    while (!(sdrstat.stopflag||sdrstat.specflag)) {
        /* spectrum analysis interval */
        sleepms(SPEC_MS);

        /* current buffer location */
        mlock(hreadmtx);
        buffloc=(sdrstat.fendbuffsize*sdrstat.buffcnt)-SPEC_LEN*spec->nsamp;
        unmlock(hreadmtx);

        /* get current if data */
        rcvgetbuff(&sdrini,buffloc,SPEC_LEN*spec->nsamp,spec->ftype,
            spec->dtype,data);

        /* histogram calculation */
        calchistgram(data,spec->dtype,SPEC_LEN*spec->nsamp,xI,yI,xQ,yQ);

        /* histogram plot */
        if (spec->dtype==DTYPEI||spec->dtype==DTYPEIQ) {
            spec->histI.x=xI;
            spec->histI.y=yI;
            plot(&spec->histI);
        }
        if (spec->dtype==DTYPEIQ) {
            spec->histQ.x=xQ;
            spec->histQ.y=yQ;
            plot(&spec->histQ);
        }

        /* spectrum analyzationr */
        if (spectrumanalyzer(data,spec->dtype,spec->nsamp*SPEC_LEN,spec->f_sf,
            SPEC_NFFT,freq,pspec)<0) {
                sdrstat.stopflag=ON;
        }
        /* power spectrum plot */
        spec->pspec.x=freq;
        spec->pspec.y=pspec;
        plot(&spec->pspec);
    }
    /* free plot structs */
    quitspecpltstruct(spec);
    free(data);
    SDRPRINTF("spectrum thred is finished!\n");

    return THRETVAL;
}
/* initialize spectrum plot struct ---------------------------------------------
* initialize spectrum plot struct
* args   : sdrspec_t *spec  I/O sdr spectrum struct
* return : int                  status 0:okay -1:failure
*-----------------------------------------------------------------------------*/
extern int initspecpltstruct(sdrspec_t *spec)
{
    int n;

    /* histogram (real sample) */
    setsdrplotprm(&spec->histI,PLT_BOX,SPEC_BITN,0,0,OFF,1,SPEC_PLT_H,
        SPEC_PLT_W,SPEC_PLT_MH,SPEC_PLT_MW,1);
    if (initsdrplot(&spec->histI)<0) return -1;
    settitle(&spec->histI,"Real Sample Histogram");
    setlabel(&spec->histI,"Sample Value","Number of Samples");
    setyrange(&spec->histI,0,70000);

    /* histogram (imaginary sample) */
    setsdrplotprm(&spec->histQ,PLT_BOX,SPEC_BITN,0,0,OFF,1,SPEC_PLT_H,
        SPEC_PLT_W,SPEC_PLT_MH,SPEC_PLT_MW,2);
    if (initsdrplot(&spec->histQ)<0) return -1;
    settitle(&spec->histQ,"Imaginary Sample Histogram");
    setlabel(&spec->histQ,"Sample Value","Number of Samples");
    setyrange(&spec->histQ,0,70000);

    if (spec->dtype==DTYPEIQ) n=3;
    else n=2;

    /* power spectrum analysis */
    setsdrplotprm(&spec->pspec,PLT_XY,SPEC_NFFT*spec->dtype,0,20,OFF,1,
        SPEC_PLT_H,SPEC_PLT_W,SPEC_PLT_MH,SPEC_PLT_MW,n);
    if (initsdrplot(&spec->pspec)<0) return -1;
    settitle(&spec->pspec,"Power Spectrum Analysis");
    setlabel(&spec->pspec,"Frequency (MHz)","Power Spectrum (dB)");
    setyrange(&spec->pspec,-40,0);

    return 0;
}
/* clean spectrum plot struct --------------------------------------------------
* free memory and close pipe
* args   : sdrspec_t *spec  I/O spectrum struct
* return : none
*-----------------------------------------------------------------------------*/
extern void quitspecpltstruct(sdrspec_t *spec)
{
    quitsdrplot(&spec->histI);
    quitsdrplot(&spec->histQ);
    quitsdrplot(&spec->pspec);
}
/* histogram calculation -------------------------------------------------------
* histogram calculation of input IF data
* args   : char   *data     I   sampling data vector (n x 1 or 2n x 1)
*          int    dtype     I   sampling data type (1:real,2:complex)
*          int    n         I   number of samples
*          double *xI       O   histogram bins {-7,-5,-3,-1,+1,+3,+5,+7} (3 bit)
*          double *yI       O   histogram values (in-phase samples) 
*          double *xQ       O   histogram bins {-7,-5,-3,-1,+1,+3,+5,+7} (3 bit)
*          double *yQ       O   histogram values (quadrature-phase samples)
* return : none
*-----------------------------------------------------------------------------*/
extern void calchistgram(char *data, int dtype, int n, double *xI, double *yI,
                         double *xQ, double *yQ)
{
    int i,maxd=0;
    double xx[SPEC_BITN]={-7,-5,-3,-1,+1,+3,+5,+7}; /* 3bit */

    memcpy(xI,xx,sizeof(double)*SPEC_BITN);
    memcpy(xQ,xx,sizeof(double)*SPEC_BITN);
    memset(yI, 0,sizeof(double)*SPEC_BITN);
    memset(yQ, 0,sizeof(double)*SPEC_BITN);

    /* check max value */
    for (i=0;i<n*dtype;i++) if (maxd<abs(data[i])) maxd=abs(data[i]);
    
    /* count samples */
    if (dtype==DTYPEI) {
        for (i=0;i<n;i++) {
            if (maxd>7)
                yI[(int)((double)data[i]/maxd*4+4)]++;
            else
                 yI[(data[i]+7)/2]++;
        }
    }
    else if (dtype==DTYPEIQ) {
        for (i=0;i<n;i++) {
            if (maxd>7)
                yI[(int)((double)data[2*i  ]/maxd*4+4)]++;
            else
                yI[(data[i]+7)/2]++;
        }
        for (i=0;i<n;i++) {
            if (maxd>7)
                yQ[(int)((double)data[2*i+1]/maxd*4+4)]++;
            else
                yQ[(data[i]+7)/2]++;
        }
    }
}
/* hanning window --------------------------------------------------------------
* create hanning window
* args   : int    n         I   number of samples
*          float *win       O   hanning window
* return : none
*-----------------------------------------------------------------------------*/
extern void hanning(int n, float *win)
{
    int i;
    for (i=0;i<n;i++)
        win[i]=(float)(0.5*(1-cos(2*PI*(i+1)/(n+1))));
}
/* spectrum analyzer -----------------------------------------------------------
* power spectrum analyzer function
* args   : char   *data     I   sampling data vector (n x 1 or 2n x 1)
*          int    dtype     I   sampling data type (1:real,2:complex)
*          int    n         I   number of samples
*          double f_sf      I   sampling frequency (Hz)
*          int    nfft      I   number of fft points
*          double *freq     O   fft frequency vector (Hz)
*          double *pspec    O   fft power spectrum vector (dB)
* return : int                  status 0:okay -1:failure
* note : http://billauer.co.il/easyspec.html as a reference
*-----------------------------------------------------------------------------*/
extern int spectrumanalyzer(const char *data, int dtype, int n, double f_sf,
                            int nfft, double *freq, double *pspec)
{
    int i,j,k,zuz,nwin=nfft/2,maxshift=n-nwin;
    float *x,*xxI,*xxQ,*win;
    double *s;
    cpx_t *xxx;

    if (!(x  =(float*)malloc(sizeof(float)*n*dtype)) || 
        !(xxI=(float*)malloc(sizeof(float)*nfft*2)) ||
        !(xxQ=(float*)malloc(sizeof(float)*nfft*2)) ||
        !(s  =(double*)calloc(sizeof(double),nfft*2)) ||
        !(xxx=cpxmalloc(nfft*2)) ||
        !(win=(float*)malloc(sizeof(float)*nwin))) {
            SDRPRINTF("error: spectrumanalyzer memory allocation\n"); return -1;
    }
    /* create hanning window */
    hanning(nwin,win);

    for (i=0;i<dtype*n;i++)
        x[i]=(float)(data[i]*(17.127/(nfft*2)/sqrt((float)SPEC_NLOOP)));

    /* spectrum analysis */
    for (i=0;i<SPEC_NLOOP;i++) {

        zuz=(int)floor((double)rand()/RAND_MAX*maxshift);
        memset(xxI,0,sizeof(float)*nfft*2);
        memset(xxQ,0,sizeof(float)*nfft*2);

        for (j=zuz,k=0;j<nwin+zuz;j++,k++) {
            if (dtype==DTYPEI) {
                xxI[k]=win[k]*x[j];
            }
            if (dtype==DTYPEIQ) {
                xxI[k]=win[k]*x[2*j];
                xxQ[k]=win[k]*x[2*j+1];
            }
        }
        /* to complex domain */
        if (dtype==DTYPEI)
            cpxcpxf(xxI,NULL,1.0,nfft*2,xxx);
        if (dtype==DTYPEIQ)
            cpxcpxf(xxI,xxQ,1.0,nfft*2,xxx);

        /* compute power spectrum */
        cpxpspec(NULL,xxx,nfft*2,1,s);
    }
    /* frequency and power */
    if (dtype==DTYPEI) {
        for (i=0;i<nfft;i++) {
            pspec[i]=10*log10(s[i]); /* dB */
            freq[i]=(i*(f_sf/2)/(nfft))/1e6; /* MHz */
        }
    } else if (dtype==DTYPEIQ) {
        for (i=0;i<dtype*nfft;i++) {
            if (i<nfft)
                pspec[i]=10*log10(s[ nfft+i]); /* dB */
            else
                pspec[i]=10*log10(s[-nfft+i]); /* dB */
            freq[i]=(-f_sf/2+i*f_sf/nfft/2)/1e6; /* MHz */
        }
    }
    free(x); free(xxI); free(xxQ); free(s); free(win); cpxfree(xxx);
    return 0;
}
