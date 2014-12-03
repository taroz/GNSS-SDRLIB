/*------------------------------------------------------------------------------
* sdrcmn.c : SDR common functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
* Copyright (C) 2014 T. Takasu <http://www.rtklib.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

#define CDIV          32               /* carrier lookup table (cycle) */
#define CMASK         0x1F             /* carrier lookup table mask */
#define CSCALE        (1.0/32.0)       /* carrier lookup table scale (LSB) */

/* get full path from relative path --------------------------------------------
* args   : char *relpath    I   relative path
*          char *fullpath   O   full path
* return : int                  0:success, -1:failure 
*-----------------------------------------------------------------------------*/
extern int getfullpath(char *relpath, char *abspath)
{
#ifdef WIN32
    if (_fullpath(abspath,relpath,_MAX_PATH)==NULL) {
        SDRPRINTF("error: getfullpath %s\n",relpath);
        return -1;
    }
#else
    if (realpath(relpath,abspath)==NULL) {
        SDRPRINTF("error: getfullpath %s\n",relpath);
        return -1;
    }
#endif
    return 0;
}
/* get tick time (micro second) ------------------------------------------------
* get current tick in ms
* args   : none
* return : current tick in us
*-----------------------------------------------------------------------------*/
extern unsigned long tickgetus(void)
{
#ifdef WIN32
    LARGE_INTEGER f,t;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t);
    return (unsigned long)(t.QuadPart*1000000UL/f.QuadPart);
#else
    struct timespec tp={0};
    struct timeval  tv={0};
    
#ifdef CLOCK_MONOTONIC_RAW
    /* linux kernel > 2.6.28 */
    if (!clock_gettime(CLOCK_MONOTONIC_RAW,&tp)) {
        return tp.tv_sec*1000000UL+tp.tv_nsec/1000UL;
    }
    else {
        gettimeofday(&tv,NULL);
        return tv.tv_sec*1000000UL+tv.tv_usec;
    }
#else
    gettimeofday(&tv,NULL);
    return (unsigned long)(tv.tv_sec*1000000UL+tv.tv_usec);
