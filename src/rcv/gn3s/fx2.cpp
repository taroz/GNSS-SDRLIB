/*
 * Code from: USRP - Universal Software Radio Peripheral (GNU Radio)
 *
 * Initial modifications by:
 *
 * Stephan Esterhuizen, Aerospace Engineering Sciences
 * University of Colorado at Boulder
 * Boulder CO, USA
 *
 * Further modifications for use with the SiGe USB module to accompany
 * the textbook: "A Software-Defined GPS and Galileo Receiver: A
 * Single-Frequency Approach" by Kai Borre, Dennis Akos, et.al. by:
 *
 * Marcus Junered, GNSS Research Group
 * Lulea University of Technology
 * Lulea, Sweden
 *
 * Further review and modifications of user interface has been made by:
 *
 * Jonas Lindstrom
 * Lulea University of Technology
 * Lulea, Sweden
 *
 * http://ccar.colorado.edu/gnss
 *
 *  Furthur modifications integrating 4120 devices have been made by:
 *
 *  Marcus Wilkerson
 *  University of Colorado, Boulder
 *  Boulder, CO, USA
 *
 *  Some minor changes were made by
 *
 *  Oscar Isoz
 *  University of Colorado, Boulder
 *  Boulder, CO, USA
 *
 * Change Documentation (2/2008 - 5/2008)
 * --------------------------------------
 * - MW - Added PID array variable for SiGe 4120 GPS Front End
 * - MW - Fixed a bug if LIBUSB found more devices on the bus and gave
 *        each device a different index number. It was hardcoded to "1" before.
 * - MW - Added check for 4120 module in usb_fx2_find fcn
 * - MW - If 4120, use I/Q values of -1 and +1 instead of -1,-3,+1,+3 as with
 *        4110 modules. This is in main().
 * - OI - Changed the user interface
 *
 * ---------------------------------------------------------------------
 *
 * GN3S - GNSS IF Streamer for Windows
 * Copyright (C) 2006 Marcus Junered
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "sdr.h"
#include "fx2.h"

using namespace std;

Fx2_dev::Fx2_dev()
{
    int fx2_pid[]={0x0b38,0x0b39,0x0b3a,0x0b3f};
    int fx2_vid[]={0x1781,0x1781,0x1781,0x1781};
    fx2_port=0;
    fx2_conf = new Fx2_c();
    agc_buf= new char[GN3S_AGC_BUFFSIZE];
}

Fx2_dev::Fx2_dev(int i)
{
    //int *fx2_pid=new int {0x0b38,0x0b39};
    //fx2_vid={0x1781,0x1781};
	
    //  fx2_pid[0]=0x04b4;
    fx2_pid[0]=0x0b38;
    fx2_pid[1]=0x0b39;
    fx2_pid[2]=0x0b3a;
    fx2_pid[3]=0x0b3f;


    //fx2_vid[0]=0x1003;
    fx2_vid[0]=0x1781;
    fx2_vid[1]=0x1781;
    fx2_vid[2]=0x1781;
    fx2_vid[3]=0x1781;

    fx2_port=i;
    //  std::cout<<fx2_pid[0] <<"\n";
    fx2_conf = new Fx2_c();
    agc_buf= new char[GN3S_AGC_BUFFSIZE];
}

Fx2_dev::~Fx2_dev()
{

    //fx2_conf

 //   delete fx2_conf->d_ephandle6;
    //std::cout<<"step 1 done"<<endl;
//    try{
   // delete fx2_conf->d_devhandle;
//    }
//     catch(const exception &e){
//        std::cerr<<e.what();.
//
//        }
   // std::cout<<"step 2 done"<<endl;
//    delete fx2_conf->interface;
    // fx2_conf->~Fx2_c();
//    std::cout<<"step 3 done"<<endl;
//    try{
// usb_release_interface( fx2_conf->udev, fx2_conf->interface );
//    }
//    catch(...){
//        std::cerr<<"strange"<<endl;
//
//        }
//    std::cout<<"step 4 done"<<endl;
//try{
//usb_close(fx2_conf->udev);
//}
//catch(exception& e){
//    std::cout<<e.what();
//
//    }
//    std::cout<<"step 5 done"<<endl;
  //   delete fx2_conf;
};

void Fx2_dev::close(){
	delete fx2_conf->d_ephandle6;
	delete fx2_conf->d_devhandle;

	usb_release_interface( fx2_conf->udev, fx2_conf->interface_ );
    usb_reset(fx2_conf->udev);
    usb_close(fx2_conf->udev);
}


int Fx2_dev::read_IF(unsigned char *ch)
{
    unsigned int ui_len =0;
    //fx2_conf->d_devhandle->_reap(false);
    try
    {
        ui_len=fx2_conf->d_ephandle6->read( ch, GN3S_BUFFSIZE );
    }
    catch (const char* e)
    {
        std::cerr<<e<<endl;
    }
    return(ui_len);

}


int Fx2_dev::read_IF(short *sh)
{
    unsigned int ui_len =0;
    //fx2_conf->d_devhandle->_reap(false);
    try
    {
        ui_len=fx2_conf->d_ephandle6->read( sh, GN3S_BUFFSIZE );
    }
    catch (const char* e)
    {
        std::cerr<<e<<endl;
    }
    return(ui_len);
}


int Fx2_dev::read_AGC(short *agc, bool *RFI,int *RFI_det,unsigned int *agc_count)
{

    unsigned int ret_agc=0;
    unsigned int bufsize_agc = GN3S_AGC_BUFFSIZE;
    bool e_bits =false;
    unsigned char cp_agc_data[64];
    unsigned char uc_flags[5];
    int i_tmp;

    for (i_tmp = 0;i_tmp<64;i_tmp++) //clear buffer
    {
        cp_agc_data[i_tmp]=0;
    }

    // ret_agc = usb_bulk_read(fx2_conf->udev,AGC_ENDPOINT,agc_buf, bufsize_agc, 500);


    //get the AGC data
    usrp_xfer2(VRQ_FLAGS, 0, uc_flags, 5);
    usrp_xfer2(VRQ_GET_AGC, 0, cp_agc_data, 64);

//std::cout<<"recieved agc data "<<(int)cp_agc_data[0]<<" "<<(int)cp_agc_data[1]<<" "<<ret_agc<<endl;
    usrp_xfer (VRQ_AGC, 2);
	i_tmp= 0;
    ret_agc = uc_flags[2];
    if ((int) ret_agc< 0)
    {
        fprintf (stderr, "i:  - usb_bulk_read(EP4): ret_agc = %d (%d) \n",ret_agc,bufsize_agc);
        fprintf (stderr, "%s\n", usb_strerror());
        return(-1);
    }
    else if (ret_agc>=0)
    {
         e_bits =this->agc_parse((char*)cp_agc_data, agc, ret_agc, agc_count, RFI);
    //e_bits =this->agc_parse(agc_buf, agc, ret_agc, agc_count, RFI);
        return(*agc_count);
    }


    return(-1);
}

int Fx2_dev::usb_fx2_init(void)
{

    char status = 0;
    int interface = RX_INTERFACE;
    int altinterface = RX_ALTINTERFACE;
    fusb_ephandle *d_ephandle6;
    fusb_devhandle *d_devhandle;
    usb_dev_handle *udev;
    udev = usb_open(fx2);
    if ( !udev )
    {
        fprintf ( stderr, "\nCould not obtain a handle to GNSS Front-End device \n" );
        return -1;
    }
    else
    {
        if ( usb_set_configuration (udev, 1 ) < 0 )
        {

            fprintf ( stderr,
                      "%s:usb_set_configuration: failed conf %d\n",
                      __FUNCTION__,
                      interface );
            fprintf ( stderr, "%s\n", usb_strerror() );
            usb_close ( udev );
            status = -1;
        }

        if ( usb_claim_interface ( udev, interface ) < 0 )
        {
            fprintf ( stderr,
                      "%s:usb_claim_interface: failed interface %d\n",
                      __FUNCTION__,
                      interface );
            fprintf ( stderr, "%s\n", usb_strerror() );
            usb_close ( udev );
            status = -1;
        }

        if ( usb_set_altinterface ( udev, altinterface ) < 0 )
        {
            fprintf ( stderr,
                      "%s:usb_set_alt_interface: failed\n",
                      __FUNCTION__ );
            fprintf ( stderr, "%s\n", usb_strerror() );
            usb_release_interface ( udev, interface );
            usb_close( udev );
            status = -1;
        }


        d_devhandle=make_devhandle ( udev );
        // d_devhandle._reap(false);

        d_ephandle6 = d_devhandle->make_ephandle ( RX_ENDPOINT,
                      true,
                      FUSB_BLOCK_SIZE,
                      FUSB_NBLOCKS );


//        d_ephandle4 = d_devhandle->make_ephandle ( AGC_ENDPOINT,
//                      true,
//                      AGC_BLOCK_SIZE,
//                      AGC_NBLOCKS );



        if ( !d_ephandle6->start () )
        {
            fprintf ( stderr, "usrp0_rx: failed to start end point streaming (EP6)" );
            usb_strerror();
            status = -1;
        }

        if ( status == 0 )
        {
            fx2_conf->altinterface = altinterface;
            fx2_conf->udev = udev;
            fx2_conf->d_devhandle = d_devhandle;
            fx2_conf->d_ephandle6 = d_ephandle6;

            //printf("fx2 initiated\n");
            return 0;
        }
        else
        {
            return -1;
        }
    }
}


int Fx2_dev::usb_fx2_find(void)
{

    struct usb_bus *bus;
    struct usb_device *dev;
    //  struct usb_device *fx2 = NULL;
    usb_dev_handle *udev;
    bool info =false;
    int ret;
    char string[256];
    char *num_str =(char*)("00");
    usb_init();
    //  fx2_port =0;
    usb_find_busses();
    usb_find_devices();


//    printf ( "bus/device idVendor/idProduct, %d pid %d \n",fx2_pid[fx2_port],fx2_vid[fx2_port] );

    for ( bus = usb_busses; bus; bus = bus->next )
    {
        for ( dev = bus->devices; dev; dev = dev->next )
        {
//            std::cout<< fx2_vid[fx2_port] <<" "<<fx2_pid[fx2_port]<<endl;
            if (dev->descriptor.idVendor == fx2_vid[fx2_port] && dev->descriptor.idProduct == fx2_pid[fx2_port])
            {
                //printf("found VID = %d , PID = %d\n" ,dev->descriptor.idVendor, dev->descriptor.idProduct);
                if (strcmp(bus->dirname,num_str )==0)
                {
                    std::cout<<"found device "<<dev->descriptor.idVendor<<" "<< dev->descriptor.idProduct<<endl;
                    fx2= dev;
                    return 1;
                }
                else if (strcmp(num_str,"00")==0)
                {
                    // std::cout<<"did not found device\n";

                    fx2= dev;
                    return 1;
                }
                else
                {
                    //printf
                    return 0;
                }
                std::cout<<"found device 1\n";
                return(0);
            }

            if (info )
            {
                printf("udev/n");
                udev = usb_open ( dev );
                if ( udev )
                {
                    if ( dev->descriptor.iManufacturer )
                    {
                        ret = usb_get_string_simple ( udev,
                                                      dev->descriptor.iManufacturer,
                                                      string,
                                                      sizeof ( string ) );

                        if ( ret > 0 )
                            printf ( "- Manufacturer : %s\n", string );
                        else
                            printf ( "- Unable to fetch manufacturer string\n" );
                    }

                    if ( dev->descriptor.iProduct )
                    {
                        ret = usb_get_string_simple ( udev,
                                                      dev->descriptor.iProduct,
                                                      string,
                                                      sizeof ( string ) );

                        if ( ret > 0 )
                            printf ( "- Product : %s\n", string );
                        else
                            printf ( "- Unable to fetch product string\n" );
                    }

                    if ( dev->descriptor.iSerialNumber )
                    {
                        ret = usb_get_string_simple ( udev,
                                                      dev->descriptor.iSerialNumber,
                                                      string,
                                                      sizeof ( string ) );

                        if ( ret > 0 )
                            printf ( "- Serial Number: %s\n", string );
                        else
                            printf ( "- Unable to fetch serial number string\n" );
                    }

                    usb_close ( udev );
                }

                if ( !dev->config )
                {
                    printf ( " Could not retrieve descriptors\n" );
                    continue;
                }

                for ( int i = 0; i < dev->descriptor.bNumConfigurations; i++ )
                {
                    print_configuration ( &dev->config[i] );

                }
            }
        }
    }
    return 0;
}

void Fx2_dev::print_configuration ( struct usb_config_descriptor *config )
{
    int i;

    printf ( " wTotalLength: %d\n", config->wTotalLength );
    printf ( " bNumInterfaces: %d\n", config->bNumInterfaces );
    printf ( " bConfigurationValue: %d\n", config->bConfigurationValue );
    printf ( " iConfiguration: %d\n", config->iConfiguration );
    printf ( " bmAttributes: %02xh\n", config->bmAttributes );
    printf ( " MaxPower: %d\n", config->MaxPower );

    for ( i = 0; i < config->bNumInterfaces; i++ )
        print_interface ( &config->interface[i] );
}

void Fx2_dev::print_altsetting ( struct usb_interface_descriptor *interface )
{
    int i;

    printf ( " bInterfaceNumber: %d\n", interface->bInterfaceNumber );
    printf ( " bAlternateSetting: %d\n", interface->bAlternateSetting );
    printf ( " bNumEndpoints: %d\n", interface->bNumEndpoints );
    printf ( " bInterfaceClass: %d\n", interface->bInterfaceClass );
    printf ( " bInterfaceSubClass: %d\n", interface->bInterfaceSubClass );
    printf ( " bInterfaceProtocol: %d\n", interface->bInterfaceProtocol );
    printf ( " iInterface: %d\n", interface->iInterface );

    for ( i = 0; i < interface->bNumEndpoints; i++ )
        print_endpoint ( &interface->endpoint[i] );
}

void Fx2_dev::print_interface ( struct usb_interface *interface )
{
    int i;

    for ( i = 0; i < interface->num_altsetting; i++ )
        print_altsetting ( &interface->altsetting[i] );
}

short  Fx2_dev::print_fifo_status (char print )
{
    unsigned char flags[5];
    short idx_data;

    usrp_xfer2 (VRQ_FLAGS, 0, flags, 5 );
    idx_data = flags[4] << 8;
    idx_data |= ( flags[3] & 0xff );

    if ( print )
    {
        printf ( "agc_en: %d (0x%02x) \n", flags[0], flags[0] );
        printf ( "op_mode: %d (0x%02x) \n", flags[1], flags[1] );
        printf ( "ep4_reset: %d (0x%02x) \n", flags[2], flags[2] );
        printf ( "idx: %d \n", idx_data );
        printf ( "\n" );
    }

    return idx_data;
}


void  Fx2_dev::print_endpoint ( struct usb_endpoint_descriptor *endpoint )
{
    printf ( " bEndpointAddress: %02xh\n", endpoint->bEndpointAddress );
    printf ( " bmAttributes: %02xh\n", endpoint->bmAttributes );
    printf ( " wMaxPacketSize: %d\n", endpoint->wMaxPacketSize );
    printf ( " bInterval: %d\n", endpoint->bInterval );
    printf ( " bRefresh: %d\n", endpoint->bRefresh );
    printf ( " bSynchAddress: %d\n", endpoint->bSynchAddress );
}


int Fx2_dev::write_cmd ( int request, int value, int index, unsigned char *bytes, int len )
{
    // int r = write_cmd (udh, VRQ_XFER, start, 0, 0, 0);
    int requesttype = ( request & 0x80 ) ? VRT_VENDOR_IN : VRT_VENDOR_OUT;

    int r = usb_control_msg ( fx2_conf->udev, requesttype, request, value, index,
                              ( char * ) bytes, len, 1000 );
//std::cout<<"tries to write "<<value << " "<< index<< " "<<bytes<<endl;

    if ( r < 0 )
    {
        // we get EPIPE if the firmware stalls the endpoint.
        if ( errno != EPIPE )
            std::cout<<"failed to write "<<value << " "<< index<< " "<<bytes<<endl;
            fprintf ( stderr, "usb_control_msg failed write_cmd_fx2.cpp: %s\n", usb_strerror() );
    }
    return r;

}

bool Fx2_dev::_get_status ( int which, bool *trouble )
{
    unsigned char status;
    *trouble = true;
	if ( write_cmd ( VRQ_GET_STATUS, 0, which, &status, sizeof ( status ) ) != sizeof ( status ) )
        return false;

    *trouble = false;
    return true;
}


bool Fx2_dev::check_rx_overrun ( bool *overrun_p )
{
    return _get_status ( GS_RX_OVERRUN, overrun_p );
}


bool Fx2_dev::usrp_xfer ( unsigned char VRQ_TYPE, unsigned char start )
{
    int r = write_cmd (VRQ_TYPE, start, 0, 0, 0 );
    return r == 0;
}

bool Fx2_dev::usrp_xfer2 ( unsigned char VRQ_TYPE, unsigned char start, unsigned char *buf, char len )
{
    int r = write_cmd (VRQ_TYPE, start, 0, buf, len );
    return r == 0;
}


fusb_devhandle* Fx2_dev::make_devhandle ( usb_dev_handle *udh )
{
    return new fusb_devhandle_win32 ( udh );
}

int Fx2_dev::fx2_usb_bulk_read(char *bytes, int size,int timeout)
{
    return(usb_bulk_read(fx2_conf->udev, AGC_ENDPOINT, bytes,  size, timeout));


};

bool Fx2_dev::agc_parse(char *buf, short *agc, unsigned int agc_size, unsigned int *count, bool *RFI)
{
    float RFI_limit = 1; //Needs to be verified
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int e_headers = 0;
    short buf16 =0;
   // short  header2;//header,
    short data, data2;
    data= 0;
    data2 =0;
    //float agc_f = 1;
    // Parse AGC data
    if (agc_size>0)
    {
        for (i=0; i<agc_size; i+=2)
        {
            buf16 = buf[i+1] << 8;
            buf16 |= (buf[i] & 0xff);
            // header2 = buf16 & 0xf000;
            data2 = buf16 & 0x0fff;
            if ( data2 > 0)  // Break the loop if only zeroes are read
            {
                // if (header2 & bmAGC)
                // {
                // Save AGC data separately
                agc[j] = data2;

                //          header2 = header2 & 0x3000;	// Clear channel bits
                j++;
                //}

            }
        } // end for loop
        *count = j;
    }
    if (e_headers > j/2)
        return true;
    else
        return false;
}


void Fx2_dev::set_port(int i)
{
    fx2_port =i;

}
