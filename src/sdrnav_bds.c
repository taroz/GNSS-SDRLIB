/*------------------------------------------------------------------------------
* sdrnav_bds.c : BeiDou navigation data
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

#define P2_66       1.355252715606881E-20 /* 2^-66 */
#define SC2RAD_CMP  3.1415926535898 /* PI in BeiDou ICD */

/* decode BeiDou navigation data (D1 subframe 1) -------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d1sf1(const uint8_t *buff, sdreph_t *eph)
{
    int oldiodc=eph->eph.iodc;
    double tow_bds,toc_bds;

    tow_bds        =getbitu2(buff, 18, 8,30,12)+6.0;
    eph->eph.svh   =getbitu( buff, 42, 1);
    eph->eph.iodc  =getbitu( buff, 43, 5);
    eph->eph.sva   =getbitu( buff, 48, 4);
    eph->eph.week  =getbitu( buff, 60,13); /* week in BDT */
    toc_bds        =getbitu2(buff, 73, 9, 90, 8)*8;
    eph->eph.tgd[0]=getbits( buff, 98,10)*0.1*1E-9;
    eph->eph.tgd[1]=getbits2(buff,108, 4,120, 6)*0.1*1E-9;
    eph->eph.f2    =getbits( buff,214,11)*P2_66;
    eph->eph.f0    =getbits2(buff,225, 7,240,17)*P2_33;
    eph->eph.f1    =getbits2(buff,257, 5,270,17)*P2_50;
    eph->eph.iode  =getbitu( buff,287, 5);
    
    eph->eph.toc   =bdt2time(eph->eph.week,toc_bds);
    eph->eph.ttr   =bdt2time(eph->eph.week,tow_bds);
    
    /* GPS time of week (BDT=>GPST) */
    eph->tow_gpst  =time2gpst(bdt2gpst(eph->eph.ttr),&eph->week_gpst);

    /* ephemeris update flag */
    if (oldiodc-eph->eph.iodc!=0) eph->update=ON;
    
    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D1 subframe 2) -------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d1sf2(const uint8_t *buff, sdreph_t *eph)
{
    double sqrtA,tow_bds;

    tow_bds        =getbitu2(buff, 18, 8,30,12)+6.0;
    eph->eph.deln  =getbits2(buff, 42,10, 60, 6)*P2_43*SC2RAD_CMP;
    eph->eph.cuc   =getbits2(buff, 66,16, 90, 2)*P2_31;
    eph->eph.M0    =getbits2(buff, 92,20,120,12)*P2_31*SC2RAD_CMP;
    eph->eph.e     =getbitu2(buff,132,10,150,22)*P2_33;
    eph->eph.cus   =getbits( buff,180,18)*P2_31;
    eph->eph.crc   =getbits2(buff,198, 4,210,14)*P2_6;
    eph->eph.crs   =getbits2(buff,224, 8,240,10)*P2_6;
    sqrtA          =getbitu2(buff,250,12,270,20)*P2_19;
    eph->toe1      =getbitu( buff,290, 2);
    eph->eph.A     =sqrtA*sqrtA;

    if (eph->eph.week!=0) {
        /* GPS time of week (BDT=>GPST) */
        eph->tow_gpst=time2gpst(bdt2gpst(bdt2time(eph->eph.week,tow_bds)),
                                &eph->week_gpst);
    }

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D1 subframe 3) -------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d1sf3(const uint8_t *buff, sdreph_t *eph)
{
    double tow_bds;

    tow_bds        =getbitu2(buff, 18, 8, 30,12)+6.0;
    eph->toe2      =getbitu2(buff, 42,10, 60, 5);
    eph->eph.i0    =getbits2(buff, 65,17, 90,15)*P2_31*SC2RAD_CMP;
    eph->eph.cic   =getbits2(buff,105, 7,120,11)*P2_31;
    eph->eph.OMGd  =getbits2(buff,131,11,150,13)*P2_43*SC2RAD_CMP;
    eph->eph.cis   =getbits2(buff,163, 9,180, 9)*P2_31;
    eph->eph.idot  =getbits2(buff,189,13,210, 1)*P2_43*SC2RAD_CMP;
    eph->eph.OMG0  =getbits2(buff,211,21,240,11)*P2_31*SC2RAD_CMP;
    eph->eph.omg   =getbits2(buff,251,11,270,21)*P2_31*SC2RAD_CMP;

    if (eph->eph.week!=0) {
        /* GPS time of week (BDT=>GPST) */
        eph->tow_gpst=time2gpst(bdt2gpst(bdt2time(eph->eph.week,tow_bds)),
                                &eph->week_gpst);
    }
    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D1 subframe 4) -------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d1sf4(const uint8_t *buff, sdreph_t *eph)
{
    double tow_bds;
    tow_bds         =getbitu2(buff, 18, 8,30,12)+6.0;

    if (eph->eph.week!=0) {
        /* GPS time of week (BDT=>GPST) */
        eph->tow_gpst=time2gpst(bdt2gpst(bdt2time(eph->eph.week,tow_bds)),
                                &eph->week_gpst);
    }
}
/* decode BeiDou navigation data (D1 subframe 5) -------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d1sf5(const uint8_t *buff, sdreph_t *eph)
{
    double tow_bds;
    tow_bds         =getbitu2(buff, 18, 8,30,12)+6.0;

    if (eph->eph.week!=0) {
        /* GPS time of week (BDT=>GPST) */
        eph->tow_gpst=time2gpst(bdt2gpst(bdt2time(eph->eph.week,tow_bds)),
                                &eph->week_gpst);
    }
}
/* merge ephmeris data ---------------------------------------------------------
* merge separated ephmeris data to ephemeris struct
* args   : sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void merge_d1(sdreph_t *eph)
{
    /* time of ephemeris (sec of BDT week) */
    eph->eph.toes  =merge_two_u(eph->toe1,eph->toe2,15)*8;
    eph->eph.toe   =bdt2time(eph->eph.week,eph->eph.toes);
}
/* decode navigation data (BeiDou B1I D1 subframe) -----------------------------
*
* args   : uint8_t *buff    I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : int                  subframe ID
*-----------------------------------------------------------------------------*/
extern int decode_flame_d1nav(const uint8_t *buff, sdreph_t *eph)
{
    int id=getbitu(buff,15,3); /* subframe ID */

    switch (id) {
    case 1: decode_d1sf1(buff,eph); break;
    case 2: decode_d1sf2(buff,eph); break;
    case 3: decode_d1sf3(buff,eph); break;
    case 4: decode_d1sf4(buff,eph); break;
    case 5: decode_d1sf5(buff,eph); break;
    }

    /* merge ephemeris */
    if (eph->cnt==eph->cntth) merge_d1(eph);

    return id;
}
/* decode BeiDou navigation data (D2 subframe 1 page 1) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p1(const uint8_t *buff, sdreph_t *eph)
{
    int oldiodc=eph->eph.iodc;
    double tow_bds,toc_bds;

    tow_bds        =getbitu2(buff, 18, 8, 30,12)+0.6;
    eph->eph.svh   =getbitu( buff, 46, 1);
    eph->eph.iodc  =getbitu( buff, 47, 5);
    eph->eph.sva   =getbitu( buff, 60, 4);
    eph->eph.week  =getbitu( buff, 64,13); /* week in BDT */
    toc_bds        =getbitu2(buff, 77, 5, 90,12)*8;
    eph->eph.tgd[0]=getbits( buff,102,10)*0.1*1E-9;
    eph->eph.tgd[1]=getbits( buff,120,10)*0.1*1E-9;

    eph->eph.toc   =bdt2time(eph->eph.week,toc_bds);
    eph->eph.ttr   =bdt2time(eph->eph.week,tow_bds);

    /* GPS time of week (BDT=>GPST) */
    eph->tow_gpst  =time2gpst(bdt2gpst(eph->eph.ttr),&eph->week_gpst);
    
    /* ephemeris update flag */
    if (oldiodc-eph->eph.iodc!=0) eph->update=ON;

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 2) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p2(const uint8_t *buff, sdreph_t *eph)
{
    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 3) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p3(const uint8_t *buff, sdreph_t *eph)
{
    eph->eph.f0    =getbits2(buff,100,12,120,12)*P2_33;
    eph->f1p3      =getbits( buff,132,4);

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 4) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p4(const uint8_t *buff, sdreph_t *eph)
{
    eph->f1p4      =getbitu2(buff, 46, 6, 60,12);
    eph->eph.f2    =getbits2(buff, 72,10, 90, 1)*P2_66;
    eph->eph.iode  =getbitu (buff, 91, 5);
    eph->eph.deln  =getbits (buff, 96,16)*P2_43*SC2RAD_CMP;
    eph->cucp4     =getbits (buff,120,14);

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 5) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p5(const uint8_t *buff, sdreph_t *eph)
{
    eph->cucp5     =getbitu( buff, 46, 4);
    eph->eph.M0    =getbits3(buff, 50, 2, 60,22, 90, 8)*P2_31*SC2RAD_CMP;
    eph->eph.cus   =getbits2(buff, 98,14,120, 4)*P2_31;
    eph->ep5       =getbits (buff,124,10);

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 6) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p6(const uint8_t *buff, sdreph_t *eph)
{
    double sqrtA;
    eph->ep6       =getbitu2(buff, 46, 6, 60,16);
    sqrtA          =getbitu3(buff, 76, 6, 90,22,120,4)*P2_19;
    eph->cicp6     =getbits (buff,124,10);
    eph->eph.A     =sqrtA*sqrtA;

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 7) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p7(const uint8_t *buff, sdreph_t *eph)
{
    eph->cicp7     =getbitu2(buff, 46, 6, 60, 2);
    eph->eph.cis   =getbits( buff, 62,18)*P2_31;
    eph->eph.toes  =getbitu2(buff, 80, 2, 90,15)*8; /* sec of BDT week */
    eph->i0p7      =getbits2(buff,105, 7,120,14);

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 8) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p8(const uint8_t *buff, sdreph_t *eph)
{
    eph->i0p8      =getbitu2(buff, 46, 6, 60, 5);
    eph->eph.crc   =getbits2(buff, 65,17, 90, 1)*P2_6;
    eph->eph.crs   =getbits( buff, 91,18)*P2_6;
    eph->OMGdp8    =getbits2(buff,109, 3,120,16);

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 9) ------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p9(const uint8_t *buff, sdreph_t *eph)
{
    eph->OMGdp9    =getbitu( buff, 46, 5);
    eph->eph.OMG0  =getbits3(buff, 51, 1, 60,22, 90, 9)*P2_31*SC2RAD_CMP;
    eph->omgp9     =getbits2(buff, 99,13,120,14);

    /* ephemeris counter */
    eph->cnt++;
}
/* decode BeiDou navigation data (D2 subframe 1 page 10) -----------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_d2sf1p10(const uint8_t *buff, sdreph_t *eph)
{
    eph->omgp10    =getbitu( buff, 46, 5);
    eph->eph.idot  =getbits2(buff,51, 1, 60,13)*P2_43*SC2RAD_CMP;

    /* ephemeris counter */
    eph->cnt++;
}
/* merge ephmeris data ---------------------------------------------------------
* merge separated ephmeris data to ephemeris struct
* args   : sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void merge_d2sf1(sdreph_t *eph)
{
    eph->eph.f1  =merge_two_s(eph->f1p3,eph->f1p4,18)*P2_50;
    eph->eph.cuc =merge_two_s(eph->cucp4,eph->cucp5,4)*P2_31;
    eph->eph.e   =merge_two_s(eph->ep5,eph->ep6,22)*P2_33;
    eph->eph.cic =merge_two_s(eph->cicp6,eph->cicp7,8)*P2_31;
    eph->eph.i0  =merge_two_s(eph->i0p7,eph->i0p8,11)*P2_31*SC2RAD_CMP;
    eph->eph.OMGd=merge_two_s(eph->OMGdp8,eph->OMGdp9,5)*P2_43*SC2RAD_CMP;
    eph->eph.omg =merge_two_s(eph->omgp9,eph->omgp10,5)*P2_31*SC2RAD_CMP;

    /* time of ephemeris (sec of BDT week) */
    eph->eph.toe =bdt2time(eph->eph.week,eph->eph.toes);
}
/* decode navigation data (BeiDou B1I D2 subframe1 page) -----------------------
*
* args   : uint8_t *buff    I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : int                  subframe ID
*-----------------------------------------------------------------------------*/
extern int decode_flame_d2nav(const uint8_t *buff, sdreph_t *eph)
{
    int id =getbitu(buff,15,3); /* subframe ID */
    int pgn=getbitu(buff,42,4); /* page number */

    /* decode subframe 1 */
    if (id==1) {
        switch (pgn) {
        case  1: decode_d2sf1p1( buff,eph); break;
        case  2: decode_d2sf1p2( buff,eph); break;
        case  3: decode_d2sf1p3( buff,eph); break;
        case  4: decode_d2sf1p4( buff,eph); break;
        case  5: decode_d2sf1p5( buff,eph); break;
        case  6: decode_d2sf1p6( buff,eph); break;
        case  7: decode_d2sf1p7( buff,eph); break;
        case  8: decode_d2sf1p8( buff,eph); break;
        case  9: decode_d2sf1p9( buff,eph); break;
        case 10: decode_d2sf1p10(buff,eph); break;
        }
        /* merge ephemeris */
        if (eph->cnt==eph->cntth) {
            merge_d2sf1(eph);
        }
    }
    return id;
}
/* BCH decoder -----------------------------------------------------------------
* BCH decoder for BeiDou D1/D2 navigation data
* args   : int     *bits    I   input encoded bits (15 bits, -1 or 1)
*          int     *decbits I   output decoded bits (15 bits, -1 or 1)
* return : none
* note   : see BeiDou SISICD V2.0 pp.13-14
*-----------------------------------------------------------------------------*/
void decodebch_bi1(int *bits, int *decbits)
{
    int i,bit,err,reg[4]={1,1,1,1};
    int errind[15]={14,13,10,12,6,9,4,11,0,5,7,8,1,3,2}; /* see Table 5.2 */
    uint8_t bin;

    /* copy input to output */
    for (i=0;i<15;i++) decbits[i]=bits[i];

    /* BCH decoding (Fig 5-4) */
    for (i=0;i<15;i++) {
        bit=reg[3];
        reg[3]=reg[2]; reg[2]=reg[1]; reg[1]=reg[0];
        reg[0]=bits[i]*bit;
        reg[1]*=bit;
    }
    /* get error index */
    bits2byte(reg,4,1,0,&bin);
    err=errind[getbitu(&bin,0,4)]; /* error index */
    
    /* error correction */
    if (err>0) decbits[err-1]*=-1;
}
/* decode BeiDou navigation data -----------------------------------------------
* decode Galileo E1B (I/NAV) navigation data and extract ephemeris
* args   : sdrnav_t *nav    I/O sdr navigation struct
* return : int                  word type
*-----------------------------------------------------------------------------*/
extern int decode_b1i(sdrnav_t *nav)
{
    int i,j,id=0,bits[300],bitsdec[300],bitsbch[30],bit1[15],bit2[15];
    uint8_t bin[38]; /* 300/8 byte */

    /* copy navigation bits (there are 300 bits in 1 subframe, bit is +1/-1) */
    for (i=0;i<nav->flen;i++) bits[i]=nav->polarity*nav->fbits[i];
    
    /* deinterleave and BCH decoding */
    for (i=0;i<10;i++) {
        if (i==0) {
            /* first 15 bits in word 1 are not interleaved */
            for (j=0;j<30;j++) bitsdec[j]=bits[j];
        } else {
            /* block deinterleaver */
            interleave(&bits[i*30],2,15,bitsbch);
            
            decodebch_bi1(&bitsbch[ 0],bit1); /* BCH decode of first 15 bits */
            decodebch_bi1(&bitsbch[15],bit2); /* BCH decode of last 15 bits */

            /* pack data bits */
            for (j=0;j<11;j++) {
                bitsdec[30*i+j+ 0]=bit1[j];
                bitsdec[30*i+j+11]=bit2[j];
            }
            /* pack parity bits */
            for (j=0;j<4;j++) {
                bitsdec[30*i+j+22]=bit1[11+j];
                bitsdec[30*i+j+26]=bit2[11+j];
            }
        }
    }
    /* convert to byte data */
    bits2byte(bitsdec,300,38,0,bin);

    /* decode navigation data */
    if (nav->sdreph.prn>5)
        id=decode_flame_d1nav(bin,&nav->sdreph); /* MEO/IGSO (D1 NAV) */
    else
        id=decode_flame_d2nav(bin,&nav->sdreph); /* GEO (D2 NAV) */
    
    return id;
}
