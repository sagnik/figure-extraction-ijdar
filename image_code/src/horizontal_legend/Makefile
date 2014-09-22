
CFILES = connexe.c \
	convert.c \
	iopnm.c \
	test-hyster-pnm.c \
	horizontal_legend.c


COBJS = connexe.o \
	convert.o \
	iopnm.o

EOBJS = test-hyster-pnm.o \
	horizontal_legend.o

.c.o:; cc -O -g -I. -c $*.c;

all : clean test-hyster-pnm horizontal_legend

clean :
	rm -f $(COBJS) $(EOBJS) test-hyster-pnm horizontal_legend

test-hyster-pnm : $(EOBJS) $(COBJS)
	cc -O -I. -o test-hyster-pnm test-hyster-pnm.o $(COBJS) -lm

horizontal_legend : $(EOBJS) $(COBJS)
	cc -O -g -I. -o horizontal_legend horizontal_legend.o $(COBJS) -lm
	/bin/cp horizontal_legend ../../binlin
