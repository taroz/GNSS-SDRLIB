How to compile gnss-sdrcli
-------------------------------------------------------------------------------
* Currentry, gnss-sdrcli of Linux version does **NOT** work well...
* I tested to compile on Ubuntu 13.10 64-bit
* If you want to use rtl-sdr or BladeRF, you must install their libraries
    * RTL-SDR: <http://sdr.osmocom.org/trac/wiki/rtl-sdr>
    * BladeRF: <https://github.com/Nuand/bladeRF>

-------------------------------------------------------------------------------
* Install dependent packages for the build
    * See "install.sh"
* Modify makefile if you use rtl-sdr or BladeRF
* "make" and "cd ../../bin"
* Run by "./gnss-sdrcli"
