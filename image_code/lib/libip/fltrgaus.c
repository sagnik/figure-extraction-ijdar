/* 
 * fltrgaus.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#define ROOTLOG2 0.832554611    /* for Gaussian calc of std. dev. */

/*
 * fltrgaus()
 *   DESCRIPTION:
 *     fltrgaus performs Gaussian filtering in frequency domain
 *     with specified low & high pass bounds
 *   ARGUMENTS:
 *     imgReal(float **) pointer to real image array
 *     imgImag(float **) pointer to imaginary image array
 *     nRow, nCol(long) number of rows and columns for real and img arrays
 *     passType(short)  passType=0 low pass
 *                              passType=1 high pass
 *                              passType=2 band pass
 *                              passType=3 stop pass
 *     f1, f2(double) low, high pass frequency bounds
 *   RETURN VALUE:
 *     none
 */

void
fltrgaus (imgReal, imgImag, nRow, nCol, passType, f1, f2)
     float **imgReal, **imgImag;  /* real,complex image arrays */
     long nRow, nCol;           /* size of image */
     short passType;            /* lowpass=0, high=1, band=2, stop=3 */
     double f1, f2;             /* low,high pass frequency bounds */
{
  register long x, y, nRowD2, nColD2,  /* half of row/column */
    nRowM1, nColM1;             /* row/col minus 1 */
  double bigger;                /* passband fraction fct of bigger axis */
  double *fltr;                 /* filter vector */
  double stdDevL, stdDevH;      /* std. dev.s of low and high pass fltrs */
  long maxRad;                  /* max. sampling radius */
  long dist;                    /* euclidean distance to point */
  double tempL, tempH;
  long i;

/* allocate filter vector -- radius from (u,v)=(0,0) to corners of freq plot */
  nRowD2 = nRow / 2;
  nColD2 = nCol / 2;
  bigger = (double) (nRowD2 > nColD2) ? nRowD2 : nColD2;
  maxRad = (long) sqrt ((double) (nRowD2 * nRowD2 + nColD2 * nColD2)) + 1;
  fltr = (double *) calloc (maxRad, sizeof (double));


/* determine filter vector coefficients for chosen type of filter */
  switch (passType) {
  case 0:                      /* low-pass */
    stdDevL = f1 / ROOTLOG2 * bigger;
    for (i = 0; i < maxRad; i++)
      fltr[i] = exp (-(double) i * (double) i / (2.0 * stdDevL * stdDevL));
    break;
  case 1:                      /* high-pass */
    stdDevH = f1 / ROOTLOG2 * bigger;
    for (i = 0; i < maxRad; i++)
      fltr[i] = 1.0 -
        exp (-(double) i * (double) i / (2.0 * stdDevH * stdDevH));
    break;
  case 2:                      /* band-pass */
    stdDevH = f1 / ROOTLOG2 * bigger;
    stdDevL = f2 / ROOTLOG2 * bigger;
    for (i = 0; i < maxRad; i++) {
      tempL = exp (-(double) i * (double) i / (2.0 * stdDevL * stdDevL));
      tempH = 1.0 -
        exp (-(double) i * (double) i / (2.0 * stdDevH * stdDevH));
      fltr[i] = tempL * tempH;
    }
    break;
  case 3:                      /* and band-stop */
    stdDevL = f1 / ROOTLOG2 * bigger;
    stdDevH = f2 / ROOTLOG2 * bigger;
    for (i = 0; i < maxRad; i++) {
      tempL = exp (-(double) i * (double) i / (2.0 * stdDevL * stdDevL));
      tempH = 1.0 -
        exp (-(double) i * (double) i / (2.0 * stdDevH * stdDevH));
      fltr[i] = tempL + tempH;
    }
    break;
  default:
    break;
  }

/* perform filtering */
  nRowM1 = nRow - 1;
  nColM1 = nCol - 1;
  for (y = 0; y < nRowD2; y++) {
    for (x = 0; x < nColD2; x++) {
      dist = (long) (sqrt ((double) (y * y + x * x)) + 0.5);


      imgReal[y][x] *= (float) fltr[dist];
      imgReal[y][nColM1 - x] *= (float) fltr[dist];
      imgReal[nRowM1 - y][x] *= (float) fltr[dist];
      imgReal[nRowM1 - y][nColM1 - x] *= (float) fltr[dist];

      imgImag[y][x] *= (float) fltr[dist];
      imgImag[y][nColM1 - x] *= (float) fltr[dist];
      imgImag[nRowM1 - y][x] *= (float) fltr[dist];
      imgImag[nRowM1 - y][nColM1 - x] *= (float) fltr[dist];
    }
  }


  return;
}
