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
void image_neighbor_fwd ();
void image_neighbor_bwd ();

static nx, ny;
int nxXny;

unsigned char *
image_hysteresis (int lo_thld)
{
  register int iy, ix;
  register unsigned char *lmapP, *lmap_hiP, *mapP;

  nx = my_image->nx;
  ny = my_image->ny;
  nxXny = nx * ny;
  my_image->lo_threshold = lo_thld;
  my_image->edge_map_hi = my_image->edge_map;
  my_image->edge_map = (unsigned char *) malloc (nx * ny * sizeof (unsigned char));

  lmap_hiP = &my_image->edge_map_hi[0];
  lmapP = &my_image->edge_map[0];

  mapP = lmapP;
  for (ix = nx * ny; --ix >= 0;)
    *mapP++ = 0;

  for (iy = 0; iy < ny; iy++, lmap_hiP += nx, lmapP += nx) {
    mapP = lmapP;
    for (ix = 0; ix < nx; ix++, mapP++) {
      if (lmap_hiP[ix] != 0) {
        *mapP = lmap_hiP[ix];
        image_neighbor_fwd (iy, ix, mapP);
        image_neighbor_bwd (iy, ix, mapP);
      }
    }
  }
  return (my_image->edge_map);
}

void
image_neighbor_fwd (register int iy, register int ix, register unsigned char *mapP)
{
  switch (*mapP) {
  case 5:
    return;

  case EDGE_Y:                 /*0 */
    if (!Fcontour (iy, ix + 1) && Fcontour (iy, ix + 2))
      goto L_EDGE_Y;
    else if (!(Fcontour (iy - 1, ix + 1) || Fcontour (iy + 1, ix + 1)) &&
             (Fcontour (iy - 1, ix + 2) || Fcontour (iy + 1, ix + 2))) {
    L_EDGE_Y:if (ix + 1 < nx)
        *(mapP + 1) = 5;
    }
    break;
  case EDGE_135:               /*45 */
    if (!Fcontour (iy - 1, ix + 1) && Fcontour (iy - 2, ix + 2))
      goto L_EDGE_135;
    else if (!(Fcontour (iy, ix + 1) || Fcontour (iy - 1, ix)) &&
             (Fcontour (iy - 2, ix + 1) || Fcontour (iy - 1, ix + 2))) {
    L_EDGE_135:if ((iy - 1 >= 0) && (ix + 1 < nx))
        *(mapP - nx + 1) = 5;
    }
    break;
  case EDGE_X:                 /*90 */
    if (!Fcontour (iy - 1, ix) && Fcontour (iy - 2, ix))
      goto L_EDGE_X;
    else if (!(Fcontour (iy - 1, ix - 1) || Fcontour (iy - 1, ix + 1)) &&
             (Fcontour (iy - 2, ix - 1) || Fcontour (iy - 2, ix + 1))) {
    L_EDGE_X:if (iy - 1 >= 0)
        *(mapP - nx) = 5;
    }
    break;
  case EDGE_45:                /*135 */
    if (!Fcontour (iy + 1, ix + 1) && Fcontour (iy + 2, ix + 2))
      goto L_EDGE_45;
    else if (!(Fcontour (iy, ix + 1) || Fcontour (iy + 1, ix)) &&
             (Fcontour (iy + 1, ix + 2) || Fcontour (iy + 2, ix + 1))) {
    L_EDGE_45:if ((iy + 1 < ny) && (ix + 1 < nx))
        *(mapP + nx + 1) = 5;
    }
    break;
  default:
    fprintf (stderr, "error in case statements\n");
    fprintf (stderr, "x=%d y=%d\n", ix, iy);
    exit (1);
    break;
  }
}

void
image_neighbor_bwd (register int iy, register int ix, register unsigned char *mapP)
{
  switch (*mapP) {
  case 5:
    return;

  case EDGE_Y:                 /*0 */
    if (!Bcontour (iy, ix - 1) && Bcontour (iy, ix - 2))
      goto L_EDGE_Y;
    else if (!(Bcontour (iy - 1, ix - 1) || Bcontour (iy + 1, ix - 1)) &&
             (Bcontour (iy - 1, ix - 2) || Bcontour (iy + 1, ix - 2))) {
    L_EDGE_Y:if (ix - 1 >= 0)
        *(mapP - 1) = 5;
    }
    break;
  case EDGE_135:               /*45 */
    if (!Bcontour (iy + 1, ix - 1) && Bcontour (iy + 2, ix - 2))
      goto L_EDGE_135;
    else if (!(Bcontour (iy, ix - 1) || Bcontour (iy + 1, ix)) &&
             (Bcontour (iy + 1, ix - 2) || Bcontour (iy + 2, ix - 1))) {
    L_EDGE_135:if ((iy + 1 < ny) && (ix - 1 >= 0))
        *(mapP + nx - 1) = 5;
    }
    break;
  case EDGE_X:                 /*90 */
    if (!Bcontour (iy + 1, ix) && Bcontour (iy + 2, ix))
      goto L_EDGE_X;
    else if (!(Bcontour (iy + 1, ix - 1) || Bcontour (iy + 1, ix + 1)) &&
             (Bcontour (iy + 2, ix - 1) || Bcontour (iy + 2, ix + 1))) {
    L_EDGE_X:if (iy + 1 < ny)
        *(mapP + nx) = 5;
    }
    break;
  case EDGE_45:                /*135 */
    if (!Bcontour (iy - 1, ix - 1) && Bcontour (iy - 2, ix - 2))
      goto L_EDGE_45;
    else if (!(Bcontour (iy, ix - 1) || Bcontour (iy - 1, ix)) &&
             (Bcontour (iy - 1, ix - 2) || Bcontour (iy - 2, ix - 1))) {
    L_EDGE_45:if ((iy - 1 >= 0) && (ix - 1 >= 0))
        *(mapP - nx - 1) = 5;
    }
    break;
  default:
    fprintf (stderr, "error in case statements\n");
    fprintf (stderr, "x=%d y=%d\n", ix, iy);
    exit (1);
    break;
  }
}

int
Fcontour (register int iy, register int ix)
{
  int edge_pt, index;
  register unsigned char *mapP;

  /*if(ix<0||ix>=nx||iy<0||iy>=ny) return(0); */

  index = iy * nx + ix;
  if (index < 0 || index >= nxXny)
    return (0);

  mapP = &my_image->edge_map[index];
  if (*mapP > 0)
    return (1);
  else if ((edge_pt = image_edge_map_lo (ix, iy, index)) != 0) {
    *mapP = edge_pt;
    image_neighbor_fwd (iy, ix, mapP);
    return (1);
  }
  else
    return (0);
}

int
Bcontour (register int iy, register int ix)
{
  register unsigned char *mapP;
  int edge_pt, index;

  /*if(ix<0||ix>=nx||iy<0||iy>=ny) return(0); */

  index = iy * nx + ix;
  if (index < 0 || index >= nxXny)
    return (0);

  mapP = &my_image->edge_map[index];
  if (*mapP > 0)
    return (1);
  else if ((edge_pt = image_edge_map_lo (ix, iy, index)) != 0) {
    *mapP = edge_pt;
    image_neighbor_bwd (iy, ix, mapP);
    return (1);
  }
  else
    return (0);
}
