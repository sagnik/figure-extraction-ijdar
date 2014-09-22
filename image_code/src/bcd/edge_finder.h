/*
 * (c) Copyright 1988 by Ingemar J. Cox
 * Last modified 2/8/88 Ingemar J. Cox
 * C version 8/2/88 Deborah A. Wallach
 */

#define abs(x) ((x)<0 ? -(x) : (x))
//#define max(x, y) ((x)>(y) ? (x) : (y))
//#define min(x, y) ((x)<(y) ? (x) : (y))

#define EDGE_X 252
#define EDGE_Y 253
#define EDGE_45 254
#define EDGE_135 255

#define FWD 0
#define BWD 1

#define diag_scale 1.414        /* scale factor for diagonals */

struct image {
  unsigned char *an_image;      /* pointer to image array */
  int nx, ny;                   /* dimensions of image array */

  int *gaussian;                /* pointer to output image after convolution */
  int *idx, *idy, *id45, *id135;  /* pointers to o/p from detn filters */

  int *filter;                  /* pointer to 1D array of filter coefficients */
  int norm;                     /* normalization factor after convolution */
  int nf, nf2;                  /* nf = size of filter (in pixels), nf2=nf/2 */
  int orient_flag;
  unsigned char *edge_map, *edge_map_hi;
  int lo_threshold;
};

/* function definitions */

/* bcd.c */
void usage (char *progname);
void main (int argc, char *argv[]);

/* conv.c */
void image_convolve (unsigned char *pic);

/* ctor.c */
void image_init (unsigned char *array, int xdim, int ydim);

/* det.c */
void image_detx ();
void image_dety ();
void image_det45 ();
void image_det135 ();

/* dtor.c */
void image_cleanup ();

/* edge_map.c */
unsigned char *image_edges (int threshold);
int image_edge_map_lo (register int ix, register int iy, register int index);

/* filter.c */
void generate_filter (float sigma);

/* find_edg.c */
unsigned char *image_find_edges (float sigma, int *threshold);

/* hyst.c */
unsigned char *image_hysteresis (int lo_thld);
void image_neighbor_fwd (register int iy, register int ix, register unsigned char *mapP);
void image_neighbor_bwd (register int iy, register int ix, register unsigned char *mapP);
int Fcontour (register int iy, register int ix);
int Bcontour (register int iy, register int ix);

/* loc.c */
int image_locx (register int iy, register int ix, register int index);
int image_locy (register int iy, register int ix, register int index);
int image_loc45 (register int iy, register int ix, register int index);
int image_loc135 (register int iy, register int ix, register int index);

/* thin.c */
unsigned char *image_thin ();

/* thld.c */
int image_threshold ();

/* write.c */
void image_Write_int (char *name, int *pointer);
void image_Write_char (char *name, unsigned char *pointer);
