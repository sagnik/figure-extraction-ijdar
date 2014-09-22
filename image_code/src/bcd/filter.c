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
generate_filter (float sigma)
{
  int i;
  float two_sigma_sq;

  my_image->nf = (int) (3 * 2 * sigma);
  my_image->nf = (my_image->nf % 2 > 0 ? my_image->nf : my_image->nf + 1);
  my_image->nf2 = my_image->nf / 2;

  if ((my_image->filter = (int *) malloc (my_image->nf * sizeof (int))) == 0) {
    fprintf (stderr, "error: cannot allocate filter array\n");
    exit (1);
  }
  two_sigma_sq = (float) (2.0 * sigma * sigma);
  my_image->norm = 0;
  for (i = 0; i < my_image->nf; i++) {
    float x = (float) i - my_image->nf2;
    my_image->filter[i] = (int) (255.0 * exp (-x * x / two_sigma_sq));
    my_image->norm += my_image->filter[i];
  }
  my_image->norm = abs (my_image->norm * my_image->norm);
#ifdef DEBUG
  fprintf (stderr, "filter length = %d\n", my_image->nf);
  for (i = 0; i < my_image->nf; i++)
    fprintf (stderr, "f[%d] = %d\n", i, my_image->filter[i]);
#endif
}
