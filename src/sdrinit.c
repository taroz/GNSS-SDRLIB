/*------------------------------------------------------------------------------
* sdrinit.c : SDR initialize/cleanup functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

/* read ini file -------------------------------------------------------------*/
#ifndef WIN32
static int GetFileAttributes(const char *file)
{
    FILE *fp;
    if (!(fp=fopen(file,"r"))) return -1;
    fclose(fp);
    return 0;
}
static void GetPrivateProfileString(const char *sec, const char *key,
    const char *def, char *str, int len, const char *file)
{
    FILE *fp;
    char buff[1024],*p,*q;
    int enter=0;

    strncpy(str,def,len-1); str[len-1]='\0';

    if (!(fp=fopen(file,"r"))) {
        fprintf(stderr,"ini file open error [%s]\n",file);
        return;
    }
    while (fgets(buff,sizeof(buff),fp)) {
        if ((p=strchr(buff,';'))) *p='\0';
        if ((p=strchr(buff,'['))&&(q=strchr(p+1,']'))) {
            *q='\0';
            enter=!strcmp(p+1,sec);
        }
        else if (enter&&(p=strchr(buff,'='))) {
            *p='\0';
            for (q=p-1;q>=buff&&(*q==' '||*q=='\t');) *q--='\0';
            if (strcmp(buff,key)) continue;
            for (q=p+1+strlen(p+1)-1;q>=p+1&&(*q=='\r'||*q=='\n');) *q--='\0';
            strncpy(str,p+1,len-1); str[len-1]='\0';
            break;
        }
    }
    fclose(fp);
}
#endif /* WIN32 */

