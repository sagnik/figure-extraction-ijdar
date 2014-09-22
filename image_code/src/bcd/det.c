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
image_detx ()
{
  register int *dP, *gP;
  register int ix, iy;
  register int nx, ny, nxM1;

  nx = my_image->nx;
  nxM1 = nx - 1;
  ny = my_image->ny;

  if ((my_image->idx = (int *) malloc (ny * nx * sizeof (int))) == 0) {
    fprintf (stderr, "error: cannot allocate idx array\n");
    exit (1);
  }

  /*
   * Left Col/side
   */
  dP = my_image->idx;
  gP = my_image->gaussian;
  for (iy = 0; iy < ny; iy++) {
/*              d[iy*nx] = g[iy*nx] - g[iy*nx+1]; */
    *dP = *(gP + 1) - *(gP);
    dP += nx;
    gP += nx;
  }

  /*
   *  Middle Cols
   */
  for (iy = 0; iy < ny; iy++) {
    dP = my_image->idx + iy * nx + 1;
    gP = my_image->gaussian + iy * nx + 2;
    for (ix = 1; ix < nxM1; ix++) {
/*                      d[ix] = g[ix+1] - g[ix-1]; */
      *dP = *gP - *(gP - 2);
      dP++;
      gP++;
    }
  }

  /*
   * Right Col/Side
   */
  dP = my_image->idx + nxM1;
  gP = my_image->gaussian + nxM1;
  for (iy = 0; iy < ny; iy++) {
/*              d[iy*nx+nx-1] = g[iy*nx+nx-1] - g[iy*nx+nx-2]; */
    *dP = *gP - *(gP - 1);
    dP += nx;
    gP += nx;
  }


#ifdef DEBUG
  image_Write_int ("detx", my_image->idx);
#endif
}

void
image_dety ()
{
  register int *dP, *gP;
  register int ix, iy, nx, ny, nyM1, nxPnx;

  nx = my_image->nx;
  nxPnx = nx + nx;
  ny = my_image->ny;
  nyM1 = ny - 1;

  if ((my_image->idy = (int *) malloc (ny * nx * sizeof (int))) == 0) {
    fprintf (stderr, "error: cannot allocate idy array\n");
    exit (1);
  }


  /*
   * Top Row
   */
  dP = my_image->idy;
  gP = my_image->gaussian;
  for (ix = 0; ix < nx; ix++) {
    dP[ix] = gP[ix + nx] - gP[ix];
/*              *dP = *gP - *(gP+nx);   */
/*              dP++; gP++;     */
  }

  /*
   * Middle Rows
   */
  for (ix = 0; ix < nx; ix++) {
    dP = my_image->idy + ix;
    gP = my_image->gaussian + ix;
    for (iy = 1; iy < nyM1; iy++) {
      dP += nx;
      *dP = *(gP + nxPnx) - *gP;
      gP += nx;
    }
  }

  /*
   * Bottom Row
   */
  dP = my_image->idy + (ny - 1) * nx;
  gP = my_image->gaussian + (ny - 1) * nx;
  for (ix = 0; ix < nx; ix++) {
    dP[ix] = gP[ix] - gP[ix - nx];
/*              *dP = *gP - *(gP-nx);   */
/*              dP++; gP++; */
  }

#ifdef DEBUG
  image_Write_int ("dety", my_image->idy);
#endif
}



