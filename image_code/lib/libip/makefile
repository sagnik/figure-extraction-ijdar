#
# libip.a  Makefile
#
# Practical Algorithms for Image Analysis
#
# Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
#

SHELL   = /bin/sh
NULL    =
CC      = /usr/bin/gcc
AR      = /usr/bin/ar
AROPTS  = rc
RANLIB  = /usr/bin/ranlib
IPATH   = -I. -I../libtiff/libtiff -I../libimage
HOME    = ..
COPTS   = -g
OPTIMIZER=-O

# OPTIONAL DEFINES #################################
DEFOPTS = -DLINUX

# SET CC COMPILE FLAGS #############################
CFLAGS  =   $(COPTS) $(OPTIMIZER) $(IPATH) $(DEFOPTS)

LIB_TIFF=$(HOME)/libtiff/libtiff
LIB_IMAGE=$(HOME)/libimage

# MAIN FILES #######################################
MAIN = libip.a

# OBJECT FILES #####################################
OBJS    = \
	acm_io.o \
        convolve.o \
        descript.o \
	drawline8.o \
        fft.o \
        fft2d.o \
        fltrbttr.o \
        fltrgaus.o \
	histogram.o \
        ip.o \
	license.o \
        llist.o \
        n2_pv.o \
        p_app.o \
        pccfct.o \
        pccfct2.o \
        pccfctde.o \
        ph.o \
        pmom.o \
        psaf.o \
        pv.o \
        sgl_stat.o \
	tlc1fct.o \
	tlc3fct.o \
	xytoline.o \
	$(NULL)

# COMPILATION ######################################
all: $(MAIN)

$(MAIN): $(OBJS)
	$(AR) $(AROPTS) $(MAIN) $?
	$(RANLIB) $(MAIN)

# HEADER DEPENDENCIES ###############################
$(OBJS): ip.h ph.h lldef.h convolve.h pcc2.h sgl_stat.h $(LIB_IMAGE)/misc.h

# CLEAN UP ##########################################
clean:
	rm -f $(MAIN) $(OBJS) core a.out

# START OVER ########################################
new:
	rm -f $(MAIN) *.o *.a core
	make
