/* 
 * lpfltr.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* LPFLTR:      program performs low-pass filtering on image
 *                usage: lpfltr inimg outimg
 *                       [-f freq <0-0.5>] [-s fltrSize] [-q quickFlag] [-L]
 *
 */

#define DFLT_CUTOFF 0.5         /* reduction by 2 is default cutoff */
#define RECT_CUTOFF 0.443883    /* factor to calc. 3dB cutoff freq */
#define GAUSS_CUTOFF 0.832555   /* factor to calc. 3dB cutoff freq */
#define ROUNDUP 0.99999         /* for rounding up integer */
#define NORM 100.0              /* normaliz. factor to integerize */

#include <stdio.h>
#include <stdlib.h>
#include <images.h>
#include <tiffimage.h>
#include <math.h>
#include <string.h>
extern void print_sos_lic ();

long convolve1 (Image *, long *, long);
long smooth (Image *, long);
long input (int, char **, double *, long *, short *);
long usage (short);

main (argc, argv)
     int argc;
     char *argv[];
{
  Image *imgIO;                 /* I/O image structure */
  long width, height;           /* image size */
  double cutoff;                /* low-pass cutoff frequency */
  long fltrSize;                /* filter mask size */
  double stdDev;                /* std. deviation param. of Gaussian */
  long *fltr;                   /* 1D filter mask */
  long midFltr;                 /* middle filter coefficient */
  short quickFlag;              /* for quick and dirty rect. filter */
  long i;

  if (input (argc, argv, &cutoff, &fltrSize, &quickFlag) < 0)
    return (-1);

/* allocate input and output image memory */
  imgIO = ImageIn (argv[1]);
  height = ImageGetHeight (imgIO);
  width = ImageGetWidth (imgIO);
  printf ("Image size is %dx%d.\n", width, height);

/* determine filter size and coefficients */
  if (quickFlag) {              /* rectangular filter window */
    if (fltrSize == 0)
      fltrSize = (long) (RECT_CUTOFF / cutoff + ROUNDUP);
  }
  else {                        /* Gaussian filter window */
    stdDev = GAUSS_CUTOFF / cutoff;
    if (fltrSize == 0)
      fltrSize = (long) (3.0 / (2.0 * cutoff) + 0.5);
  }
  if ((fltrSize % 2) == 0)
    fltrSize += 1;
  printf ("Filter cutoff is %5.2f and filter size is %dx%d.\n",
          cutoff, fltrSize, fltrSize);

/* calculate Gaussian filter coefficients */
  if (!quickFlag) {
    fltr = (long *) calloc (fltrSize, sizeof (*fltr));
    midFltr = fltrSize / 2;
    for (i = 0; i <= midFltr; i++)
      fltr[i + midFltr] = fltr[midFltr - i]
        = (long) (NORM * exp (-i * i / (2.0 * stdDev * stdDev)) + 0.5);
  }

/* perform filtering */
  if (quickFlag)
    smooth (imgIO, fltrSize);
  else
    convolve1 (imgIO, fltr, fltrSize);

/* output low-passed image */
  ImageOut (argv[2], imgIO);

  return (0);
}


/* USAGE:       function gives instructions on usage of program
 *                    usage: usage (flag)
 *              When flag is 1, the long message is given, 0 gives short.
 */

long
usage (flag)
     short flag;                /* flag =1 for long message; =0 for short message */
{

/* print short usage message or long */
  printf ("USAGE: lpfltr inimg outimg [-f CUTOFF <%4.2f>] [-s FLTRSIZE <odd>]\n", DFLT_CUTOFF);
  printf ("                           [-q QUICK_FLAG] [-L]\n");
  if (flag == 0)
    return (-1);

  printf ("\nlpfltr performs low-pass filtering upon image\n");
  printf ("using filter window of chosen size; the default is to use\n");
  printf ("a Gaussian-shaped filter window.\n\n");
  printf ("ARGUMENTS:\n");
  printf ("    inimg: input image filename (TIF)\n");
  printf ("   outimg: output image filename (TIF)\n\n");
  printf ("OPTIONS:\n");
  printf ("     -f CUTOFF: <0.0 to 0.5> is the fraction of the passband;\n");
  printf ("                the default is 0.25, that is half of original passband.\n");
  printf ("  -s FLTR_SIZE: is the size of the filter; this will override\n");
  printf ("                the size that would otherwise be automatically set from\n");
  printf ("                the cutoff frequency; this size must be odd.\n");
  printf (" -q QUICK_FLAG: for quick (and dirty) rectangular filtering;\n");
  printf ("                NOTE: specifying both cutoff frequency and filter\n");
  printf ("                size are redundant for the rectangular filter;\n");
  printf ("                the cutoff is used if both are specified.\n");
  printf ("            -L: print Software License for this module\n");
  return (-1);
}


/* INPUT:       function reads input parameters
 *                  usage: input (argc, argv, &cutoff, &fltrSize, &quickFlag)
 */

#define USAGE_EXIT(VALUE) {usage (VALUE); return (-1);}

long
input (argc, argv, cutoff, fltrSize, quickFlag)
     int argc;
     char *argv[];
     double *cutoff;            /* cutoff frequency (0.0 to 1.0) */
     long *fltrSize;            /* sidelength of square filter */
     short *quickFlag;          /* for quick and dirty rect. filter */
{
  long n;

  if (argc < 3)
    USAGE_EXIT (1);

  *cutoff = 0.0;
  *fltrSize = 0;
  *quickFlag = 0;

  for (n = 3; n < argc; n++) {
    if (strcmp (argv[n], "-f") == 0) {
      if (++n == argc || argv[n][0] == '-')
        USAGE_EXIT (-1);
      *cutoff = atof (argv[n]);
      if (*cutoff < 0.0 || *cutoff > 0.5) {
        printf ("Cutoff frequency must be between 0.0 and 0.5.\n");
        USAGE_EXIT (-1);
      }
    }
    else if (strcmp (argv[n], "-s") == 0) {
      if (++n == argc || argv[n][0] == '-')
        USAGE_EXIT (-1);
      *fltrSize = atol (argv[n]);
    }
    else if (strcmp (argv[n], "-q") == 0)
      *quickFlag = 1;
    else if (strcmp (argv[n], "-L") == 0) {
      print_sos_lic ();
      exit (0);
    }
    else
      USAGE_EXIT (-1);
  }

/* resolve any redundancy for rectangular filter parameter specification */
  if ((*quickFlag) && (*fltrSize != 0 && *cutoff != 0.0)) {
    printf ("For rectangular filter, specifying filter cutoff and size\n");
    printf ("are redundant. Program is using size -- not cutoff -- here.\n");
  }

  if (*cutoff == 0.0)
    *cutoff = DFLT_CUTOFF;

  return (0);
}
