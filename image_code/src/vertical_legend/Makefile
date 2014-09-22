
CFILES = connexe.c \
	convert.c \
	iopnm.c \
	test-hyster-pnm.c \
	vertical_legend.c


COBJS = connexe.o \
	convert.o \
	iopnm.o

EOBJS = test-hyster-pnm.o \
	vertical_legend.o

.c.o:; cc -O -g -I. -c $*.c;

all : clean test-hyster-pnm vertical_legend

clean :
	rm -f $(COBJS) $(EOBJS) test-hyster-pnm vertical_legend

test-hyster-pnm : $(EOBJS) $(COBJS)
	cc -O -I. -o test-hyster-pnm test-hyster-pnm.o $(COBJS) -lm

vertical_legend : $(EOBJS) $(COBJS)
	cc -O -g -I. -o vertical_legend vertical_legend.o $(COBJS) -lm
	/bin/cp vertical_legend ../../binlin
