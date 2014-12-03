/*------------------------------------------------------------------------------
* stereo.h : NSL STEREO functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
* Copyright (C) 2012 Nottingham Scientific Limited
*-----------------------------------------------------------------------------*/
/* constants -----------------------------------------------------------------*/
/* sterei confugration file path */
#ifdef STEREOV26
#define STEREO_FW      ("./frontend/stereo/V26/stereo_fx2fw.ihx")
#define STEREO_FPGA    ("./frontend/stereo/V26/stereo_fpga.bin")
#define STEREO_FPGAREG ("./frontend/stereo/V26/stereo_fpga_regs.cfg")
#define STEREO_SYNTH   ("./frontend/stereo/V26/stereo_clksynth.cfg")
#define STEREO_ADC     ("./frontend/stereo/V26/stereo_adc.cfg")
#else
#define STEREO_FW      ("stereo_fx2fw.ihx")
#define STEREO_FPGA    ("stereo_fpga.bin")
#define STEREO_SYNTH   ("stereo_clksynth.cfg")
#define STEREO_ADC     ("stereo_adc.cfg")
#endif
#define STEREO_MAX2769_L1 ("max2769_l1.cfg")
#define STEREO_MAX2769_B1 ("max2769_b1.cfg")
#define STEREO_MAX2769_G1 ("max2769_g1.cfg")
#define STEREO_MAX2112_L1 ("max2112_l1.cfg")
#define STEREO_MAX2112_B1 ("max2112_b1.cfg")
#define STEREO_MAX2112_G1 ("max2112_g1.cfg")
#define STEREO_MAX2112_L2 ("max2112_l2.cfg")
#define STEREO_MAX2112_B2 ("max2112_b2.cfg")
#define STEREO_MAX2112_G2 ("max2112_g2.cfg")
#define STEREO_MAX2112_L5 ("max2112_l5.cfg")
#define STEREO_MAX2112_L6 ("max2112_l6.cfg")

#define MAX_FILENAME_LEN (256)

/* type definition -----------------------------------------------------------*/
typedef struct _max2769Conf_t {
    uint32_t confOne;
    uint32_t confTwo;
    uint32_t confThree;
    uint32_t pllConf;
    uint32_t nrDiv;
    uint32_t fDiv;
    uint32_t strm;
    uint32_t clk;
    uint32_t testOne;
    uint32_t testTwo;
} max2769Conf_t;

typedef struct _max2112Conf_t {
    uint8_t regValue[14];
} max2112Conf_t;

typedef struct _synthConf_t {
    uint32_t r[8];
    uint32_t r8, r9, r11, r13, r14, r15;
} synthConf_t;

typedef struct _adcConf_t {
    unsigned char uiReg[10];
} adcConf_t;

/* stereo.c ------------------------------------------------------------------*/
extern int stereo_init(void);
extern void stereo_quit(void);
extern int stereo_initoptions(void);
extern int stereo_initconf(void);
extern void stereo_exp(const uint8_t *buf, int n, int dtype, char *expbuf);
extern void stereo_getbuff(uint64_t buffloc, int n, int dtype, char *expbuf);
extern void stereo_pushtomembuf(void);
extern void fstereo_pushtomembuf(void);

/* STEREO library functions --------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


#ifdef STEREOV26 /* version 26 */

#ifdef WIN32
#define USB_BLK_SIZE (1 << 16) /* 64KBytes */
#define USB_NUM_BLKS (256) 
#else
#define USB_BLK_SIZE (1 << 14) /* 16KBytes */
#define USB_NUM_BLKS (256*2) 
#endif
#define INCREASE_FACTOR (1<<5) 
#define FPGA_REGS_CONF_SIZE 6 /**< Number of FPGA configuration registers */
#define FPGA_REGS_STAT_SIZE 8 /**< Number of FPGA status registers */


/**< Endpoint definition */
typedef enum {
    L1_EP, /**< L1 endpoint */
    LB_EP /**< LB endpoint, not in use - all transferred via L1_EP */
} endpoint_t;

/** Used bit type for configuration */
typedef unsigned char bit_t;

/** Configuration structure to LMK03033C. */
typedef struct _synth_t {
    double f_xo_l1; /**< Frequency of MAX2769 clock */
    double f_xo_lb; /**< Frequency of MAX2112 clock */
    double f_xo_adc;/**< Frequency of ADC clock */
    double f_xo_fpga;/**< Frequency of FPGA clock */
    double f_xo_in;/**< Frequency of synthesizer's input clock */
} synth_t;

/** Configuration structure to MAX2769. */
typedef struct _max2769_t {
    double f; /**< Carrier frequency */
    double f_if; /**< IF */
    double bw; /**< Bandwidth */
    bit_t anten; /**< Antenna voltage bias flag */
    bit_t fcenx; /**< Baseband/bandpass filter flag */
} max2769_t;

