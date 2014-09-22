#fig2xml build
#you may have to specify -L/path/to/png
#you will probably want to change -L/path/to/fftw and -L/path/to/opencv etc

CC=gcc
CFLAGS=-c -g 
LFLAGS=-lpng

all : fig2xml.x

fig2xml.x : src/main.c
	$(CC) $(LFLAGS) src/main.c -o fig2xml.x
	rm -rf src/*o
	mv fig2xml.x bin
