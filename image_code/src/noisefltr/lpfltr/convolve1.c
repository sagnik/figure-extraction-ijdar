/* 
 * convolve1.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* CONVOLVE1:   function performs 2-D convolution by separable, 
 *            symmetric, 1-D filter mask
 *                  usage: convolve1 (imgIO, fltr1D, nFltr)
 */

#include <images.h>
#include <tiffimage.h>

void
convolve1 (imgIO, fltr1D, nFltr)
     Image *imgIO;              /* input/output image structure */
     long *fltr1D;              /* 1-D of filter mask */
     long nFltr;                /* number of filter coefficients */
{
  Image *imgT;                  /* intermediate image structure */
  unsigned char **imgIOn,       /* input/output image */
  **imgInt;                     /* intermediate image */
  long width, height;           /* size of image */
  long sumFltr;                 /* sum of fltr coefficients */
  long sum;                     /* sum of filter convolution at a pixel */
  long midFltr;                 /* middle coefficient index of filter */
  long xEnd, yEnd;              /* end coefficients of convolution */
  long x, y, i;

/* intermediate image for result of row-wise convolution */
  imgIOn = ImageGetPtr (imgIO);
  height = ImageGetHeight (imgIO);
  width = ImageGetWidth (imgIO);
  imgT = ImageAlloc (height, width, 8);
  imgInt = ImageGetPtr (imgT);

/* find sum of filter coefficients */
  for (i = 0, sumFltr = 0; i < nFltr; i++)
    sumFltr += fltr1D[i];

/* perform row-wise convolution */
  midFltr = (nFltr - 1) / 2;
  xEnd = width - midFltr;
  for (y = 0; y < height; y++) {
    for (x = midFltr; x < xEnd; x++) {
      sum = fltr1D[midFltr] * imgIOn[y][x];
      for (i = 1; i <= midFltr; i++)
        sum += fltr1D[i + midFltr]
          * (imgIOn[y][x - i] + imgIOn[y][x + i]);
      imgInt[y][x] = (unsigned char) (sum / sumFltr);
    }
  }

/* perform column-wise convolution */
  yEnd = height - midFltr;
  for (y = midFltr; y < yEnd; y++) {
    for (x = midFltr; x < xEnd; x++) {
      sum = fltr1D[midFltr] * imgInt[y][x];
      for (i = 1; i <= midFltr; i++)
        sum += fltr1D[i + midFltr] * (imgInt[y - i][x] + imgInt[y + i][x]);
      imgIOn[y][x] = (unsigned char) (sum / sumFltr);
    }
  }

/* set border regions to zero */
  for (y = 0; y < height; y++)
    for (x = 0; x < midFltr; x++)
      imgIOn[y][x] = imgIOn[y][width - x - 1] = 0;
  for (y = 0; y < midFltr; y++)
    for (x = 0; x < width; x++)
      imgIOn[y][x] = imgIOn[height - y - 1][x] = 0;

  return;
}