/** Configuration structure to MAX2112 */
typedef struct _max2112_t {
    double f; /**< Carrier frequency */
    double bw; /**< Bandwidth */
    uint32_t gain; /**< Digital gain */
} max2112_t;

/** Configuration and status structure to/from FPGA registers. */
typedef struct _fpga_t {
    /* Status data */
    int l1_ld; /**< Lock detect from MAX2769 */
    int syn_ld;/**< Lock detect from LMK03033C */
    int dipsw; /**< DIPSW read back */
    uint32_t exp_conn;/**< Expansion connector read back */
    /* Control and read-back data */
    int pwm_xo; /**< Oscillator enable read back */
    int clk_ext; /**< External/internal oscillator read back */
    int use_agc; /**< Use AGC read back */
    int duty; /**< Duty cycle of PWM gain read back */
    int out_mode; /**< Read back of output bit format */
    int exp_rd_wr_n; /**< Read/write flag (expansion connector) */
} fpga_t;

/** Configuration words to FPGA registers. */
typedef struct _fpgaConf_t {
    uint8_t regValue[FPGA_REGS_CONF_SIZE];
} fpgaConf_t;

/** Status and read-back words from FPGA registers. */
typedef struct _fpgaStat_t {
    uint8_t regValue[FPGA_REGS_STAT_SIZE];
} fpgaStat_t;

/** Stereo status data structure */
typedef struct {
    /* Configuration register and read-back structures */
    max2769Conf_t max2769Conf; /* MAX2769 configuration registers */
    max2112Conf_t max2112Conf; /* MAX2112 configuration registers */
    synthConf_t synthConf; /* LMK03033C clock synth. configuration registers*/
    adcConf_t adcConf; /* ADC configuration registers */
    fpgaConf_t fpgaConf; /* FPGA registers - configuration registers */ 
    fpgaStat_t fpgaStat; /* FPGA registers - status and read-back registers */
    /* Single parameter configuration structures */
    max2769_t max2769; /* MAX2769 - structure with changable parameters */
    max2112_t max2112; /* MAX2112 - structure with changable parameters */
    synth_t synth; /* LMK03033C - structure with changable parameters */
    synth_t synth_old; /* LMK03033C - old structure with changable parameters */
    fpga_t fpga_regs; /* FPGA register data */
} stereo_state_t; 

uint8_t STEREO_globalDataBuffer[USB_BLK_SIZE*USB_NUM_BLKS*INCREASE_FACTOR]; 
extern const uint32_t STEREO_PKT_SIZE;
extern const uint32_t STEREO_NUM_BLKS;
extern int STEREO_InitLibrary( void );
extern void STEREO_QuitLibrary( void );
extern char* STEREO_Perror( void );
extern void STEREO_UsbError( int err );
extern int STEREO_IsConfigured( void );
extern int STEREO_IsConnected( void );
extern int STEREO_ConnectEndPoint( endpoint_t ep, uint8_t* buf, int size );
extern int STEREO_ReapPacket(
    endpoint_t ep, 
    unsigned long int countPackets, 
    int timeOut );
extern void STEREO_DisconnectEndPoint( endpoint_t ep );
extern int STEREO_LoadFirmware( FILE *fid );
extern int STEREO_ConfigureMax2769(FILE *fid, max2769Conf_t *pResult);
extern void STEREO_FprintfMax2769Conf(max2769Conf_t *pResult);
extern int STEREO_ConfigureMax2769_Conf( max2769Conf_t *pConf);
extern int STEREO_GetConfMax2769(FILE *fid, max2769Conf_t *pResult);
extern void STEREO_FprintfMax2769Str(max2769_t *str);
extern int STEREO_UpdateMax2769Conf(
    max2769Conf_t *conf, 
    max2769_t *str, 
    double f_xo);
extern int STEREO_UpdateMax2769Str(
    max2769_t *str, 
    max2769Conf_t *conf, 
    double f_xo);
extern int STEREO_ConfigureMax2112(FILE *fid, max2112Conf_t *pResult);
extern void STEREO_FprintfMax2112Conf(max2112Conf_t *pResult);
extern int STEREO_ConfigureMax2112_Conf(max2112Conf_t *pConfResult );
extern int STEREO_GetConfMax2112(FILE* fid, max2112Conf_t *pConfResult);
extern void STEREO_FprintfMax2112Str(max2112_t *str);
extern int STEREO_UpdateMax2112Conf(
    max2112Conf_t *conf, 
    max2112_t *str, 
    double f_xo);
extern int STEREO_UpdateMax2112Str(
    max2112_t *str, 
    max2112Conf_t *conf, 
    double f_xo);
