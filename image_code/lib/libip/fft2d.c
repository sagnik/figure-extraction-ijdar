/* 
 * fft2d.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>

/*
 * fft2d()
 *   DESCRIPTION:
 *     fft2d performs 2-dimensional FFT on square image file
 *     using Kernel as the kernel and
 *     placing the convolved image in ImageOut
 *   ARGUMENTS:
 *     imageReal(float **) pointer to real array
 *     imgImag(float **) pointer to imaginary array
 *     nRow, nCol(long) number of rows and columns for real and img arrays
 *                      must be power of 2
 *     flag(short)      flag=-1 forward transform
 *                              flag=1 reverse transform
 *   RETURN VALUE:
 *     none
 */

void
fft2d (imgReal, imgImag, nRow, nCol, flag)
     float **imgReal, **imgImag;  /* real and imaginary image arrays */
     register long nRow, nCol;  /* no. rows and columns */
     short flag;                /* forward transform if -1; reverse if 1 */
{
  register int x, y;
  float *tempReal, *tempImag;   /* temporary complex vectors */
  int fft ();                   /* performs 1-D FFT */

/* allocate space for temporary vectors */
  if ((tempReal = (float *) calloc (nRow, sizeof (float))) == NULL)
      exit (1);
  if ((tempImag = (float *) calloc (nRow, sizeof (float))) == NULL)
      exit (2);

/* perform row-wise FFTs */
  for (y = 0; y < nRow; y++) {
    fft (nCol, imgReal[y], imgImag[y], flag);
  }

/* perform column-wise FFTs */
  for (x = 0; x < nCol; x++) {
    for (y = 0; y < nRow; y++) {
      tempReal[y] = imgReal[y][x];
      tempImag[y] = imgImag[y][x];
    }
    fft (nRow, tempReal, tempImag, flag);
    for (y = 0; y < nRow; y++) {
      imgReal[y][x] = tempReal[y];
      imgImag[y][x] = tempImag[y];
    }
  }

  return;
}
