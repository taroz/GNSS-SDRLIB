/* User include file for libfec
 * Copyright 2004, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */

#ifndef _FEC_H_
#define _FEC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* r=1/2 k=7 convolutional encoder polynomials */
#define	V27POLYA	0x4f
#define	V27POLYB	0x6d

void *create_viterbi27(int len);
void set_viterbi27_polynomial(int polys[2]);
int init_viterbi27(void *vp,int starting_state);
int update_viterbi27_blk(void *vp,unsigned char sym[],int npairs);
int chainback_viterbi27(void *vp, unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi27(void *vp);

#ifdef __VEC__
void *create_viterbi27_av(int len);
void set_viterbi27_polynomial_av(int polys[2]);
int init_viterbi27_av(void *p,int starting_state);
int chainback_viterbi27_av(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi27_av(void *p);
int update_viterbi27_blk_av(void *p,unsigned char *syms,int nbits);
#endif

#ifdef __i386__
void *create_viterbi27_mmx(int len);
void set_viterbi27_polynomial_mmx(int polys[2]);
int init_viterbi27_mmx(void *p,int starting_state);
int chainback_viterbi27_mmx(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi27_mmx(void *p);
int update_viterbi27_blk_mmx(void *p,unsigned char *syms,int nbits);

void *create_viterbi27_sse(int len);
void set_viterbi27_polynomial_sse(int polys[2]);
int init_viterbi27_sse(void *p,int starting_state);
int chainback_viterbi27_sse(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi27_sse(void *p);
int update_viterbi27_blk_sse(void *p,unsigned char *syms,int nbits);

void *create_viterbi27_sse2(int len);
void set_viterbi27_polynomial_sse2(int polys[2]);
int init_viterbi27_sse2(void *p,int starting_state);
int chainback_viterbi27_sse2(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi27_sse2(void *p);
int update_viterbi27_blk_sse2(void *p,unsigned char *syms,int nbits);
#endif

void *create_viterbi27_port(int len);
void set_viterbi27_polynomial_port(int polys[2]);
int init_viterbi27_port(void *p,int starting_state);
int chainback_viterbi27_port(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi27_port(void *p);
int update_viterbi27_blk_port(void *p,unsigned char *syms,int nbits);

/* r=1/2 k=9 convolutional encoder polynomials */
#define	V29POLYA	0x1af
#define	V29POLYB	0x11d

void *create_viterbi29(int len);
void set_viterbi29_polynomial(int polys[2]);
int init_viterbi29(void *vp,int starting_state);
int update_viterbi29_blk(void *vp,unsigned char syms[],int nbits);
int chainback_viterbi29(void *vp, unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi29(void *vp);

#ifdef __VEC__
void *create_viterbi29_av(int len);
void set_viterbi29_polynomial_av(int polys[2]);
int init_viterbi29_av(void *p,int starting_state);
int chainback_viterbi29_av(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi29_av(void *p);
int update_viterbi29_blk_av(void *p,unsigned char *syms,int nbits);
#endif

#ifdef __i386__
void *create_viterbi29_mmx(int len);
void set_viterbi29_polynomial_mmx(int polys[2]);
int init_viterbi29_mmx(void *p,int starting_state);
int chainback_viterbi29_mmx(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi29_mmx(void *p);
int update_viterbi29_blk_mmx(void *p,unsigned char *syms,int nbits);

void *create_viterbi29_sse(int len);
void set_viterbi29_polynomial_sse(int polys[2]);
int init_viterbi29_sse(void *p,int starting_state);
int chainback_viterbi29_sse(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi29_sse(void *p);
int update_viterbi29_blk_sse(void *p,unsigned char *syms,int nbits);

void *create_viterbi29_sse2(int len);
void set_viterbi29_polynomial_sse2(int polys[2]);
int init_viterbi29_sse2(void *p,int starting_state);
int chainback_viterbi29_sse2(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi29_sse2(void *p);
int update_viterbi29_blk_sse2(void *p,unsigned char *syms,int nbits);
#endif

void *create_viterbi29_port(int len);
void set_viterbi29_polynomial_port(int polys[2]);
int init_viterbi29_port(void *p,int starting_state);
int chainback_viterbi29_port(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi29_port(void *p);
int update_viterbi29_blk_port(void *p,unsigned char *syms,int nbits);

/* r=1/3 k=9 convolutional encoder polynomials */
#define	V39POLYA	0x1ed
#define	V39POLYB	0x19b
#define	V39POLYC	0x127

void *create_viterbi39(int len);
void set_viterbi39_polynomial(int polys[3]);
int init_viterbi39(void *vp,int starting_state);
int update_viterbi39_blk(void *vp,unsigned char syms[],int nbits);
int chainback_viterbi39(void *vp, unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi39(void *vp);

#ifdef __VEC__
void *create_viterbi39_av(int len);
void set_viterbi39_polynomial_av(int polys[3]);
int init_viterbi39_av(void *p,int starting_state);
int chainback_viterbi39_av(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi39_av(void *p);
int update_viterbi39_blk_av(void *p,unsigned char *syms,int nbits);
#endif

#ifdef __i386__
void *create_viterbi39_mmx(int len);
void set_viterbi39_polynomial_mmx(int polys[3]);
int init_viterbi39_mmx(void *p,int starting_state);
int chainback_viterbi39_mmx(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi39_mmx(void *p);
int update_viterbi39_blk_mmx(void *p,unsigned char *syms,int nbits);

void *create_viterbi39_sse(int len);
void set_viterbi39_polynomial_sse(int polys[3]);
int init_viterbi39_sse(void *p,int starting_state);
int chainback_viterbi39_sse(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi39_sse(void *p);
int update_viterbi39_blk_sse(void *p,unsigned char *syms,int nbits);

void *create_viterbi39_sse2(int len);
void set_viterbi39_polynomial_sse2(int polys[3]);
int init_viterbi39_sse2(void *p,int starting_state);
int chainback_viterbi39_sse2(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi39_sse2(void *p);
int update_viterbi39_blk_sse2(void *p,unsigned char *syms,int nbits);
#endif

void *create_viterbi39_port(int len);
void set_viterbi39_polynomial_port(int polys[3]);
int init_viterbi39_port(void *p,int starting_state);
int chainback_viterbi39_port(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi39_port(void *p);
int update_viterbi39_blk_port(void *p,unsigned char *syms,int nbits);


/* r=1/6 k=15 Cassini convolutional encoder polynomials without symbol inversion
 * dfree = 56
 * These bits may be left-right flipped from some textbook representations;
 * here I have the bits entering the shift register from the right (low) end
 *
 * Some other spacecraft use the same code, but with the polynomials in a different order.
 * E.g., Mars Pathfinder and STEREO swap POLYC and POLYD. All use alternate symbol inversion,
 * so use set_viterbi615_polynomial() as appropriate.
 */
#define	V615POLYA	042631
#define	V615POLYB	047245
#define V615POLYC       056507
#define V615POLYD       073363
#define V615POLYE       077267
#define V615POLYF       064537

void *create_viterbi615(int len);
void set_viterbi615_polynomial(int polys[6]);
int init_viterbi615(void *vp,int starting_state);
int update_viterbi615_blk(void *vp,unsigned char *syms,int nbits);
int chainback_viterbi615(void *vp, unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi615(void *vp);

#ifdef __VEC__
void *create_viterbi615_av(int len);
void set_viterbi615_polynomial_av(int polys[6]);
int init_viterbi615_av(void *p,int starting_state);
int chainback_viterbi615_av(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi615_av(void *p);
int update_viterbi615_blk_av(void *p,unsigned char *syms,int nbits);
#endif

#ifdef __i386__
void *create_viterbi615_mmx(int len);
void set_viterbi615_polynomial_mmx(int polys[6]);
int init_viterbi615_mmx(void *p,int starting_state);
int chainback_viterbi615_mmx(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi615_mmx(void *p);
int update_viterbi615_blk_mmx(void *p,unsigned char *syms,int nbits);

void *create_viterbi615_sse(int len);
void set_viterbi615_polynomial_sse(int polys[6]);
int init_viterbi615_sse(void *p,int starting_state);
int chainback_viterbi615_sse(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi615_sse(void *p);
int update_viterbi615_blk_sse(void *p,unsigned char *syms,int nbits);

void *create_viterbi615_sse2(int len);
void set_viterbi615_polynomial_sse2(int polys[6]);
int init_viterbi615_sse2(void *p,int starting_state);
int chainback_viterbi615_sse2(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi615_sse2(void *p);
int update_viterbi615_blk_sse2(void *p,unsigned char *syms,int nbits);

#endif

void *create_viterbi615_port(int len);
void set_viterbi615_polynomial_port(int polys[6]);
int init_viterbi615_port(void *p,int starting_state);
int chainback_viterbi615_port(void *p,unsigned char *data,unsigned int nbits,unsigned int endstate);
void delete_viterbi615_port(void *p);
int update_viterbi615_blk_port(void *p,unsigned char *syms,int nbits);


/* General purpose RS codec, 8-bit symbols */
void encode_rs_char(void *rs,unsigned char *data,unsigned char *parity);
int decode_rs_char(void *rs,unsigned char *data,int *eras_pos,
		   int no_eras);
void *init_rs_char(int symsize,int gfpoly,
		   int fcr,int prim,int nroots,
		   int pad);
void free_rs_char(void *rs);

/* General purpose RS codec, integer symbols */
void encode_rs_int(void *rs,int *data,int *parity);
int decode_rs_int(void *rs,int *data,int *eras_pos,int no_eras);
void *init_rs_int(int symsize,int gfpoly,int fcr,
		  int prim,int nroots,int pad);
void free_rs_int(void *rs);

/* CCSDS standard (255,223) RS codec with conventional (*not* dual-basis)
 * symbol representation
 */
void encode_rs_8(unsigned char *data,unsigned char *parity,int pad);
int decode_rs_8(unsigned char *data,int *eras_pos,int no_eras,int pad);

/* CCSDS standard (255,223) RS codec with dual-basis symbol representation */
void encode_rs_ccsds(unsigned char *data,unsigned char *parity,int pad);
int decode_rs_ccsds(unsigned char *data,int *eras_pos,int no_eras,int pad);

/* Tables to map from conventional->dual (Taltab) and
 * dual->conventional (Tal1tab) bases
 */
extern unsigned char Taltab[],Tal1tab[];


/* CPU SIMD instruction set available */
enum Cpu_mode {UNKNOWN=0,PORT,MMX,SSE,SSE2_=4,ALTIVEC};
void find_cpu_mode(void); /* Call this once at startup to set Cpu_mode */

/* Determine parity of argument: 1 = odd, 0 = even */
#ifdef __i386__
static inline int parityb(unsigned char x){
  __asm__ __volatile__ ("test %1,%1;setpo %0" : "=q"(x) : "q" (x));
  return x;
}
#else
void partab_init();

//static int parityb(unsigned char x){
//  extern unsigned char Partab[256];
//  extern int P_init;
//  if(!P_init){
//    partab_init();
//  }
//  return Partab[x];
//}
#endif


//static int parity(int x){
//  /* Fold down to one byte */
//  x ^= (x >> 16);
//  x ^= (x >> 8);
//  return parityb(x);
//}

/* Useful utilities for simulation */
double normal_rand(double mean, double std_dev);
unsigned char addnoise(int sym,double amp,double gain,double offset,int clip);

extern int Bitcnt[];

/* Dot product functions */
void *initdp(signed short coeffs[],int len);
void freedp(void *dp);
long dotprod(void *dp,signed short a[]);

void *initdp_port(signed short coeffs[],int len);
void freedp_port(void *dp);
long dotprod_port(void *dp,signed short a[]);

#ifdef __i386__
void *initdp_mmx(signed short coeffs[],int len);
void freedp_mmx(void *dp);
long dotprod_mmx(void *dp,signed short a[]);

void *initdp_sse(signed short coeffs[],int len);
void freedp_sse(void *dp);
long dotprod_sse(void *dp,signed short a[]);

void *initdp_sse2(signed short coeffs[],int len);
void freedp_sse2(void *dp);
long dotprod_sse2(void *dp,signed short a[]);
#endif

#ifdef __VEC__
void *initdp_av(signed short coeffs[],int len);
void freedp_av(void *dp);
long dotprod_av(void *dp,signed short a[]);
#endif

/* Sum of squares - accepts signed shorts, produces unsigned long long */
unsigned long long sumsq(signed short *in,int cnt);
unsigned long long sumsq_port(signed short *in,int cnt);

#ifdef __i386__
unsigned long long sumsq_mmx(signed short *in,int cnt);
unsigned long long sumsq_sse(signed short *in,int cnt);
unsigned long long sumsq_sse2(signed short *in,int cnt);
#endif
#ifdef __VEC__
unsigned long long sumsq_av(signed short *in,int cnt);
#endif


/* Low-level data structures and routines */

int cpu_features(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif /* __cplusplus */

#endif /* _FEC_H_ */



