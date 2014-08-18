/*------------------------------------------------------------------------------
* sdr.h : constants, types and function prototypes

* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#ifndef SDR_H
#define SDR_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>

/* SIMD (SSE2_ENABLE) */
#if defined(SSE2_ENABLE)
#include <emmintrin.h>
#include <tmmintrin.h>
#endif

/* SIMD (AVX_ENABLE/AVX2_ENABLE) */
#if defined(AVX_ENABLE)||defined(AVX2_ENABLE)
#include <immintrin.h>
#endif

/* for windows ---------------------------------------------------------------*/
#ifdef WIN32

#include <windows.h>
#include <process.h>
#include <shlwapi.h>
#include <shlobj.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"fec/libfec.a")
#pragma comment(lib,"fft/libfftw3f-3.lib")
#pragma comment(lib,"usb/libusb.lib")
#pragma comment(lib,"stereo/libnslstereo.a")
#pragma comment(lib,"bladerf/bladeRF.lib")
#pragma comment(lib,"rtlsdr/rtlsdr.lib")

#include "fec/fec.h"
#include "fft/fftw3.h"
#include "rtklib/rtklib.h"
#include "usb/lusb0_usb.h"
#include "stereo/stereo.h"
#include "gn3s/gn3s.h"
#include "bladerf/libbladeRF.h"
#include "rtlsdr/rtl-sdr.h"

#if defined(GUI)
#include "../gui/gnss-sdrgui/maindlg.h"
using namespace gnsssdrgui;
#endif

/* printf function */
#if defined(GUI)
#define SDRPRINTF(...) \
    do { \
    char str[1024]; \
    sprintf(str,__VA_ARGS__);  \
    maindlg^form=static_cast<maindlg^>(hform.Target); \
    String^ strstr = gcnew String(str); \
    form->mprintf(strstr); \
    } while (0)
#else
#define SDRPRINTF printf
#endif 

/* for linux -----------------------------------------------------------------*/
#else

#include <pthread.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <inttypes.h>

#include "fec.h"
#include "fftw3.h"
#include "rtklib.h"
#include "libusb-1.0/libusb.h"
#ifdef STEREO
#include "stereo.h"
#endif
#ifdef GN3S
#include "gn3s.h"
#endif
#ifdef BLADERF
#include "libbladeRF.h"
#endif
#ifdef RTLSDR
#include "rtl-sdr.h"
#endif

#define SDRPRINTF printf

#endif /* defined(WIN32) */

