#
# makefile for gnss-sdr-cli
#

# Use or not use RTLSDR and BLADERF
# 1:Use 0:Not Use
USE_RTLSDR=0
USE_BLADERF=0

SRC=../../src
RTKLIB=../../lib/rtklib
FEC=../../lib/fec
STEREO=../../src/rcv/stereo
RTLSDR=../../src/rcv/rtlsdr
BLADERF=../../src/rcv/bladerf

INCLUDE=-I$(SRC) -I$(RTKLIB) -I$(FEC) -I$(STEREO) -I$(RTLSDR) -I$(BLADERF)

CC=gcc
OPTIONS=-DSSE2_ENABLE -DFFTMTX -DSTEREO -DSTEREOV26

LIBS=$(STEREO)/linux/libnslstereo.a $(FEC)/linux/libfec.a

OBS= sdrmain.o sdrcmn.o sdracq.o sdrcode.o sdrinit.o sdrnav.o\
     sdrnav_gps.o sdrnav_glo.o sdrnav_gal.o sdrnav_bds.o sdrnav_sbs.o\
     sdrout.o sdrplot.o sdrrcv.o sdrspec.o sdrtrk.o sdrlex.o\
     sdrsync.o stereo.o rtkcmn.o rtcm.o rtcm2.o rtcm3.o rtcm3e.o rinex.o

ifeq ($(USE_RTLSDR),1)
OPTIONS+=-DRTLSDR
LIBS+=-lrtlsdr
OBS+=rtlsdr.o convenience.o
endif

ifeq ($(USE_BLADERF),1)
OPTIONS+=-DBLADERF
LIBS+=-lbladeRF
OBS+=bladerf.o
endif

CFLAGS=-Wall -O3 -march=native $(INCLUDE) $(OPTIONS) -g
LDLIBS=-lm -lrt -lfftw3f -lfftw3f_threads -lpthread $(LIBS) -lusb-1.0

BIN= gnss-sdrcli
$(BIN): $(OBS)
	 $(CC) -o $(BIN) $(OBS) $(CFLAGS) $(LDLIBS)
	 @cp $(BIN) ../../bin

sdrmain.o: $(SRC)/sdrmain.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrmain.c
sdrcmn.o : $(SRC)/sdrcmn.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrcmn.c
sdracq.o : $(SRC)/sdracq.c
	$(CC) -c $(CFLAGS) $(SRC)/sdracq.c
sdrcode.o: $(SRC)/sdrcode.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrcode.c
sdrinit.o: $(SRC)/sdrinit.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrinit.c
sdrout.o : $(SRC)/sdrout.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrout.c
sdrnav.o : $(SRC)/sdrnav.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrnav.c
sdrnav_gps.o : $(SRC)/sdrnav_gps.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrnav_gps.c
sdrnav_glo.o : $(SRC)/sdrnav_glo.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrnav_glo.c
sdrnav_gal.o : $(SRC)/sdrnav_gal.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrnav_gal.c
sdrnav_bds.o : $(SRC)/sdrnav_bds.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrnav_bds.c
sdrnav_sbs.o : $(SRC)/sdrnav_sbs.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrnav_sbs.c
sdrplot.o: $(SRC)/sdrplot.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrplot.c
sdrrcv.o : $(SRC)/sdrrcv.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrrcv.c
sdrspec.o: $(SRC)/sdrspec.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrspec.c
sdrtrk.o : $(SRC)/sdrtrk.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrtrk.c
sdrlex.o : $(SRC)/sdrlex.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrlex.c
sdrsync.o : $(SRC)/sdrsync.c
	$(CC) -c $(CFLAGS) $(SRC)/sdrsync.c
rtkcmn.o   : $(RTKLIB)/rtkcmn.c
	$(CC) -c $(CFLAGS) $(RTKLIB)/rtkcmn.c
rtcm.o     : $(RTKLIB)/rtcm.c
	$(CC) -c $(CFLAGS) $(RTKLIB)/rtcm.c
rtcm2.o    : $(RTKLIB)/rtcm2.c
	$(CC) -c $(CFLAGS) $(RTKLIB)/rtcm2.c
rtcm3.o    : $(RTKLIB)/rtcm3.c
	$(CC) -c $(CFLAGS) $(RTKLIB)/rtcm3.c
rtcm3e.o   : $(RTKLIB)/rtcm3e.c
	$(CC) -c $(CFLAGS) $(RTKLIB)/rtcm3e.c
rinex.o    : $(RTKLIB)/rinex.c
	$(CC) -c $(CFLAGS) $(RTKLIB)/rinex.c
stereo.o : $(STEREO)/stereo.c
	$(CC) -c $(CFLAGS) $(STEREO)/stereo.c
rtlsdr.o : $(RTLSDR)/rtlsdr.c
	$(CC) -c $(CFLAGS) $(RTLSDR)/rtlsdr.c
convenience.o : $(RTLSDR)/convenience.c
	$(CC) -c $(CFLAGS) $(RTLSDR)/convenience.c
bladerf.o : $(BLADERF)/bladerf.c
	$(CC) -c $(CFLAGS) $(BLADERF)/bladerf.c

sdrmain.o: $(SRC)/sdr.h
sdrcmn.o : $(SRC)/sdr.h
sdracq.o : $(SRC)/sdr.h
sdrcode.o: $(SRC)/sdr.h
sdrinit.o: $(SRC)/sdr.h
sdrout.o : $(SRC)/sdr.h
sdrnav.o : $(SRC)/sdr.h
sdrnav_gps.o : $(SRC)/sdr.h
sdrnav_glo.o : $(SRC)/sdr.h
sdrnav_gal.o : $(SRC)/sdr.h
sdrnav_bds.o : $(SRC)/sdr.h
sdrnav_sbs.o : $(SRC)/sdr.h
sdrplot.o: $(SRC)/sdr.h
sdrrcv.o : $(SRC)/sdr.h
sdrspec.o: $(SRC)/sdr.h
sdrtrk.o : $(SRC)/sdr.h
sdrlex.o : $(SRC)/sdr.h
sdrsync.o: $(SRC)/sdr.h
rtkcmn.o : $(SRC)/sdr.h
rtcm.o: $(SRC)/sdr.h
rtcm2.o : $(SRC)/sdr.h
rtcm3.o : $(SRC)/sdr.h
rtcm3e.o: $(SRC)/sdr.h
rinex.o : $(SRC)/sdr.h
stereo.o : $(SRC)/sdr.h
rtlsdr.o : $(SRC)/sdr.h
convenience.o : $(SRC)/sdr.h
bladerf.o : $(SRC)/sdr.h

clean:
	rm -f *.o $(BIN)


