#
# hough  Makefile
#
# Practical Algorithms for Image Analysis
#
# Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
#

SHELL   = /bin/sh
NULL    =
CC      = /usr/bin/gcc
HOME    = ../..
BIN     = $(HOME)/binlin
IPATH   = -I. -I$(HOME)/lib/libtiff/libtiff -I$(HOME)/lib/libimage -I$(HOME)/lib/libip
LPATH   = -L$(HOME)/lib/libtiff/libtiff -L$(HOME)/lib/libimage -L$(HOME)/lib/libip
COPTS   = -g -O

# OPTIONAL DEFINES #################################
DEFOPTS = -DLINUX

# SET CC COMPILE FLAGS #############################
CFLAGS = $(COPTS) $(IPATH) $(DEFOPTS)

CC = /usr/bin/gcc

LIB_TIFF=$(HOME)/lib/libtiff/libtiff
LIB_IMAGE=$(HOME)/lib/libimage
LDFLAGS=$(OPTIONS)

HOUGH = hough

# EXECUTABLES #######################################

EXECS = $(HOUGH)

# OBJECT FILES #####################################

HOUGHO = \
	hough.o \
	$(NULL)

# COMPILATION ######################################

all: $(EXECS)

$(HOUGH): $(HOUGHO)
	$(CC) $(COPTS) $(HOUGHO) $(LPATH) -lip -limage -ltiff -lm -o $@
	/bin/cp $@ $(BIN)

# HEADER DEPENDENCIES ###############################
HDRS =  $(HOME)/lib/libimage/tiffimage.h \
	$(HOME)/lib/libimage/draw.h \
	$(HOME)/lib/libip/ip.h \
	$(NULL)

$(HOUGHO):	$(HDRS)

clean:
	rm -f $(EXECS) *.o *.a core

# START OVER ########################################
new:
	rm -f $(EXECS) *.o *.a core
	make

