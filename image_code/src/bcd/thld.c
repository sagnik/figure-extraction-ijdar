/*
 * This program is used with permission from I. Cox.
 * Please reference:
 * R. A. Boie, I. Cox, Proc. IEEE 1st Int. Conf. Computer Vision,
 * London, 1987, pp. 450-456.
 */

#include <stdio.h>
#include "edge_finder.h"

extern struct image *my_image;

int
image_threshold ()
{
  int ix, iy, nx, ny;
  int *detx, tmp;
  float mad = (float) 0;        /* calculate mean absolute deviation */

  detx = my_image->idx;
  nx = my_image->nx;
  ny = my_image->ny;

  for (iy = 0; iy < ny; iy++) {
    for (ix = 0; ix < nx; ix++) {
      tmp = *detx++;
      mad += abs (tmp);
    }
  }
  return ((int) ((float) (3 * mad / nx / ny) / 0.8));
}
