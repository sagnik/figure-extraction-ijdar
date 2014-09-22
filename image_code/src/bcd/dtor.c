/*
 * This program is used with permission from I. Cox.
 * Please reference:
 * R. A. Boie, I. Cox, Proc. IEEE 1st Int. Conf. Computer Vision,
 * London, 1987, pp. 450-456.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "edge_finder.h"

extern struct image *my_image;

void
image_cleanup ()
{
  free (my_image->gaussian);
  free (my_image->filter);
  free (my_image->idx);
  free (my_image->idy);
  free (my_image->id45);
  free (my_image->id135);
  free (my_image->edge_map_hi);
}
