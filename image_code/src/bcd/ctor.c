/*
 * This program is used with permission from I. Cox.
 * Please reference:
 * R. A. Boie, I. Cox, Proc. IEEE 1st Int. Conf. Computer Vision,
 * London, 1987, pp. 450-456.
 */
#include <stdio.h>
#include <math.h>
#include "edge_finder.h"

struct image *my_image;

void
image_init (unsigned char *array, int xdim, int ydim)
{
  static struct image temp_image;

  temp_image.gaussian = 0;
  temp_image.filter = 0;
  temp_image.idx = 0;
  temp_image.idy = 0;
  temp_image.id45 = 0;
  temp_image.id135 = 0;
  temp_image.edge_map = 0;
  temp_image.an_image = array;
  temp_image.nx = xdim;
  temp_image.ny = ydim;
  my_image = &temp_image;

}