#endif
#endif
}
/* calculation log2(x) ---------------------------------------------------------
* args   : double x         I   x data
* return : double               log2(x)
*-----------------------------------------------------------------------------*/
extern double log2(double x)  
{  
    return log(x)/log(2.0);  
}
/* calculation FFT number of points (2^bits samples) ---------------------------
* calculation FFT number of points (round up)
* args   : double x         I   number of points (not 2^bits samples)
*          int    next      I   increment multiplier
* return : int                  FFT number of points (2^bits samples)
*-----------------------------------------------------------------------------*/
extern int calcfftnum(double x, int next)
{
    int nn=(int)(log2(x)+0.5)+next;
    return (int)pow(2.0,nn);
}
/* sdr malloc ------------------------------------------------------------------
* memorry allocation
* args   : int    size      I   sizee of allocation
* return : void*                allocated pointer
*-----------------------------------------------------------------------------*/
extern void *sdrmalloc(size_t size)
{
#if !defined(SSE2_ENABLE)
    return malloc(size);
#elif defined(WIN32)
    return _aligned_malloc(size,16);
#else
    void *p;
    if (posix_memalign(&p,16,size)) return NULL;
    return p;
#endif
}
/* sdr free --------------------------------------------------------------------
* free data
* args   : void   *p        I/O input/output complex data
* return : none
*-----------------------------------------------------------------------------*/
extern void sdrfree(void *p)
{
#if !defined(SSE2_ENABLE)
    free(p);
#elif defined(WIN32)
    _aligned_free(p);
#else
    free(p);
#endif
}
/* complex malloc --------------------------------------------------------------
* memorry allocation of complex data
* args   : int    n         I   number of allocation
* return : cpx_t*               allocated pointer
*-----------------------------------------------------------------------------*/
extern cpx_t *cpxmalloc(int n)
{
    return (cpx_t *)fftwf_malloc(sizeof(cpx_t)*n+32);
}
/* complex free ----------------------------------------------------------------
* free complex data
* args   : cpx_t  *cpx      I/O input/output complex data
* return : none
*-----------------------------------------------------------------------------*/
extern void cpxfree(cpx_t *cpx)
{
    fftwf_free(cpx);
}
/* complex FFT -----------------------------------------------------------------
* cpx=fft(cpx)
* args   : fftwf_plan plan  I   fftw plan (NULL: create new plan)
*          cpx_t  *cpx      I/O input/output complex data
*          int    n         I   number of input/output data
* return : none
*-----------------------------------------------------------------------------*/
extern void cpxfft(fftwf_plan plan, cpx_t *cpx, int n)
{
#ifdef FFTMTX
        mlock(hfftmtx);
#endif
    if (plan==NULL) {
        fftwf_plan_with_nthreads(NFFTTHREAD); /* fft execute in multi threads */
        plan=fftwf_plan_dft_1d(n,cpx,cpx,FFTW_FORWARD,FFTW_ESTIMATE);
        fftwf_execute_dft(plan,cpx,cpx); /* fft */
        fftwf_destroy_plan(plan);
    } else {
        fftwf_execute_dft(plan,cpx,cpx); /* fft */
    }
#ifdef FFTMTX
        unmlock(hfftmtx);
#endif
}
/* complex IFFT ----------------------------------------------------------------
* cpx=ifft(cpx)
* args   : fftwf_plan plan  I   fftw plan (NULL: create new plan)
*          cpx_t  *cpx      I/O input/output complex data
*          int    n         I   number of input/output data
* return : none
*-----------------------------------------------------------------------------*/
extern void cpxifft(fftwf_plan plan, cpx_t *cpx, int n)
{
#ifdef FFTMTX
        mlock(hfftmtx);
#endif
    if (plan==NULL) {
        fftwf_plan_with_nthreads(NFFTTHREAD); /* fft execute in multi threads */
        plan=fftwf_plan_dft_1d(n,cpx,cpx,FFTW_BACKWARD,FFTW_ESTIMATE);
        fftwf_execute_dft(plan,cpx,cpx); /* fft */
        fftwf_destroy_plan(plan);
    } else {
        fftwf_execute_dft(plan,cpx,cpx); /* fft */
    }
#ifdef FFTMTX
        unmlock(hfftmtx);
#endif

}
/* convert short vector to complex vector --------------------------------------
* cpx=complex(I,Q)
* args   : short  *I        I   input data array (real)
*          short  *Q        I   input data array (imaginary)
*          double scale     I   scale factor
*          int    n         I   number of input data
*          cpx_t *cpx       O   output complex array
* return : none
*-----------------------------------------------------------------------------*/
extern void cpxcpx(const short *II, const short *QQ, double scale, int n, 
                   cpx_t *cpx)
{
    float *p=(float *)cpx;
    int i;

    for (i=0;i<n;i++,p+=2) {
        p[0]=   II[i]*(float)scale;
        p[1]=QQ?QQ[i]*(float)scale:0.0f;
    }
}
/* convert float vector to complex vector --------------------------------------
* cpx=complex(I,Q)
* args   : float  *I        I   input data array (real)
*          float  *Q        I   input data array (imaginary)
*          double scale     I   scale factor
*          int    n         I   number of input data
*          cpx_t *cpx       O   output complex array
* return : none
*-----------------------------------------------------------------------------*/
extern void cpxcpxf(const float *II, const float *QQ, double scale, int n, 
                    cpx_t *cpx)
{
    float *p=(float *)cpx;
    int i;

    for (i=0;i<n;i++,p+=2) {
        p[0]=   II[i]*(float)scale;
        p[1]=QQ?QQ[i]*(float)scale:0.0f;
    }
}
/* FFT convolution -------------------------------------------------------------
* conv=sqrt(abs(ifft(fft(cpxa).*conj(cpxb))).^2) 
* args   : fftwf_plan plan  I   fftw plan (NULL: create new plan)
*          fftwf_plan iplan I   ifftw plan (NULL: create new plan)
*          cpx_t  *cpxa     I   input complex data array
*          cpx_t  *cpxb     I   input complex data array
*          int    m         I   number of input data
*          int    n         I   number of output data
*          int    flagsum   I   cumulative sum flag (conv+=conv)
*          double *conv     O   output convolution data
* return : none
*-----------------------------------------------------------------------------*/
extern void cpxconv(fftwf_plan plan, fftwf_plan iplan, cpx_t *cpxa, cpx_t *cpxb,
                    int m, int n, int flagsum, double *conv)
{
    float *p,*q,real,m2=(float)m*m;
    int i;

    cpxfft(plan,cpxa,m); /* fft */

    for (i=0,p=(float *)cpxa,q=(float *)cpxb;i<m;i++,p+=2,q+=2) {
        real=-p[0]*q[0]-p[1]*q[1];
        p[1]= p[0]*q[1]-p[1]*q[0];
        p[0]=real;
    }

    cpxifft(iplan,cpxa,m); /* ifft */

    if (flagsum) { /* cumulative sum */
        for (i=0,p=(float *)cpxa;i<n;i++,p+=2)
            conv[i]+=(p[0]*p[0]+p[1]*p[1])/m2;
    } else {
        for (i=0,p=(float *)cpxa;i<n;i++,p+=2)
            conv[i]=(p[0]*p[0]+p[1]*p[1])/m2;
    }
}
/* power spectrum calculation --------------------------------------------------
* power spectrum: pspec=abs(fft(cpx)).^2
* args   : fftwf_plan plan  I   fftw plan (NULL: create new plan)
*          cpx_t  *cpx      I   input complex data array
*          int    n         I   number of input data
*          int    flagsum   I   cumulative sum flag (pspec+=pspec)
*          double *pspec    O   output power spectrum data
* return : none
*-----------------------------------------------------------------------------*/
extern void cpxpspec(fftwf_plan plan, cpx_t *cpx, int n, int flagsum,
                     double *pspec)
{
    float *p;
    int i;

    cpxfft(plan,cpx,n); /* fft */

    if (flagsum) { /* cumulative sum */
        for (i=0,p=(float *)cpx;i<n;i++,p+=2)
            pspec[i]+=(p[0]*p[0]+p[1]*p[1]);
    } else {
        for (i=0,p=(float *)cpx;i<n;i++,p+=2)
            pspec[i]=(p[0]*p[0]+p[1]*p[1]);
    }
}
/* fundamental functions using SIMD --------------------------------------------
* note : SSE2 instructions are used
*-----------------------------------------------------------------------------*/
#if defined(SSE2_ENABLE)