/* functions used in read ini file ---------------------------------------------
* note : these functions are only used in CLI application
*-----------------------------------------------------------------------------*/
int splitint(char *src, char *dlm, int *out, int n)
{
    int i;
    char *str;
    for (i=0;i<n;i++) {
        if ((str=strtok((i==0)?src:NULL,dlm))==NULL) return -1;
        out[i]=atoi(str);
    }
    return 0;
}
int splitdouble(char *src, char *dlm, double *out, int n)
{
    int i;
    char *str;
    for (i=0;i<n;i++) {
        if ((str=strtok((i==0)?src:NULL,dlm))==NULL) return -1;
        out[i]=atof(str);
    }
    return 0;
}
int readiniint(char *file, char *sec, char *key)
{
    char str[256];
    GetPrivateProfileString(sec,key,"",str,256,file);
    return atoi(str);
}
int readiniints(char *file, char *sec, char *key, int *out, int n)
{
    char str[256];
    GetPrivateProfileString(sec,key,"",str,256,file);
    return splitint(str,",",out,n);
}
double readinidouble(char *file, char *sec, char *key)
{
    char str[256];
    GetPrivateProfileString(sec,key,"",str,256,file);
    return atof(str);
}
int readinidoubles(char *file, char *sec, char *key, double *out, int n)
{
    char str[256];
    GetPrivateProfileString(sec,key,"",str,256,file);
    return splitdouble(str,",",out,n);
}
void readinistr(char *file, char *sec, char *key, char *out)
{
    GetPrivateProfileString(sec,key,"",out,256,file);
}
/* read ini file ---------------------------------------------------------------
* read ini file and set value to sdrini struct
* args   : sdrini_t *ini    I/0 sdrini struct
* return : int                  0:okay -1:error
* note : this function is only used in CLI application
*-----------------------------------------------------------------------------*/
extern int readinifile(sdrini_t *ini)
{
    int i,ret;
    char inifile[]="./gnss-sdrcli.ini";
    char fendfile[256],str[256];

    /* check ini file */
    if ((ret=GetFileAttributes(inifile))<0){
        SDRPRINTF("error: gnss-sdrcli.ini doesn't exist\n");
        return -1;
    }
    /* receiver setting */
    readinistr(inifile,"RCV","FENDCONF",fendfile);

    /* check front-end configuration  file */
    if ((ret=GetFileAttributes(fendfile))<0){
        SDRPRINTF("error: %s doesn't exist\n",fendfile);
        return -1;
    }
    readinistr(fendfile,"FEND","TYPE",str);
    if (strcmp(str,"STEREO")==0)     ini->fend=FEND_STEREO;
    else if (strcmp(str,"GN3SV2")==0)     ini->fend=FEND_GN3SV2;
    else if (strcmp(str,"GN3SV3")==0)     ini->fend=FEND_GN3SV3;
    else if (strcmp(str,"BLADERF")==0)     ini->fend=FEND_BLADERF;
    else if (strcmp(str,"RTLSDR")==0)     ini->fend=FEND_RTLSDR;
    else if (strcmp(str,"FILESTEREO")==0) ini->fend=FEND_FSTEREO;
    else if (strcmp(str,"FILEGN3SV2")==0) ini->fend=FEND_FGN3SV2;
    else if (strcmp(str,"FILEGN3SV3")==0) ini->fend=FEND_FGN3SV3;
    else if (strcmp(str,"FILEBLADERF")==0) ini->fend=FEND_FBLADERF;
    else if (strcmp(str,"FILERTLSDR")==0) ini->fend=FEND_FRTLSDR;
    else if (strcmp(str,"FILE")==0)       ini->fend=FEND_FILE;
    else { SDRPRINTF("error: wrong frontend type: %s\n",str); return -1; }
    if (ini->fend==FEND_FILE    ||ini->fend==FEND_FSTEREO||
        ini->fend==FEND_FGN3SV2 ||ini->fend==FEND_FGN3SV3||
        ini->fend==FEND_FBLADERF||ini->fend==FEND_FRTLSDR) {
        readinistr(fendfile,"FEND","FILE1",ini->file1);
        if (strcmp(ini->file1,"")!=0) ini->useif1=ON;
    }
    if (ini->fend==FEND_FILE) {
        readinistr(fendfile,"FEND","FILE2",ini->file2);
        if (strcmp(ini->file2,"")!=0) ini->useif2=ON;
    }
    ini->f_cf[0]=readinidouble(fendfile,"FEND","CF1");
    ini->f_sf[0]=readinidouble(fendfile,"FEND","SF1");
    ini->f_if[0]=readinidouble(fendfile,"FEND","IF1");
    ini->dtype[0]=readiniint(fendfile,"FEND","DTYPE1");
    ini->f_cf[1]=readinidouble(fendfile,"FEND","CF2");
    ini->f_sf[1]=readinidouble(fendfile,"FEND","SF2");
    ini->f_if[1]=readinidouble(fendfile,"FEND","IF2");
    ini->dtype[1]=readiniint(fendfile,"FEND","DTYPE2");

    /* RTL-SDR only */
    ini->rtlsdrppmerr=readiniint(fendfile,"FEND","PPMERR");

    /* tracking parameter setting */
    ini->trkcorrn=readiniint(fendfile,"TRACK","CORRN");
    ini->trkcorrd=readiniint(fendfile,"TRACK","CORRD");
    ini->trkcorrp=readiniint(fendfile,"TRACK","CORRP");
    ini->trkdllb[0]=readinidouble(fendfile,"TRACK","DLLB1");
    ini->trkpllb[0]=readinidouble(fendfile,"TRACK","PLLB1");
    ini->trkfllb[0]=readinidouble(fendfile,"TRACK","FLLB1");
    ini->trkdllb[1]=readinidouble(fendfile,"TRACK","DLLB2");
    ini->trkpllb[1]=readinidouble(fendfile,"TRACK","PLLB2");
    ini->trkfllb[1]=readinidouble(fendfile,"TRACK","FLLB2");
    
    /* channel setting */
    ini->nch=readiniint(inifile,"CHANNEL","NCH");
    if (ini->nch<1) {
        SDRPRINTF("error: wrong inifile value NCH=%d\n",ini->nch);
        return -1;
    }
    if ((ret=readiniints(inifile,"CHANNEL","PRN",ini->prn,ini->nch))<0 ||
        (ret=readiniints(inifile,"CHANNEL","SYS",ini->sys,ini->nch))<0 ||
        (ret=readiniints(inifile,"CHANNEL","CTYPE",ini->ctype,ini->nch))<0 ||
        (ret=readiniints(inifile,"CHANNEL","FTYPE",ini->ftype,ini->nch))<0) {
            SDRPRINTF("error: wrong inifile value NCH=%d\n",ini->nch);
            return -1;
    }

    /* plot setting */
    ini->pltacq=readiniint(inifile,"PLOT","ACQ");
    ini->plttrk=readiniint(inifile,"PLOT","TRK");

    /* output setting */
    ini->outms   =readiniint(inifile,"OUTPUT","OUTMS");
    ini->rinex   =readiniint(inifile,"OUTPUT","RINEX");
    ini->rtcm    =readiniint(inifile,"OUTPUT","RTCM");
    ini->lex     =readiniint(inifile,"OUTPUT","LEX");
    ini->sbas    =readiniint(inifile,"OUTPUT","SBAS");
    ini->log     =readiniint(inifile,"OUTPUT","LOG");
    readinistr(inifile,"OUTPUT","RINEXPATH",ini->rinexpath);
    ini->rtcmport=readiniint(inifile,"OUTPUT","RTCMPORT");
    ini->lexport =readiniint(inifile,"OUTPUT","LEXPORT");
    ini->sbasport=readiniint(inifile,"OUTPUT","SBASPORT");

    /* spectrum setting */
    ini->pltspec=readiniint(inifile,"SPECTRUM","SPEC");

    /* sdr channel setting */
    for (i=0;i<sdrini.nch;i++) {
        if (sdrini.ctype[i]==CTYPE_L1CA ||
            sdrini.ctype[i]==CTYPE_G1 ||
            sdrini.ctype[i]==CTYPE_E1B ||
            sdrini.ctype[i]==CTYPE_B1I
            ) {
            sdrini.nchL1++;
        }
        if (sdrini.ctype[i]==CTYPE_LEXS) {
            sdrini.nchL6++;
        }
    }
    return 0;
}
/* check initial value ---------------------------------------------------------
* checking value in sdrini struct
* args   : sdrini_t *ini    I   sdrini struct
* return : int                  0:okay -1:error
*-----------------------------------------------------------------------------*/
extern int chk_initvalue(sdrini_t *ini)
{
    int ret;

    /* checking frequency input */
    if ((ini->f_sf[0]<=0||ini->f_sf[0]>100e6) ||
        (ini->f_if[0]<0 ||ini->f_if[0]>100e6)) {
            SDRPRINTF("error: wrong freq. input sf1: %.0f if1: %.0f\n",
                ini->f_sf[0],ini->f_if[0]);
            return -1;
    }

    /* checking frequency input */
    if(ini->useif2||ini->fend==FEND_STEREO) {
        if ((ini->f_sf[1]<=0||ini->f_sf[1]>100e6) ||
            (ini->f_if[1]<0 ||ini->f_if[1]>100e6)) {
                SDRPRINTF("error: wrong freq. input sf2: %.0f if2: %.0f\n",
                    ini->f_sf[1],ini->f_if[1]);
                return -1;
        }
    }

    /* checking port number input */
    if ((ini->rtcmport<0||ini->rtcmport>32767) ||
        (ini->lexport<0||ini->lexport>32767)) {
            SDRPRINTF("error: wrong rtcm port rtcm:%d lex:%d\n",
                ini->rtcmport,ini->lexport);
            return -1;
    }

    /* checking filepath */
    if (ini->fend==FEND_FILE   ||ini->fend==FEND_FSTEREO||
        ini->fend==FEND_FGN3SV2||ini->fend==FEND_FGN3SV2||
        ini->fend==FEND_FRTLSDR||ini->fend==FEND_FBLADERF) {
        if (ini->useif1&&((ret=GetFileAttributes(ini->file1))<0)){
            SDRPRINTF("error: file1 doesn't exist: %s\n",ini->file1);
            return -1;
        }
        if (ini->useif2&&((ret=GetFileAttributes(ini->file2))<0)){
            SDRPRINTF("error: file2 doesn't exist: %s\n",ini->file2);
            return -1;
        }
        if ((!ini->useif1)&&(!ini->useif2)) {
            SDRPRINTF("error: file1 or file2 are not selected\n");
            return -1;
        }
    }

    /* checking rinex directory */
    if (ini->rinex) {
        if ((ret=GetFileAttributes(ini->rinexpath))<0) {
            SDRPRINTF("error: rinex output directory doesn't exist: %s\n",
                ini->rinexpath);
            return -1;
        }
    }

    return 0;
}
/* initialize mutex and event --------------------------------------------------
* create mutex and event handles
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern void openhandles(void)
{
    /* mutexes */
    initmlock(hbuffmtx);
    initmlock(hreadmtx);
    initmlock(hfftmtx);
    initmlock(hpltmtx);
    initmlock(hobsmtx);
    initmlock(hlexmtx);

    /* events */
    initevent(hlexeve);
}
/* close mutex and event -------------------------------------------------------
* close mutex and event handles
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern void closehandles(void)
{
    /* mutexes */
    delmlock(hbuffmtx);
    delmlock(hreadmtx);
    delmlock(hfftmtx);
    delmlock(hpltmtx);
    delmlock(hobsmtx);
    delmlock(hlexmtx);

    /* events */
    delevent(hlexeve);

