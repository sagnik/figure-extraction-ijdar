/* 
 * smooth.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* SMOOTH:      function performs 2-D smoothing by separable, 1-D averaging
 *                usage: smooth (imgIO, fltr1D, nFltr)
 */

#include <images.h>
#include <tiffimage.h>

smooth (imgIO, nFltr)
     Image *imgIO;              /* input/output image structure */
     long nFltr;                /* number of filter coefficients */
{
  Image *imgT;                  /* intermediate image structure */
  unsigned char **imgIOn,       /* input/output image */
  **imgInt;                     /* intermediate image */
  long width, height;           /* size of image */
  long sum;                     /* sum of filter convolution at a pixel */
  long midFltr;                 /* middle coefficient index of filter */
  long xEnd, yEnd;              /* end coefficients of convolution */
  long x, y, i;

/* intermediate image for result of row-wise smoothing */
  imgIOn = ImageGetPtr (imgIO);
  height = ImageGetHeight (imgIO);
  width = ImageGetWidth (imgIO);
  imgT = ImageAlloc (height, width, 8);
  imgInt = ImageGetPtr (imgT);

/* perform row-wise smoothing */
  midFltr = (nFltr - 1) / 2;
  yEnd = height - midFltr;
  xEnd = width - midFltr;
  for (y = 0; y < height; y++) {
    for (x = midFltr; x < xEnd; x++) {
      sum = imgIOn[y][x];
      for (i = 1; i <= midFltr; i++) {
        sum += imgIOn[y][x - i] + imgIOn[y][x + i];
      }
      imgInt[y][x] = (unsigned char) (sum / nFltr);
    }
  }

/* perform column-wise convolution */
  for (y = midFltr; y < yEnd; y++) {
    for (x = midFltr; x < xEnd; x++) {
      sum = imgInt[y][x];
      for (i = 1; i <= midFltr; i++)
        sum += imgInt[y - i][x] + imgInt[y + i][x];
      imgIOn[y][x] = (unsigned char) (sum / nFltr);
    }
  }

/* set border regions to zero */
  for (y = 0; y < height; y++)
    for (x = 0; x < midFltr; x++)
      imgIOn[y][x] = imgIOn[y][width - x - 1] = 0;
  for (y = 0; y < midFltr; y++)
    for (x = 0; x < width; x++)
      imgIOn[y][x] = imgIOn[height - y - 1][x] = 0;

  return (0);
}
