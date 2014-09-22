#
# libimage.a  Makefile
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
IPATH   = -I. -I../libtiff/libtiff
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
MAINS = libimage.a

# OBJECT FILES #####################################
OBJS    = \
        draw.o \
        pgmimage.o \
	tiffimage.o \
        gdfontg.o \
        gdfontl.o \
        gdfontmb.o \
        gdfonts.o \
        gdfontt.o \
        misc.o \
	$(NULL)

# COMPILATION ######################################
all: $(MAINS)

libimage.a: $(OBJS)
	$(AR) $(AROPTS) libimage.a $?
	$(RANLIB) libimage.a

# HEADER DEPENDENCIES ###############################
$(OBJS): tiffimage.h getopt.h draw.h gdfontg.h gdfontl.h gdfontmb.h gdfonts.h gdfontt.h misc.h

# CLEAN UP ##########################################
clean:
	rm -f $(MAINS) $(OBJS) core a.out

# START OVER ########################################
new:
	rm -f $(MAINS) *.o *.a core
	make
