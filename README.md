GNSS-SDRLIB v2.0 Beta
===============================================================================
An Open Source GNSS Software Defined Radio Library


Author
-------------------------------------------------------------------------------
Taro Suzuki  
E-Mail: <gnsssdrlib@gmail.com>
HP: <http://www.taroz.net>


Features
-------------------------------------------------------------------------------
* GNSS signal processing functions written in C
    * Code generations
    * Signal acquisition / tracking
    * Decoding navigation messages 
    * Pseudo-range / carrier phase mesurements 
* GUI application (AP) written in C++/CLI
* Visualization of GNSS signal processing in real-time 
* Real-time positioning with RTKLIB (<http://www.rtklib.com/>)
* Observation data can be outputted in RINEX or RTCM format
* Support following signals (tracking and decoding navigation message) 
    * GPS L1CA
    * GLONASS G1
    * Galileo E1B
    * BeiDou B1I
    * QZSS L1CA/SAIF/LEX
    * SBAS L1
* Support following front-ends for real-time positioning
    * NSL Stereo <http://www.nsl.eu.com/primo.html>
    * SiGe GN3S sampler v2/v3 <https://www.sparkfun.com/products/10981>
    * Nuand BladeRF <http://nuand.com/>
    * RTL-SDR <http://sdr.osmocom.org/trac/wiki/rtl-sdr>
* Support RF binary file for post processing


System Requirements
-------------------------------------------------------------------------------
* GNSS-SDRLIB v2.0 only works in **64-bit Windows**
* The CLI/GUI applications are built with Microsoft Visual Studio Express 2012
* SIMD SSE2 supported CPU (Pentium IV and later processor) is required


Directory and Files
-------------------------------------------------------------------------------
    ./bin                   Executable APs for Windows  
        ./gnss-sdrcli.exe   Real-time GNSS signal processing AP (CLI)  
        ./gnss-sdrcli.ini   Configuration file for CLI AP  
        ./gnss-sdrgui.exe   Real-time GNSS signal processing AP (GUI)  
        ./frontend          Directory of front-end configuration files  
        ./cli               Command line interface  
        ./windows           VS2012 project of CLI AP (for Windows)  
    ./linux                 Makefile of CLI AP (for Linux)  
    ./gui                   VS2012 project of GUI AP (for Windows)  
    ./src                   Library source codes  
        ./sdr.h             Library header file  
        ./sdracq.c          Functions related to signal acquisition  
        ./sdrcmn.c          Functions related to SIMD operation  
        ./sdrcode.c         Functions related to generation of ranging code  
        ./sdrinit.c         Functions related to initialization/end process  
        ./sdrlex.c          Functions related to QZSS LEX decoding  
        ./sdrmain.c         Main function  
        ./sdrnav.c          Functions related to navigation data  
        ./sdrnav_gps.c      Functions related to decoding GPS nav. data  
        ./sdrnav_glo.c      Functions related to decoding GLONASS nav. data  
        ./sdrnav_gal.c      Functions related to decoding Galileo nav. data  
        ./sdrnav_bds.c      Functions related to decoding BeiDou nav. data  
        ./sdrnav_sbs.c      Functions related to decoding SBAS nav. data  
        ./sdrout.c          Functions related to RINEX/RTCM outputs  
        ./sdrplot.c         Functions related to plot graph  
        ./sdrrcv.c          Functions related to receiving RF data  
        ./sdrspec.c         Functions related to spectrum analysis  
        ./sdrsync.c         Functions related to generating observation data  
        ./sdrtrk.c          Functions related to signal tracking  
        ./rcv               Source codes related to front-end  
    ./lib                   Source codes related to used library  
    ./test                  Test data  
        ./data              Test IF data  
        ./output            Default RINEX output directory  


How to use
-------------------------------------------------------------------------------
See manual or support page <http://www.taroz.net/gnsssdrlib_e.html>


License
-------------------------------------------------------------------------------
Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
