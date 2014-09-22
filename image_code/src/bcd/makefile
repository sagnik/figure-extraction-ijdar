#
#  bcd  Makefile
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

BCD = bcd

# EXECUTABLES #######################################

EXECS = $(BCD)

# OBJECT FILES #####################################

BCDO = \
	bcd.o \
	conv.o \
	ctor.o \
	det.o \
	dtor.o \
	edge_map.o \
	filter.o \
	find_edg.o \
	hyst.o \
	loc.o \
	thin.o \
	thld.o \
	write.o \
	$(NULL)

# COMPILATION ######################################

all: $(EXECS)

$(BCD): $(BCDO)
	$(CC) $(COPTS) $(BCDO) $(LPATH) -lip -limage -ltiff -lm -o $@
	/bin/cp $@ $(BIN)

# HEADER DEPENDENCIES ###############################
HDRS =  ./edge_finder.h \
	$(HOME)/lib/libimage/tiffimage.h \
	$(HOME)/lib/libimage/draw.h \
	$(HOME)/lib/libip/ip.h \
	$(NULL)

$(BCDO):	$(HDRS)

clean:
	rm -f $(EXECS) *.o *.a core

# START OVER ########################################
new:
	rm -f $(EXECS) *.o *.a core
	make

