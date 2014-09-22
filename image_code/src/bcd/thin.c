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
image_thin ()
{
  register unsigned char *emP, *emPiy;
  register int ix, nx, nxM1, nxP1;
  register int iy, nlinks, npieces;
  register int nyM1;

  register int b01, b12, b21, b10;
  register int p1, p2, p3, p4;
  register int b00, b02, b20, b22;

  nx = my_image->nx;
  nxM1 = nx - 1;
  nxP1 = nx + 1;
  nyM1 = my_image->ny - 1;

  emPiy = &my_image->edge_map[0];
  for (iy = 1; iy < nyM1; iy++) {
    emPiy += nx;
    for (ix = 1; ix < nxM1; ix++) {
      emP = emPiy + ix;
      b01 = *(emP - nx) > 0;
      b12 = *(emP + 1) > 0;
      b21 = *(emP + nx) > 0;
      b10 = *(emP - 1) > 0;
      if ((b01 + b12 + b21 + b10) > 1) {
        b00 = *(emP - nxP1) > 0;
        b02 = *(emP - nxM1) > 0;
        b20 = *(emP + nxM1) > 0;
        b22 = *(emP + nxP1) > 0;

        p1 = b00 | b01;
        p2 = b02 | b12;
        p3 = b22 | b21;
        p4 = b20 | b10;

        nlinks = b01 & p2;
        nlinks += b12 & p3;
        nlinks += b21 & p4;
        nlinks += b10 & p1;

        npieces = p1 + p2 + p3 + p4;

        if ((npieces - nlinks) < 2)
          *emP = 0;             /*edge_map[iy*nx+ix]=0; */
      }
    }
  }
  return (my_image->edge_map);
}
