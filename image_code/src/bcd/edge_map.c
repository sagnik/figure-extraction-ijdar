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
extern int nxXny;               /*??? */

#define _nx my_image->nx
#define image_zc_x(ix,iy,i) \
(((image_locx(iy,ix,i)>0) != (image_locx(iy,ix+1,i+1)>0)) ?EDGE_X:0)

#define image_zc_y(ix,iy,i) \
(((image_locy(iy+1,ix,i+_nx)>0) != (image_locy(iy,ix,i)>0)) ?EDGE_Y:0)

#define image_zc_135(ix,iy,i) \
(((image_loc135(iy+1,ix+1,i+_nx+1)>0) != (image_loc135(iy,ix,i)>0)) ?EDGE_135:0)

#define image_zc_45(ix,iy,i) \
(((image_loc45(iy+1,ix-1,i+_nx-1)>0) != (image_loc45(iy,ix,i)>0)) ?EDGE_45:0)

unsigned char *
image_edges (int threshold)
{
  unsigned char *map;
  register int ix, iy, nx, orient_flag, index, ny;

  register int *px = my_image->idx;
  register int *py = my_image->idy;
  register int *p45 = my_image->id45;
  register int *p135 = my_image->id135;
  register unsigned char *mapp;

  nx = my_image->nx;
  ny = my_image->ny;
  nxXny = nx * ny;

  if ((map = (unsigned char *) malloc (ny * nx * sizeof (unsigned char))) == 0) {
    fprintf (stderr, "error: cannot allocate map array\n");
    exit (1);
  }
  mapp = map;

  for (iy = 0; iy < ny; iy++) {
    for (ix = 0; ix < nx; ix++) {
      register int sx, sy, s45, s135;
      register int big;
      sx = abs (*px);
      px++;
      sy = abs (*py);
      py++;
      s45 = (int) ((float) (abs (*p45)) / diag_scale);
      p45++;
      s135 = (int) ((float) (abs (*p135)) / diag_scale);
      p135++;

      big = sx;

      orient_flag = EDGE_X;

      if (sy > big) {
        big = sy;
        orient_flag = EDGE_Y;
      }
      if (s45 > big) {
        big = s45;
        orient_flag = EDGE_45;
      }
      if (s135 > big) {
        big = s135;
        orient_flag = EDGE_135;
      }

      my_image->orient_flag = orient_flag;

      if (big > threshold) {
        index = mapp - map;
        switch (orient_flag) {
        case EDGE_X:
          *mapp++ = image_zc_x (ix, iy, index);
          break;
        case EDGE_Y:
          *mapp++ = image_zc_y (ix, iy, index);
          break;
        case EDGE_45:
          *mapp++ = image_zc_45 (ix, iy, index);
          break;
        case EDGE_135:
          *mapp++ = image_zc_135 (ix, iy, index);
          break;
        default:
          fprintf (stderr, "error in case statements\n");
          exit (1);
          break;
        }
      }
      else {
        *mapp++ = 0;
      }
    }
  }
#ifdef DEBUG
  image_Write_char ("hi_map", map);
#endif
  return (map);
}

int
image_edge_map_lo (register int ix, register int iy, register int index)
{
  register int big, sx, sy, s45, s135;

  sx = abs (my_image->idx[index]);
  sy = abs (my_image->idy[index]);
  s45 = (int) ((float) (abs (my_image->id45[index])) / diag_scale);
  s135 = (int) ((float) (abs (my_image->id135[index])) / diag_scale);
  big = sx;

  my_image->orient_flag = EDGE_X;

  if (sy > big) {
    big = sy;
    my_image->orient_flag = EDGE_Y;
  }
  if (s45 > big) {
    big = s45;
    my_image->orient_flag = EDGE_45;
  }
  if (s135 > big) {
    big = s135;
    my_image->orient_flag = EDGE_135;
  }

  if (big > my_image->lo_threshold) {
    switch (my_image->orient_flag) {
    case EDGE_X:
      return (image_zc_x (ix, iy, index));
    case EDGE_Y:
      return (image_zc_y (ix, iy, index));
    case EDGE_45:
      return (image_zc_45 (ix, iy, index));
    case EDGE_135:
      return (image_zc_135 (ix, iy, index));
    default:
      fprintf (stderr, "error in case statements\n");
      exit (1);
      break;
    }
  }
  else
    return (0);
}
