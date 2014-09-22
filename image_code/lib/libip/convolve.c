/* 
 * convolve.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ip.h"
#include "convolve.h"

/*
 * convolve()
 *   DESCRIPTION:
 *     convolve performs a 2-D convolution on ImageIn
 *     using Kernel as the kernel and
 *     placing the convolved image in ImageOut
 *   ARGUMENTS:
 *     ImageIn(Image *) pointer to input image struct (see tiffimage.h)
 *     ImageOut(Image *) pointer to output image struct (see tiffimage.h)
 *     Kernel(Matrix *) pointer to convolution kernel struct (see convolve.h)
 *   RETURN VALUE:
 *     0
 */
int
convolve (Image * ImageIn, Image * ImageOut, Matrix * Kernel)
{

  int row, column, i, j;
  int kernel_rows, kernel_cols, dead_rows, dead_cols;
  float normal_factor;
  unsigned char **pImgOut;
  float sumval;
  float *filptr;
  int pixval;


  pImgOut = ImageOut->img;
  kernel_rows = Kernel->nRows;
  kernel_cols = Kernel->nCols;

  dead_rows = kernel_rows / 2;
  dead_cols = kernel_cols / 2;

  normal_factor = (float) 0.0;
  for (row = 0; row < kernel_rows; row++) {
    filptr = Kernel->matrix[row];
    for (column = 0; column < kernel_cols; column++)
      normal_factor += (float) (Kernel->matrix[row][column]);
  }

  if (!normal_factor)
    normal_factor = (float) 1;

  for (row = 0; row < (ImageIn->height) - kernel_rows + 1; row++) {
    for (column = 0; column < (ImageIn->width) - kernel_cols + 1; column++) {
      sumval = (float) 0.0;
      for (i = 0; i < kernel_rows; i++) {
        for (j = 0; j < kernel_cols; j++) {
          sumval += (ImageIn->img[i + row][j + column]) * (Kernel->matrix[i][j]);
        }
      }
      if ((pixval = abs ((int) (sumval / normal_factor))) > 255)
        pixval = 255;
      pImgOut[row + dead_rows][column + dead_cols] = (unsigned char) pixval;
    }
  }
  return (0);
}
