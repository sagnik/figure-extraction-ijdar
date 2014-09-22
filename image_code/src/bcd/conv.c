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
static int iklim, nf, nf2;
static int iy, ny;
static int nxX2M1, ikXnx, nyX2M1Xnx, nfXnx;
static int iyMnf2Xnx, iy0, iy0Xnx, it;
static int *temp_image, *filter;
static unsigned char *tpicP;

void
image_convolve (unsigned char *pic)
{
  register int result, ik, ix, nx;
  register unsigned char *picP;
  register int *filtP, *tmpP, *gaussianP;

  nx = my_image->nx;
  ny = my_image->ny;
  nf = my_image->nf;
  nfXnx = nf * nx;
  nf2 = my_image->nf2;
  nxX2M1 = nx + nx - 1;
  nyX2M1Xnx = (ny + ny - 1) * nx;
  filter = my_image->filter;

/*
 *    create temp and output arrays
 */

  if ((temp_image = (int *) malloc (ny * nx * sizeof (int))) == 0) {
    fprintf (stderr, "error: cannot allocate temp array\n");
    exit (1);
  }

  if ((my_image->gaussian = (int *) malloc (ny * nx * sizeof (int))) == 0) {
    fprintf (stderr, "error: cannot allocate gaussian array\n");
    exit (1);
  }
/*
 *    first convolve in x-dirn
 *              do left side first
 *              then middle
 *              then right side
 */


  tmpP = &temp_image[0];
  picP = pic;
  for (iy = 0; iy < ny; iy++, tmpP += nx, picP += nx) {
    for (ix = 0; ix < nf2; ix++) {
      filtP = filter;
      result = 0;
      ik = ix - nf2;
      iklim = ik + nf;
      for (; ik < iklim; ik++)
        result += (*filtP++) * picP[abs (ik)];

      *(tmpP + ix) = result;
    }
  }

  tmpP = &temp_image[0];
  tpicP = pic;
  for (iy = 0; iy < ny; iy++, tmpP += nx, tpicP += nx) {
    int xlim = nx - nf2 - 1;
    for (ix = nf2; ix < xlim; ix++) {
      picP = tpicP + ix - nf2;
      filtP = filter;
      result = 0;
      ik = nf;
      while (ik--)
        result += (*filtP++) * (*picP++);

      *(tmpP + ix) = result;
    }
  }

  tmpP = &temp_image[0];
  picP = pic;
  for (iy = 0; iy < ny; iy++, tmpP += nx, picP += nx) {
    for (ix = nx - nf2 - 1; ix < nx; ix++) {
      filtP = filter;
      result = 0;
      ik = ix - nf2;
      iklim = ik + nf;
      for (; ik < iklim; ik++) {
        /*                      register int index = ix-nf2+ik;
         *                    if(index>=nx) index = nx+nx-index-1;
         *                      result += (*filtP++) * picP[index];
         */
        if (ik >= nx)           /* nxX2M1 = nx+nx-ik-1; */
          result += *filtP * picP[nxX2M1 - ik];
        else
          result += *filtP * picP[ik];
        filtP++;
      }
      *(tmpP + ix) = result;
    }
  }

/*
 * then in y-dirn
 *              first top
 *              then middle
 *              then bottom
 */
  it = -nf2 * nx;
  for (ix = 0; ix < nx; ix++) {
    gaussianP = &my_image->gaussian[ix];
    tmpP = &temp_image[ix];
    iy = 0;
    iyMnf2Xnx = it;             /* = (iy - nf2)*nx; */
    for (; iy < nf2; iy++, iyMnf2Xnx += nx) {
      filtP = filter;
      result = 0;
      /*              ik = iy - nf2;
       *            iklim = ik + nf;
       *              for(; ik<iklim; ik++)
       *                      result += (*filtP++) * tmpP[abs(ik)*nx];
       */
      ik = iyMnf2Xnx;
      iklim = ik + nfXnx;
      for (; ik < iklim; ik += nx)
        result += (*filtP++) * tmpP[abs (ik)];

      /*              my_image->gaussian[iy*nx+ix] = result/my_image->norm; */
      *(gaussianP) = result / my_image->norm;
      gaussianP += nx;
    }
  }

  iy0 = nf2;
  iy0Xnx = iy0 * nx;
  for (ix = 0; ix < nx; ix++) {
    int *col_tmpP = &temp_image[ix];
    int ylim = ny - nf2 - 1;
    iy = iy0;
    gaussianP = &my_image->gaussian[iy0Xnx + ix];
    iyMnf2Xnx = 0;              /* = (iy-nf2)*nx; */
    for (; iy < ylim; iy++, iyMnf2Xnx += nx) {
      filtP = filter;
      tmpP = col_tmpP + iyMnf2Xnx;
      result = 0;
      ik = nf;
      while (ik--) {
        result += (*filtP++) * (*tmpP);
        tmpP += nx;
      }
      /*              my_image->gaussian[iy*nx+ix] = result/my_image->norm; */
      *(gaussianP) = result / my_image->norm;
      gaussianP += nx;
    }
  }

  iy0 = ny - nf2 - 1;
  iy0Xnx = iy0 * nx;
  it = (iy0 - nf2) * nx;
  for (ix = 0; ix < nx; ix++) {
    tmpP = &temp_image[ix];
    iy = iy0;
    gaussianP = &my_image->gaussian[iy0Xnx + ix];
    iyMnf2Xnx = it;             /* = (iy-nf2)*nx; */
    for (; iy < ny; iy++, iyMnf2Xnx += nx) {
      filtP = filter;
      result = 0;
      ik = iy - nf2;
      iklim = ik + nf;
      ikXnx = iyMnf2Xnx;
      for (; ik < iklim; ik++) {
        /*              register int index = iyMnf2+ik;
         *            if(index>=ny) index = ny+ny-index-1;
         *              result += (*filtP++) * tmpP[index*nx];
         */
        if (ik >= ny) {         /* nyX2M1Xnx = (ny+ny-1)*nx; */
          result += *filtP * tmpP[nyX2M1Xnx - ikXnx];
        }
        else
          result += *filtP * tmpP[ikXnx];
        filtP++;
        ikXnx += nx;
      }
      /*              my_image->gaussian[iy*nx+ix] = result/my_image->norm; */
      *(gaussianP) = result / my_image->norm;
      gaussianP += nx;
    }
  }
  free (temp_image);
#ifdef DEBUG
  image_Write_int ("gauss", my_image->gaussian);
#endif
}