void
image_det45 ()
{
  register int *dP, *gP;
  register int i, ix, iy, nx, index, ny;
  register nxP1, nxM1, nyM1;

  nx = my_image->nx;
  nxM1 = nx - 1;
  nxP1 = nx + 1;
  ny = my_image->ny;
  nyM1 = ny - 1;

  if ((my_image->id45 = (int *) malloc (ny * nx * sizeof (int))) == 0) {
    fprintf (stderr, "error: cannot allocate id45 array\n");
    exit (1);
  }

  /*
   * Top row
   */
  dP = my_image->id45 + nx - 2;
  gP = my_image->gaussian + nx - 2;
  for (ix = nx - 2; ix > 0; ix--) {
/*              d[ix] = g[ix] - g[ix+nx+1]; */
    *dP = *(gP + nxM1) - *(gP + 1);
    dP--;
    gP--;
  }

  /*
   * Upper Diagonal
   */
  dP = my_image->id45;
  gP = my_image->gaussian;
  for (i = nx - 2; i > 0; i--) {
    ix = i;
    iy = 1;
    index = nx + ix;
    while (ix > -1 && iy < nyM1) {
/*                      dP[iy*nx+ix] = gP[(iy+1)*nx+ix-1]-gP[(iy-1)*nx+ix+1]; */
/*                      dP[iy*nx+ix] = gP[iy*nx+ix+nx-1] -gP[iy*nx+ix-nx+1];  */
      dP[index] = gP[index + nxM1] - gP[index - nxM1];
      index += nxM1;
      ix--;
      iy++;
    }
  }

  /*
   * Lower Diagonal
   */
  for (i = 1; i < ny; i++) {
    ix = nx - 2;
    iy = i;
    index = iy * nx + ix;
    while (ix > 0 && iy < nyM1) {
/*                      dP[iy*nx+ix] = gP[(iy+1)*nx+ix-1]-gP[(iy-1)*nx+ix+1]; */
/*                      dP[iy*nx+ix] = gP[iy*nx+ix+nx-1] -gP[iy*nx+ix-nx+1];  */
      dP[index] = gP[index + nxM1] - gP[index - nxM1];
      index += nxM1;
      ix--;
      iy++;
    }
  }


  /*
   * Left Middle Side
   */
  dP = my_image->id45 + nx + nx;
  gP = my_image->gaussian + nx + nx;
  for (iy = 1; iy < nyM1; iy++) {
    *dP = *(gP + nx) - *(gP - nxM1);
  }


  /*
   * Right Middle Side
   */
  dP = my_image->id45 + nx + nx - 1;
  gP = my_image->gaussian + nx + nx - 1;
  for (iy = 1; iy < nyM1; iy++) {
/*              d[iy*nx+nx-1] = g[iy*nx+nx-1] - g[(iy-1)*nx+nx-2]; */
/*              d[iy*nx+nx-1] = g[iy*nx+nx-1] - g[iy*nx+nx-1-nx-1]; */
    *dP = *(gP + nxM1) - *(gP - nx);
    dP += nx;
    gP += nx;
  }

  /*
   * Bottom Row
   */
  dP = my_image->id45 + (ny - 1) * nx;
  gP = my_image->gaussian + (ny - 1) * nx;
  for (ix = 1; ix < nxM1; ix++) {
/*              dP[(ny-1)*nx+ix] = gP[(ny-1)*nx+ix] - gP[(ny-2)*nx+ix+1];    */
/*              dP[(ny-1)*nx+ix] = gP[(ny-1)*nx+ix] - gP[(ny-1)*nx+ix-nx+1]; */
    *dP = *(gP - 1) - *(gP - nxM1);
    dP++;
    gP++;
  }

  /*
   * Now the top left Corner
   */
  dP = my_image->id45;
  gP = my_image->gaussian;
  *dP = *(gP + nx) - *(gP + 1);

  /*
   * Now th bottom left corner
   */
  dP = my_image->id45 + (ny - 1) * nx;
  gP = my_image->gaussian + (ny - 1) * nx;
/*      dP[(ny-1)*nx+nx-1] = gP[(ny-1)*nx+nx-1] - gP[(ny-2)*nx+nx-2];      */
/*      dP[(ny-1)*nx+nx-1] = gP[(ny-1)*nx+nx-1] - gP[(ny-1)*nx+nx-1-nx-1]; */
  *dP = *(gP) - *(gP - nxM1);

  /*
   * Now the bottom right corner
   */
  dP[nxM1] = *(gP + nxM1 - 1) - *(gP - 1);


  /*
   * Now the top right Corner
   */
  dP = my_image->id45 + nxM1;
  gP = my_image->gaussian + nxM1;
  *dP = *(gP + nxM1) - *(gP);

#ifdef DEBUG
  image_Write_int ("det45", my_image->id45);
#endif
}




