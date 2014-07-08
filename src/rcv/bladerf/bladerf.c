/*------------------------------------------------------------------------------
* bladerf.c : Nuand bladeRF functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
* Copyright (C) 2014 Nuand LLC
*-----------------------------------------------------------------------------*/
#include "sdr.h"

struct bladerf *bladerf; 
struct bladerf_stream *stream;
bladerf_module module;
void **buffers;
uint64_t count=0;

/* bladeRF stream callback  ----------------------------------------------------
* callback for receiving RF data
* see libbladeRF.h L854-L882
*-----------------------------------------------------------------------------*/
void *stream_callback(struct bladerf *dev, struct bladerf_stream *stream,
                      struct bladerf_metadata *metadata, void *samples,
                      size_t num_samples, void *user_data)
{
    int i,ind;
    void *rv;
    int16_t *sample=(int16_t *)samples ;

    /* buffer index */
    ind=(sdrstat.buffcnt%MEMBUFFLEN)*2*BLADERF_DATABUFF_SIZE;

    mlock(hbuffmtx);
    /* copy stream data to global buffer */
    for (i=0;i<2*BLADERF_DATABUFF_SIZE;i++)
        sdrstat.buff[ind+i]=(unsigned char)((sample[i]&0xfff));
    unmlock(hbuffmtx);

    mlock(hreadmtx);
    sdrstat.buffcnt++;
    unmlock(hreadmtx);

    /* stop stream callback */
    if (sdrstat.stopflag) {
        return NULL;
    } else {
        rv=buffers[count%16];
        count++;
        return rv;
    }
}
/* bladeRF initialization ------------------------------------------------------
* search front end and initialization
* args   : none
* return : int                  status 0:okay -1:failure
*-----------------------------------------------------------------------------*/
extern int bladerf_init(void) 
{
    int ret;
    char fpga[255];
    bladerf_fpga_size s;

    /* open bladeRF */
    ret=bladerf_open(&bladerf,NULL);
    if (ret<0) {
        SDRPRINTF("error: failed to open bladerf: %s\n",bladerf_strerror(ret));
        return -1;
    }

    /* check FPGA */
    ret=bladerf_is_fpga_configured(bladerf);
    if (ret<0) {
        SDRPRINTF("error: failed to config. FPGA: %s\n",bladerf_strerror(ret));
        bladerf_close(bladerf);
        return -1;
    } else if (ret==0) {
        bladerf_get_fpga_size(bladerf,&s);

        /* load FPGA */
        if (s==40) {
            if (getfullpath("./frontend/bladerf/hostedx40.rbf",fpga)<0)
                return -1;

            ret=bladerf_load_fpga(bladerf,fpga);
        } else if (s==115) {
            if (getfullpath("./frontend/bladerf/hostedx115.rbf",fpga)<0)
                return -1;
            
            ret=bladerf_load_fpga(bladerf,fpga);
        } else {
            SDRPRINTF("error: get_fpga_size: %s\n",bladerf_strerror(ret));
            bladerf_close(bladerf);
            return -1;
        }
        if (ret<0) {
            SDRPRINTF("error: failed to load FPGA: %s\n",bladerf_strerror(ret));
            bladerf_close(bladerf);
            return -1;
        }
    }

    /* set configuration */
    ret=bladerf_initconf();
    if (ret<0) {
        SDRPRINTF("error: failed to init. bladerf: %s\n",bladerf_strerror(ret));
        return -1;
    }
    return 0;
}
/* stop front-end --------------------------------------------------------------
* stop grabber of front end
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern void bladerf_quit(void) 
{
    bladerf_close(bladerf);
}
/* bladeRF configuration function ----------------------------------------------
* load configuration file and setting
* args   : none
* return : int                  status 0:okay -1:failure
*-----------------------------------------------------------------------------*/
extern int bladerf_initconf(void) 
{
    int ret;
    unsigned int actual,samplerate=(unsigned int)sdrini.f_sf[0];

    /* set direction(Rx/Tx) */
    module=BLADERF_MODULE_RX;

    /* set center frequency (currently only L1) */
    ret=bladerf_set_frequency(bladerf,module,(unsigned int)(FREQ1));
    if (ret<0) {
        SDRPRINTF("error: failed to set frequency: %s\n",bladerf_strerror(ret));
        bladerf_quit();
        return -1;
    }
    
    /* set bandwidth (half of sampling frequency) */
    ret=bladerf_set_bandwidth(bladerf,module,samplerate/2,&actual);
    if (ret<0) {
        SDRPRINTF("error: failed to set bandwidth: %s\n",bladerf_strerror(ret));
        bladerf_quit();
        return -1;
    }
    /* set sample rate */
    ret=bladerf_set_sample_rate(bladerf,module,samplerate,&actual);
    if (ret<0) {
        SDRPRINTF("error: failed to set samprate: %s\n",bladerf_strerror(ret));
        bladerf_quit();
        return -1;
    }

    /* initialize the stream */
    ret=bladerf_init_stream(&stream,bladerf,stream_callback,&buffers,
                    16,BLADERF_FORMAT_SC16_Q11,BLADERF_DATABUFF_SIZE,16,NULL);
    if (ret<0) {
        SDRPRINTF("error: failed to init. stream: %s\n",bladerf_strerror(ret));
        bladerf_quit();
        return -1;
    }
    return 0;
}
/* start grabber ---------------------------------------------------------------
* start grabber of front end
* args   : none
* return : int                  status 0:okay -1:failure
*-----------------------------------------------------------------------------*/
extern int bladerf_start(void) 
{
    int ret;
    
    /* enable RF module */
    ret=bladerf_enable_module(bladerf,module,true);
    if (ret<0) {
        SDRPRINTF("error: failed to enable module: %s\n",bladerf_strerror(ret));
        return -1;
    }

    /* start stream and stay there until we kill the stream */
    ret=bladerf_stream(stream,module);
    if (ret<0) {
        SDRPRINTF("error: stream error: %s\n", bladerf_strerror(ret));
        return -1;
    }

    return 0;
}
/* stop grabber ----------------------------------------------------------------
* stop grabber of front end
* args   : none
* return : int                  status 0:okay -1:failure
*-----------------------------------------------------------------------------*/
extern int bladerf_stop(void) 
{
    int ret;

    /* disable RF module */
    ret=bladerf_enable_module(bladerf,module,false);
    if (ret<0) {
        SDRPRINTF("error: failed to enable module: %s\n",bladerf_strerror(ret));
        return -1;
    }

    /* deinitialize stream */
    bladerf_deinit_stream(stream);

    return 0;
}
/* DC-offset calibration -------------------------------------------------------
* calibration DC offset and I/Q imbalance
* args   : double *buf      I   orignal RF data buffer
*          int    n         I   number of data buffer
*          int    dtype     I   data type (DTYPEI or DTYPEIQ)
*          char   *outbuf   O   output data buffer
* return : none
*-----------------------------------------------------------------------------*/
extern void calibration_dcoffset(double *inbuf, int n, int dtype, char *outbuf)
{
    int i;
    double dmeanI=0,dmeanQ=0;

    for (i=0;i<n;i++) {
        if (dtype==DTYPEI) {
            dmeanI+=inbuf[i];
        } else if (dtype==DTYPEIQ) {
            dmeanI+=inbuf[2*i  ];
            dmeanQ+=inbuf[2*i+1];
        }
    }
    dmeanI/=n; dmeanQ/=n;

    for (i=0;i<n;i++) {
        if (dtype==DTYPEI) {
            outbuf[i]=(char)(inbuf[i]-dmeanI);
        } else if (dtype==DTYPEIQ) {
            outbuf[2*i  ]=(char)(inbuf[2*i  ]-dmeanI);
            outbuf[2*i+1]=(char)(inbuf[2*i+1]-dmeanQ);
        }
    }
}
/* data expansion --------------------------------------------------------------
* get current data buffer from memory buffer
* args   : int16_t *buf     I   bladeRF raw buffer
*          int    n         I   number of grab data
*          char   *expbuf   O   extracted data buffer
* return : none
*-----------------------------------------------------------------------------*/
extern void bladerf_exp(unsigned char *buf, int n, char *expbuf)
{
    int i;
    double *dbuf;
    unsigned char *data=buf;

    dbuf=(double*)malloc(sizeof(double)*n);

    for (i=0;i<n/2;i++) {
        dbuf[2*i  ]=(double)(*(data+2*i  ));
        dbuf[2*i+1]=(double)(*(data+2*i+1));
    }
    calibration_dcoffset(dbuf,n/2,DTYPEIQ,expbuf);
    free(dbuf);
}
/* get current data buffer -----------------------------------------------------
* get current data buffer from memory buffer
* args   : uint64_t buffloc I   buffer location
*          int    n         I   number of grab data
*          char   *expbuf   O   extracted data buffer
* return : none
*-----------------------------------------------------------------------------*/
extern void bladerf_getbuff(uint64_t buffloc, int n, char *expbuf)
{
    uint64_t membuffloc=2*buffloc%(MEMBUFFLEN*2*BLADERF_DATABUFF_SIZE);
    int nout;
    n=2*n;
    nout=(int)((membuffloc+n)-(MEMBUFFLEN*2*BLADERF_DATABUFF_SIZE));

    mlock(hbuffmtx);
    if (nout>0) {
        bladerf_exp(&sdrstat.buff[membuffloc],n-nout,expbuf);
        bladerf_exp(&sdrstat.buff[0],nout,&expbuf[n-nout]);
    } else {
        bladerf_exp(&sdrstat.buff[membuffloc],n,expbuf);
    }
    unmlock(hbuffmtx);
}
/* push data to memory buffer --------------------------------------------------
* push data to memory buffer from BladeRF binary IF file
* args   : none
* return : none
*-----------------------------------------------------------------------------*/
extern void fbladerf_pushtomembuf(void) 
{
    size_t nread;
    uint16_t buff[BLADERF_DATABUFF_SIZE*2];
    int i,ind;

    mlock(hbuffmtx);

    nread=fread(buff,sizeof(uint16_t),2*BLADERF_DATABUFF_SIZE,sdrini.fp1);
    
    /* buffer index */
    ind=(sdrstat.buffcnt%MEMBUFFLEN)*2*BLADERF_DATABUFF_SIZE;

    for (i=0;i<nread;i++) {
        sdrstat.buff[ind+i]=(uint8_t)(buff[i]&0xfff);
    }

    unmlock(hbuffmtx);

    if (nread<2*BLADERF_DATABUFF_SIZE) {
        sdrstat.stopflag=ON;
        SDRPRINTF("end of file!\n");
    }

    mlock(hreadmtx);
    sdrstat.buffcnt++;
    unmlock(hreadmtx);
}
