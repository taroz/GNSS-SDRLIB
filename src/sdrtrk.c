/*------------------------------------------------------------------------------
* sdrtrk.c : SDR tracking functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

/* sdr tracking function -------------------------------------------------------
* sdr tracking function called from sdr channel thread
* args   : sdrch_t *sdr      I/O sdr channel struct
*          uint64_t buffloc  I   buffer location
*          uint64_t cnt      I   counter of sdr channel thread
* return : uint64_t              current buffer location
*-----------------------------------------------------------------------------*/
extern uint64_t sdrtracking(sdrch_t *sdr, uint64_t buffloc, uint64_t cnt)
{
    char *data=NULL;
    uint64_t bufflocnow;

    sdr->flagtrk=OFF;

    /* memory allocation */
    data=(char*)sdrmalloc(sizeof(char)*(sdr->nsamp+100)*sdr->dtype);

    /* current buffer location */
    mlock(hreadmtx);
    bufflocnow=sdrstat.fendbuffsize*sdrstat.buffcnt-sdr->nsamp; 
    unmlock(hreadmtx);

    if (bufflocnow>buffloc) {
        sdr->currnsamp=(int)((sdr->clen-sdr->trk.remcode)/
            (sdr->trk.codefreq/sdr->f_sf));
        rcvgetbuff(&sdrini,buffloc,sdr->currnsamp,sdr->ftype,sdr->dtype,data);

        memcpy(sdr->trk.oldI,sdr->trk.II,1+2*sdr->trk.corrn*sizeof(double));
        memcpy(sdr->trk.oldQ,sdr->trk.QQ,1+2*sdr->trk.corrn*sizeof(double));
        sdr->trk.oldremcode=sdr->trk.remcode;
        sdr->trk.oldremcarr=sdr->trk.remcarr;
        /* correlation */
        correlator(data,sdr->dtype,sdr->ti,sdr->currnsamp,sdr->trk.carrfreq,
            sdr->trk.oldremcarr,sdr->trk.codefreq, sdr->trk.oldremcode,
            sdr->trk.corrp,sdr->trk.corrn,sdr->trk.QQ,sdr->trk.II,
            &sdr->trk.remcode,&sdr->trk.remcarr,sdr->code,sdr->clen);

        /* navigation data */
        sdrnavigation(sdr,buffloc,cnt);

        sdr->flagtrk=ON;
    } else {
        sleepms(1);
    }
    sdrfree(data);
    return bufflocnow;
}
/* cumulative sum of correlation output ----------------------------------------
* phase/frequency lock loop (2nd order PLL with 1st order FLL)
* carrier frequency is computed
* args   : sdrtrk_t trk     I/0 sdr tracking struct
*          int    polarity  I   polarity caused by secondary code
*          int    flag1     I   reset flag 1
*          int    flag2     I   reset flag 2
* return : none
*-----------------------------------------------------------------------------*/
extern void cumsumcorr(sdrtrk_t *trk, int polarity)
{
    int i;
    for (i=0;i<1+2*trk->corrn;i++) {
        trk->II[i]*=polarity;
        trk->QQ[i]*=polarity;

        trk->oldsumI[i]+=trk->oldI[i];
        trk->oldsumQ[i]+=trk->oldQ[i];
        trk->sumI[i]+=trk->II[i];
        trk->sumQ[i]+=trk->QQ[i];
    }
}
extern void clearcumsumcorr(sdrtrk_t *trk)
{
    int i;
    for (i=0;i<1+2*trk->corrn;i++) {
        trk->oldsumI[i]=0;
        trk->oldsumQ[i]=0;
        trk->sumI[i]=0;
        trk->sumQ[i]=0;
    }
}
/* phase/frequency lock loop ---------------------------------------------------
* phase/frequency lock loop (2nd order PLL with 1st order FLL)
* carrier frequency is computed
* args   : sdrch_t *sdr     I/0 sdr channel struct
*          sdrtrkprm_t *prm I   sdr tracking prameter struct
* return : none
*-----------------------------------------------------------------------------*/
extern void pll(sdrch_t *sdr, sdrtrkprm_t *prm, double dt)
{
    double carrErr,freqErr;
    double IP=sdr->trk.sumI[0],QP=sdr->trk.sumQ[0];
    double oldIP=sdr->trk.oldsumI[0],oldQP=sdr->trk.oldsumQ[0];
    double f1,f2;

    /* PLL discriminator */
    if (IP>0)
        carrErr=atan2(QP,IP)/PI;
    else
        carrErr=atan2(-QP,-IP)/PI;

    /* FLL discriminator */
    f1=(IP==0)?    PI/2:atan(QP/IP);
    f2=(oldIP==0)? PI/2:atan(oldQP/oldIP);
    freqErr=f1-f2;

    if (freqErr>PI/2)
        freqErr = PI-freqErr;
    if (freqErr<-PI/2)
        freqErr = -PI-freqErr;
    //freqErr/=DPI;

    /* 2nd order PLL with 1st order FLL */
    sdr->trk.carrNco+=prm->pllaw*(carrErr-sdr->trk.carrErr)+
        prm->pllw2*dt*carrErr+prm->fllw*dt*freqErr;

    sdr->trk.carrfreq=sdr->acq.acqfreq+sdr->trk.carrNco;
    sdr->trk.carrErr=carrErr;
    sdr->trk.freqErr=freqErr;
}
/* delay lock loop -------------------------------------------------------------
* delay lock loop (2nd order DLL)
* code frequency is computed
* args   : sdrch_t *sdr     I/0 sdr channel struct
*          sdrtrkprm_t *prm I   sdr tracking prameter struct
* return : none
*-----------------------------------------------------------------------------*/
extern void dll(sdrch_t *sdr, sdrtrkprm_t *prm, double dt)
{
    double codeErr;
    double IE=sdr->trk.sumI[sdr->trk.ne],IL=sdr->trk.sumI[sdr->trk.nl];
    double QE=sdr->trk.sumQ[sdr->trk.ne],QL=sdr->trk.sumQ[sdr->trk.nl];

    codeErr=(sqrt(IE*IE+QE*QE)-
        sqrt(IL*IL+QL*QL))/(sqrt(IE*IE+QE*QE)+sqrt(IL*IL+QL*QL));

    /* 2nd order DLL */
    sdr->trk.codeNco+=prm->dllaw*(codeErr-sdr->trk.codeErr)+
        prm->dllw2*dt*codeErr;

    /* carrier aiding */
    sdr->trk.codefreq=sdr->crate-sdr->trk.codeNco+
        (sdr->trk.carrfreq-sdr->f_if-sdr->foffset)/(sdr->f_cf/sdr->crate);
    sdr->trk.codeErr=codeErr;
}
/* set observation data --------------------------------------------------------
* calculate doppler/carrier phase/SNR
* args   : sdrch_t *sdr     I   sdr channel struct
*          uint64_t buffloc I   current buffer location
*          uint64_t cnt     I   current counter of sdr channel thread
*          sdrtrk_t trk     I/0 sdr tracking struct
*          int    snrflag   I   SNR calculation flag
* return : none
*-----------------------------------------------------------------------------*/
extern void setobsdata(sdrch_t *sdr, uint64_t buffloc, uint64_t cnt, 
                       sdrtrk_t *trk, int snrflag)
{
    shiftdata(&trk->tow[1],&trk->tow[0],sizeof(double),OBSINTERPN-1);
    shiftdata(&trk->L[1],&trk->L[0],sizeof(double),OBSINTERPN-1);
    shiftdata(&trk->D[1],&trk->D[0],sizeof(double),OBSINTERPN-1);
    shiftdata(&trk->codei[1],&trk->codei[0],sizeof(uint64_t),OBSINTERPN-1);
    shiftdata(&trk->cntout[1],&trk->cntout[0],sizeof(uint64_t),OBSINTERPN-1);
    shiftdata(&trk->remcout[1],&trk->remcout[0],sizeof(double),OBSINTERPN-1);

    trk->tow[0]=sdr->nav.firstsftow+
        (double)(cnt-sdr->nav.firstsfcnt)*sdr->ctime;
    trk->codei[0]=buffloc;
    trk->cntout[0]=cnt;
    trk->remcout[0]=trk->oldremcode*sdr->f_sf/trk->codefreq;

    /* doppler */
    trk->D[0]=-(trk->carrfreq-sdr->f_if-sdr->foffset);

    /* carrier phase */
    if (!trk->flagremcarradd) {
        trk->L[0]-=trk->remcarr/DPI;
        //SDRPRINTF("%s cnt=%llu inicarrier=%f m\n",sdr->satstr,cnt,CLIGHT/FREQ1*trk->remcarr/DPI);
        trk->flagremcarradd=ON;
    }

    if (sdr->nav.flagsyncf&&!trk->flagpolarityadd) {
        if (sdr->nav.polarity==1) {
            trk->L[0]+=0.5;
            //SDRPRINTF("%s cnt=%llu polarity=0.5\n",sdr->satstr,cnt);
        } else {
            //SDRPRINTF("%s cnt=%llu polarity=0.0\n",sdr->satstr,cnt);
        }
        trk->flagpolarityadd=ON;
    }

    trk->L[0]+=trk->D[0]*(trk->loopms*sdr->currnsamp/sdr->f_sf);

    trk->Isum+=fabs(trk->sumI[0]);
    if (snrflag) {
        shiftdata(&trk->S[1],&trk->S[0],sizeof(double),OBSINTERPN-1);
        shiftdata(&trk->codeisum[1],&trk->codeisum[0],
            sizeof(uint64_t),OBSINTERPN-1);

        /* signal to noise ratio */
        trk->S[0]=10*log(trk->Isum/100.0/100.0)+log(500.0)+5;
        trk->codeisum[0]=buffloc;
        trk->Isum=0;
    }
}
