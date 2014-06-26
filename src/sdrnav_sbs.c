/*------------------------------------------------------------------------------
* sdrnav_sbs.c : SBAS message
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

#define OEMSYNC1   0xAA        /* NovAtel message start sync code 1 */
#define OEMSYNC2   0x44        /* NovAtel message start sync code 2 */
#define OEMSYNC3   0x12        /* NovAtel message start sync code 3 */
#define OEMHLEN    28          /* NovAtel message header length (bytes) */
#define OEMSBASLEN 48          /* NovAtel sbas message length (bytes) */
#define ID_RAWSBASFRAME 973     /* NovAtel message id: oem6 raw sbas frame */

/* set bits --------------------------------------------------------------------
* set bits to byte data
* args   : uint8_t *p       I/O byte data
*          uint16/32_t u    I   data
* return : none
*-----------------------------------------------------------------------------*/
void setU2(uint8_t *p, uint16_t u)
{
    uint8_t pp[2];
    setbitu(pp,0,16,u);
    p[0]=pp[1]; p[1]=pp[0];
}
void setU4(uint8_t *p, uint32_t u)
{
    uint8_t pp[4];
    setbitu(pp,0,32,u);
    p[0]=pp[3]; p[1]=pp[2];
    p[2]=pp[1]; p[3]=pp[0];
}
/* generate NovAtel format SBAS message ----------------------------------------
* generate NovAtel format SBAS message to send RTKLIB
* args   : sdrsbas_t *sbas  I/O sdr sbas structure
* return : none
* not    : see OEM6 Firmware Reference Manual
*-----------------------------------------------------------------------------*/
void gen_novatel_sbasmsg(sdrsbas_t *sbas)
{
    int i;
    memset(sbas->novatelmsg,0,LENSBASNOV);

    /* header */
    sbas->novatelmsg[0]=OEMSYNC1; /* sync code 1 */
    sbas->novatelmsg[1]=OEMSYNC2; /* sync code 2 */
    sbas->novatelmsg[2]=OEMSYNC3; /* sync code 3 */
    setU2(&sbas->novatelmsg[4],ID_RAWSBASFRAME); /* message ID */
    setU2(&sbas->novatelmsg[8],OEMSBASLEN); /* message length */
    setU2(&sbas->novatelmsg[14],sbas->week); /* GPS week */
    setU4(&sbas->novatelmsg[16],(int)(sbas->tow*1000)); /* GPS tow */

    /* body */
    setU4(&sbas->novatelmsg[OEMHLEN+4],183); /* PRN */
    setU4(&sbas->novatelmsg[OEMHLEN+8],sbas->id); /* frame ID */
    /* message (29 bytes) */
    for (i=0;i<29;i++) sbas->novatelmsg[OEMHLEN+12+i]=sbas->msg[i];

    /* crc32 */
    setU4(&sbas->novatelmsg[OEMHLEN+48],crc32(sbas->novatelmsg,(OEMHLEN+48))); 
}
/* decode SBAS message (Message Type 12) ---------------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdrsbas_t *sbas  I/O sdr sbas structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_MT12(uint8_t *buff, sdrsbas_t *sbas)
{
    sbas->tow =getbitu(buff,107,20)+1.0; /* GPS tow */
    sbas->week=getbitu(buff,127,10)+1024; /* GPS week */
}
/* decode SBAS message ---------------------------------------------------------
*
* args   : uint8_t *buff    I   navigation data bits
*          sdrsbas_t *sbas  I/O sdr sbas structure
* return : int                  subframe ID
*-----------------------------------------------------------------------------*/
void decode_msg_sbas(uint8_t *buff, sdrsbas_t *sbas)
{
    /* sbas message type */
    sbas->id=getbitu(buff,8,6);

    /* currently only extruct time information */
    switch (sbas->id) {
    case 12: /* decode GPS tow and week*/
        decode_MT12(buff,sbas);
        break;
    default:
        sbas->tow+=1.0;
        break;
    }
}
/* decode SBAS navigation data -------------------------------------------------
* decode SBAS navigation data and extract message
* args   : sdrnav_t *nav    I/O sdr navigation struct
* return : int                  word type
*-----------------------------------------------------------------------------*/
extern int decode_l1sbas(sdrnav_t *nav)
{
    int i,crc,crcmsg,bits[250];
    uint8_t bin[29]={0},pbin[3];

    /* copy navigation bits (250 bits/sec) */
    for (i=0;i<250;i++) bits[i]=nav->polarity*nav->fbitsdec[i];
    
    bits2byte(&bits[0],226,29,1,bin);  /* body bits (right alignment for crc) */
    bits2byte(&bits[226],24,3,0,pbin); /* crc24 */

    /* compute and check crc24 */
    crc=crc24q(bin,29);
    crcmsg=getbitu(pbin,0,24);
    if (crc==crcmsg) {
    } else {
        SDRPRINTF("error: parity mismatch crc=%d msg=%d\n",crc,crcmsg);
    }

    /* decode sbas message */
    bits2byte(bits,250,32,0,nav->sbas.msg);
    decode_msg_sbas(nav->sbas.msg,&nav->sbas);

    /* tentative: get tow from other channel */
    if (sdrini.nch>1&&sdrch[sdrini.nch-2].nav.sdreph.week_gpst!=0) {
        nav->sbas.tow=sdrch[sdrini.nch-2].trk.tow[0];
        nav->sbas.week=sdrch[sdrini.nch-2].nav.sdreph.week_gpst;
    }

    /* generate NovAtel sbas message */
    if (nav->sbas.week!=0) {
        gen_novatel_sbasmsg(&nav->sbas);

        if (sdrini.sbas&&sdrout.soc_sbas.flag)
            sendsbas(&nav->sbas,&sdrout.soc_sbas);

        nav->sdreph.tow_gpst=nav->sbas.tow;
        nav->sdreph.week_gpst=nav->sbas.week;
    }

    return nav->sbas.id;
}
