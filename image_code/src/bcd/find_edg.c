/*
 * This program is used with permission from I. Cox.
 * Please reference:
 * R. A. Boie, I. Cox, Proc. IEEE 1st Int. Conf. Computer Vision,
 * London, 1987, pp. 450-456.
 */
#include <stdio.h>
#include <math.h>
#include "edge_finder.h"

extern struct image *my_image;

unsigned char *
image_find_edges (float sigma, int *threshold)
{
  unsigned char *image_edges ();

  fprintf (stderr, "\ngenerating filter sigma = %.1f", sigma);
  generate_filter (sigma);
  fprintf (stderr, " ( length = %d)\n", my_image->nf);

  fprintf (stderr, "\nconvolving image\n");
  image_convolve (my_image->an_image);

  fprintf (stderr, "\ngenerating detx\n");
  image_detx ();

  fprintf (stderr, "\ngenerating dety\n");
  image_dety ();

  fprintf (stderr, "\ngenerating det45\n");
  image_det45 ();

  fprintf (stderr, "\ngenerating det135\n");
  image_det135 ();

  if (*threshold == 0) {
    fprintf (stderr, "\nestimating threshold\n");
    *threshold = image_threshold ();
  }
  fprintf (stderr, "\ngenerating edge_map (threshold = %d)\n",
           *threshold);
  my_image->edge_map = image_edges (*threshold);

  return (my_image->edge_map);
}
