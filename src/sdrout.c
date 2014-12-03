/*------------------------------------------------------------------------------
* sdrout.c : output observation data functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

#ifdef WIN32
static int errsock(void) {return WSAGetLastError();}
#define socklen_t int
#else
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define INVALID_SOCKET     -1
#define SOCKET_ERROR       -1
#define closesocket        close

static int errsock(void) {return errno;}

#endif
/* set rinex option struct -----------------------------------------------------
* set value to rinex option struct (rtklib)
* args   : rnxopt_t *opt    I/O rinex option struct
* return : none
*-----------------------------------------------------------------------------*/
extern void createrinexopt(rnxopt_t *opt)
{
    int i;

    /* rinex setting */
    opt->rnxver=3.02;
    opt->navsys =SYS_ALL;
    strcpy(opt->prog,"GNSS-SDRLIB v1.1");
    strcpy(opt->rec[0],"GNSS-SDRLIB");
    strcpy(opt->rec[1],"GNSS-SDRLIB");
    strcpy(opt->rec[2],"1.1");

    /* signal type (L1 only) */
    for (i=0;i<6;i++) {
        opt->nobs[i]=4;
        strcpy(opt->tobs[i][0],"C1C");
        strcpy(opt->tobs[i][1],"L1C");
        strcpy(opt->tobs[i][2],"D1C");
        strcpy(opt->tobs[i][3],"S1C");
    }

    for (i=0;i<MAXSAT;i++) opt->exsats[i]=0;
}
/* convert sedobs to obsd struct -----------------------------------------------
* convert sdrobs struct to obsd struct(rtklib) for rinex/rtcm outputs
* args   : sdrobs_t *sdrobs I   rinex observation file name
*          int    ns        I   number of observed satellite
*          obsd_t *out      O   obsd struct(rtklib)
* return : none
*-----------------------------------------------------------------------------*/
extern void sdrobs2obsd(sdrobs_t *sdrobs, int ns, obsd_t *out)
{
    int i;
    for (i=0;i<ns;i++) {

        /* set observation time */
        out[i].time=gpst2time(sdrobs->week,sdrobs->tow);
        out[i].rcv=1;
        out[i].sat=satno(sdrobs[i].sys,sdrobs[i].prn);
        out[i].P[0]=sdrobs[i].P;
        out[i].L[0]=sdrobs[i].L;
        out[i].D[0]=(float)sdrobs[i].D;
        out[i].SNR[0]=(unsigned char)(sdrobs[i].S*4.0+0.5);

        /* signal type */
        out[i].code[0]=CODE_L1C; /* L1C/A,G1C/A,E1C (GPS,GLO,GAL,QZS,SBS) */
    }
}
/* create rinex observation data file ------------------------------------------
* create rinex observation data file
* args   : char   *file     I   rinex observation file name
*          rnxopt_t *opt    I   rinex option struct
* return : int                  status 0:okay -1:can't create file 
*-----------------------------------------------------------------------------*/
extern int createrinexobs(char *file, rnxopt_t *opt)
{
    FILE *fd;
    time_t timer;
    struct tm *utc;
    nav_t nav={0};

    /* UTC time */
    timer=time(NULL);
    utc=gmtime(&timer);
    sprintf(file,"%s/sdr_%04d%02d%02d%02d%02d%02d.obs",sdrini.rinexpath,
        utc->tm_year+1900,utc->tm_mon+1,utc->tm_mday,
        utc->tm_hour,utc->tm_min,utc->tm_sec);

    /* write rinex header */
    if ((fd=fopen(file,"w"))==NULL) {
        SDRPRINTF("error: rinex obs can't be created %s",file); return -1;
    }
    outrnxobsh(fd,opt,&nav);
    fclose(fd);
    return 0;
}
/* write rinex observation data ------------------------------------------------
* write observation data to file in rinex format
* args   : char   *file     I   rinex observation file name
*          rnxopt_t *opt    I   rinex option struct
*          obsd_t *obsd     I   observation data struct
*          int    ns        I   number of observed satellite
* return : int                  status 0:okay -1:can't write file 
*-----------------------------------------------------------------------------*/
extern int writerinexobs(char *file, rnxopt_t *opt, obsd_t *obsd, int ns)
{
    FILE *fd;

    /* write rinex body */
    if ((fd=fopen(file,"a"))==NULL) {
        SDRPRINTF("error: rinex obs can't be written %s",file); return -1;
    }
    outrnxobsb(fd,opt,obsd,ns,0);
    fclose(fd);

    return 0;
}
/* create rinex navigation data file -------------------------------------------
* create rinex navigation data file
* args   : char   *file     I   rinex navigation file name
*          rnxopt_t *opt    I   rinex option struct
* return : int                  status 0:okay -1:can't create file 
*-----------------------------------------------------------------------------*/
extern int createrinexnav(char *file, rnxopt_t *opt)
{
    FILE *fd;
    time_t timer;
    struct tm *utc;
    nav_t nav={0};

    /* UTC time */
    timer=time(NULL);
    utc=gmtime(&timer);
    sprintf(file,"%s/sdr_%04d%02d%02d%02d%02d%02d.nav",sdrini.rinexpath,
        utc->tm_year+1900,utc->tm_mon+1,utc->tm_mday,
        utc->tm_hour,utc->tm_min,utc->tm_sec);

    /* write rinex header */
    if ((fd=fopen(file,"w"))==NULL) {
        SDRPRINTF("error: rinex nav can't be created %s",file); return -1;
    }
    outrnxnavh(fd,opt,&nav);
    fclose(fd);
    return 0;
}
/* write rinex navigation data -------------------------------------------------
* write navigation data to file in rinex format
* args   : char   *file     I   rinex navigation file name
*          rnxopt_t *opt    I   rinex option struct
*          eph_t  *eph      I   ephemeris data struct
*          geph_t *geph     I   glonass ephemeris data struct
* return : int                  status 0:okay -1:can't write file 
*-----------------------------------------------------------------------------*/
extern int writerinexnav(char *file, rnxopt_t *opt, sdreph_t *sdreph)
{
    FILE *fd;

    /* write rinex body */
    if ((fd=fopen(file,"a"))==NULL) {
        SDRPRINTF("error: rinex nav can't be written %s",file); 
        return -1;
    }
    
    /* GLONASS ephemeris */
    if (sdreph->ctype==CTYPE_G1)
        outrnxgnavb(fd,opt,&sdreph->geph);
    else /* other GNSS */
        outrnxnavb(fd,opt,&sdreph->eph);

    SDRPRINTF("prn=%d rinex output navigation data\n",sdreph->prn);   
    fclose(fd);
    return 0;
}
/* socket functions----- -------------------------------------------------------
* initialize and cleanup socket (for windows)
*-----------------------------------------------------------------------------*/
int socketstartup(void)
{
#ifdef WIN32
    WSADATA data;
    if (WSAStartup(MAKEWORD(2,0),&data)!=0) {
        SDRPRINTF("error: tcp/ip WSAStartup() failed\n");
        return -1;
    }
#endif
    return 0;
}
void socketcleanup(void)
{
#ifdef WIN32
    WSACleanup();
#endif
}
/* tcp/ip server theread -------------------------------------------------------
* create tcp/ip server thread
* args   : void   *arg      I   sdr socket struct
* return : none
*-----------------------------------------------------------------------------*/
#ifdef WIN32
static void tcpsvrthread(void * arg) 
#else
static void *tcpsvrthread(void * arg) 
#endif
{
    sdrsoc_t *soc=(sdrsoc_t*)arg;
    struct sockaddr_in srcAddr,dstAddr;
    socklen_t dstAddrSize=sizeof(dstAddr);
    int yes=1;

    /* socket startup (for windows) */
    if (socketstartup()!=0) return THRETVAL;

    /* create socket */
    if ((soc->s_soc=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET) {
        SDRPRINTF("error: tcp/ip socket failed with %d\n",errsock());
        socketcleanup();
        return THRETVAL;
    }
    /* reuse port */
    setsockopt(soc->s_soc,SOL_SOCKET,SO_REUSEADDR,
        (const char*)&yes,sizeof(yes));

    /* sockaddr_in struct */
    srcAddr.sin_port=htons(soc->port);
    srcAddr.sin_family=AF_INET;
    srcAddr.sin_addr.s_addr=htonl(INADDR_ANY);

    /* bind to the local address */
    if ((bind(soc->s_soc,(struct sockaddr *)&srcAddr,
            sizeof(srcAddr)))==SOCKET_ERROR) {
        SDRPRINTF("error: tcp/ip bind failed with %d soc=%d\n",
            errsock(),(int)soc->s_soc);
        
        socketcleanup();
        return THRETVAL;
    }

    /* listen */
    if ((listen(soc->s_soc,SOMAXCONN))==SOCKET_ERROR) {
        SDRPRINTF("error: tcp/ip listen failed with %d\n",errsock());
        socketcleanup();
        return THRETVAL;
    }

    SDRPRINTF("Waiting for connection ...\n");
    while (1) {
        /* accept */
        if ((soc->c_soc=accept(soc->s_soc,
            (struct sockaddr *)&dstAddr,&dstAddrSize))==INVALID_SOCKET) {
            return THRETVAL;
        }
        SDRPRINTF("Connected from %s!\n", inet_ntoa(dstAddr.sin_addr));
        soc->flag=ON;
    }
    return THRETVAL;
}
/* start tcp server ------------------------------------------------------------
* create tcp/ip server thread
* args   : sdrsoc_t *soc    I   sdr socket struct
* return : none
*-----------------------------------------------------------------------------*/
extern void tcpsvrstart(sdrsoc_t *soc)
{
    cratethread(soc->hsoc,tcpsvrthread,soc);
}
/* stop tcp server -------------------------------------------------------------
* close tcp/ip sockets
* args   : sdrsoc_t *soc    I   sdr socket struct
* return : none
*-----------------------------------------------------------------------------*/
extern void tcpsvrclose(sdrsoc_t *soc)
{
    if (soc->s_soc!=0) closesocket(soc->s_soc);
    if (soc->c_soc!=0) closesocket(soc->c_soc);
    if (soc->flag==ON) socketcleanup();
}
/* send navigation data via tcp/ip ---------------------------------------------
* generate rtcm msm message and send via tcp/ip
* args   : eph_t  *eph      I   ephemeris data struct
*          sdrsoc_t *soc    I   sdr socket struct
* return : none
*-----------------------------------------------------------------------------*/
extern void sendrtcmnav(sdreph_t *sdreph, sdrsoc_t *soc)
{
    int sys,prn;
    rtcm_t rtcm={0};
    init_rtcm(&rtcm);

    switch (sdreph->ctype) {
    /* GPS/QZSS L1CA navigation data */
    case CTYPE_L1CA:
        rtcm.ephsat=sdreph->eph.sat;
        rtcm.nav.eph[rtcm.ephsat-1]=sdreph->eph;
        sys=satsys(sdreph->eph.sat,NULL);
        if (sys==SYS_GPS)       gen_rtcm3(&rtcm,1019,0); /* rtcm generation */
        else if (sys==SYS_QZS)  gen_rtcm3(&rtcm,1044,0); /* rtcm generation */
        break;
    /* Galileo E1B (INAV) navigation data */
    case CTYPE_E1B:
        rtcm.ephsat=sdreph->eph.sat;
        rtcm.nav.eph[rtcm.ephsat-1]=sdreph->eph;
        gen_rtcm3(&rtcm,1045,0); /* rtcm generation */
        break;
    /* GLONASS G1 navigation data */
    case CTYPE_G1:
        satsys(sdreph->geph.sat,&prn);
        rtcm.ephsat=sdreph->geph.sat;
        rtcm.nav.geph[prn-1]=sdreph->geph;
        gen_rtcm3(&rtcm,1020,0); /* rtcm generation */
        break;
    /* BeiDou B1I navigation data (note: using original rtcm format) */
    case CTYPE_B1I:
        rtcm.ephsat=sdreph->eph.sat;
        rtcm.nav.eph[rtcm.ephsat-1]=sdreph->eph;
        gen_rtcm3(&rtcm,1047,0); /* rtcm generation */
        break;
    }
    /* tcp send */
    if (send(soc->c_soc,(char*)rtcm.buff,rtcm.nbyte,0)==SOCKET_ERROR) {
        soc->flag=OFF;
    } else {
        SDRPRINTF("prn=%d rtcm output navigation data\n",sdreph->prn);
    }
}
/* send observation data via tcp/ip --------------------------------------------
* generate rtcm msm message and send via tcp/ip
* args   : obsd_t *obsd     I   observation data struct
*          sdrsoc_t *soc    I   sdr socket struct
*          int    n         I   number of observed satellite
* return : none
*-----------------------------------------------------------------------------*/
extern void sendrtcmobs(obsd_t *obsd, sdrsoc_t *soc, int nsat)
{
    rtcm_t rtcm={0};
    init_rtcm(&rtcm);

    /* observation */
    rtcm.time=obsd[0].time;
    rtcm.obs.n=nsat;
    rtcm.obs.data=obsd;
    
    /* GPS rtcm msm */
    gen_rtcm3(&rtcm,1077,1);
    if (send(soc->c_soc,(char*)rtcm.buff,rtcm.nbyte,0)==SOCKET_ERROR) {
        soc->flag=OFF;
    }
    /* QZSS rtcm msm */
    gen_rtcm3(&rtcm,1117,1);
    if (send(soc->c_soc,(char*)rtcm.buff,rtcm.nbyte,0)==SOCKET_ERROR) {
        soc->flag=OFF;
    }
    /* Galileo rtcm msm */
    gen_rtcm3(&rtcm,1097,1);
    if (send(soc->c_soc,(char*)rtcm.buff,rtcm.nbyte,0)==SOCKET_ERROR) {
        soc->flag=OFF;
    }
    /* GLONASS rtcm msm generation */
    gen_rtcm3(&rtcm,1087,1);
    if (send(soc->c_soc,(char*)rtcm.buff,rtcm.nbyte,0)==SOCKET_ERROR) {
        soc->flag=OFF;
    }
    /* BeiDou rtcm msm generation */
    gen_rtcm3(&rtcm,1127,0);
    if (send(soc->c_soc,(char*)rtcm.buff,rtcm.nbyte,0)==SOCKET_ERROR) {
        soc->flag=OFF;
    }
}
/* send sbas message -----------------------------------------------------------
* send sbas message via tcp/ip
* args   : sdrsbas_t *sbas  I   sdr sbas struct
*          sdrsoc_t *soc    I   sdr socket struct
* return : none
*-----------------------------------------------------------------------------*/
extern void sendsbas(sdrsbas_t *sbas, sdrsoc_t *soc)
{
    if (send(soc->c_soc,(char*)sbas->novatelmsg,LENSBASNOV,0)==SOCKET_ERROR) {
        soc->flag=OFF;
    }
}
/* write log header to file ----------------------------------------------------
* write tracking log header to file
* args   : FILE     *fp     I   file pointer
*          sdrtrk_t *trk    I   sdr tracking struct
* return : none
*-----------------------------------------------------------------------------*/
void writelog_header(FILE *fp, sdrtrk_t *trk)
{
    int i,ind[64]={0},n=trk->corrn;
    fprintf(fp,"Cnt,Tow,IP,QP,sumI,sumQ");

    /* generating correlation points indices */
    for (i=0;i<n;i++) {
        ind[i    ]=2*(n-i)-1;
        ind[n+i+1]=2*(i+1);
    }
    /* output correlation result in order */
    for (i=0;i<2*n+1;i++) fprintf(fp,",I(%d)",(int)trk->corrx[ind[i]]);
    
    fprintf(fp,",Code Freq,Code Err,Code NCO");
    fprintf(fp,",Carr Freq,Carr Err,Carr NCO");
    fprintf(fp,",Freq Err,Carrier Phase");
    fprintf(fp,",FlagSync,FlagSyncf,FlagTOW,FlagDec,FlagLoopFilter,swsync");
    fprintf(fp,"\n");
}
/* write log to file -----------------------------------------------------------
* write tracking log to file
* args   : FILE     *fp     I   file pointer
*          sdrtrk_t *trk    I   sdr tracking struct
*          sdrnav_t *nav    I   sdr navigation struct
* return : none
*-----------------------------------------------------------------------------*/
extern void writelog(FILE *fp, sdrtrk_t *trk,sdrnav_t *nav)
{
    int i,ind[64]={0},n=trk->corrn;
    /* generating correlation points indices */
    for (i=0;i<n;i++) {
        ind[i    ]=2*(n-i)-1;
        ind[n+i+1]=2*(i+1);
    }

#ifdef WIN32
    fprintf(fp,"%llu,%f,%f,%f",
        trk->cntout[0],trk->tow[0],trk->II[0],trk->QQ[0]);
#else
    fprintf(fp,"%"PRIu64",%f,%f,%f",
        trk->cntout[0],trk->tow[0],trk->II[0],trk->QQ[0]);
#endif
    fprintf(fp,",%f,%f",trk->sumI[0],trk->sumQ[0]);
    for (i=0;i<2*n+1;i++) fprintf(fp,",%f",trk->II[ind[i]]);
    fprintf(fp,",%f,%f,%f",trk->codefreq,trk->codeErr,trk->codeNco);
    fprintf(fp,",%f,%f,%f",trk->carrfreq,trk->carrErr,trk->carrNco);
    fprintf(fp,",%f,%f",trk->freqErr,trk->L[0]);
    fprintf(fp,",%d,%d,%d,%d,%d,%d",
        nav->flagsync,nav->flagsyncf,nav->flagtow,nav->flagdec,
        trk->flagloopfilter,nav->swsync);
    fprintf(fp,"\n");
}
/* create log file -------------------------------------------------------------
* create tracking log file
* args   : char     *filename I sdr sbas struct
*          sdrtrk_t *trk    I   sdr tracking struct
* return : FILE *fp             file pointer
*-----------------------------------------------------------------------------*/
extern FILE* createlog(char *filename, sdrtrk_t *trk)
{
    FILE *fp;
    if ((fp=fopen(filename,"w"))==NULL) return NULL;
    writelog_header(fp,trk);
    return fp;
}
/* close log file --------------------------------------------------------------
* close tracking log file
* args   : FILE     *fp     I   file pointer
* return : none
*-----------------------------------------------------------------------------*/
extern void closelog(FILE *fp)
{
    fclose(fp);
}