#ifdef __cplusplus
extern "C" {
#endif

/* constants -----------------------------------------------------------------*/
#define ROUND(x)      ((int)floor((x)+0.5)) /* round function */
#define PI            3.1415926535897932 /* pi */
#define DPI           (2.0*PI)         /* 2*pi */
#define D2R           (PI/180.0)       /* degree to radian */
#define R2D           (180.0/PI)       /* radian to degree */
#define CLIGHT        299792458.0      /* speed of light (m/s) */
#define ON            1                /* flag ON */
#define OFF           0                /* flag OFF */
#define MAXBITS       3000             /* maximum bit length */

/* front end setting */
#define FEND_STEREO   0                /* front end type: NSL STEREO */
#define FEND_GN3SV2   1                /* front end type: SiGe GN3S v2 */
#define FEND_GN3SV3   2                /* front end type: SiGe GN3S v3 */
#define FEND_RTLSDR   3                /* front end type: RTL-SDR */
#define FEND_BLADERF  4                /* front end type: Nuand BladeRF */
#define FEND_FSTEREO  5                /* front end type: STEREO binary file */
#define FEND_FGN3SV2  6                /* front end type: GN3Sv2 binary file */
#define FEND_FGN3SV3  7                /* front end type: GN3Sv3 binary file */
#define FEND_FRTLSDR  8                /* front end type: RTL-SDR binary file */
#define FEND_FBLADERF 9                /* front end type: BladeRF binary file */
#define FEND_FILE     10               /* front end type: IF file */
#define FTYPE1        1                /* front end number */
#define FTYPE2        2                /* front end number */
#define DTYPEI        1                /* sampling type: real */
#define DTYPEIQ       2                /* sampling type: real+imag */

#ifdef STEREOV26
#define STEREO_DATABUFF_SIZE STEREO_PKT_SIZE
#define MEMBUFFLEN    (STEREO_NUM_BLKS*32)
                                       /* number of temporary buffer */
#else
#define MEMBUFFLEN    5000             /* number of temporary buffer */
#endif

#define FILE_BUFFSIZE 65536            /* buffer size for post processing */

/* acquisition setting */
#define NFFTTHREAD    4                /* number of thread for executing FFT */
#define ACQINTG_L1CA  10               /* number of non-coherent integration */
#define ACQINTG_G1    10               /* number of non-coherent integration */
#define ACQINTG_E1B   4                /* number of non-coherent integration */
#define ACQINTG_B1I   10               /* number of non-coherent integration */
#define ACQINTG_SBAS  10               /* number of non-coherent integration */
#define ACQHBAND      7000             /* half width for doppler search (Hz) */
#define ACQSTEP       250              /* doppler search frequency step (Hz) */
#define ACQTH         2.5              /* acquisition threshold (peak ratio) */
#define ACQSLEEP      2000             /* acquisition process interval (ms) */

/* tracking setting */
#define LOOP_L1CA     10               /* loop interval */
#define LOOP_G1       10               /* loop interval */
#define LOOP_E1B      1                /* loop interval */
#define LOOP_B1I      10               /* loop interval */
#define LOOP_B1IG     2                /* loop interval */
#define LOOP_SBAS     2                /* loop interval */
#define LOOP_LEX      4                /* loop interval */

/* navigation parameter */
#define NAVSYNCTH       50             /* navigation frame synch. threshold */
/* GPS/QZSS L1CA */
#define NAVRATE_L1CA    20             /* length (multiples of ranging code) */
#define NAVFLEN_L1CA    300            /* navigation frame data (bits) */
#define NAVADDFLEN_L1CA 2              /* additional bits of frame (bits) */
#define NAVPRELEN_L1CA  8              /* preamble bits length (bits) */
#define NAVEPHCNT_L1CA  3              /* number of eph. contained frame */
/* L1 SBAS/QZSS L1SAIF */
#define NAVRATE_SBAS    2              /* length (multiples of ranging code) */
#define NAVFLEN_SBAS    1500           /* navigation frame data (bits) */
#define NAVADDFLEN_SBAS 12             /* additional bits of frame (bits) */
#define NAVPRELEN_SBAS  16             /* preamble bits length (bits) */
#define NAVEPHCNT_SBAS  3              /* number of eph. contained frame */
/* GLONASS G1 */
#define NAVRATE_G1      10             /* length (multiples of ranging code) */
#define NAVFLEN_G1      200            /* navigation frame data (bits) */
#define NAVADDFLEN_G1   0              /* additional bits of frame (bits) */
#define NAVPRELEN_G1    30             /* preamble bits length (bits) */
#define NAVEPHCNT_G1    5              /* number of eph. contained frame */
/* Galileo E1B */
#define NAVRATE_E1B     1              /* length (multiples of ranging code) */
#define NAVFLEN_E1B     500            /* navigation frame data (bits) */
#define NAVADDFLEN_E1B  0              /* additional bits of frame (bits) */
#define NAVPRELEN_E1B   10             /* preamble bits length (bits) */
#define NAVEPHCNT_E1B   5              /* number of eph. contained frame */
/* BeiDou BI1 */
#define NAVRATE_B1I     20             /* length (multiples of ranging code) */
#define NAVFLEN_B1I     300            /* navigation frame data (bits) */
#define NAVADDFLEN_B1I  0              /* additional bits of frame (bits) */
#define NAVPRELEN_B1I   11             /* preamble bits length (bits) */
#define NAVEPHCNT_B1I   3              /* number of eph. contained frame */
/* BeiDou BI1(GEO satellite) */
#define NAVRATE_B1IG    2              /* length (multiples of ranging code) */
#define NAVFLEN_B1IG    300            /* navigation frame data (bits) */
#define NAVADDFLEN_B1IG 0              /* additional bits of frame (bits) */
#define NAVPRELEN_B1IG  11             /* preamble bits length (bits) */
#define NAVEPHCNT_B1IG  10             /* number of eph. contained frame */

/* observation data generation */
#define PTIMING       68.802           /* pseudo range generation timing (ms) */
#define OBSINTERPN    40               /* # of obs. stock for interpolation */
#define SNSMOOTHMS    100              /* SNR smoothing interval (ms) */

/* code generation parameter */
#define MAXGPSSATNO   210              /* max satellite number */
#define MAXGALSATNO   50               /* max satellite number */
#define MAXCMPSATNO   37               /* max satellite number */
/* code type */
#define CTYPE_L1CA    1                /* GPS/QZSS L1C/A */
#define CTYPE_L1CP    2                /* GPS/QZSS L1C Pilot */
#define CTYPE_L1CD    3                /* GPS/QZSS L1C Data */
#define CTYPE_L1CO    4                /* GPS/QZSS L1C overlay */
#define CTYPE_L2CM    5                /* GPS/QZSS L2CM */
#define CTYPE_L2CL    6                /* GPS/QZSS L2CL */
#define CTYPE_L5I     7                /* GPS/QZSS L5I */
#define CTYPE_L5Q     8                /* GPS/QZSS L5Q */
#define CTYPE_E1B     9                /* Galileo E1B (Data) */
#define CTYPE_E1C     10               /* Galileo E1C (Pilot) */
#define CTYPE_E5AI    11               /* Galileo E5aI (Data) */
#define CTYPE_E5AQ    12               /* Galileo E5aQ (Pilot) */
#define CTYPE_E5BI    13               /* Galileo E5bI (Data) */
#define CTYPE_E5BQ    14               /* Galileo E5bQ (Pilot) */
#define CTYPE_E1CO    15               /* Galileo E1C overlay */
#define CTYPE_E5AIO   16               /* Galileo E5aI overlay */
#define CTYPE_E5AQO   17               /* Galileo E5aQ overlay */
#define CTYPE_E5BIO   18               /* Galileo E5bI overlay */
#define CTYPE_E5BQO   19               /* Galileo E5bQ overlay */
#define CTYPE_G1      20               /* GLONASS G1 */
#define CTYPE_G2      21               /* GLONASS G2 */
#define CTYPE_B1I     22               /* BeiDou B1I */
#define CTYPE_B2I     23               /* BeiDou B2I */
#define CTYPE_LEXS    24               /* QZSS LEX short */
#define CTYPE_LEXL    25               /* QZSS LEX long */
#define CTYPE_L1SAIF  26               /* QZSS L1 SAIF */
#define CTYPE_L1SBAS  27               /* SBAS compatible L1CA */
#define CTYPE_NH10    28               /* 10 bit Neuman-Hoffman code */
#define CTYPE_NH20    29               /* 20 bit Neuman-Hoffman code */

/* gnuplot plotting setting */
#define PLT_Y         1                /* plotting type: 1D data */
#define PLT_XY        2                /* plotting type: 2D data */
#define PLT_SURFZ     3                /* plotting type: 3D surface data */
#define PLT_BOX       4                /* plotting type: BOX */
#define PLT_WN        5                /* number of figure window column */
#define PLT_HN        4                /* number of figure window row */
#define PLT_W         200              /* window width (pixel) */
#define PLT_H         300              /* window height (pixel) */
#define PLT_MW        100              /* margin (pixel) */
#define PLT_MH        20                /* margin (pixel) */
#define PLT_MS        200              /* plotting interval (ms) */
#define PLT_MS_FILE   1000               /* plotting interval (ms) */

/* spectrum analysis */
#define SPEC_MS       200              /* plotting interval (ms) */
#define SPEC_LEN      7                /* number of integration of 1 ms data */
#define SPEC_BITN     8                /* number of bin for histogram */
#define SPEC_NLOOP    100              /* number of loop for smoothing */
#define SPEC_NFFT     16384            /* number of FFT points */
#define SPEC_PLT_W    400              /* window width (pixel) */
#define SPEC_PLT_H    500              /* window height (pixel) */
#define SPEC_PLT_MW   100              /* margin (pixel) */
#define SPEC_PLT_MH   0                /* margin (pixel) */

/* QZSS LEX setting */
#define DSAMPLEX      12               /* L1CA-LEX DCB (sample) */
#define LEXMS         4                /* LEX short length (ms) */
#define LENLEXPRE     4                /* LEX preamble length (byte) */
#define LENLEXMSG     250              /* LEX message length (byte) */
#define LENLEXRS      255              /* LEX RS data length (byte) */
#define LENLEXRSK     223              /* LEX RS K (byte) */
#define LENLEXRSP     (LENLEXRS-LENLEXRSK) /* LEX RS parity length (byte) */
#define LENLEXERR     (LENLEXRSP/2)    /* RS max error correction len (byte) */
#define LENLEXRCV     (8+LENLEXMSG-LENLEXRSP) /* LEX transmitting length */

/* SBAS/QZSS L1-SAIF setting */
#define LENSBASMSG    32               /* SBAS message length 150/8 (byte) */
#define LENSBASNOV    80               /* message length in NovAtel format */

/* thread functions */
#ifdef WIN32
#define mlock_t       HANDLE
#define initmlock(f)  (f=CreateMutex(NULL,FALSE,NULL))
#define mlock(f)      WaitForSingleObject(f,INFINITE)
#define unmlock(f)    ReleaseMutex(f)
#define delmlock(f)   CloseHandle(f)
#define event_t       HANDLE
#define initevent(f)  (f=CreateEvent(NULL,FALSE,FALSE,NULL))
#define setevent(f)   SetEvent(f)
#define waitevent(f,m) WaitForSingleObject(f,INFINITE)
#define delevent(f)   CloseHandle(f)
#define waitthread(f) WaitForSingleObject(f,INFINITE)
#define cratethread(f,func,arg) (f=(thread_t)_beginthread(func,0,arg))
#define THRETVAL      
#else
#define mlock_t       pthread_mutex_t
#define initmlock(f)  pthread_mutex_init(&f,NULL)
#define mlock(f)      pthread_mutex_lock(&f)
#define unmlock(f)    pthread_mutex_unlock(&f)
#define delmlock(f)   pthread_mutex_destroy(&f)
#define event_t       pthread_cond_t
#define initevent(f)  pthread_cond_init(&f,NULL)
#define setevent(f)   pthread_cond_signal(&f)
#define waitevent(f,m) pthread_cond_wait(&f,&m)
#define delevent(f)   pthread_cond_destroy(&f)
#define waitthread(f) pthread_join(f,NULL)
#define cratethread(f,func,arg) pthread_create(&f,NULL,func,arg)
#define THRETVAL      NULL
#endif

/* type definition -----------------------------------------------------------*/
typedef fftwf_complex cpx_t; /* complex type for fft */

/* sdr initialization struct */
typedef struct {
    int fend;            /* front end type */
    double f_cf[2];      /* center frequency (Hz) */
    double f_sf[2];      /* sampling frequency (Hz) */
    double f_if[2];      /* intermediate frequency (Hz) */
    int dtype[2];        /* data type (DTYPEI/DTYPEIQ) */
    FILE *fp1;           /* IF1 file pointer */
    FILE *fp2;           /* IF2 file pointer */
    char file1[1024];    /* IF1 file path */
    char file2[1024];    /* IF2 file path */
    int useif1;          /* IF1 flag */
    int useif2;          /* IF2 flag */
    int nch;             /* number of sdr channels */
    int nchL1;           /* number of L1 channels */
    int nchL2;           /* number of L2 channels */
    int nchL5;           /* number of L5 channels */
    int nchL6;           /* number of L6 channels */
    int prn[MAXSAT];     /* PRN of channels */
    int sys[MAXSAT];     /* satellite system type of channels (SYS_*) */
    int ctype[MAXSAT];   /* code type of channels (CTYPE_* )*/
    int ftype[MAXSAT];   /* front end type of channels (FTYPE1/FTYPE2) */
    int pltacq;          /* plot acquisition flag */
    int plttrk;          /* plot tracking flag */
    int pltspec;         /* plot spectrum flag */
    int outms;           /* output interval (ms) */
    int rinex;           /* rinex output flag */
    int rtcm;            /* rtcm output flag */
    int lex;             /* QZSS LEX output flag */
    int sbas;            /* SBAS/QZSS L1SAIF output flag */
    int log;             /* tracking log output flag */
    char rinexpath[1024];/* rinex output path */
    int rtcmport;        /* rtcm TCP/IP port */
    int lexport;         /* LEX TCP/IP port */
    int sbasport;        /* SBAS/L1-SAIF TCP/IP port */
    int trkcorrn;        /* number of correlation points */
    int trkcorrd;        /* interval of correlation points (sample) */
    int trkcorrp;        /* correlation points (sample) */
    double trkdllb[2];   /* dll noise bandwidth (Hz) */
    double trkpllb[2];   /* pll noise bandwidth (Hz) */
    double trkfllb[2];   /* fll noise bandwidth (Hz) */
    int rtlsdrppmerr;    /* clock collection for RTL-SDR */
} sdrini_t;

/* sdr current state struct */
typedef struct {
    int stopflag;        /* stop flag */
    int specflag;        /* spectrum flag */
    int buffsize;        /* data buffer size */
    int fendbuffsize;    /* front end data buffer size */
    unsigned char *buff; /* IF data buffer */
    unsigned char *buff2;/* IF data buffer (for file input) */
    unsigned char *tmpbuff; /* USB temporary buffer (for STEREO_V26) */
    uint64_t buffcnt;    /* current buffer location */
} sdrstat_t;

/* sdr observation struct */
typedef struct {
    int prn;             /* PRN */
    int sys;             /* satellite system */
    double tow;          /* time of week (s) */
    int week;            /* week number */
    double P;            /* pseudo range (m) */
    double L;            /* carrier phase (cycle) */
    double D;            /* doppler frequency (Hz) */
    double S;            /* SNR (dB-Hz) */
} sdrobs_t;

/* sdr acquisition struct */
typedef struct {
    int intg;            /* number of integration */
    double hband;        /* half band of search frequency (Hz) */
    double step;         /* frequency search step (Hz) */
    int nfreq;           /* number of search frequency */
    double *freq;        /* search frequency (Hz) */
    int acqcodei;        /* acquired code phase */
    int freqi;           /* acquired frequency index */
    double acqfreq;      /* acquired frequency (Hz) */
    int nfft;            /* number of FFT points */
    double cn0;          /* signal C/N0 */ 
    double peakr;        /* first/second peak ratio */
} sdracq_t;

/* sdr tracking parameter struct */
typedef struct {
    double pllb;         /* noise bandwidth of PLL (Hz) */
    double dllb;         /* noise bandwidth of DLL (Hz) */
    double fllb;         /* noise bandwidth of FLL (Hz) */
    double dllw2;        /* DLL coefficient */
    double dllaw;        /* DLL coefficient */
    double pllw2;        /* PLL coefficient */
    double pllaw;        /* PLL coefficient */
    double fllw;         /* FLL coefficient */
} sdrtrkprm_t;

/* sdr tracking struct */
typedef struct {
    double codefreq;     /* code frequency (Hz) */
    double carrfreq;     /* carrier frequency (Hz) */
    double remcode;      /* remained code phase (chip) */
    double remcarr;      /* remained carrier phase (rad) */
    double oldremcode;   /* previous remained code phase (chip) */
    double oldremcarr;   /* previous remained carrier phase (chip) */
    double codeNco;      /* code NCO */
    double codeErr;      /* code tracking error */
    double carrNco;      /* carrier NCO */
    double carrErr;      /* carrier tracking error */
    double freqErr;      /* frequencyr error in FLL */
    uint64_t buffloc;    /* current buffer location */
    double tow[OBSINTERPN]; /* time of week (s) */
    uint64_t codei[OBSINTERPN]; /* code phase (sample) */
    uint64_t codeisum[OBSINTERPN]; /* code phase for SNR computation (sample) */
    uint64_t cntout[OBSINTERPN]; /* loop counter */
    double remcout[OBSINTERPN]; /* remained code phase (chip)*/
    double L[OBSINTERPN];/* carrier phase (cycle) */
    double D[OBSINTERPN];/* doppler frequency (Hz) */
    double S[OBSINTERPN];/* signal to noise ratio (dB-Hz) */
    double *II;          /* correlation (in-phase) */
    double *QQ;          /* correlation (quadrature-phase) */
    double *oldI;        /* previous correlation (I-phase) */
    double *oldQ;        /* previous correlation (Q-phase) */
    double *sumI;        /* integrated correlation (I-phase) */
    double *sumQ;        /* integrated correlation (Q-phase) */
    double *oldsumI;     /* previous integrated correlation (I-phase) */
    double *oldsumQ;     /* previous integrated correlation (Q-phase) */
    double Isum;         /* correlation for SNR computation (I-phase) */
    int loop;            /* loop filter interval */
    int loopms;          /* loop filter interval (ms) */
    int flagpolarityadd; /* polarity (half cycle ambiguity) add flag */
    int flagremcarradd;  /* remained carrier phase add flag */
    int corrn;           /* number of correlation points */
    int *corrp;          /* correlation points (sample) */
    double *corrx;       /* correlation points (for plotting) */
    int ne,nl;           /* early/late correlation point */
    sdrtrkprm_t prm1;    /* tracking parameter struct */
    sdrtrkprm_t prm2;    /* tracking parameter struct */
} sdrtrk_t;

/* sdr ephemeris struct */
typedef struct {
    eph_t eph;           /* GPS/QZS/GAL/COM ephemeris struct (from rtklib.h) */
    geph_t geph;         /* GLO ephemeris struct (from rtklib.h) */
    int ctype;           /* code type */
    double tow_gpst;     /* ephemeris tow in GPST */
    int week_gpst;       /* ephemeris week in GPST */
    int cnt;             /* ephemeris decode counter */
    int cntth;           /* ephemeris decode count threshold */
    int update;          /* ephemeris update flag */
    int prn;             /* PRN */
    int tk[3],nt,n4,s1cnt; /* temporary variables for decoding GLONASS */
    double toc_gst;      /* temporary variables for decoding Galileo */
    int week_gst;
                         /* temporary variables for decoding BeiDou D1 */
    unsigned int toe1,toe2;
                         /* temporary variables for decoding BeiDou D2 */
    int toe_bds,f1p3,cucp4,ep5,cicp6,i0p7,OMGdp8,omgp9;
    unsigned int f1p4,cucp5,ep6,cicp7,i0p8,OMGdp9,omgp10;
} sdreph_t;

/* sdr LEX struct */
typedef struct {
    unsigned char msg[LENLEXMSG]; /* LEX message (250bytes/s) */
} sdrlex_t;

/* sdr SBAS struct */
typedef struct {
    unsigned char msg[LENSBASMSG]; /* SBAS message (250bits/s) */
    unsigned char novatelmsg[LENSBASNOV]; /* NovAtel format (80bytes/s) */
    int id;              /* message ID */
    int week;            /* GPS week */
    double tow;          /* GPS time of week (s) */
} sdrsbas_t;

/* sdr navigation struct */
typedef struct {
    FILE *fpnav;         /* for navigation bit logging */
    int ctype;           /* code type */
    int rate;            /* navigation data rate (ms) */
    int flen;            /* frame length (bits) */
    int addflen;         /* additional frame bits (bits) */
    int prebits[32];     /* preamble bits */
    int prelen;          /* preamble bits length (bits) */
    int bit;             /* current navigation bit */
    int biti;            /* current navigation bit index */
    double bitIP;        /* current navigation bit (IP data) */
    int *fbits;          /* frame bits */
    int *fbitsdec;       /* decoded frame bits */
    int update;          /* decode interval (ms) */
    int *bitsync;        /* frame bits synchronization count */
    int synci;           /* frame bits synchronization index */
    uint64_t firstsf;    /* first subframe location (sample) */
    uint64_t firstsfcnt; /* first subframe count */
    double firstsftow;   /* tow of first subframe */
    int polarity;        /* bit polarity */
    int flagpol;         /* bit polarity flag (only used in L1-SAIF) */
    void *fec;           /* FEC (fec.h)  */
    short *ocode;        /* overlay code (secondary code) */
    int ocodei;          /* current overray code index */
    int swsync;          /* switch of frame synchronization (last bit) */
    int swreset;         /* switch of frame synchronization (first bit) */
    int flagsync;        /* navigation bit synchronization flag */
    int flagsyncf;       /* navigation frame synchronization (preamble found) */
    int flagtow;         /* first subframe found flag */
    int flagdec;         /* navigation data decoded flag */
    sdreph_t sdreph;     /* sdr ephemeris struct */
    sdrlex_t lex;        /* QZSS LEX message struct */
    sdrsbas_t sbas;      /* SBAS message struct */
} sdrnav_t;

/* sdr channel struct */
typedef struct {
    thread_t hsdr;       /* thread handle */
    int no;              /* channel number */
    int sat;             /* satellite number */
    int sys;             /* satellite system */
    int prn;             /* PRN */
    char satstr[5];      /* PRN string */
    int ctype;           /* code type */
    int dtype;           /* data type */
    int ftype;           /* front end type */
    double f_cf;         /* carrier frequency (Hz) */
    double f_sf;         /* sampling rate (Hz) */
    double f_if;         /* intermediate frequency (Hz) */
    double foffset;      /* frequency offset (Hz) */
    short *code;         /* original code */
    cpx_t *xcode;        /* resampled code in frequency domain */
    int clen;            /* code length */
    double crate;        /* code chip rate (Hz) */
    double ctime;        /* code period (s) */
    double ti;           /* sampling interval (s) */
    double ci;           /* chip interval (s) */
    int nsamp;           /* number of samples in one code (doppler=0Hz) */
    int currnsamp;       /* current number of samples in one code */
    int nsampchip;       /* number of samples in one code chip (doppler=0Hz) */
    sdracq_t acq;        /* acquisition struct */
    sdrtrk_t trk;        /* tracking struct */
    sdrnav_t nav;        /* navigation struct */
    int flagacq;         /* acquisition flag */
    int flagtrk;         /* tracking flag */
} sdrch_t;

/* sdr plotting struct */
typedef struct {
    FILE *fp;            /* file pointer (gnuplot pipe) */
#ifdef WIN32
    HWND hw;             /* window handle */
#endif
    int nx;              /* length of x data */
    int ny;              /* length of y data */
    double *x;           /* x data */
    double *y;           /* y data */
    double *z;           /* z data */
    int type;            /* plotting type (PLT_X/PLT_XY/PLT_SURFZ) */
    int skip;            /* skip data (0: plotting all data) */
    int flagabs;         /* y axis data absolute flag (y=abs(y)) */
    double scale;        /* y axis data scale (y=scale*y) */
    int plth;            /* plot window height */
    int pltw;            /* plot window width */
    int pltmh;           /* plot window margin height */
    int pltmw;           /* plot window margin width */
    int pltno;           /* number of figure */
    double pltms;        /* plot interval (ms) */
} sdrplt_t;

/* sdr socket struct */
typedef struct {
    thread_t hsoc;       /* thread handle */
    int port;            /* port number */
#ifdef WIN32
    SOCKET s_soc,c_soc;  /* server/client socket */
#else
    int s_soc,c_soc;     /* server/client socket */
#endif
    int flag;            /* connection flag */
} sdrsoc_t;

/* sdr output struct */
typedef struct {
    int nsat;            /* number of satellite */
    obsd_t *obsd;        /* observation struct (defined in rtklib.h) */
    rnxopt_t opt;        /* rinex option struct (defined in rtklib.h) */
    sdrsoc_t soc_rtcm;   /* sdr socket struct for rtcm output */
    sdrsoc_t soc_lex;    /* sdr socket struct for lex output */
    sdrsoc_t soc_sbas;   /* sdr socket struct for sbas output */
    char rinexobs[1024]; /* rinex observation file name */
    char rinexnav[1024]; /* rinex navigation file name */
} sdrout_t;

/* sdr spectrum struct */
typedef struct {
    int dtype;           /* data type (DTYPEI/DTYPEIQ) */
    int ftype;           /* front end type */
    int nsamp;           /* number of samples in one code */
    double f_sf;         /* sampling frequency (Hz) */
    sdrplt_t histI;      /* plot struct for histogram */
    sdrplt_t histQ;      /* plot struct for histogram */
    sdrplt_t pspec;      /* plot struct for spectrum analysis */
} sdrspec_t;

/* global variables ----------------------------------------------------------*/
extern thread_t hmainthread;  /* main thread handle */
extern thread_t hsyncthread;  /* synchronization thread handle */
extern thread_t hspecthread;  /* spectrum analyzer thread handle */
extern thread_t hkeythread;   /* keyboard thread handle */
extern mlock_t hbuffmtx;      /* buffer access mutex */
extern mlock_t hreadmtx;      /* buffloc access mutex */
extern mlock_t hfftmtx;       /* fft function mutex */
extern mlock_t hpltmtx;       /* plot function mutex */
extern mlock_t hobsmtx;       /* observation data access mutex */
extern mlock_t hlexmtx;       /* QZSS LEX mutex */
extern event_t hlexeve;       /* QZSS LEX event */

extern sdrini_t sdrini;       /* sdr initialization struct */
extern sdrstat_t sdrstat;     /* sdr state struct */
extern sdrch_t sdrch[MAXSAT]; /* sdr channel structs */
extern sdrspec_t sdrspec;     /* sdr spectrum analyzer structs */
extern sdrout_t sdrout;       /* sdr output structs */

/* sdrmain.c -----------------------------------------------------------------*/
#ifdef GUI
extern GCHandle hform;
extern void initsdrgui(maindlg^ form, sdrini_t* sdrinigui);
extern void startsdr(void *arg);
#else
extern void startsdr(void);
#endif
extern void quitsdr(sdrini_t *ini, int stop);
#ifdef WIN32
extern void sdrthread(void *arg);
#else
extern void *sdrthread(void *arg);
#endif

/* sdrsync.c -----------------------------------------------------------------*/
#ifdef WIN32
extern void syncthread(void * arg);
#else
extern void *syncthread(void * arg);
#endif

/* sdracq.c ------------------------------------------------------------------*/
extern uint64_t sdraccuisition(sdrch_t *sdr, double *power);
extern int checkacquisition(double *P, sdrch_t *sdr);


/* sdrtrk.c ------------------------------------------------------------------*/
extern uint64_t sdrtracking(sdrch_t *sdr, uint64_t buffloc, uint64_t cnt);
extern void cumsumcorr(sdrtrk_t *trk, int polarity, int flag1, int flag2);
extern void pll(sdrch_t *sdr, sdrtrkprm_t *prm, double dt);
extern void dll(sdrch_t *sdr, sdrtrkprm_t *prm, double dt);
extern void setobsdata(sdrch_t *sdr, uint64_t buffloc, uint64_t cnt, 
                       sdrtrk_t *trk, int flag);

/* sdrinit.c -----------------------------------------------------------------*/
extern int readinifile(sdrini_t *ini);
extern int chk_initvalue(sdrini_t *ini);
extern void openhandles(void);
extern void closehandles(void);
extern int initpltstruct(sdrplt_t *acq, sdrplt_t *trk,sdrch_t *sdr);
extern void quitpltstruct(sdrplt_t *acq, sdrplt_t *trk);
extern void initacqstruct(int sys, int ctype, int prn, sdracq_t *acq);
extern void inittrkprmstruct(sdrtrk_t *trk);
extern int inittrkstruct(int sat, int ctype, double ctime, sdrtrk_t *trk);
extern int initnavstruct(int sys, int ctype, int prn, sdrnav_t *nav);
extern int initsdrch(int chno, int sys, int prn, int ctype, int dtype, 
                     int ftype, double f_cf, double f_sf, double f_if,
                     sdrch_t *sdr);
extern void freesdrch(sdrch_t *sdr);

/* sdrcmn.c ------------------------------------------------------------------*/
extern int getfullpath(char *relpath, char *abspath);
extern void sleepus(int usec);
extern void settimeout(struct timespec *timeout, int waitms);
extern double log2(double n);
extern int calcfftnum(double x, int next);
extern void *sdrmalloc(size_t size);
extern void sdrfree(void *p);
extern cpx_t *cpxmalloc(int n);
extern void cpxfree(cpx_t *cpx);
extern void cpxfft(fftwf_plan plan, cpx_t *cpx, int n);
extern void cpxifft(fftwf_plan plan, cpx_t *cpx, int n);
extern void cpxcpx(const short *II, const short *QQ, double scale, int n,
                   cpx_t *cpx);
extern void cpxcpxf(const float *II, const float *QQ, double scale,  int n,
                    cpx_t *cpx);
extern void cpxconv(fftwf_plan plan, fftwf_plan iplan, cpx_t *cpxa, cpx_t *cpxb,
                    int m, int n, int flagsum, double *conv);
extern void cpxpspec(fftwf_plan plan, cpx_t *cpx, int n, int flagsum,
                     double *pspec);
extern void dot_21(const short *a1, const short *a2, const short *b, int n, 
                   double *d1, double *d2);
extern void dot_22(const short *a1, const short *a2, const short *b1, 
                   const short *b2, int n, double *d1, double *d2);
extern void dot_23(const short *a1, const short *a2, const short *b1, 
                   const short *b2, const short *b3, int n, double *d1, 
                   double *d2);
extern double mixcarr(const char *data, int dtype, double ti, int n, 
                      double freq, double phi0, short *II, short *QQ);
extern void mulvcs(const char *data1, const short *data2, int n, short *out);
extern void sumvf(const float *data1, const float *data2, int n, float *out);
extern void sumvd(const double *data1, const double *data2, int n, double *out);
extern int maxvi(const int *data, int n, int exinds, int exinde, int *ind);
extern float maxvf(const float *data, int n, int exinds, int exinde, int *ind);
extern double maxvd(const double *data, int n, int exinds, int exinde,int *ind);
extern double meanvd(const double *data, int n, int exinds, int exinde);
extern double interp1(double *x, double *y, int n, double t);
extern void uint64todouble(uint64_t *data, uint64_t base, int n, double *out);
extern void ind2sub(int ind, int nx, int ny, int *subx, int *suby);
extern void shiftright(void *dst, void *src, size_t size, int n);
extern double rescode(const short *code, int len, double coff, int smax, 
                      double ci, int n, short *rcode);
extern void pcorrelator(const char *data, int dtype, double ti, int n, 
                        double *freq, int nfreq, double crate, int m, 
                        cpx_t* codex, double *P);
extern void correlator(const char *data, int dtype, double ti, int n, 
                       double freq, double phi0, double crate, double coff, 
                       int* s, int ns, double *II, double *QQ, double *remc, 
                       double *remp, short* codein, int coden);

/* sdrcode.c -----------------------------------------------------------------*/
extern short *gencode(int prn, int ctype, int *len, double *crate);

/* sdrplot.c -----------------------------------------------------------------*/
extern int updatepltini(int nx, int ny, int posx, int posy);
extern void setsdrplotprm(sdrplt_t *plt, int type, int nx, int ny, int skip, 
                       int abs, double s, int h, int w, int mh, int mw, int no);
extern int initsdrplot(sdrplt_t *plt);
extern void quitsdrplot(sdrplt_t *plt);
extern void setxrange(sdrplt_t *plt, double xmin, double xmax);
extern void setyrange(sdrplt_t *plt, double ymin, double ymax);
extern void setlabel(sdrplt_t *plt, char *xlabel, char *ylabel);
extern void settitle(sdrplt_t *plt, char *title);
extern void ploty(FILE *fp, double *x, int n, int skip, double scale);
extern void plotxy(FILE *fp, double *x, double *y, int n, int skip, double s);
extern void plotsurfz(FILE *fp, double*z, int nx, int ny, int skip, double s);
extern void plotbox(FILE *fp, double *x, double *y, int n, int skip, double s);
extern void plotthread(sdrplt_t *plt);
extern void plot(sdrplt_t *plt);

/* sdrnav.c ------------------------------------------------------------------*/
extern void sdrnavigation(sdrch_t *sdr, uint64_t buffloc, uint64_t cnt);
extern uint32_t getbitu2(const uint8_t *buff, int p1, int l1, int p2, int l2);
extern int32_t getbits2(const uint8_t *buff, int p1, int l1, int p2, int l2);
extern uint32_t getbitu3(const uint8_t *buff, int p1, int l1, int p2, int l2, 
                         int p3, int l3);
extern int32_t getbits3(const uint8_t *buff, int p1, int l1, int p2, int l2,
                        int p3, int l3);
extern uint32_t merge_two_u(const uint32_t a, const uint32_t b, int n);
extern int32_t merge_two_s(const int32_t a, const uint32_t b, int n);
extern void bits2byte(int *bits, int nbits, int nbin, int right, uint8_t *bin);
extern void interleave(const int *in, int row, int col, int *out);
extern int checksync(double IP, double IPold, sdrnav_t *nav);
extern int checkbit(double IP, sdrnav_t *nav);
extern void predecodefec(sdrnav_t *nav);
extern int paritycheck(sdrnav_t *nav);
extern int findpreamble(sdrnav_t *nav);
extern int decodenav(sdrnav_t *nav);
extern void check_hamming(int *hamming, int n, int parity, int m);

/* sdrnav_gps/gal/glo.c/sbs.c ------------------------------------------------*/
extern int decode_l1ca(sdrnav_t *nav);
extern int decode_e1b(sdrnav_t *nav);
extern int decode_g1(sdrnav_t *nav);
extern int decode_b1i(sdrnav_t *nav);
extern int decode_l1sbas(sdrnav_t *nav);
extern int paritycheck_l1ca(int *bits);

/* sdrout.c ------------------------------------------------------------------*/
extern void createrinexopt(rnxopt_t *opt);
extern void sdrobs2obsd(sdrobs_t *sdrobs, int ns, obsd_t *out);
extern int createrinexobs(char *file, rnxopt_t *opt);
extern int writerinexobs(char *file, rnxopt_t *opt, obsd_t *obsd, int ns);
extern int createrinexnav(char *file, rnxopt_t *opt);
extern int writerinexnav(char *file, rnxopt_t *opt, sdreph_t *sdreph);
extern void tcpsvrstart(sdrsoc_t *soc);
extern void tcpsvrclose(sdrsoc_t *soc);
extern void sendrtcmnav(sdreph_t *eph, sdrsoc_t *soc);
extern void sendrtcmobs(obsd_t *obsd, sdrsoc_t *soc, int nsat);
extern void sendsbas(sdrsbas_t *sbas, sdrsoc_t *soc);
extern void writelog(FILE *fp, sdrtrk_t *trk,sdrnav_t *nav);
extern FILE* createlog(char *filename, sdrtrk_t *trk);
extern void closelog(FILE *fp);

/* sdrrcv.c ------------------------------------------------------------------*/
extern int rcvinit(sdrini_t *ini);
extern int rcvquit(sdrini_t *ini);
extern int rcvgrabstart(sdrini_t *ini);
extern int rcvgrabdata(sdrini_t *ini);
extern int rcvgetbuff(sdrini_t *ini, uint64_t buffloc, int n, int ftype, 
                      int dtype, char *expbuf);
extern void file_pushtomembuf(void);
extern void file_getbuff(uint64_t buffloc, int n, int ftype, int dtype, 
                         char *expbuf);

/* sdrspec.c -----------------------------------------------------------------*/
extern void initsdrspecgui(sdrspec_t* sdrspecgui);
#ifdef WIN32
extern void specthread(void * arg);
#else
extern void *specthread(void * arg);
#endif
extern int initspecpltstruct(sdrspec_t *spec);
extern void quitspecpltstruct(sdrspec_t *spec);
extern void calchistgram(char *data, int dtype, int n, double *xI, double *yI, 
                         double *xQ, double *yQ);
extern void hanning(int n, float *win);
extern int spectrumanalyzer(const char *data, int dtype, int n, double f_sf, 
                            int nfft, double *freq, double *pspec);

/* sdrlex.c ------------------------------------------------------------------*/
#ifdef WIN32
extern void lexthread(void *arg);
#else
extern void *lexthread(void *arg);
#endif

#ifdef __cplusplus
}
#endif
#endif /* SDR_H */