void
image_det135 ()
{
  register int *dP, *gP;
  register int i, ix, iy, nx, index, ny;
  register nxP1, nxM1, nyM1, nxM2;

  nx = my_image->nx;
  nxM1 = nx - 1;
  nxP1 = nx + 1;
  nxM2 = nx - 2;
  ny = my_image->ny;
  nyM1 = ny - 1;

  if ((my_image->id135 = (int *) malloc (ny * nx * sizeof (int))) == 0) {
    fprintf (stderr, "error: cannot allocate id135 array\n");
    exit (1);
  }

  /*
   * Top Middle Row
   */
  dP = my_image->id135 + 1;
  gP = my_image->gaussian + 1;
  for (ix = 1; ix < nxM1; ix++) {
/*              d[ix] = g[ix] - g[ix+nx-1]; */
    *dP = *(gP + nxP1) - *(gP - 1);
    dP++;
    gP++;
  }

  /*
   * Upper Middle Diagonal
   */
  dP = my_image->id135;
  gP = my_image->gaussian;
  for (i = 1; i < nxM1; i++) {
    ix = i;
    iy = 1;
    index = nx + ix;
    while (ix < nxM1 && iy < nyM1) {
/*                      dP[iy*nx+ix] = gP[(iy+1)*nx+ix+1]-gP[(iy-1)*nx+ix-1]; */
/*                      dP[iy*nx+ix] = gP[iy*nx+ix+nx+1]-gP[iy*nx+ix-nx-1];  */
      dP[index] = gP[index + nxP1] - gP[index - nxP1];
      index += nxP1;
      ix++;
      iy++;
    }
  }


  /*
   * Lower Middle Diagonal
   */
  for (i = 1; i < ny; i++) {
    ix = 1;
    iy = i;
    index = iy * nx + ix;
    while (ix < nxM1 && iy < nyM1) {
/*                      dP[iy*nx+ix] = gP[(iy+1)*nx+ix+1]- gP[(iy-1)*nx+ix-1]; */
/*                      dP[iy*nx+ix] = gP[iy*nx+ix+nx+1] - gP[iy*nx+ix-nx-1]; */
      dP[index] = gP[index + nxP1] - gP[index - nxP1];
      index += nxP1;
      ix++;
      iy++;
    }
  }

  /*
   * Left Middle Side
   */
  dP = my_image->id135 + nx;
  gP = my_image->gaussian + nx;
  for (iy = 1; iy < nyM1; iy++) {
/*              d[iy*nx] = g[iy*nx] - g[(iy-1)*nx+2]; */
/*              d[iy*nx] = g[iy*nx] - g[iy*nx-nx+2]; */
    *dP = *(gP + nxP1) - *(gP - nx);
    dP += nx;
    gP += nx;
  }

  /*
   * Right Middle Side
   */
  dP = my_image->id135 + nx + nx - 1;
  gP = my_image->gaussian + nx + nx - 1;
  for (iy = 1; iy < nyM1; iy++) {
/*              d[iy*nx+nx-1] = g[iy*nx+nx-1] - g[(iy-1)*nx+nx-2];  */
/*              d[iy*nx+nx-1] = g[iy*nx+nx-1] - g[iy*nx+nx-1-nx-1]; */
    *dP = *(gP + nx) - *(gP - nxP1);
    dP += nx;
    gP += nx;
  }

  /*
   * Bottom Middle Row
   */
  dP = my_image->id135 + (ny - 1) * nx + 1;
  gP = my_image->gaussian + (ny - 1) * nx + 1;
  for (ix = 1; ix < nxM1; ix++) {
/*              d[(ny-1)*nx+ix] = g[(ny-1)*nx+ix] - g[(ny-2)*nx+ix-1];    */
/*              d[(ny-1)*nx+ix] = g[(ny-1)*nx+ix] - g[(ny-1)*nx+ix-nx-1]; */
    *dP = *(gP + 1) - *(gP - nxP1);
    dP++;
    gP++;
  }


  /*
   * Now the top left Corner
   */
  dP = my_image->id45;
  gP = my_image->gaussian;
  *dP = *(gP + nxP1) - *(gP);

  /*
   * Now th bottom left corner
   */
  dP = my_image->id45 + (ny - 1) * nx;
  gP = my_image->gaussian + (ny - 1) * nx;
/*      dP[(ny-1)*nx+nx-1] = gP[(ny-1)*nx+nx-1] - gP[(ny-2)*nx+nx-2];      */
/*      dP[(ny-1)*nx+nx-1] = gP[(ny-1)*nx+nx-1] - gP[(ny-1)*nx+nx-1-nx-1]; */
  *dP = *(gP + 1) - *(gP - nx);

  /*
   * Now the bottom right corner
   */
  dP[nxM1] = *(gP + nxM1) - *(gP - 2);


  /*
   * Now the top right Corner
   */
  dP = my_image->id45 + nxM1;
  gP = my_image->gaussian + nxM1;
  *dP = *(gP + nx) - *(gP - 1);


#ifdef DEBUG
  image_Write_int ("det135", my_image->id135);
#endif
}
