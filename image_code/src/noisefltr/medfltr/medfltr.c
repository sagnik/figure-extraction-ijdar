/* 
 * medfltr.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* MEDFLTR:     program performs median filtering on image
 *                usage: medfltr inimg outimg [-s fltrSize] [-L]
 *
 */

#define SIZE_DFLT 3             /* default filter size */
#define MAXLIST 225             /* max list size */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <images.h>
#include <tiffimage.h>
extern void print_sos_lic ();

unsigned char median2 ();       /* median filter function */
long list[MAXLIST];             /* list of filter neighborhood */
long nList;                     /* length of list */

long usage (short);
long input (int, char **, long *);

main (argc, argv)
     int argc;
     char *argv[];
{
  Image *imgI, *imgO;           /* I/O image structure */
  unsigned char **imgIn, **imgOut;  /* input and output images */
  long width, height;           /* image size */
  long fltrSize;                /* filter mask size */
  long midFltr;                 /* middle filter coefficient */
  long xEnd, yEnd;              /* end of image minus borders */
  long xxEnd, yyEnd;
  long x, y, xx, yy;

  if (input (argc, argv, &fltrSize) < 0)
    return (-1);

/* allocate input and output image memory */
  imgI = ImageIn (argv[1]);
  imgIn = imgI->img;
  height = ImageGetHeight (imgI);
  width = ImageGetWidth (imgI);
  printf ("Image size is %dx%d. Filter size is %d.\n",
          width, height, fltrSize);

  imgO = ImageAlloc (height, width, 8);
  imgOut = ImageGetPtr (imgO);

/* set border regions of output image to zero */
  midFltr = (fltrSize - 1) / 2;
  for (y = 0; y < height; y++)
    for (x = 0; x < midFltr; x++)
      imgOut[y][x] = imgOut[y][width - x - 1] = 0;
  for (y = 0; y < midFltr; y++)
    for (x = 0; x < width; x++)
      imgOut[y][x] = imgOut[height - y - 1][x] = 0;

/* perform filtering */
  yEnd = height - midFltr;
  xEnd = width - midFltr;
  for (y = midFltr; y < yEnd; y++) {
    for (x = midFltr; x < xEnd; x++) {
      yyEnd = y + midFltr;
      xxEnd = x + midFltr;
      for (yy = y - midFltr, nList = 0; yy <= yyEnd; yy++)
        for (xx = x - midFltr; xx <= xxEnd; xx++, nList++)
          list[nList] = imgIn[yy][xx];
      imgOut[y][x] = median2 ();
    }
  }

/* write out median-filtered image */
  ImageOut (argv[2], imgO);

  return (0);
}


/* MEDIAN2: function returns median value from an input list of integer values
 *        This function is more efficient than function MEDIAN1 when
 *          the number of points <n> is small wrt the number of values that
 *          they may take on.
 *              usage: med = median2()
 */

unsigned char
median2 ()
{
  long arrayle[MAXLIST],        /* array of number of values that is less
                                 * * than or equal to the corresponding
                                 * * <value> */
    value[MAXLIST],             /* value corresponding to less than or
                                 * * equal to array <arrayle> */
    nd2;                        /* number of input values, divided by 2 */

  register long sumle,          /* running sum of less than or equals */
    sum,                        /* sum of numbers less than or equal to */
    i, j;


/* initialize */
  for (i = 0; i < nList; i++)
    arrayle[i] = 0;

/* construct less than or equal to array */
  for (i = 0; i < nList; i++) {
    sumle = 0;
    for (j = 0; j < nList; j++)
      if (list[i] <= list[j])
        sumle++;
    arrayle[sumle]++;
    value[sumle] = list[i];
  }

/* find median */
  nd2 = nList / 2;
  sum = 0;
  for (i = 1; i <= nList; i++) {
    sum += arrayle[i];
    if (sum > nd2)
      break;
  }

  return ((unsigned char) value[i]);
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
  printf ("USAGE: medfltr inimg outimg [-s FLTRSIZE] [-L]\n");
  if (flag == 0)
    return (-1);

  printf ("\nmedfltr performs median filtering upon image\n");
  printf ("using filter window of chosen size.\n\n");
  printf ("ARGUMENTS:\n");
  printf ("    inimg: input image filename (TIF)\n");
  printf ("   outimg: output image filename (TIF)\n\n");
  printf ("OPTIONS:\n");
  printf ("  -s FLTR_SIZE: filter size; the larger the size,\n");
  printf ("                the greater the degree of smoothing;\n");
  printf ("                the size must be odd. (Default = %d)\n", SIZE_DFLT);
  printf ("            -L: print Software License for this module\n");
  return (-1);
}


/* INPUT:       function reads input parameters
 *                  usage: input (argc, argv, &fltrSize)
 */

#define USAGE_EXIT(VALUE) {usage (VALUE); return (-1);}

long
input (argc, argv, fltrSize)
     int argc;
     char *argv[];
     long *fltrSize;            /* sidelength of square filter */
{
  long n;

  if (argc < 3)
    USAGE_EXIT (1);

  *fltrSize = SIZE_DFLT;

  for (n = 3; n < argc; n++) {
    if (strcmp (argv[n], "-s") == 0) {
      if (++n == argc || argv[n][0] == '-')
        USAGE_EXIT (0);
      *fltrSize = atol (argv[n]);
    }
    else if (strcmp (argv[n], "-L") == 0) {
      print_sos_lic ();
      exit (0);
    }
    else
      USAGE_EXIT (0);
  }

  if (!(*fltrSize % 2))
    *fltrSize += 1;

  return (0);
}
