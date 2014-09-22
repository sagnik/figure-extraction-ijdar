/* 
 * descript.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * DESCRIPT
 *
 *  evaluation of Fourier descriptors for a plane curve
 *   encoded in a set {delta_phi(k), l(k)};
 *
 *  references:
 *  C. T. Zahn, 
 *  Proc. Joint Intern. Conf. on Artif. Intelligence, May 1969, pp. 621 - 628;
 *  SLAC Report 70, Stanford Linear Accelerator Center, 1968;
 *  C. T. Zahn & R. Z. Roskies, IEEE Trans. Comp., Vol C-21, 269 - 281 (1972);
 *
 *  -->the truncated Fourier expansion derived by Z & R is computed 
 *     in form of inner products using array processor functions
 *
 *  -->test shapes (see Z & R): 
 *           four (xdrawfour.c), inverted L (fdzahnl.c)
 *
 * ---------------------------------------------------------------------------
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ip.h"

#define	EPS		0.00000001
#define	SQ2		1.414213562

#define	ON		1
#define	OFF		0
#define	FD_DEBUG	ON


/*
 * descriptors()
 *   DESCRIPTION:
 *     evaluate ZAHN-ROSKIES Fourier descriptors
 *   ARGUMENTS:
 *     dphik: delta phik for polygon (float *)
 *     dlk: delta lk for polygon (float *)
 *     mcp: length of dphik and dlk (long)
 *     a_n: Fourier coefficients array (float *)
 *     b_n: Fourier coefficients array (float *)
 *     n_order: order of Fourier descriptors to compute (long)
 *   RETURN VALUE:
 *     none
 */

void
descriptors (float *dphik, float *dlk, long mcp, float *a_n, float *b_n, long n_order)
{
  int k, n_ord;
  int fund_flag = OFF;

  float real_length, length;
  float dc_term, a, b, part_sum;
  float *angle;
  float *sne, *csn;
  float *mag, *phase;
  int n;


/*  
 *  compute (in place) running sums of the elements in dlk 
 *  and the corresponding phase angles required in the evaluation
 *  of the fundamental
 */
  if ((sne = (float *) calloc ((int) mcp, sizeof (double))) == NULL) {
    printf ("descriptors: memory allocation error for sne\n");
    exit (1);
  }
  if ((csn = (float *) calloc ((int) mcp, sizeof (double))) == NULL) {
    printf ("descriptors: memory allocation error for csn\n");
    exit (1);
  }
  if ((angle = (float *) calloc ((int) mcp, sizeof (double))) == NULL) {
    printf ("descriptors: memory allocation error for angle\n");
    exit (1);
  }


/*
 * evaluate contour length, based on curvature points
 */
  part_sum = *(dlk + 0);
  for (k = 1; k < mcp; k++) {
    part_sum += *(dlk + k);
    *(dlk + k) = part_sum;      /* array of partial sums */
  }
  length = *(dlk + mcp - 1);

  for (k = 0; k < mcp; k++)
    *(angle + k) = (float) (2 * M_PI * (*(dlk + k)) / length);

  real_length = (float) (0.5 * length);
  printf ("\n...length = %f\n", real_length);

/*
 *  dphik contains elements of delta_phik multiplied by PI/4;
 *  to speed up computation, factor out PI 
 */
  for (k = 0; k < mcp; k++)
    *(dphik + k) *= (float) 0.25;

#ifdef FD_DEBUG
  printf ("...elements of dphik and dlk:\n");
  for (k = 0; k < mcp; k++)
    printf ("%7.4f  %7.4f\n", *(dphik + k), *(dlk + k));
#endif

/*
 *  compute DC term
 */
  vdot (dphik, dlk, &dc_term, mcp);
  dc_term = (float) (-M_PI * (1.0 + dc_term / length));
  printf ("...and we have a result for the DC term: %f   \n", dc_term);

/*
 * compute increasing orders of Fourier coefficients up to n
 */
  n = 0;
  while (n < n_order) {
    for (k = 0; k < mcp; k++) {
      if (fabs (*(sne + k) = (float) sin (*(angle + k) * (n + 1))) < EPS)
        *(sne + k) = (float) 0.0;
      if (fabs (*(csn + k) = (float) cos (*(angle + k) * (n + 1))) < EPS)
        *(csn + k) = (float) 0.0;
    }
    vdot (dphik, sne, &a, mcp);
    vdot (dphik, csn, &b, mcp);
    *(b_n + n) = (b / (float) (n + 1));
    *(a_n + n) = -(a / (float) (n + 1));

    n++;
  }
  printf ("...descriptors up to %dth order are:\n", n_order);
  for (n = 0; n < n_order; n++)
    printf ("%7.3f   %7.3f\n", *(a_n + n), *(b_n + n));

  mag = (float *) calloc ((int) n_order, sizeof (float));
  phase = (float *) calloc ((int) n_order, sizeof (float));
/*
 *  calculate xy to polar coordinate transformation
 */
  vrtop (a_n, b_n, mag, phase, n_order);
  printf ("...polar descriptors up to %ld-th order are:\n", n_order);
  for (n_ord = 0; n_ord < (int) n_order; n_ord++) {
    if (*(phase + n_ord) < 0.0)
      *(phase + n_ord) += (float) (2.0 * M_PI);
    printf ("%7.3f   %7.3f\n", *(mag + n_ord), *(phase + n_ord));
  }

  free (angle);
  free (sne);
  free (csn);
  free (mag);
  free (phase);
}

