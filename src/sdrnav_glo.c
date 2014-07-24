/*------------------------------------------------------------------------------
* sdrnav_glo.c : GLONASS navigation data
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

/* extract signed bits ---------------------------------------------------------
* extract unsigned/signed bits from byte data (for GLONASS version)
* args   : uint8_t *buff    I   byte data
*          int    pos       I   bit start position (bits)
*          int    len       I   bit length (bits)
* return : extracted unsigned/signed bits
*-----------------------------------------------------------------------------*/
int getbits_glo(const uint8_t *buff, int pos, int len)
{
    if (getbitu(buff,pos,1)) return -(int)getbitu(buff,pos+1,len-1);
    else                     return       getbitu(buff,pos+1,len-1);
}
/* decode GLONASS navigation data (string 1) -----------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_g1s1(const uint8_t *buff, sdreph_t *eph)
{
    eph->tk[0]      =getbitu(buff, 9, 5)-3; /* 3 hour bias in UTC-GPST */
    eph->tk[1]      =getbitu(buff,14, 6);
    eph->tk[2]      =getbitu(buff,20, 1)*30;
    eph->geph.vel[0]=getbits_glo(buff,21,24)*P2_20*1000; /* km to m */
    eph->geph.acc[0]=getbits_glo(buff,45, 5)*P2_30*1000; /* km/s to m/s */
    eph->geph.pos[0]=getbits_glo(buff,50,27)*P2_11*1000; /* km/s^2 to m/s^2 */

    /* ephemeris counter */
    eph->cnt++;
}
/* decode GLONASS navigation data (string 2) -----------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_g1s2(const uint8_t *buff, sdreph_t *eph)
{
    int oldiode=eph->geph.iode;
    
    eph->geph.svh   =getbitu(buff, 5, 1);
    eph->geph.iode  =getbitu(buff, 9, 7);
    eph->geph.vel[1]=getbits_glo(buff,21,24)*P2_20*1000; /* km to m */
    eph->geph.acc[1]=getbits_glo(buff,45, 5)*P2_30*1000; /* km/s to m/s */
    eph->geph.pos[1]=getbits_glo(buff,50,27)*P2_11*1000; /* km/s^2 to m/s^2 */

    /* ephemeris update flag */
    if (oldiode-eph->geph.iode!=0) eph->update=ON;

    /* ephemeris counter */
    eph->cnt++;
}
/* decode GLONASS navigation data (string 3) -----------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_g1s3(const uint8_t *buff, sdreph_t *eph)
{
    eph->geph.gamn  =getbits_glo(buff, 6,11)*P2_40;
    eph->geph.vel[2]=getbits_glo(buff,21,24)*P2_20*1000; /* km to m */
    eph->geph.acc[2]=getbits_glo(buff,45, 5)*P2_30*1000; /* km/s to m/s */
    eph->geph.pos[2]=getbits_glo(buff,50,27)*P2_11*1000; /* km/s^2 to m/s^2 */

    /* ephemeris counter */
    eph->cnt++;
}
/* decode GLONASS navigation data (string 4) -----------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_g1s4(const uint8_t *buff, sdreph_t *eph)
{
    eph->geph.taun  =getbits_glo(buff, 5,22)*P2_30;
    eph->geph.dtaun =getbits_glo(buff,27, 5)*P2_30;
    eph->geph.age   =getbitu(buff,32, 5);
    eph->geph.sva   =getbitu(buff,52, 4);
    eph->nt         =getbitu(buff,59,11);
    eph->prn        =getbitu(buff,70, 5);
    eph->geph.sat   =satno(SYS_GLO,eph->prn);

    /* ephemeris counter */
    eph->cnt++;
}
/* decode GLONASS navigation data (string 5) -----------------------------------
*
* args   : uint8_t  *buff   I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void decode_g1s5(const uint8_t *buff, sdreph_t *eph)
{
    eph->n4         =getbitu(buff,49,5);

    /* ephemeris counter */
    eph->cnt++;
}
/* convert glonass time to time  -----------------------------------------------
* convert glonass time in ephemeris to gtime_t struct (GPST)
* args   : int      nt      I   current day
*          int      n4      I   4 year interval
*          int      h       I   hour
*          int      m       I   minute
*          int      s       I   second
* return : gtime_t struct
* note   : Reference: GLONASS ICD A.3.1.3
*-----------------------------------------------------------------------------*/
gtime_t glot2time(int nt, int n4, int h, int m, int s)
{
    double ep[6];
    int j=0,year,mon,day=0,doy=0;
    int doys[]= {1,32,60,91,121,152,182,213,244,274,305,335}; /* day of year */
    int doysl[]={1,32,61,92,122,153,183,214,245,275,306,336}; /* leap year */
    
    ep[3]=h; ep[4]=m; ep[5]=s;

    if     (nt<= 366) {j=1; doy=nt;}
    else if(nt<= 731) {j=2; doy=nt-366+1;}
    else if(nt<=1096) {j=3; doy=nt-731+1;}
    else if(nt<=1461) {j=4; doy=nt-1096+1;}

    /* current year */
    year=1996+4*(n4-1)+(j-1);
    
    /* compute current month and day */
    for (mon=1;mon<12;mon++) {
        if (j==1) {
            if (doy<doysl[mon]) {
                day=doy-doysl[mon-1];
                break;
            }
        } else {
            if (doy<doys[ mon]) {
                day=doy-doys[mon-1];
                break;
            }
        }
    }
    ep[0]=year; ep[1]=mon; ep[2]=day;
    return utc2gpst(epoch2time(ep)); /* convert to gtime_t in GPST */
}
/* merge ephmeris data ---------------------------------------------------------
* merge separated ephmeris data to ephemeris struct
* args   : sdreph_t *eph    I/O sdr ephemeris structure
* return : none
*-----------------------------------------------------------------------------*/
void merge_g1(sdreph_t *eph)
{
    double ep[6]; 

    eph->geph.tof=glot2time(eph->nt,eph->n4,eph->tk[0],eph->tk[1],eph->tk[2]);
    
    /* compute current tow (tk is time of word 1) */
    eph->tow_gpst=time2gpst(eph->geph.tof,&eph->eph.week)+eph->s1cnt*2.0;
    eph->week_gpst=eph->eph.week;
    
    time2epoch(eph->geph.tof,ep);
    ep[3]=0;ep[4]=eph->geph.iode*15-60*3;ep[5]=0; /* 3 hour bias in UTC-GPST */
    eph->geph.toe=utc2gpst(epoch2time(ep)); /* time of ephemeris */
}
/* decode navigation data (GLONASS word) ---------------------------------------
*
* args   : uint8_t *buff    I   navigation data bits
*          sdreph_t *eph    I/O sdr ephemeris structure
* return : int                  string number (1-5)
*-----------------------------------------------------------------------------*/
extern int decode_flame_g1(const uint8_t *buff, sdreph_t *eph)
{
    int id =getbitu(buff,1,4); /* string number */

    switch (id) {
        case  1: decode_g1s1(buff,eph); eph->s1cnt=1; break;
        case  2: decode_g1s2(buff,eph); eph->s1cnt++; break;
        case  3: decode_g1s3(buff,eph); eph->s1cnt++; break;
        case  4: decode_g1s4(buff,eph); eph->s1cnt++; break;
        case  5: decode_g1s5(buff,eph); eph->s1cnt++; break;
        default: eph->s1cnt++; break;
    }
    /* merge ephemeris */
    if (eph->cnt==eph->cntth) merge_g1(eph);

    return id;
}
/* decode GLONASS navigation data ----------------------------------------------
* decode GLONASS navigation data and extract ephemeris
* args   : sdrnav_t *nav    I/O sdr navigation struct
* return : int                  string number (1-5)
*-----------------------------------------------------------------------------*/
extern int decode_g1(sdrnav_t *nav)
{
    int i,id=0,bits1[170],bits2[85];
    uint8_t bin[11]; /* 85/8 word bits */

    /* remove meandr from data */
    for (i=0;i<170;i++) {
        if (i%2==0)
            bits1[i]= nav->polarity*nav->fbits[i];
        else
            bits1[i]=-nav->polarity*nav->fbits[i];
    }
    for (i=0;i<84;i++) {
        bits2[i+1]=bits1[2*i]*bits1[2*(i+1)];
    }
    bits2[0] = -1;
    bits2byte(bits2,85,11,0,bin);

    /* decode navigation data */
    id=decode_flame_g1(bin,&nav->sdreph);

    if (id<1||id>15)
        SDRPRINTF("error: GLONASS word number sfn=%d\n",id);

    return id;
}