#ifdef WIN32
    hbuffmtx=NULL;
    hreadmtx=NULL;
    hfftmtx=NULL;
    hpltmtx=NULL;
    hobsmtx=NULL;
    hlexmtx=NULL;
    hlexeve=NULL;
#endif
}
/* initialization plot struct --------------------------------------------------
* set value to plot struct
* args   : sdrplt_t *acq    I/0 plot struct for acquisition
*          sdrplt_t *trk    I/0 plot struct for tracking
*          sdrch_t  *sdr    I   sdr channel struct
* return : int                  0:okay -1:error
*-----------------------------------------------------------------------------*/
extern int initpltstruct(sdrplt_t *acq, sdrplt_t *trk, sdrch_t *sdr)
{
    double scale=1.0;

    /* acquisition */
    if (sdrini.pltacq) {
        setsdrplotprm(acq,PLT_SURFZ,sdr->acq.nfreq,sdr->nsamp,3,OFF,1,
            PLT_H,PLT_W,PLT_MH,PLT_MW,sdr->no);
        if (initsdrplot(acq)<0) return -1;
        settitle(acq,sdr->satstr);
        setlabel(acq,"Frequency (Hz)","Code Offset (sample)");
    }
    /* tracking */
    if (sdrini.plttrk) {
        setsdrplotprm(trk,PLT_XY,1+2*sdr->trk.corrn,0,0,ON,0.001,
            PLT_H,PLT_W,PLT_MH,PLT_MW,sdr->no);
        if(initsdrplot(trk)<0) return -1;
        settitle(trk,sdr->satstr);
        setlabel(trk,"Code Offset (sample)","Correlation Output");
        
        switch (sdrini.fend) {
            case FEND_GN3SV2:
            case FEND_GN3SV3:
            case FEND_FGN3SV2:
            case FEND_FGN3SV3:
                scale=1.5; break;
            case FEND_BLADERF:
            case FEND_FBLADERF:
                scale=5.0; break;
            case FEND_RTLSDR:
            case FEND_FRTLSDR:
                scale=3.5; break;
        }
        setyrange(trk,0,sdr->trk.loop*sdr->nsamp/4000*scale);
    }

    if (sdrini.fend==FEND_FILE||sdrini.fend==FEND_FSTEREO||
        sdrini.fend==FEND_FGN3SV2||sdrini.fend==FEND_FGN3SV2||
        sdrini.fend==FEND_FRTLSDR||sdrini.fend==FEND_FBLADERF) {
        trk->pltms=PLT_MS_FILE;
    } else {
        trk->pltms=PLT_MS;
    }
    return 0;
}
/* termination plot struct -----------------------------------------------------
* termination plot struct
* args   : sdrplt_t *acq    I/0 plot struct for acquisition
*          sdrplt_t *trk    I/0 plot struct for tracking
* return : none
*-----------------------------------------------------------------------------*/
extern void quitpltstruct(sdrplt_t *acq, sdrplt_t *trk)
{
    if (sdrini.pltacq)
        quitsdrplot(acq);

    if (sdrini.plttrk)
        quitsdrplot(trk);
}
/* initialize acquisition struct -----------------------------------------------
* set value to acquisition struct
* args   : int sys          I   system type (SYS_GPS...)
*          int ctype        I   code type (CTYPE_L1CA...)
*          int prn          I   PRN
*          sdracq_t *acq    I/0 acquisition struct
* return : none
*-----------------------------------------------------------------------------*/
extern void initacqstruct(int sys, int ctype, int prn, sdracq_t *acq)
{
    if (ctype==CTYPE_L1CA) acq->intg=ACQINTG_L1CA;
    if (ctype==CTYPE_G1)   acq->intg=ACQINTG_G1;
    if (ctype==CTYPE_E1B)  acq->intg=ACQINTG_E1B;
    if (ctype==CTYPE_B1I)  acq->intg=ACQINTG_B1I;
    if (ctype==CTYPE_L1SAIF||ctype==CTYPE_L1SBAS) acq->intg=ACQINTG_SBAS;

    acq->hband=ACQHBAND;
    acq->step=ACQSTEP;
    acq->nfreq=2*(ACQHBAND/ACQSTEP)+1;
}
/* initialize tracking parameter struct ----------------------------------------
* set value to tracking parameter struct
* args   : sdrtrk_t *trk    I/0 tracking struct
* return : none
*-----------------------------------------------------------------------------*/
extern void inittrkprmstruct(sdrtrk_t *trk)
{
    /* set tracking parameter */
    trk->prm1.dllb=sdrini.trkdllb[0];
    trk->prm1.pllb=sdrini.trkpllb[0];
    trk->prm1.fllb=sdrini.trkfllb[0];
    trk->prm2.dllb=sdrini.trkdllb[1];
    trk->prm2.pllb=sdrini.trkpllb[1];
    trk->prm2.fllb=sdrini.trkfllb[1];

    /* calculation loop filter parameters (before nav frame synchronization) */
    trk->prm1.dllw2=(trk->prm1.dllb/0.53)*(trk->prm1.dllb/0.53);
    trk->prm1.dllaw=1.414*(trk->prm1.dllb/0.53);
    trk->prm1.pllw2=(trk->prm1.pllb/0.53)*(trk->prm1.pllb/0.53);
    trk->prm1.pllaw=1.414*(trk->prm1.pllb/0.53);
    trk->prm1.fllw =trk->prm1.fllb/0.25;
    
    /* calculation loop filter parameters (after nav frame synchronization) */
    trk->prm2.dllw2=(trk->prm2.dllb/0.53)*(trk->prm2.dllb/0.53);
    trk->prm2.dllaw=1.414*(trk->prm2.dllb/0.53);
    trk->prm2.pllw2=(trk->prm2.pllb/0.53)*(trk->prm2.pllb/0.53);
    trk->prm2.pllaw=1.414*(trk->prm2.pllb/0.53);
    trk->prm2.fllw =trk->prm2.fllb/0.25;
}
/* initialize tracking struct --------------------------------------------------
* set value to tracking struct
* args   : int    sat       I   satellite number
*          int    ctype     I   code type (CTYPE_L1CA...)
*          double ctime     I   code period (s)
*          sdrtrk_t *trk    I/0 tracking struct
* return : int                  0:okay -1:error
*-----------------------------------------------------------------------------*/
extern int inittrkstruct(int sat, int ctype, double ctime, sdrtrk_t *trk)
{
    int i,prn;
    int ctimems=(int)(ctime*1000);
    int sys=satsys(sat,&prn);

    /* set tracking parameter */
    inittrkprmstruct(trk);

    /* correlation point */
    trk->corrn=sdrini.trkcorrn;
    trk->corrp=(int *)malloc(sizeof(int)*trk->corrn);
    for (i=0;i<trk->corrn;i++) {
        trk->corrp[i]=sdrini.trkcorrd*(i+1);
        if (trk->corrp[i]==sdrini.trkcorrp){
            trk->ne=2*(i+1)-1; /* Early */
            trk->nl=2*(i+1);   /* Late */
        }
    }
    /* correlation point for plot */
    (trk->corrx=(double *)calloc(2*trk->corrn+1,sizeof(double)));
    for (i=1;i<=trk->corrn;i++) {
        trk->corrx[2*i-1]=-sdrini.trkcorrd*i;
        trk->corrx[2*i  ]= sdrini.trkcorrd*i;
    }

    trk->II     =(double*)calloc(1+2*trk->corrn,sizeof(double));
    trk->QQ     =(double*)calloc(1+2*trk->corrn,sizeof(double));
    trk->oldI   =(double*)calloc(1+2*trk->corrn,sizeof(double));
    trk->oldQ   =(double*)calloc(1+2*trk->corrn,sizeof(double));
    trk->sumI   =(double*)calloc(1+2*trk->corrn,sizeof(double));
    trk->sumQ   =(double*)calloc(1+2*trk->corrn,sizeof(double));
    trk->oldsumI=(double*)calloc(1+2*trk->corrn,sizeof(double));
    trk->oldsumQ=(double*)calloc(1+2*trk->corrn,sizeof(double));

    if (ctype==CTYPE_L1CA)   trk->loop=LOOP_L1CA;
    if (ctype==CTYPE_G1)     trk->loop=LOOP_G1;
    if (ctype==CTYPE_E1B)    trk->loop=LOOP_E1B;
    if (ctype==CTYPE_L1SAIF) trk->loop=LOOP_SBAS;
    if (ctype==CTYPE_L1SBAS) trk->loop=LOOP_SBAS;
    if (ctype==CTYPE_B1I&&prn>5 ) trk->loop=LOOP_B1I;
    if (ctype==CTYPE_B1I&&prn<=5) trk->loop=LOOP_B1IG;
    
    /* for LEX */
    if (sys==SYS_QZS&&ctype==CTYPE_L1CA&&sdrini.nchL6) trk->loop=LOOP_LEX;
    
    /* loop interval (ms) */
    trk->loopms=trk->loop*ctimems;

    if (!trk->II||!trk->QQ||!trk->oldI||!trk->oldQ||!trk->sumI||!trk->sumQ||
        !trk->oldsumI||!trk->oldsumQ) {
        SDRPRINTF("error: inittrkstruct memory allocation\n");
        return -1;
    }
    return 0;
}
/* initialize navigation struct ------------------------------------------------
* set value to navigation struct
* args   : int sys          I   system type (SYS_GPS...)
*          int ctype        I   code type (CTYPE_L1CA...)
*          int prn          I   PRN (or SV) number
*          sdrnav_t *nav    I/0 navigation struct
* return : int                  0:okay -1:error
*-----------------------------------------------------------------------------*/
extern int initnavstruct(int sys, int ctype, int prn, sdrnav_t *nav)
{
    int i;
    int pre_l1ca[8]= { 1,-1,-1,-1, 1,-1, 1, 1}; /* L1CA preamble*/
    int pre_e1b[10]= { 1,-1, 1,-1,-1, 1, 1, 1, 1, 1}; /* E1B preamble */
    int pre_g1[30]=  {-1,-1,-1,-1,-1, 1, 1, 1,-1,-1,
                       1,-1,-1,-1, 1,-1, 1,-1, 1, 1,
                       1, 1,-1, 1, 1,-1, 1,-1,-1, 1}; /* G1 preamble */
    int pre_b1i[11]= {-1,-1,-1, 1, 1, 1,-1, 1, 1,-1, 1}; /* B1I preamble */
    int pre_sbs[24]= { 1,-1, 1,-1, 1, 1,-1,-1,-1, 1,
                       1,-1,-1, 1,-1, 1,-1,-1, 1, 1,
                       1 -1,-1, 1}; /* SBAS L1/QZS L1SAIF preamble */

    int poly[2]={V27POLYA,V27POLYB};

    nav->ctype=ctype;
    nav->sdreph.ctype=ctype;
    nav->sdreph.prn=prn;
    nav->sdreph.eph.iodc=-1;

    /* GPS/QZS L1CA */
    if (ctype==CTYPE_L1CA) {
        nav->rate=NAVRATE_L1CA;
        nav->flen=NAVFLEN_L1CA;
        nav->addflen=NAVADDFLEN_L1CA;
        nav->prelen=NAVPRELEN_L1CA;
        nav->sdreph.cntth=NAVEPHCNT_L1CA;
        nav->update=(int)(nav->flen*nav->rate);
        memcpy(nav->prebits,pre_l1ca,sizeof(int)*nav->prelen);

        /* overlay code (all 1) */
        nav->ocode=(short *)calloc(nav->rate,sizeof(short));
        for (i=0;i<nav->rate;i++) nav->ocode[i]=1;
    }
    /* SBAS/QZS L1SAIF */
    if (ctype==CTYPE_L1SAIF||ctype==CTYPE_L1SBAS) {
        nav->rate=NAVRATE_SBAS;
        nav->flen=NAVFLEN_SBAS;
        nav->addflen=NAVADDFLEN_SBAS;
        nav->prelen=NAVPRELEN_SBAS;
        nav->sdreph.cntth=NAVEPHCNT_SBAS;
        nav->update=(int)(nav->flen/3*nav->rate);
        memcpy(nav->prebits,pre_sbs,sizeof(int)*nav->prelen);

        /* create fec */
        if((nav->fec=create_viterbi27_port(NAVFLEN_SBAS/2))==NULL) {
            SDRPRINTF("error: create_viterbi27 failed\n");
            return -1;
        }
        /* set polynomial */
        set_viterbi27_polynomial_port(poly);

        /* overlay code (all 1) */
        nav->ocode=(short *)calloc(nav->rate,sizeof(short));
        for (i=0;i<nav->rate;i++) nav->ocode[i]=1;
    }
    /* GLONASS G1 */
    if (ctype==CTYPE_G1) {
        nav->rate=NAVRATE_G1;
        nav->flen=NAVFLEN_G1;
        nav->addflen=NAVADDFLEN_G1;
        nav->prelen=NAVPRELEN_G1;
        nav->sdreph.cntth=NAVEPHCNT_G1;
        nav->update=(int)(nav->flen*nav->rate);
        memcpy(nav->prebits,pre_g1,sizeof(int)*nav->prelen);
        nav->sdreph.geph.frq=prn; /* glonass frequency number */

        /* overlay code (all 1) */
        nav->ocode=(short *)calloc(nav->rate,sizeof(short));
        for (i=0;i<nav->rate;i++) nav->ocode[i]=1;
    }
    /* Galileo E1B */
    if (ctype==CTYPE_E1B) {
        nav->rate=NAVRATE_E1B;
        nav->flen=NAVFLEN_E1B;
        nav->addflen=NAVADDFLEN_E1B;
        nav->prelen=NAVPRELEN_E1B;
        nav->sdreph.cntth=NAVEPHCNT_E1B;
        nav->update=(int)(nav->flen*nav->rate);
        memcpy(nav->prebits,pre_e1b,sizeof(int)*nav->prelen);

        /* create fec */
        if((nav->fec=create_viterbi27_port(120))==NULL) {
            SDRPRINTF("error: create_viterbi27 failed\n");
            return -1;
        }
        /* set polynomial */
        set_viterbi27_polynomial_port(poly);

        /* overlay code (all 1) */
        nav->ocode=(short *)calloc(nav->rate,sizeof(short));
        for (i=0;i<nav->rate;i++) nav->ocode[i]=1;
    }
    /* BeiDou B1I */
    if (ctype==CTYPE_B1I) {
        /* MEO/IGSO (D1 NAV) */
        if (prn>5) {
            nav->rate=NAVRATE_B1I;
            nav->flen=NAVFLEN_B1I;
            nav->addflen=NAVADDFLEN_B1I;
            nav->prelen=NAVPRELEN_B1I;
            nav->sdreph.cntth=NAVEPHCNT_B1I;
            nav->update=(int)(nav->flen*nav->rate);
            memcpy(nav->prebits,pre_b1i,sizeof(int)*nav->prelen);
            
            /* secondary code generation */
            nav->ocode=gencode(-1,CTYPE_NH20,NULL,NULL);

        /* GEO (D2 NAV) */
        } else {
            nav->rate=NAVRATE_B1IG;
            nav->flen=NAVFLEN_B1IG;
            nav->addflen=NAVADDFLEN_B1IG;
            nav->prelen=NAVPRELEN_B1IG;
            nav->sdreph.cntth=NAVEPHCNT_B1IG;
            nav->update=(int)(nav->flen*nav->rate);
            memcpy(nav->prebits,pre_b1i,sizeof(int)*nav->prelen);

            /* overlay code (all 1) */
            nav->ocode=(short *)calloc(nav->rate,sizeof(short));
            for (i=0;i<nav->rate;i++) nav->ocode[i]=1;
        }
    }

    if (!(nav->bitsync= (int *)calloc(nav->rate,sizeof(int))) || 
        !(nav->fbits=   (int *)calloc(nav->flen+nav->addflen,sizeof(int))) ||
        !(nav->fbitsdec=(int *)calloc(nav->flen+nav->addflen,sizeof(int)))) {
            SDRPRINTF("error: initnavstruct memory alocation\n");
            return -1;
    }
    return 0;
}
/* initialize sdr channel struct -----------------------------------------------
* set value to sdr channel struct
* args   : int    chno      I   channel number (1,2,...)
*          int    sys       I   system type (SYS_***)
*          int    prn       I   PRN number
*          int    ctype     I   code type (CTYPE_***)
*          int    dtype     I   data type (DTYPEI or DTYPEIQ)
*          int    ftype     I   front end type (FTYPE1 or FTYPE2)
*          double f_cf      I   center (carrier) frequency (Hz)
*          double f_sf      I   sampling frequency (Hz)
*          double f_if      I   intermidiate frequency (Hz)
*          sdrch_t *sdr     I/0 sdr channel struct
* return : int                  0:okay -1:error
*-----------------------------------------------------------------------------*/
extern int initsdrch(int chno, int sys, int prn, int ctype, int dtype,
                     int ftype, double f_cf, double f_sf, double f_if,
                     sdrch_t *sdr)
{
    int i;
    short *rcode;

    sdr->no=chno;
    sdr->sys=sys;
    sdr->prn=prn;
    sdr->sat=satno(sys,prn);
    sdr->ctype=ctype;
    sdr->dtype=dtype;
    sdr->ftype=ftype;
    sdr->f_sf=f_sf;
    sdr->f_if=f_if;
    sdr->ti=1/f_sf;
    
    /* code generation */
    if (!(sdr->code=gencode(prn,ctype,&sdr->clen,&sdr->crate))) {
        SDRPRINTF("error: gencode\n"); return -1;
    }
    sdr->ci=sdr->ti*sdr->crate;
    sdr->ctime=sdr->clen/sdr->crate;
    sdr->nsamp=(int)(f_sf*sdr->ctime);
    sdr->nsampchip=(int)(sdr->nsamp/sdr->clen);
    satno2id(sdr->sat,sdr->satstr);

    /* set carrier frequency */
    if (ctype==CTYPE_G1) {
        sprintf(sdr->satstr,"R%d",prn); /* frequency number instead of PRN */
        sdr->f_cf=FREQ1_GLO+DFRQ1_GLO*prn; /* FDMA */
        sdr->foffset=DFRQ1_GLO*prn; /* FDMA */
    } else if (sdrini.fend==FEND_FRTLSDR) {
        sdr->foffset=f_cf*sdrini.rtlsdrppmerr*1e-6;
    } else {
        sdr->f_cf=f_cf; /* carrier frequency */
        sdr->foffset=0.0; /* frequency offset */
    }

    /* for BeiDou B1I */
    if (ctype==CTYPE_B1I) sdr->nsampchip*=2; /* for BOC code */

    /* acqisition struct */
    initacqstruct(sys,ctype,prn,&sdr->acq);
    sdr->acq.nfft=2*sdr->nsamp;//calcfftnum(2*sdr->nsamp,0);

    /* memory allocation */
    if (!(sdr->acq.freq=(double*)malloc(sizeof(double)*sdr->acq.nfreq))) {
        SDRPRINTF("error: initsdrch memory alocation\n"); return -1;
    }

    /* doppler search frequency */
    for (i=0;i<sdr->acq.nfreq;i++)
        sdr->acq.freq[i]=sdr->f_if+((i-(sdr->acq.nfreq-1)/2)*sdr->acq.step)
                            +sdr->foffset;

    /* tracking struct */
    if (inittrkstruct(sdr->sat,ctype,sdr->ctime,&sdr->trk)<0) return -1;

    /* navigation struct */
    if (initnavstruct(sys,ctype,prn,&sdr->nav)<0) {
        return -1;
    }
    /* memory allocation */
    if (!(rcode=(short *)sdrmalloc(sizeof(short)*sdr->acq.nfft)) || 
        !(sdr->xcode=cpxmalloc(sdr->acq.nfft))) {
            SDRPRINTF("error: initsdrch memory alocation\n"); return -1;
    }
    /* other code generation */
    for (i=0;i<sdr->acq.nfft;i++) rcode[i]=0; /* zero padding */
    rescode(sdr->code,sdr->clen,0,0,sdr->ci,sdr->nsamp,rcode); /* resampling */
    cpxcpx(rcode,NULL,1.0,sdr->acq.nfft,sdr->xcode); /* FFT for acquisition */
    cpxfft(NULL,sdr->xcode,sdr->acq.nfft);

    sdrfree(rcode);
    return 0;
}
/* free sdr channel struct -----------------------------------------------------
* free memory in sdr channel struct
* args   : sdrch_t *sdr     I/0 sdr channel struct
* return : none 
*-----------------------------------------------------------------------------*/
extern void freesdrch(sdrch_t *sdr)
{
    free(sdr->code);
    cpxfree(sdr->xcode);
    free(sdr->nav.fbits);
    free(sdr->nav.fbitsdec);
    free(sdr->nav.bitsync);
    free(sdr->trk.II);
    free(sdr->trk.QQ);
    free(sdr->trk.oldI);
    free(sdr->trk.oldQ);
    free(sdr->trk.sumI);
    free(sdr->trk.sumQ);
    free(sdr->trk.oldsumI);
    free(sdr->trk.oldsumQ);
    free(sdr->trk.corrp);
    free(sdr->acq.freq);

    if (sdr->nav.fec!=NULL)
        delete_viterbi27_port(sdr->nav.fec);

    if (sdr->nav.ocode!=NULL)
        free(sdr->nav.ocode);
}