/*
 * vdot()
 *   DESCRIPTION:
 *     take the dot product of 2 vectors
 *     and compute the sum
 *   ARGUMENTS:
 *     v1: first vector (float *)
 *     v2: second vector (float *)
 *     vsum: vector sum (float *)
 *     vlen: length of vectors (long)
 *   RETURN VALUE:
 *     none
 */

void
vdot (float *v1, float *v2, float *vsum, long vlen)
{
  float rsum = (float) 0.0;
  int i;

  for (i = 0; i < vlen; i++)
    rsum = rsum + *(v1 + i) * (*(v2 + i));
  *vsum = rsum;
}

/*
 * vcos()
 *   DESCRIPTION:
 *     takes the cosine of a vector
 *   ARGUMENTS:
 *     source: input vector (float *) NOTE: radians!!
 *     dest: output vector (float *)
 *     vlen: vector length (long)
 *   RETURN VALUE:
 *     none
 */

void
vcos (float *source, float *dest, long vlen)
{
  int i;

  for (i = 0; i < vlen; i++)
    *(dest + i) = (float) cos ((double) *(source + i));
}

/*
 * vsin()
 *   DESCRIPTION:
 *     takes the sine of a vector
 *   ARGUMENTS:
 *     source: input vector (float *) NOTE: radians!!
 *     dest: output vector (float *)
 *     vlen: vector length (long)
 *   RETURN VALUE:
 *     none
 */

void
vsin (float *source, float *dest, long vlen)
{
  int i;

  for (i = 0; i < vlen; i++)
    *(dest + i) = (float) sin ((double) *(source + i));
}

/*
 * vrtop()
 *   DESCRIPTION:
 *     converts rectangular cartesian
 *     coordinates to polar
 *   ARGUMENTS:
 *     x: input x vector (float *)
 *     y: input y vector (float *)
 *     mod: modulus output vector (float *)
 *     arg: atan2 output vector (float *)
 *     vlen: vector lengths (long)
 *   RETURN VALUE:
 *     none
 */

void
vrtop (float *x, float *y, float *mag, float *phase, long vlen)
{
  int i;

  for (i = 0; i < vlen; i++) {
    *(mag + i) = (float) sqrt ((*(x + i)) * (*(x + i)) + (*(y + i)) * (*(y + i)));
    *(phase + i) = (float) atan2 (*(y + i), *(x + i));
    if (fabs (*(phase + i)) < EPS)
      *(phase + i) = (float) 0.0;
    else if (*(phase + i) < (float) 0.0)
      *(phase + i) += (float) (2.0 * M_PI);
  }
}

/*
 * msdescriptors()
 *   DESCRIPTION:
 *     wrapper for call to descriptors()
 *   ARGUMENTS:
 *     delta_phik: delta phik for polygon (float *)
 *     delta_lk: delta lk for polygon (float *)
 *     mcp: length of dphik and dlk (long)
 *     a_n: Fourier coefficients array (float *)
 *     b_n: Fourier coefficients array (float *)
 *     n_order: order of Fourier descriptors to compute (long)
 *   RETURN VALUE:
 *     none
 */

void
msdescriptors (float *delta_phik, float *delta_lk, long mcp, float *a_n, float *b_n, long n_order)
{
  int k;

#ifdef FD_DEBUG
  printf ("\nevaluation of Fourier descriptors (Zahn & Roskies)\n");
  printf ("--------------------------------------------------\n");

  printf ("...given: two vectors, delta_phik[] and delta_lk[]\n");

  printf (" delta_phik:\n");
  for (k = 0; k < (int) mcp; k++) {
    printf ("%7.2f  ", *(delta_phik + k));
    if ((k + 1) % 8 == 0)
      printf ("\n");
  }
  printf ("\n   delta_lk:\n");
  for (k = 0; k < (int) mcp; k++) {
    printf ("%7.2f  ", *(delta_lk + k));
    if ((k + 1) % 8 == 0)
      printf ("\n");
  }
#endif

  if (n_order > mcp) {
    printf ("...polygon only has %ld vertices;");
    printf (" cannot yield %ld harmonics!\n", mcp, n_order);
    exit (1);
  }
  descriptors (delta_phik, delta_lk, mcp, a_n, b_n, n_order);

}
