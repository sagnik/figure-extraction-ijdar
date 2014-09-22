/* 
 * images.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1999 SOS Software
 */

/* IMAGES.H:    include file contains informataion for image display on sun
 *
 */

#ifndef IMAGESH                 /* prevents multiple images.h defn */
#define IMAGESH 1

/* image size */
#define	XSIZE		512              /* sun monitor actually goes to 640 */
#define	YSIZE		512              /* and y size only goes to 480 */

#define XSIZEBIG 1024           /* bigger image than standard 512 */
#define YSIZEBIG 1024

/*  Color mapping table for pseudo color on sun */

#define RED 249
#define GREEN 250
#define BLUE 251
#define CYAN 252
#define MAGENTA 253
#define YELLOW 254
#define OVERLAY 248
#define CURSOR 247
#define BACKCOLOR 246
#define HIVALUE 246
#define LOWVALUE 0
#define HIBINARY 255

#define IMGOFF 0
#define IMGON 255

#ifdef max
#undef min
#undef max
#endif
int cg1dd ();

/* image file header */

struct pheader {                /* header in front of each binary image file */
  char magic;                   /* 8 bit magic number PICMAGIC */
  char type;                    /* compressed, expanded, or black and white */
  char psize;                   /* number of bytes per pixel */
  char spare1;
  int transparent;              /* transparent color */
  int xsize;                    /* pixels per line */
  int ysize;                    /* lines in image */
  int spare2;
};

/* defines for use on all machines */

#define	PICMAGIC	'P'            /* magic numbers for image files */
#define	PICIMAGES	'M'

#define	PICTYPE		char           /* types for PICMAGIC type files */
#define	PICNORMAL	'e'
#define	PICCOMPRESSED	'c'
#define	PICBW		'b'
#define	PICRUNLENGTH	'r'

struct point {
  int x;                        /* x address */
  int y;                        /* y address */
};

struct line {
  struct point begin;
  struct point end;
};

struct rectangle {
  struct point min;
  struct point max;
};

     /* from Sun */
struct raster {
  int wd, ht, dp;
  unsigned char *bits;
};
struct bwraster {
  int wd, ht, dp;
  short *bits;
};

struct dpoint {
  double x, y;                  /* x,y coordinate */
};

struct dsegment {
  struct dpoint pt1;
  struct dpoint pt2;
};

#endif