/* multiply and add: xmm{int32}+=src1[8]{int16}.*src2[8]{int16} --------------*/
#define MULADD_INT16(xmm,src1,src2) { \
    __m128i _x1,_x2; \
    _x1=_mm_load_si128 ((__m128i *)(src1)); \
    _x2=_mm_loadu_si128((__m128i *)(src2)); \
    _x2=_mm_madd_epi16(_x2,_x1); \
    xmm=_mm_add_epi32(xmm,_x2); \
}
/* sum: dst{any}=sum(xmm{int32}) ---------------------------------------------*/
#define SUM_INT32(dst,xmm) { \
    int _sum[4]; \
    _mm_storeu_si128((__m128i *)_sum,xmm); \
    dst=_sum[0]+_sum[1]+_sum[2]+_sum[3]; \
}
/* expand int8: (xmm1,xmm2){int16}=xmm3{int8} --------------------------------*/
#define EXPAND_INT8(xmm1,xmm2,xmm3,zero) { \
    xmm1=_mm_unpacklo_epi8(zero,xmm3); \
    xmm2=_mm_unpackhi_epi8(zero,xmm3); \
    xmm1=_mm_srai_epi16(xmm1,8); \
    xmm2=_mm_srai_epi16(xmm2,8); \
}
/* load int8: (xmm1,xmm2){int16}=src[16]{int8} -------------------------------*/
#define LOAD_INT8(xmm1,xmm2,src,zero) { \
    __m128i _x; \
    _x  =_mm_loadu_si128((__m128i *)(src)); \
    EXPAND_INT8(xmm1,xmm2,_x,zero); \
}
/* load int8 complex: (xmm1,xmm2){int16}=src[16]{int8,int8} ------------------*/
#define LOAD_INT8C(xmm1,xmm2,src,zero,mask8) { \
    __m128i _x1,_x2; \
    _x1 =_mm_loadu_si128((__m128i *)(src)); \
    _x2 =_mm_srli_epi16(_x1,8); \
    _x1 =_mm_and_si128(_x1,mask8); \
    _x1 =_mm_packus_epi16(_x1,_x2); \
    EXPAND_INT8(xmm1,xmm2,_x1,zero); \
}
/* multiply int16: dst[16]{int16}=(xmm1,xmm2){int16}.*(xmm3,xmm4){int16} -----*/
#define MUL_INT16(dst,xmm1,xmm2,xmm3,xmm4) { \
    xmm1=_mm_mullo_epi16(xmm1,xmm3); \
    xmm2=_mm_mullo_epi16(xmm2,xmm4); \
    _mm_storeu_si128((__m128i *)(dst)    ,xmm1); \
    _mm_storeu_si128((__m128i *)((dst)+8),xmm2); \
}
/* multiply int8: dst[16]{int16}=src[16]{int8}.*(xmm1,xmm2){int16} -----------*/
#define MUL_INT8(dst,src,xmm1,xmm2,zero) { \
    __m128i _x1,_x2; \
    LOAD_INT8(_x1,_x2,src,zero); \
    MUL_INT16(dst,_x1,_x2,xmm1,xmm2); \
}
/* double to int32: xmm{int32}=(xmm1,xmm2){double} ---------------------------*/
#define DBLTOINT32(xmm,xmm1,xmm2) { \
    __m128i _int1,_int2; \
    _int1=_mm_cvttpd_epi32(xmm1); \
    _int2=_mm_cvttpd_epi32(xmm2); \
    _int2=_mm_slli_si128(_int2,8); \
    xmm=_mm_add_epi32(_int1,_int2); \
}
/* double to int16: xmm{int16}=(xmm1,...,xmm4){double}&mask{int32} -----------*/
#define DBLTOINT16(xmm,xmm1,xmm2,xmm3,xmm4,mask) { \
    __m128i _int3,_int4; \
    DBLTOINT32(_int3,xmm1,xmm2); \
    DBLTOINT32(_int4,xmm3,xmm4); \
    _int3=_mm_and_si128(_int3,mask); \
    _int4=_mm_and_si128(_int4,mask); \
    xmm=_mm_packs_epi32(_int3,_int4); \
}
/* multiply int8 with lut:dst[16]{int16}=(xmm1,xmm2){int8}.*xmm3{int8}[index] */
#define MIX_INT8(dst,xmm1,xmm2,xmm3,index,zero) { \
    __m128i _x,_x1,_x2; \
    _x=_mm_shuffle_epi8(xmm3,index); \
    EXPAND_INT8(_x1,_x2,_x,zero); \
    MUL_INT16(dst,_x1,_x2,xmm1,xmm2); \
}
#endif /* SSE2_ENABLE */

#if defined(AVX2_ENABLE)

/* multiply and add: xmm256{int32}+=src1[16]{int16}.*src2[16]{int16} ---------*/
#define MULADD_INT16_AVX(xmm,src1,src2) { \
    __m256i _x1,_x2; \
    _x1=_mm256_load_si256 ((__m256i *)(src1)); \
    _x2=_mm256_loadu_si256((__m256i *)(src2)); \
    _x2=_mm256_madd_epi16(_x2,_x1); \
    xmm=_mm256_add_epi32(xmm,_x2); \
}
/* sum: dst{any}=sum(xmm{int32}) ---------------------------------------------*/
#define SUM_INT32_AVX(dst,xmm) { \
    int _sum[8]; \
    _mm256_storeu_si256((__m256i *)_sum,xmm); \
    dst=_sum[0]+_sum[1]+_sum[2]+_sum[3]+_sum[4]+_sum[5]+_sum[6]+_sum[7]; \
}
#endif /* AVX2_ENABLE */

