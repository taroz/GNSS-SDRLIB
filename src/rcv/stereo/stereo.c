/*------------------------------------------------------------------------------
* stereo.c : NSL STEREO functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
* Copyright (C) 2012 Nottingham Scientific Limited
*-----------------------------------------------------------------------------*/
#include "sdr.h"

#ifdef STEREOV26
#define STEREOBUFF STEREO_globalDataBuffer
#else
#define STEREOBUFF sdrstat.buff
#endif

/* global variables ----------------------------------------------------------*/
char fx2lp[MAX_FILENAME_LEN];
char fpga[MAX_FILENAME_LEN];
char fpgareg[MAX_FILENAME_LEN];
char max2769[MAX_FILENAME_LEN];
char max2112[MAX_FILENAME_LEN];
char synth[MAX_FILENAME_LEN];
char adc[MAX_FILENAME_LEN];

/* stereo initialization -------------------------------------------------------
* search front end and initialization
* args   : none
* return : int                  status 0:okay -1:failure
*-----------------------------------------------------------------------------*/
extern int stereo_init(void) 
{
    int ret;
    
    ret=STEREO_InitLibrary();
    if (ret!=0) {
        SDRPRINTF("error: initialising Stereo driver\n"); return -1;
    }

    if (!STEREO_IsConnected()) {
        SDRPRINTF("error: STEREO does not appear to be connected\n"); return -1;
    }
    
    /* initiarize stereo */
    if (stereo_initconf()<0) return -1;

    return 0;
}
/* stop front-end --------------------------------------------------------------
* stop grabber of front end
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern void stereo_quit(void) 
{
#ifdef STEREOV26
    STEREO_DisconnectEndPoint(L1_EP);
#else
    STEREO_GrabStop(); /* stop and clean the grabber */
    STEREO_GrabClean();
