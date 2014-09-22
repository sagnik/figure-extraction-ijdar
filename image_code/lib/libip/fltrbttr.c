/* 
 * fltrbttr.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

#include <stdlib.h>
#include <malloc.h>
#include <math.h>

/*
 * fltrbttr()
 *   DESCRIPTION:
 *     fltrbttr performs Butterworth filtering in frequency domain
 *     with specified low & high pass bounds and filter order
 *   ARGUMENTS:
 *     imgReal(float **) pointer to real image array
 *     imgImag(float **) pointer to imaginary image array
 *     nRow, nCol(long) number of rows and columns for real and img arrays
 *     passType(short)  passType=0 low pass
 *                              passType=1 high pass
 *                              passType=2 band pass
 *                              passType=3 stop pass
 *     f1, f2(double) low, high pass frequency bounds
 *     order(double) order of filter
 *   RETURN VALUE:
 *     none
 */

void
fltrbttr (imgReal, imgImag, nRow, nCol, passType, f1, f2, order)
     float **imgReal, **imgImag;  /* real,complex image arrays */
     long nRow, nCol;           /* size of image */
     short passType;            /* lowpass=0, high=1, band=2, stop=3 */
     double f1, f2;             /* low,high pass frequency bounds */
     double order;              /* order of filter */
{
  register long x, y, nRowD2, nColD2,  /* half of row/column */
    nRowM1, nColM1;             /* row/col minus 1 */
  double bigger;                /* passband fraction fct of bigger axis */
  double *fltr;                 /* filter vector */
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

/* determine filter vector coefficients for chosen passband type of filter */
  order *= 2.0;
  switch (passType) {
  case 0:                      /* low-pass */
    f1 *= bigger;
    for (i = 0; i < maxRad; i++) {
      fltr[i] = 1.0 / (1.0 + 0.414 * pow (((double) i / f1), order));

    }
    break;
  case 1:                      /* high-pass */
    f1 *= bigger;
    for (i = 0; i < maxRad; i++)
      fltr[i] = 1.0 - 1.0 / (1.0 + 0.414 * pow (((double) i / f1), order));
    break;
  case 2:                      /* band-pass */
    f1 *= bigger;
    f2 *= bigger;
    for (i = 0; i < maxRad; i++) {
      tempL = 1.0 / (1.0 + 0.414 * pow (((double) i / f1), order));
      tempH = 1.0 - 1.0 / (1.0 + 0.414 * pow (((double) i / f2), order));
      fltr[i] = tempL * tempH;
    }
    break;
  case 3:                      /* and band-stop */
    f1 *= bigger;
    f2 *= bigger;
    for (i = 0; i < maxRad; i++) {
      tempL = 1.0 / (1.0 + 0.414 * pow (((double) i / f1), order));
      tempH = 1.0 - 1.0 / (1.0 + 0.414 * pow (((double) i / f2), order));
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