/* dot products: d1=dot(a1,b),d2=dot(a2,b) -------------------------------------
* args   : short  *a1       I   input short array
*          short  *a2       I   input short array
*          short  *b        I   input short array
*          int    n         I   number of input data
*          double *d1       O   output short array
*          double *d2       O   output short array
* return : none
* notes  : -128<=a1[i],a2[i],b[i]<127
*-----------------------------------------------------------------------------*/
extern void dot_21(const short *a1, const short *a2, const short *b, int n,
                   double *d1, double *d2)
{
    const short *p1=a1,*p2=a2,*q=b;

#if defined(AVX2_ENABLE)
    __m256i xmm1,xmm2;

    n=16*(int)ceil((double)n/16); /* modification to multiples of 16 */
    xmm1=_mm256_setzero_si256();
    xmm2=_mm256_setzero_si256();

    for (;p1<a1+n;p1+=16,p2+=16,q+=16) {
        MULADD_INT16_AVX(xmm1,p1,q);
        MULADD_INT16_AVX(xmm2,p2,q);
    }
    SUM_INT32_AVX(d1[0],xmm1);
    SUM_INT32_AVX(d2[0],xmm2);

#elif defined(SSE2_ENABLE)
    __m128i xmm1,xmm2;

    n=8*(int)ceil((double)n/8); /* modification to multiples of 8 */
    xmm1=_mm_setzero_si128();
    xmm2=_mm_setzero_si128();

    for (;p1<a1+n;p1+=8,p2+=8,q+=8) {
        MULADD_INT16(xmm1,p1,q);
        MULADD_INT16(xmm2,p2,q);
    }
    SUM_INT32(d1[0],xmm1);
    SUM_INT32(d2[0],xmm2);

#else
    d1[0]=d2[0]=0.0;

    for (;p1<a1+n;p1++,p2++,q++) {
        d1[0]+=(*p1)*(*q);
        d2[0]+=(*p2)*(*q);
    }
#endif
}
/* dot products: d1={dot(a1,b1),dot(a1,b2)},d2={dot(a2,b1),dot(a2,b2)} ---------
* args   : short  *a1       I   input short array
*          short  *a2       I   input short array
*          short  *b1       I   input short array
*          short  *b2       I   input short array
*          int    n         I   number of input data
*          short  *d1       O   output short array
*          short  *d2       O   output short array
* return : none
*-----------------------------------------------------------------------------*/
extern void dot_22(const short *a1, const short *a2, const short *b1,
                   const short *b2, int n, double *d1, double *d2)
{
    const short *p1=a1,*p2=a2,*q1=b1,*q2=b2;

#if defined(AVX2_ENABLE)
    __m256i xmm1,xmm2,xmm3,xmm4;

    n=16*(int)ceil((double)n/16); /* modification to multiples of 16 */
    xmm1=_mm256_setzero_si256();
    xmm2=_mm256_setzero_si256();
    xmm3=_mm256_setzero_si256();
    xmm4=_mm256_setzero_si256();

    for (;p1<a1+n;p1+=16,p2+=16,q1+=16,q2+=16) {
        MULADD_INT16_AVX(xmm1,p1,q1);
        MULADD_INT16_AVX(xmm2,p1,q2);
        MULADD_INT16_AVX(xmm3,p2,q1);
        MULADD_INT16_AVX(xmm4,p2,q2);
    }
    SUM_INT32_AVX(d1[0],xmm1);
    SUM_INT32_AVX(d1[1],xmm2);
    SUM_INT32_AVX(d2[0],xmm3);
    SUM_INT32_AVX(d2[1],xmm4);

#elif defined(SSE2_ENABLE)
    __m128i xmm1,xmm2,xmm3,xmm4;

    n=8*(int)ceil((double)n/8); /* modification to multiples of 8 */
    xmm1=_mm_setzero_si128();
    xmm2=_mm_setzero_si128();
    xmm3=_mm_setzero_si128();
    xmm4=_mm_setzero_si128();

    for (;p1<a1+n;p1+=8,p2+=8,q1+=8,q2+=8) {
        MULADD_INT16(xmm1,p1,q1);
        MULADD_INT16(xmm2,p1,q2);
        MULADD_INT16(xmm3,p2,q1);
        MULADD_INT16(xmm4,p2,q2);
    }
    SUM_INT32(d1[0],xmm1);
    SUM_INT32(d1[1],xmm2);
    SUM_INT32(d2[0],xmm3);
    SUM_INT32(d2[1],xmm4);

#else
    d1[0]=d1[1]=d2[0]=d2[1]=0.0;

    for (;p1<a1+n;p1++,p2++,q1++,q2++) {
        d1[0]+=(*p1)*(*q1);
        d1[1]+=(*p1)*(*q2);
        d2[0]+=(*p2)*(*q1);
        d2[1]+=(*p2)*(*q2);
    }
#endif
}
/* dot products: d1={dot(a1,b1),dot(a1,b2),dot(a1,b3)},d2={...} ----------------
* args   : short  *a1       I   input short array
*          short  *a2       I   input short array
*          short  *b1       I   input short array
*          short  *b2       I   input short array
*          short  *b3       I   input short array
*          int    n         I   number of input data
*          short  *d1       O   output short array
*          short  *d2       O   output short array
* return : none
*-----------------------------------------------------------------------------*/
extern void dot_23(const short *a1, const short *a2, const short *b1,
                   const short *b2, const short *b3, int n, double *d1,
                   double *d2)
{
    const short *p1=a1,*p2=a2,*q1=b1,*q2=b2,*q3=b3;

#if defined(AVX2_ENABLE)
    __m256i xmm1,xmm2,xmm3,xmm4,xmm5,xmm6;

    n=16*(int)ceil((double)n/16); /* modification to multiples of 16 */
    xmm1=_mm256_setzero_si256();
    xmm2=_mm256_setzero_si256();
    xmm3=_mm256_setzero_si256();
    xmm4=_mm256_setzero_si256();
    xmm5=_mm256_setzero_si256();
    xmm6=_mm256_setzero_si256();

    for (;p1<a1+n;p1+=16,p2+=16,q1+=16,q2+=16,q3+=16) {
        MULADD_INT16_AVX(xmm1,p1,q1);
        MULADD_INT16_AVX(xmm2,p1,q2);
        MULADD_INT16_AVX(xmm3,p1,q3);
        MULADD_INT16_AVX(xmm4,p2,q1);
        MULADD_INT16_AVX(xmm5,p2,q2);
        MULADD_INT16_AVX(xmm6,p2,q3);
    }
    SUM_INT32_AVX(d1[0],xmm1);
    SUM_INT32_AVX(d1[1],xmm2);
    SUM_INT32_AVX(d1[2],xmm3);
    SUM_INT32_AVX(d2[0],xmm4);
    SUM_INT32_AVX(d2[1],xmm5);
    SUM_INT32_AVX(d2[2],xmm6);

#elif defined(SSE2_ENABLE)
    __m128i xmm1,xmm2,xmm3,xmm4,xmm5,xmm6;

    n=8*(int)ceil((double)n/8); /* modification to multiples of 8 */
    xmm1=_mm_setzero_si128();
    xmm2=_mm_setzero_si128();
    xmm3=_mm_setzero_si128();
    xmm4=_mm_setzero_si128();
    xmm5=_mm_setzero_si128();
    xmm6=_mm_setzero_si128();

    for (;p1<a1+n;p1+=8,p2+=8,q1+=8,q2+=8,q3+=8) {
        MULADD_INT16(xmm1,p1,q1);
        MULADD_INT16(xmm2,p1,q2);
        MULADD_INT16(xmm3,p1,q3);
        MULADD_INT16(xmm4,p2,q1);
        MULADD_INT16(xmm5,p2,q2);
        MULADD_INT16(xmm6,p2,q3);
    }
    SUM_INT32(d1[0],xmm1);
    SUM_INT32(d1[1],xmm2);
    SUM_INT32(d1[2],xmm3);
    SUM_INT32(d2[0],xmm4);
    SUM_INT32(d2[1],xmm5);
    SUM_INT32(d2[2],xmm6);

#else
    d1[0]=d1[1]=d1[2]=d2[0]=d2[1]=d2[2]=0.0;

    for (;p1<a1+n;p1++,p2++,q1++,q2++,q3++) {
        d1[0]+=(*p1)*(*q1);
        d1[1]+=(*p1)*(*q2);
        d1[2]+=(*p1)*(*q3);
        d2[0]+=(*p2)*(*q1);
        d2[1]+=(*p2)*(*q2);
        d2[2]+=(*p2)*(*q3);
    }
#endif
}
/* multiply char/short vectors -------------------------------------------------
* multiply char/short vectors: out=data1.*data2
* args   : char   *data1    I   input char array
*          short  *data2    I   input short array
*          int    n         I   number of input data
*          short  *out      O   output short array
* return : none
*-----------------------------------------------------------------------------*/
extern void mulvcs(const char *data1, const short *data2, int n, short *out)
{
    int i;
    for (i=0;i<n;i++) out[i]=data1[i]*data2[i];
}
/* sum float vectors -----------------------------------------------------------
* sum float vectors: out=data1.+data2
* args   : float  *data1    I   input float array
*          float  *data2    I   input float array
*          int    n         I   number of input data
*          float  *out      O   output float array
* return : none
* note   : AVX command is used if "AVX" is defined
*-----------------------------------------------------------------------------*/
extern void sumvf(const float *data1, const float *data2, int n, float *out)
{
    int i;
#if !defined(AVX_ENABLE)
    for (i=0;i<n;i++) out[i]=data1[i]+data2[i];
#else
    int m=n/8;
    __m256 xmm1,xmm2,xmm3;

    if (n<8) {
        for (i=0;i<n;i++) out[i]=data1[i]+data2[i];
    }
    else {
        for (i=0;i<8*m;i+=8) {
            xmm1=_mm256_loadu_ps(&data1[i]);
            xmm2=_mm256_loadu_ps(&data2[i]);
            xmm3=_mm256_add_ps(xmm1,xmm2);
            _mm256_storeu_ps(&out[i],xmm3);
        }
        for (;i<n;i++)  out[i]=data1[i]+data2[i];
    }
#endif
}
/* sum double vectors ----------------------------------------------------------
* sum double vectors: out=data1.+data2
* args   : double *data1    I   input double array
*          double *data2    I   input double array
*          int    n         I   number of input data
*          double *out      O   output double array
* return : none
* note   : AVX command is used if "AVX" is defined
*-----------------------------------------------------------------------------*/
extern void sumvd(const double *data1, const double *data2, int n, double *out)
{
    int i;
#if !defined(AVX_ENABLE)
    for (i=0;i<n;i++) out[i]=data1[i]+data2[i];
#else
    int m=n/4;
    __m256d xmm1,xmm2,xmm3;

    if (n<8) {
        for (i=0;i<n;i++) out[i]=data1[i]+data2[i];
    }
    else {
        for (i=0;i<4*m;i+=4) {
            xmm1=_mm256_loadu_pd(&data1[i]);
            xmm2=_mm256_loadu_pd(&data2[i]);
            xmm3=_mm256_add_pd(xmm1,xmm2);
            _mm256_storeu_pd(&out[i],xmm3);
        }
        for (;i<n;i++)  out[i]=data1[i]+data2[i];
    }
#endif
}
/* maximum value and index (int array) -----------------------------------------
* calculate maximum value and index
* args   : double *data     I   input int array
*          int    n         I   number of input data
*          int    exinds    I   exception index (start)
*          int    exinde    I   exception index (end)
*          int    *ind      O   index at maximum value
* return : int                  maximum value
* note   : maximum value and index are calculated without exinds-exinde index
*          exinds=exinde=-1: use all data
*-----------------------------------------------------------------------------*/
extern int maxvi(const int *data, int n, int exinds, int exinde, int *ind)
{
    int i;
    int max=data[0];
    *ind=0;
    for(i=1;i<n;i++) {
        if ((exinds<=exinde&&(i<exinds||i>exinde))||
            (exinds> exinde&&(i<exinds&&i>exinde))) {
                if (max<data[i]) {
                    max=data[i];
                    *ind=i;
                }
        }
    }
    return max;
}
/* maximum value and index (float array) ---------------------------------------
* calculate maximum value and index
* args   : float  *data     I   input float array
*          int    n         I   number of input data
*          int    exinds    I   exception index (start)
*          int    exinde    I   exception index (end)
*          int    *ind      O   index at maximum value
* return : float                maximum value
* note   : maximum value and index are calculated without exinds-exinde index
*          exinds=exinde=-1: use all data
*-----------------------------------------------------------------------------*/
extern float maxvf(const float *data, int n, int exinds, int exinde, int *ind)
{
    int i;
    float max=data[0];
    *ind=0;
    for(i=1;i<n;i++) {
        if ((exinds<=exinde&&(i<exinds||i>exinde))||
            (exinds> exinde&&(i<exinds&&i>exinde))) {
                if (max<data[i]) {
                    max=data[i];
                    *ind=i;
                }
        }
    }
    return max;
}
/* maximum value and index (double array) --------------------------------------
* calculate maximum value and index
* args   : double *data     I   input double array
*          int    n         I   number of input data
*          int    exinds    I   exception index (start)
*          int    exinde    I   exception index (end)
*          int    *ind      O   index at maximum value
* return : double               maximum value
* note   : maximum value and index are calculated without exinds-exinde index
*          exinds=exinde=-1: use all data
*-----------------------------------------------------------------------------*/
extern double maxvd(const double *data, int n, int exinds, int exinde, int *ind)
{
    int i;
    double max=data[0];
    *ind=0;
    for(i=1;i<n;i++) {
        if ((exinds<=exinde&&(i<exinds||i>exinde))||
            (exinds> exinde&&(i<exinds&&i>exinde))) {
                if (max<data[i]) {
                    max=data[i];
                    *ind=i;
                }
        }
    }
    return max;
}
/* mean value (double array) ---------------------------------------------------
* calculate mean value
* args   : double *data     I   input double array
*          int    n         I   number of input data
*          int    exinds    I   exception index (start)
*          int    exinde    I   exception index (end)
* return : double               mean value
* note   : mean value is calculated without exinds-exinde index
*          exinds=exinde=-1: use all data
*-----------------------------------------------------------------------------*/
extern double meanvd(const double *data, int n, int exinds, int exinde)
{
    int i,ne=0;
    double mean=0.0;
    for(i=0;i<n;i++) {
        if ((exinds<=exinde)&&(i<exinds||i>exinde)) mean+=data[i];
        else if ((exinds>exinde)&&(i<exinds&&i>exinde)) mean+=data[i];
        else ne++;
    }
    return mean/(n-ne);
}
/* 1D interpolation ------------------------------------------------------------
* interpolation of 1D data
* args   : double *x,*y     I   x and y data array
*          int    n         I   number of input data
*          double t         I   interpolation point on x data
* return : double               interpolated y data at t
*-----------------------------------------------------------------------------*/
extern double interp1(double *x, double *y, int n, double t)
{
    int i,j,k,m;
    double z,s,*xx,*yy;
    z=0.0;
    if(n<1) return(z);
    if(n==1) {z=y[0];return(z);}
    if(n==2) {
        z=(y[0]*(t-x[1])-y[1]*(t-x[0]))/(x[0]-x[1]);
        return(z);
    }

    xx=(double*)malloc(sizeof(double)*n);
    yy=(double*)malloc(sizeof(double)*n);
    if (x[0]>x[n-1]) {
        for (j=n-1,k=0;j>=0;j--,k++) {
            xx[k]=x[j];
            yy[k]=y[j];
        }
    } else {
        memcpy(xx,x,sizeof(double)*n);
        memcpy(yy,y,sizeof(double)*n);
    }

    if(t<=xx[1]) {k=0;m=2;}
    else if(t>=xx[n-2]) {k=n-3;m=n-1;}
    else {
        k=1;m=n;
        while (m-k!=1) {
            i=(k+m)/2;
            if (t<xx[i-1]) m=i;
            else k=i;
        }
        k=k-1; m=m-1;
        if(fabs(t-xx[k])<fabs(t-xx[m])) k=k-1;
        else m=m+1;
    }
    z=0.0;
    for (i=k;i<=m;i++) {
        s=1.0;
        for (j=k;j<=m;j++)
            if (j!=i) s=s*(t-xx[j])/(xx[i]-xx[j]);
        z=z+s*yy[i];
    }

    free(xx); free(yy);
    return z;
}
/* convert uint64_t to double --------------------------------------------------
* convert uint64_t array to double array (subtract base value)
* args   : uint64_t *data   I   input uint64_t array
*          uint64_t base    I   base value
*          int    n         I   number of input data
*          double *out      O   output double array
* return : none
*-----------------------------------------------------------------------------*/
extern void uint64todouble(uint64_t *data, uint64_t base, int n, double *out)
{
    int i;
    for (i=0;i<n;i++) out[i]=(double)(data[i]-base);
}
/* index to subscribe ----------------------------------------------------------
* 1D index to subscribe (index of 2D array)
* args   : int    *ind      I   input data
*          int    nx, ny    I   number of row and column
*          int    *subx     O   subscript index of x
*          int    *suby     O   subscript index of y
* return : none
*-----------------------------------------------------------------------------*/
extern void ind2sub(int ind, int nx, int ny, int *subx, int *suby)
{
    *subx = ind%nx;
    *suby = ny*ind/(nx*ny);
}
/* vector shift function  ------------------------------------------------------
* shift of vector data
* args   : void   *dst      O   output shifted data
*          void   *src      I   input data
*          size_t size      I   type of input data (byte)
*          int    n         I   number of input data
* return : none
*-----------------------------------------------------------------------------*/
extern void shiftdata(void *dst, void *src, size_t size, int n)
{
    void *tmp;
    tmp=malloc(size*n);
    if (tmp!=NULL) {
        memcpy(tmp,src,size*n);
        memcpy(dst,tmp,size*n);
        free(tmp);
    }
}
/* resample code ---------------------------------------------------------------
* resample code
* args   : char   *code     I   code
*          int    len       I   code length (len < 2^(31-FPBIT))
*          double coff      I   initial code offset (chip)
*          int    smax      I   maximum correlator space (sample) 
*          double ci        I   code sampling interval (chip)
*          int    n         I   number of samples
*          short  *rcode    O   resampling code
* return : double               code remainder
*-----------------------------------------------------------------------------*/
extern double rescode(const short *code, int len, double coff, int smax, 
                      double ci, int n, short *rcode)
{
    short *p;

#if !defined(SSE2_ENABLE)
    coff-=smax*ci;
    coff-=floor(coff/len)*len; /* 0<=coff<len */

    for (p=rcode;p<rcode+n+2*smax;p++,coff+=ci) {
        if (coff>=len) coff-=len;
        *p=code[(int)coff];
    }
    return coff-smax*ci;

#else
    int i,index[4],x[4],nbit,scale;
    __m128i xmm1,xmm2,xmm3,xmm4,xmm5;

    coff-=smax*ci;
    coff-=floor(coff/len)*len; /* 0<=coff<len */

    for (i=len,nbit=31;i;i>>=1,nbit--) ;
    nbit-=1;
    scale=1<<nbit; /* scale factor */

    for (i=0;i<4;i++,coff+=ci) {
        x[i]=(int)(coff*scale+0.5);
    }
    xmm1=_mm_loadu_si128((__m128i *)x);
    xmm2=_mm_set1_epi32(len*scale-1);
    xmm3=_mm_set1_epi32(len*scale);
    xmm4=_mm_set1_epi32((int)(ci*4*scale+0.5));

    for (p=rcode;p<rcode+n+2*smax;p+=4) {

        xmm5=_mm_cmpgt_epi32(xmm1,xmm2);
        xmm5=_mm_and_si128(xmm5,xmm3);
        xmm1=_mm_sub_epi32(xmm1,xmm5);
        xmm5=_mm_srai_epi32(xmm1,nbit);
        _mm_storeu_si128((__m128i *)index,xmm5);
        p[0]=code[index[0]];
        p[1]=code[index[1]];
        p[2]=code[index[2]];
        p[3]=code[index[3]];
        xmm1=_mm_add_epi32(xmm1,xmm4);
    }
    coff+=ci*(n+2*smax)-4*ci;
    coff-=floor(coff/len)*len;
    return coff-smax*ci;
#endif
}
/* mix local carrier -----------------------------------------------------------
* mix local carrier to data
* args   : char   *data     I   data
*          int    dtype     I   data type (0:real,1:complex)
*          double ti        I   sampling interval (s)
*          int    n         I   number of samples
*          double freq      I   carrier frequency (Hz)
*          double phi0      I   initial phase (rad)
*          short  *I,*Q     O   carrier mixed data I, Q component
* return : double               phase remainder
*-----------------------------------------------------------------------------*/
extern double mixcarr(const char *data, int dtype, double ti, int n, 
                      double freq, double phi0, short *II, short *QQ)
{
    const char *p;
    double phi,ps,prem;

#if !defined(SSE2_ENABLE)
    static short cost[CDIV]={0},sint[CDIV]={0};
    int i,index;

    /* initialize local carrier table */
    if (!cost[0]) { 
        for (i=0;i<CDIV;i++) {
            cost[i]=(short)floor((cos(DPI/CDIV*i)/CSCALE+0.5));
            sint[i]=(short)floor((sin(DPI/CDIV*i)/CSCALE+0.5));
        }
    }
    phi=phi0*CDIV/DPI;
    ps=freq*CDIV*ti; /* phase step */

    if (dtype==DTYPEIQ) { /* complex */
        for (p=data;p<data+n*2;p+=2,II++,QQ++,phi+=ps) {
            index=((int)phi)&CMASK;
            *II=cost[index]*p[0]-sint[index]*p[1];
            *QQ=sint[index]*p[0]+cost[index]*p[1];
        }
    }
    if (dtype==DTYPEI) { /* real */
        for (p=data;p<data+n;p++,II++,QQ++,phi+=ps) {
            index=((int)phi)&CMASK;
            *II=cost[index]*p[0];
            *QQ=sint[index]*p[0];
        }
    }
    prem=phi*DPI/CDIV;
    while(prem>DPI) prem-=DPI;
    return prem;
#else
    static char cost[16]={0},sint[16]={0};
    short I1[16]={0},I2[16]={0},Q1[16]={0},Q2[16]={0};
    int i;
    __m128d xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8,xmm9;
    __m128i dat1,dat2,dat3,dat4,ind1,ind2,xcos,xsin;
    __m128i zero=_mm_setzero_si128();
    __m128i mask4=_mm_set1_epi32(15);
    __m128i mask8=_mm_set1_epi16(255);

    if (!cost[0]) {
        for (i=0;i<16;i++) {
            cost[i]=(char)floor((cos(DPI/16*i)/CSCALE+0.5));
            sint[i]=(char)floor((sin(DPI/16*i)/CSCALE+0.5));
        }
    }
    phi=phi0/DPI*16-floor(phi0/DPI)*16;
    ps=freq*16*ti;
    xmm1=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm2=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm3=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm4=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm5=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm6=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm7=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm8=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm9=_mm_set1_pd(ps*16);
    xcos=_mm_loadu_si128((__m128i *)cost);
    xsin=_mm_loadu_si128((__m128i *)sint);

    if (dtype==DTYPEIQ) { /* complex */
        for (p=data;p<data+n*2;p+=32,II+=16,QQ+=16) {
            LOAD_INT8C(dat1,dat2,p   ,zero,mask8);
            LOAD_INT8C(dat3,dat4,p+16,zero,mask8);

            DBLTOINT16(ind1,xmm1,xmm2,xmm3,xmm4,mask4);
            DBLTOINT16(ind2,xmm5,xmm6,xmm7,xmm8,mask4);
            ind1=_mm_packus_epi16(ind1,ind2);
            MIX_INT8(I1,dat1,dat3,xcos,ind1,zero);
            MIX_INT8(I2,dat1,dat3,xsin,ind1,zero);
            MIX_INT8(Q1,dat2,dat4,xsin,ind1,zero);
            MIX_INT8(Q2,dat2,dat4,xcos,ind1,zero);
            for (i=0;i<16;i++) {
                II[i]=I1[i]-Q1[i];
                QQ[i]=I2[i]+Q2[i];
            }
            xmm1=_mm_add_pd(xmm1,xmm9);
            xmm2=_mm_add_pd(xmm2,xmm9);
            xmm3=_mm_add_pd(xmm3,xmm9);
            xmm4=_mm_add_pd(xmm4,xmm9);
            xmm5=_mm_add_pd(xmm5,xmm9);
            xmm6=_mm_add_pd(xmm6,xmm9);
            xmm7=_mm_add_pd(xmm7,xmm9);
            xmm8=_mm_add_pd(xmm8,xmm9);
        }
    }
    if (dtype==DTYPEI) { /* real */
        for (p=data;p<data+n;p+=16,II+=16,QQ+=16) {
            LOAD_INT8(dat1,dat2,p,zero);

            DBLTOINT16(ind1,xmm1,xmm2,xmm3,xmm4,mask4);
            DBLTOINT16(ind2,xmm5,xmm6,xmm7,xmm8,mask4);
            ind1=_mm_packus_epi16(ind1,ind2);
            MIX_INT8(II,dat1,dat2,xcos,ind1,zero);
            MIX_INT8(QQ,dat1,dat2,xsin,ind1,zero);
            xmm1=_mm_add_pd(xmm1,xmm9);
            xmm2=_mm_add_pd(xmm2,xmm9);
            xmm3=_mm_add_pd(xmm3,xmm9);
            xmm4=_mm_add_pd(xmm4,xmm9);
            xmm5=_mm_add_pd(xmm5,xmm9);
            xmm6=_mm_add_pd(xmm6,xmm9);
            xmm7=_mm_add_pd(xmm7,xmm9);
            xmm8=_mm_add_pd(xmm8,xmm9);
        }
    }
    prem=phi0+freq*ti*n*DPI;
    while(prem>DPI) prem-=DPI;
    return prem;
#endif
}
/* correlator ------------------------------------------------------------------
* multiply sampling data and carrier (I/Q), multiply code (E/P/L), and integrate
* args   : char   *data     I   sampling data vector (n x 1 or 2n x 1)
*          int    dtype     I   sampling data type (1:real,2:complex)
*          double ti        I   sampling interval (s)
*          int    n         I   number of samples
*          double freq      I   carrier frequency (Hz)
*          double phi0      I   carrier initial phase (rad)
*          double crate     I   code chip rate (chip/s)
*          double coff      I   code chip offset (chip)
*          int    s         I   correlator points (sample)
*          short  *I,*Q     O   correlation power I,Q
*                                 I={I_P,I_E1,I_L1,I_E2,I_L2,...,I_Em,I_Lm}
*                                 Q={Q_P,Q_E1,Q_L1,Q_E2,Q_L2,...,Q_Em,Q_Lm}
* return : none
* notes  : see above for data
*-----------------------------------------------------------------------------*/
extern void correlator(const char *data, int dtype, double ti, int n, 
                       double freq, double phi0, double crate, double coff, 
                       int* s, int ns, double *II, double *QQ, double *remc, 
                       double *remp, short* codein, int coden)
{
    short *dataI=NULL,*dataQ=NULL,*code_e=NULL,*code;
    int i;
    int smax=s[ns-1];

    /* 8 is treatment of remainder in SSE2 */
    if (!(dataI=(short *)sdrmalloc(sizeof(short)*(n+64)))|| 
        !(dataQ=(short *)sdrmalloc(sizeof(short)*(n+64)))|| 
        !(code_e=(short *)sdrmalloc(sizeof(short)*(n+2*smax)))) {
            SDRPRINTF("error: correlator memory allocation\n");
            return;
    }
    code=code_e+smax;

    /* mix local carrier */
    *remp=mixcarr(data,dtype,ti,n,freq,phi0,dataI,dataQ);

    /* resampling code */
    *remc=rescode(codein,coden,coff,smax,ti*crate,n,code_e);

    /* multiply code and integrate */
    dot_23(dataI,dataQ,code,code-s[0],code+s[0],n,II,QQ);
    for (i=1;i<ns;i++) {
        dot_22(dataI,dataQ,code-s[i],code+s[i],n,II+1+i*2,QQ+1+i*2);
    }
    for (i=0;i<1+2*ns;i++) {
        II[i]*=CSCALE;
        QQ[i]*=CSCALE;
    }
    sdrfree(dataI); sdrfree(dataQ); sdrfree(code_e);
    dataI=dataQ=code_e=NULL;
}
/* parallel correlator ---------------------------------------------------------
* fft based parallel correlator
* args   : char   *data     I   sampling data vector (n x 1 or 2n x 1)
*          int    dtype     I   sampling data type (1:real,2:complex)
*          double ti        I   sampling interval (s)
*          int    n         I   number of samples
*          double *freq     I   doppler search frequencies (Hz)
*          int    nfreq     I   number of frequencies
*          double crate     I   code chip rate (chip/s)
*          int    m         I   number of resampling data
*          cpx_t  codex     I   frequency domain code
*          double *P        O   normalized correlation power vector
* return : none
* notes  : P=abs(ifft(conj(fft(code)).*fft(data.*e^(2*pi*freq*t*i)))).^2
*-----------------------------------------------------------------------------*/
extern void pcorrelator(const char *data, int dtype, double ti, int n,
                        double *freq, int nfreq, double crate, int m,
                        cpx_t* codex, double *P)
{
    int i;
    cpx_t *datax;
    short *dataI,*dataQ;
    char *dataR;

    if (!(dataR=(char  *)sdrmalloc(sizeof(char )*m*dtype))||
        !(dataI=(short *)sdrmalloc(sizeof(short)*(m+64)))||
        !(dataQ=(short *)sdrmalloc(sizeof(short)*(m+64)))||
        !(datax=cpxmalloc(m))) {
            SDRPRINTF("error: pcorrelator memory allocation\n");
            return;
    }

    /* zero padding */
    memset(dataR,0,m*dtype); /* zero paddinng */
    memcpy(dataR,data,2*n*dtype); /* for zero padding FFT */

    for (i=0;i<nfreq;i++) {
        /* mix local carrier */
        mixcarr(dataR,dtype,ti,m,freq[i],0.0,dataI,dataQ);

        /* to complex */
        cpxcpx(dataI,dataQ,CSCALE/m,m,datax);

        /* convolution */
        cpxconv(NULL,NULL,datax,codex,m,n,1,&P[i*n]);
    }
    sdrfree(dataR);
    sdrfree(dataI);
    sdrfree(dataQ);
    cpxfree(datax);
}
