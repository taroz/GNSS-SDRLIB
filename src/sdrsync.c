/*------------------------------------------------------------------------------
* sdrmain.c : SDR main functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

/* synchronization thread ------------------------------------------------------
* synchronization thread for pseudo range computation  
* args   : void   *arg      I   not used
* return : none
* note : this thread collects all data of sdr channel thread and compute pseudo
*        range at every output timing.
*-----------------------------------------------------------------------------*/
#ifdef WIN32
extern void syncthread(void * arg)
#else
extern void *syncthread(void * arg)
#endif
{
    int i,j,nsat,isat[MAXOBS],ind[MAXSAT]={0},refi;
    uint64_t sampref,sampbase,codei[MAXSAT],diffcnt,mincodei;
    double codeid[OBSINTERPN],remcode[MAXSAT],samprefd,reftow=0,oldreftow;
    sdrobs_t obs[MAXSAT];
    sdrtrk_t trk[MAXSAT]={{0}};

    /* start tcp server (rtcm) */
    if (sdrini.rtcm) {
        sdrout.soc_rtcm.port=sdrini.rtcmport;
        tcpsvrstart(&sdrout.soc_rtcm);
    }
    
    /* start tcp server (sbas) */
    if (sdrini.sbas) {
        sdrout.soc_sbas.port=sdrini.sbasport;
        tcpsvrstart(&sdrout.soc_sbas);
    }

    /* rinex output setting */
    if (sdrini.rinex) {
        createrinexopt(&sdrout.opt);
        if ((createrinexobs(sdrout.rinexobs,&sdrout.opt)<0)|| 
            (createrinexnav(sdrout.rinexnav,&sdrout.opt)<0)) {
                sdrstat.stopflag=ON;
        }
    }
    sdrout.obsd=(obsd_t *)calloc(MAXSAT,sizeof(obsd_t));

    while (!sdrstat.stopflag) {

        mlock(hobsmtx);

        /* copy all tracking data */
        for (i=nsat=0;i<sdrini.nch;i++) {
            if (sdrch[i].nav.flagdec&&sdrch[i].nav.sdreph.eph.week!=0) {
                memcpy(&trk[nsat],&sdrch[i].trk,sizeof(sdrch[i].trk));
                isat[nsat]=i;
                nsat++;
            }
        }

        unmlock(hobsmtx);

        /* find minimum tow channel (most distant satellite) */
        oldreftow=reftow;
        reftow=3600*24*7;
        for (i=0;i<nsat;i++) {
            if (trk[i].tow[0]<reftow)
                reftow=trk[i].tow[0];
        }
        /* output timing check */
        if (nsat==0||oldreftow==reftow||((int)(reftow*1000)%sdrini.outms)!=0) {
            continue;
        }
        /* select same timing index */
        for (i=0;i<nsat;i++) {
            for (j=0;j<OBSINTERPN;j++) {
                if (fabs(trk[i].tow[j]-reftow)<1E-4) {
                    ind[i]=j;
                    break;
                }
            }
            if (j==OBSINTERPN-1&&ind[i]==0) 
                SDRPRINTF("error:%s reftow=%.1f tow=%.1f\n",
                    sdrch[isat[i]].satstr,trk[i].tow[OBSINTERPN-1],reftow);
        }

        /* decide reference satellite (nearest satellite) */
        mincodei=UINT64_MAX;
        refi=0;
        for (i=0;i<nsat;i++) {
            codei[i]=trk[i].codei[ind[i]];
            remcode[i]=trk[i].remcout[ind[i]];
            if (trk[i].codei[ind[i]]<mincodei) {
                refi=i;
                mincodei=trk[i].codei[ind[i]];
            }
        }
        /* reference satellite */
        diffcnt=trk[refi].cntout[ind[refi]]-sdrch[isat[refi]].nav.firstsfcnt;
        sampref=sdrch[isat[refi]].nav.firstsf+
            (uint64_t)(sdrch[isat[refi]].nsamp*
            (-PTIMING/(1000*sdrch[isat[refi]].ctime)+diffcnt));
        sampbase=trk[refi].codei[OBSINTERPN-1]-10*sdrch[isat[refi]].nsamp;
        samprefd=(double)(sampref-sampbase);

        /* computation observation data */
        for (i=0;i<nsat;i++) {
            obs[i].sys=sdrch[isat[i]].sys;
            obs[i].prn=sdrch[isat[i]].prn;
            obs[i].week=sdrch[isat[i]].nav.sdreph.week_gpst;
            obs[i].tow=reftow+(double)(PTIMING)/1000; 
            obs[i].P=CLIGHT*sdrch[isat[i]].ti*
                ((double)(codei[i]-sampref)-remcode[i]); /* pseudo range */
            
            /* uint64 to double for interp1 */
            uint64todouble(trk[i].codei,sampbase,OBSINTERPN,codeid);
            obs[i].L=interp1(codeid,trk[i].L,OBSINTERPN,samprefd);
            obs[i].D=interp1(codeid,trk[i].D,OBSINTERPN,samprefd);
            obs[i].S=trk[i].S[0];
        }
        sdrout.nsat=nsat;
        sdrobs2obsd(obs,nsat,sdrout.obsd);

        /* rinex obs output */
        if (sdrini.rinex) {
            if (writerinexobs(sdrout.rinexobs,&sdrout.opt,sdrout.obsd,
                sdrout.nsat)<0) {
                    sdrstat.stopflag=ON;
            }
        }
        /* rtcm obs output */
        if (sdrini.rtcm&&sdrout.soc_rtcm.flag) 
            sendrtcmobs(sdrout.obsd,&sdrout.soc_rtcm,sdrout.nsat);

        /* navigation data output */
        for (i=0;i<sdrini.nch;i++) {
            if ((sdrch[i].nav.sdreph.update)&&
                (sdrch[i].nav.sdreph.cnt==sdrch[i].nav.sdreph.cntth)) {
                sdrch[i].nav.sdreph.cnt=0;
                sdrch[i].nav.sdreph.update=OFF;

                /* rtcm nav output */
                if (sdrini.rtcm&&sdrout.soc_rtcm.flag) 
                    sendrtcmnav(&sdrch[i].nav.sdreph,&sdrout.soc_rtcm);

                /* rinex nav output */
                if (sdrini.rinex) {
                    if (writerinexnav(sdrout.rinexnav,
                        &sdrout.opt,&sdrch[i].nav.sdreph)<0) {
                        
                        sdrstat.stopflag=ON;
                    }
                }
            }
        }
    }
    /* thread termination */
    free(sdrout.obsd);
    tcpsvrclose(&sdrout.soc_rtcm);
    tcpsvrclose(&sdrout.soc_sbas);
    SDRPRINTF("SDR syncthread finished!\n");

    return THRETVAL;
}
