#ifndef FX_2_DEV_H
#define FX_2_DEV_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "fusb.h"
#include "fusb_win32.h"

#define GN3S_AGC_BUFFSIZE 4*512
#define LOOPS 1024

#define RX_ENDPOINT 	0x86
#define TX_ENDPOINT 	0x02
#define AGC_ENDPOINT	0x84

#define VRT_VENDOR_IN 0xC0
#define VRT_VENDOR_OUT 0x40

#define RX_INTERFACE 2
#define TX_INTERFACE 1

#define TX_ALTINTERFACE 0
#define RX_ALTINTERFACE 0

// IN commands
#define VRQ_FLAGS 	    0x90
#define VRQ_GET_STATUS 	0x80
#define VRQ_GET_AGC     0x91
#define GS_TX_UNDERRUN 	0   	// wIndexL  // returns 1 byte
#define GS_RX_OVERRUN 	1   	// wIndexL  // returns 1 byte

// OUT commands
#define VRQ_XFER	0x01
#define VRQ_XFER_TX 0x02
#define VRQ_MODE	0x04
#define VRQ_AGC		0x08
#define VRQ_CMODE 	0x0F

typedef struct Fx2_c
{
    int interface_;
    int altinterface;
    usb_dev_handle *udev;
    fusb_ephandle *d_ephandle6;
    fusb_devhandle *d_devhandle;
} fx2_c;

class Fx2_dev
{
private:
    int fx2_vid[4];
    int fx2_pid[4];
    struct usb_device *fx2;
    bool fx2_AGC;
    int fx2_ret;
    int fx2_reg_agc;
    int fx2_port;
    Fx2_c *fx2_conf;
    char *agc_buf ;

public:
    Fx2_dev(void);
    Fx2_dev(int i);
    ~Fx2_dev();

    int usb_fx2_init(void);
    int usb_fx2_find(void);
    void print_configuration ( struct usb_config_descriptor *config );
    void print_altsetting ( struct usb_interface_descriptor *interface );
    void print_interface ( struct usb_interface *interface );
    short print_fifo_status ( char print );
    void  print_endpoint ( struct usb_endpoint_descriptor *endpoint );
    int write_cmd (int request, int value, int index, unsigned char *bytes, int len );
    bool _get_status ( int which, bool *trouble );
    bool check_rx_overrun (bool *overrun_p );
    bool usrp_xfer ( unsigned char VRQ_TYPE, unsigned char start );
    bool usrp_xfer2 (unsigned char VRQ_TYPE, unsigned char start, unsigned char *buf, char len );
    fusb_devhandle *make_devhandle ( usb_dev_handle *udh );
    int read_IF(unsigned char *ch);
    int read_IF(short *sh);
    int read_AGC(short *agc, bool *RFI,int *RFI_det, unsigned int *agc_count);
    int fx2_usb_bulk_read( char *bytes, int size,int timeout);
    bool agc_parse(char *buf, short *agc, unsigned int agc_size, unsigned int *count, bool *RFI);
    void set_port(int i);
    void read_flags(char *cp);
    void close(void);

    static const int FUSB_BUFFER_SIZE = 16 * ( 1L << 20 ); // 8 MB
    static const int FUSB_BLOCK_SIZE = 16 * ( 1L << 10 ); // 16KB is hard limit
    static const int FUSB_NBLOCKS    = FUSB_BUFFER_SIZE / FUSB_BLOCK_SIZE;
    static const int AGC_BUFFER_SIZE =16 * ( 1L << 20 ); // x
    static const int AGC_BLOCK_SIZE =16 * ( 1L << 10 );
    static const int AGC_NBLOCKS    = AGC_BUFFER_SIZE / AGC_BLOCK_SIZE;
};

#endif
