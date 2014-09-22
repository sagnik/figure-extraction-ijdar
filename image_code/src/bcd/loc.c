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
extern int nxXny;

int
image_locx (register int iy, register int ix, register int index)
{                               /* index = iy*nx+ix */
  register int *imP;
  register int nx = my_image->nx;

/*      if(index<=0 || index>=nxXny) */
  if (ix < 2 || ix > nx - 2 || iy < 0 || iy > my_image->ny - 1)
    return (0);

/*      return(gauss[iy*nx+x-1]+gauss[iy*nx+ix+1]-2*gauss[iy*nx+ix]); */

/*      return(idx[iy*nx+ix] - idx[iy*nx+ix-1]); */
  imP = &my_image->idx[index];
  return (*imP - *(imP - 1));
}

int
image_locy (register int iy, register int ix, register int index)
{                               /* index = iy*nx+ix */
  register int *imP;
  register int nx = my_image->nx;

/*      if(index<nx || index>=nxXny) */
  if (ix < 0 || ix > nx - 1 || iy < 2 || iy > my_image->ny - 2)
    return (0);

/*      return(gauss[(iy-1)*nx+ix]+gauss[(iy+1)*nx+ix]-2*gauss[iy*nx+ix]); */

/*      return(idy[iy*nx+ix] - idy[(iy-1)*nx+ix]); */
  imP = &my_image->idy[index];
  return (*imP - *(imP - nx));
}

int
image_loc45 (register int iy, register int ix, register int index)
{                               /* index = iy*nx+ix */
  register int *imP;
  register int nx = my_image->nx;

/*      if(index<nx || index>=nxXny) */
  if (ix < 2 || ix > nx - 2 || iy < 2 || iy > my_image->ny - 2)
    return (0);

/*      return(gauss[(iy-1)*nx+ix+1]+gauss[(iy+1)*nx+ix-1]-2*gauss[iy*nx+ix]); */

/*      return(id45[iy*nx+ix] - id45[(iy-1)*nx+ix+1]); */
  imP = &my_image->id45[index];
  return (*imP - *(imP - nx + 1));
}

int
image_loc135 (register int iy, register int ix, register int index)
{                               /* index = iy*nx+ix */
  register int *imP;
  register int nx = my_image->nx;

/*      if(index<=nx || index>=nxXny) */
  if (ix < 2 || ix > nx - 2 || iy < 2 || iy > my_image->ny - 2)
    return (0);

/*      return(gauss[(iy-1)*nx+ix-1]+gauss[(iy+1)*nx+ix+1]-2*gauss[iy*nx+ix]); */

/*      return(id135[iy*nx+ix] - id135[(iy-1)*nx+ix-1]); */
  imP = &my_image->id135[index];
  return (*imP - *(imP - nx - 1));
}