extern int  STEREO_SendFpga(uint8_t *bitArray, int length) ;
extern int  STEREO_ConfigureSynth(FILE *fid, synthConf_t *pConfResult);
extern int  STEREO_ConfigureSynth_Conf(synthConf_t *pConfResult);
extern int STEREO_GetConfSynth(FILE* fid, synthConf_t *pConfResult);
extern int STEREO_UpdateSynthConf(synthConf_t *conf, synth_t *str);
extern int STEREO_UpdateSynthStr(synth_t *str, synthConf_t *conf);
extern void STEREO_FprintfSynthConf(synthConf_t *conf);
extern void STEREO_FprintfSynthStr(synth_t *str);
extern int STEREO_ConfigureAdc( FILE* fid, adcConf_t *pConfResult );
extern void STEREO_FprintfAdcConf(adcConf_t *pResult);
extern int STEREO_SetFpgaRegs_Conf(fpgaConf_t *pConfResult );
extern int STEREO_GetFpgaRegs_Conf(fpgaStat_t *pConfResult );
extern void STEREO_FprintfFpgaRegs(fpgaStat_t *pResult);
extern int STEREO_ConfigureFpgaRegs( FILE* fid, fpgaConf_t *pConfResult );
extern int STEREO_GetConfFpgaRegs(FILE* fid, fpgaConf_t *pConfResult);
extern int STEREO_SetFpgaRegs_Conf(fpgaConf_t *pConfResult );
extern void STEREO_FprintfSetFpgaRegs(fpgaConf_t *pResult);
extern int STEREO_UpdateFpgaRegsConf(fpgaConf_t *conf, fpga_t *fpga);
extern int STEREO_UpdateFpgaRegsStr(fpga_t *fpga, fpgaConf_t *conf);

#else /* version 25(default) */

typedef unsigned char bit_t;

typedef struct _synth_t {
    double f_xo_l1;
    double f_xo_lb;
    double f_xo_adc;
    double f_xo_fpga;
    double f_xo_in;
} synth_t;

typedef struct _max2769_t {
    double f;
    double f_if;
    double bw;
    bit_t anten;
    bit_t fcenx;
} max2769_t;

typedef struct _max2112_t {
    double f;
    double bw;
    uint32_t gain;
} max2112_t;

extern const uint32_t STEREO_DATABUFF_SIZE;
extern uint8_t STEREO_dataBuffer[];

int STEREO_InitLibrary( void );
void STEREO_QuitLibrary( void );
char* STEREO_Perror( void );
void STEREO_LibusbError( int err );
int STEREO_LoadFirmware( FILE *fid );
int STEREO_IsConfigured( void );
int STEREO_IsConnected( void );
int STEREO_ConfigureMax2769(FILE *fid, max2769Conf_t *pResult);
int STEREO_ConfigureMax2769_Conf( max2769Conf_t *pConf);
int STEREO_GetConfMax2769(FILE *fid, max2769Conf_t *pResult);
void STEREO_FprintfMax2769Conf( FILE *fid, max2769Conf_t *pResult);
void STEREO_FprintfMax2769Str( FILE *fid, max2769_t *str);
int STEREO_UpdateMax2769Conf(max2769Conf_t *conf, max2769_t *str, double f_xo);
int STEREO_UpdateMax2769Str(max2769_t *str, max2769Conf_t *conf, double f_xo);
int STEREO_ConfigureMax2112(FILE *fid, max2112Conf_t *pResult);
int STEREO_ConfigureMax2112_Conf(max2112Conf_t *pConfResult );
int STEREO_GetConfMax2112(FILE* fid, max2112Conf_t *pConfResult);
void STEREO_FprintfMax2112Conf( FILE *fid, max2112Conf_t *pResult);
void STEREO_FprintfMax2112Str( FILE *fid, max2112_t *str);
int STEREO_UpdateMax2112Conf(max2112Conf_t *conf, max2112_t *str, double f_xo);
int STEREO_UpdateMax2112Str(max2112_t *str, max2112Conf_t *conf, double f_xo);
int  STEREO_SendFpga(uint8_t *bitArray, int length) ;
int STEREO_ConfigureSynth(FILE *fid, synthConf_t *pConfResult);
int  STEREO_ConfigureSynth_Conf(synthConf_t *pConfResult);
int STEREO_GetConfSynth(FILE* fid, synthConf_t *pConfResult);
int STEREO_UpdateSynthConf(synthConf_t *conf, synth_t *str);
int STEREO_UpdateSynthStr(synth_t *str, synthConf_t *conf);
void STEREO_FprintfSynthConf( FILE *fid, synthConf_t *conf);
void STEREO_FprintfSynthStr( FILE *fid, synth_t *str);
int STEREO_ConfigureAdc( FILE* fid, adcConf_t *pConfResult );
void STEREO_FprintfAdcConf( FILE *fid, adcConf_t *pResult);
int STEREO_GrabInit( void );
int STEREO_GrabStart( void );
int STEREO_RefillDataBuffer( void );
int STEREO_GrabStop( void );
void STEREO_GrabClean( void );
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


