
CFILES = connexe.c \
	convert.c \
	iopnm.c \
	test-hyster-pnm.c \
	extractdata.c


COBJS = connexe.o \
	convert.o \
	iopnm.o

EOBJS = test-hyster-pnm.o \
	extractdata.o

.c.o:; cc -O -g -I. -c $*.c;

all : clean test-hyster-pnm extractdata

clean :
	rm -f $(COBJS) $(EOBJS) test-hyster-pnm extractdata

test-hyster-pnm : $(EOBJS) $(COBJS)
	cc -O -I. -o test-hyster-pnm test-hyster-pnm.o $(COBJS) -lm

extractdata : $(EOBJS) $(COBJS)
	cc -O -g -I. -o extractdata extractdata.o $(COBJS) -lm
	/bin/cp extractdata ../../binlin