#endif    
    STEREO_QuitLibrary();
}
/* stereo initialization of file oprions ---------------------------------------
* stereo initialization of file oprions
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern int stereo_initoptions(void) 
{
    strcpy(fx2lp,STEREO_FW);
    strcpy(fpga,STEREO_FPGA);
    strcpy(synth,STEREO_SYNTH);
    strcpy(adc,STEREO_ADC);
#ifdef STEREOV26
    strcpy(fpgareg,STEREO_FPGAREG);
#endif

    /* select max2769 configuration file */
    switch ((int)sdrini.f_cf[0]) {
        case (int)FREQ1:
            strcpy(max2769,STEREO_MAX2769_L1); break;
        case (int)FREQ1_CMP:
            strcpy(max2769,STEREO_MAX2769_B1); break;
        case (int)FREQ1_GLO:
            strcpy(max2769,STEREO_MAX2769_G1); break;
        default:
            SDRPRINTF("error: stereo_initoptions f_cf[0]= %f",sdrini.f_cf[0]);
            return -1;
    }
    
    /* select max2112 configuration file */
    switch ((int)sdrini.f_cf[1]) {
        case (int)FREQ1:
            strcpy(max2112,STEREO_MAX2112_L1); break;
        case (int)FREQ1_CMP:
            strcpy(max2112,STEREO_MAX2112_B1); break;
        case (int)FREQ1_GLO:
            strcpy(max2112,STEREO_MAX2112_G1); break;
        case (int)FREQ2:
            strcpy(max2112,STEREO_MAX2112_L2); break;
        case (int)FREQ5:
            strcpy(max2112,STEREO_MAX2112_L5); break;
        case (int)FREQ6:
            strcpy(max2112,STEREO_MAX2112_L6); break;
        case (int)FREQ2_CMP:
            strcpy(max2112,STEREO_MAX2112_B2); break;
        case (int)FREQ2_GLO:
            strcpy(max2112,STEREO_MAX2112_G2); break;
        default:
            SDRPRINTF("error: stereo_initoptions f_cf[1]= %f",sdrini.f_cf[1]);
            return -1;
    }
    return 0;
}
/* stereo configuration function -----------------------------------------------
* load configuration file and setting
* args   : none
* return : int                  status 0:okay -1:failure
*-----------------------------------------------------------------------------*/
extern int stereo_initconf(void) 
{
    char cmd[1024];
    char cdcmd[]="cd ./frontend/stereo";
    
#ifdef WIN32
    SDRPRINTF("STEREO configuration start...\n");

    /* initialize configuration file */
    if (stereo_initoptions()<0) return -1;

    /* load firmware and fpga if they are not loaded */
    if (!STEREO_IsConfigured()) {
        sprintf(cmd,"%s & stereo_app -w %s -g %s -s %s -a %s > nul",
            cdcmd,fx2lp,fpga,synth,adc);
        system(cmd);
    }

    /* max2769/max2112 configuration */
    sprintf(cmd,"%s & stereo_app -s %s -1 %s -2 %s > nul 2>&1",
        cdcmd,synth,max2769,max2112);
    system(cmd);

    /* change sampling frequency */
    if ((int)sdrini.f_sf[0]!=26e6) {
        sprintf(cmd,"%s & stereo_app -sf %f > nul 2>&1",cdcmd,
            sdrini.f_sf[0]/1000000);
        system(cmd);
    }
#else
    SDRPRINTF("STEREO configuration is not supported in Linux\n");
#endif
    
    SDRPRINTF("STEREO configuration is finished!\n");
    return 0;
}
/* initialization of data expansion --------------------------------------------
* initialization of data expansion
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
static char lut1[256]={0};
static char lut2[256][2]={{0}};
void stereo_exp_init(void)
{
    char BASELUT1[4]={-3,-1,+1,+3}; /* 2bits */
    char BASELUT2[8]={+1,+3,+5,+7,-7,-5,-3,-1}; /* 3bits */
    int r; 
    unsigned char tmp;

    for (r=0;r<256;r++) {
        tmp=r;
        lut1[r]   =BASELUT1[((tmp>>6)&0x03)];
        lut2[r][0]=BASELUT2[((tmp>>3)&0x07)];
        lut2[r][1]=BASELUT2[((tmp   )&0x07)];
    }
}
/* data expansion to binary (stereo)  ------------------------------------------
* get current data buffer from memory buffer
* args   : char   *buf      I   memory buffer
*          int    n         I   number of grab data
*          int    dtype     I   data type (DTYPEI or DTYPEIQ)
*          char   *expbuff  O   extracted data buffer
* return : none
*-----------------------------------------------------------------------------*/
extern void stereo_exp(const unsigned char *buf, int n, int dtype, char *expbuf)
{
    int i;

    if (!lut1[0]||!lut2[0][0]) stereo_exp_init();

    switch (dtype) {
        /* front end 1 (max2769) */
    case DTYPEI:
        for (i=0;i<n;i++) {
            expbuf[i]=lut1[buf[i]];
        }
        break;
        /* front end 2 (max2112) */
    case DTYPEIQ:
        for (i=0;i<n;i++) {
            expbuf[2*i  ]=lut2[buf[i]][0];
            expbuf[2*i+1]=lut2[buf[i]][1];
        }
        break;
    }
}
/* get current data buffer (stereo) --------------------------------------------
* get current data buffer from memory buffer
* args   : uint64_t buffloc I   buffer location
*          int    n         I   number of grab data
*          int    dtype     I   data type (DTYPEI or DTYPEIQ)
*          char   *expbuff  O   extracted data buffer
* return : none
*-----------------------------------------------------------------------------*/
extern void stereo_getbuff(uint64_t buffloc, int n, int dtype, char *expbuf)
{
    uint64_t membuffloc=buffloc%(MEMBUFFLEN*STEREO_DATABUFF_SIZE);
    int nout=(int)((membuffloc+n)-(MEMBUFFLEN*STEREO_DATABUFF_SIZE));

    mlock(hbuffmtx);

    if (nout>0) {
        stereo_exp(&STEREOBUFF[membuffloc],n-nout,dtype,expbuf);
        stereo_exp(&STEREOBUFF[0],nout,dtype,&expbuf[dtype*(n-nout)]);
    } else {
        stereo_exp(&STEREOBUFF[membuffloc],n,dtype,expbuf);
    }

    unmlock(hbuffmtx);
}
/* push data to memory buffer --------------------------------------------------
* push data to memory buffer from STEREO front end
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern void stereo_pushtomembuf(void) 
{
    mlock(hbuffmtx);
#ifndef STEREOV26
    memcpy(&sdrstat.buff[(sdrstat.buffcnt%MEMBUFFLEN)*STEREO_DATABUFF_SIZE],
        STEREO_dataBuffer,STEREO_DATABUFF_SIZE);
#endif
    unmlock(hbuffmtx);

    mlock(hreadmtx);
    sdrstat.buffcnt++;
    unmlock(hreadmtx);
}
/* push data to memory buffer --------------------------------------------------
* push data to memory buffer from STEREO binary IF file
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern void fstereo_pushtomembuf(void) 
{
    size_t nread;

    mlock(hbuffmtx);

    nread=fread(&STEREOBUFF[(sdrstat.buffcnt%MEMBUFFLEN)*STEREO_DATABUFF_SIZE],
        1,STEREO_DATABUFF_SIZE,sdrini.fp1);

    unmlock(hbuffmtx);

    if (nread<STEREO_DATABUFF_SIZE) {
        sdrstat.stopflag=ON;
        SDRPRINTF("end of file!\n");
    }

    mlock(hreadmtx);
    sdrstat.buffcnt++;
    unmlock(hreadmtx);
}
