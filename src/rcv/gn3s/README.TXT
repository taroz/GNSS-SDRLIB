
General
=======

The software in this distribution is developed to work with
the 'CU SiGe SE4120L-EK3' L1 band GNSS data acquisition module 
as a tool for both teaching and learning software GNSS receiver
techniques. The software is licensed under GNU GPL version 2.
License agreement is enclosed in file COPYING_GPL.txt

The software has been designed to work under Win 7, WinXP and tested under those platform.

Please note that the module and software have been developed
to keep costs as low as possible.  Thus it will not be possible
to support the device/software beyond this simple readme and 
files bundled here.

We have tested the module and software on a number of different
platforms with about a 95% success rate (some USB chipsets (Intel-
based) seem to work better than others.  If having issues on one 
platform, a different platform should work.  In order to allow 
users to try and resolve issues and simplify development, the 
code associated with project has been built on the open source
philosophy and all source code has been included.

Note: the module has been designed for an active antenna.  The
module is powered by the host USB port and provide the USB voltage
(~5V for this purpose).  It is unlikely to power "hungry" amplifiers
or do well in the event of a short.

More details may be found here: http://ccar.colorado.edu/gnss  

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
PURPOSE.


Installation
============

First thing to do is to install the driver part. This is done
by connecting the module using a USB cable to the PC. Windows
will then ask for a driver to assign to the module. You should
answer "NO" to the questions regarding searching for a driver on
the web and automatic installation. Instead direct windows to
the driver directory in this software package by means of the
[Have disk..] option. You should direct it to the \driver\
directory in this software package. If Windows does not ask for
a driver, you could assign the driver manually. Right click
"Computer" and select "Management", Double click the "Device 
Manager". Find the divice name in the right column and double 
click. Select the "Driver" label and click "Update Driver". 
Then choose "Browse my computer for driver software" and direct
windows to the driver directory and do as mentioned above.

Second, copy the application to c:\GNSS or any other
location of your choice, preferably within your system\
partition. It is recommended for your convenience that you
include this directory to the search space for the command
line interface, e.g:

path = %PATH%;c:\GNSS\


Usage
=====

This command line application requires only one parameter to
run, that is the name of the file where to save data. By
running the application at any time without any parameters
will view the usage options as below:



 ----------
 GNSS - GNSS IF Streamer for Windows
 ----------

        Usage:

        GN3SS  [options]

        Options:

        -s filesize : Number of seconds data to collect, default: 2 sec
        -o filename : Filename, default is 'test.bin'
        -c          : Data collection mode, default: 1 (fs = 16.368MHz, if = 4.092MHz, 2bit real)
        -?          : The help screen
		
	The data collection mode parameters are listed as follows:
    Mode#     Band     Sampling frequency    Intermediate frequency     Data format
      1      Narrow        16.368MHz,               4.092MHz,            2bit real 
      2      Narrow         8.184MHz,                   0MHz,            4bit I/Q 
      3      Narrow         5.456MHz,               1.364MHz,            2bit real 
      4      Narrow         4.092MHz,                   0MH,             4bit I/Q 
      5       Wide         16.368MHz,               4.092MHz,            2bit real 
      6       Wide          8.184MHz,                   0MHz,            4bit I/Q 
      7       Wide          5.456MHz,               1.364MHz,            2bit real 
      8       Wide          4.092MHz,                   0MHz,            4bit I/Q 
	  
No default suffix will be appended to the filename and the use
of '.bin' is encouraged, as well as having a separate directory
designated to saving GNSS data. The user will NOT be prompted
when saving data to an existing file. The old data WILL be
overwritten.


Data processing
===============
With "A Software-Defined GPS and Galileo Receiver: A Single-
Frequency Approach", K. Borre, D. Akos, et.al. (ISBN: 0817643907)
comes a DVD containing Matlab based processing algorithms well
suited for processing this kind of data.  

See: http://ccar.colorado.edu/gnss for any updates/further info

Enjoy!
