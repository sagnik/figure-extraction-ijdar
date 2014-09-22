/* 
 * pmom.c P(oly)MOM(ents)
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ip.h"

#define	DENT_CUTOFF	0.001
#define	TANGENT_LIMIT	1.0e06    /* indicates vertical axis        */
#define	MU11_EPS	5.0e03         /* indicates alignment with axes */

#define ZERO		0.0
#define FABS(a)		((a) > ZERO ? (a) : - (a))
#define	SQR(a)		( (a)*(a) )

#define ON		1
#define OFF		0
#define SAVE_MOMENTS	ON

#define	DEBUG
#define	CEN_DEBUG
#define	SHOW_VERT

/*
 * poly_moments()
 *   DESCRIPTION:
 *       poly_moments computes centroid, central moments, principal axes and
 *       first two moment invariants
 *     the centroid position is marked with a cross
 *     the principle axis directions are plotted
 *   ARGUMENTS:
 *     nv(long) number of vertices in polygon
 *     v(struct spoint *) pointer to struct containing the vertices
 *     moments(float *) pointer to array of floats to hold calculated moments
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for plotting
 *   RETURN VALUE:
 *     (struct spoint *) that contains the centroid value
 */

struct spoint *
poly_moments (long nv, struct spoint *v, float *moments, Image * imgIO, int value)
{
  int i, i_max, i_min;
  int nvpp;
  int size = 30;
  int circle = 0, horizontal = 0, vertical = 0;

  double ximm, xi, yimm, yi;
  double d_xy, d_min, d_max;

  double m00, m00_sum;
  double m10, m10_sum, m01, m01_sum, m11, m11_sum;
  double m20, m20_sum, m02, m02_sum;
  double mu, mu11, mu20, mu02, dent;
  double musq, phi_1, phi_2;
  double rad_gyr;
  double tg_tth, tg_th1, tg_th2, sq_root;
  double mu02_div_mu20, mu11mu20_sign;
  double x_major, y_major, x_minor, y_minor;
  int quad_IV = OFF, quad_I = OFF;

  static struct spoint *pvc, vc;

  int color_index = 191;
  pvc = &vc;


#ifdef SHOW_VERT
  printf ("\n...PMOM: vertex coordinates\n");
  for (i = 0; i < (int) nv; i++)
    printf ("...%d: (%3d, %3d)\n", i, (v + i)->x, (v + i)->y);
#endif

/*
 * compute moments
 * refs:
 *   Hu, IRE Trans. Inf. Theory, IT-8, 179-187 (1962)
 *   Seul, Sammon and Monar, Rev. Sci. Instr. 62, 784-792 (1991)
 */
  m00 = m10 = m01 = 0.0;
  m11 = m20 = m02 = 0.0;
  nvpp = (int) nv + 1;
  for (i = 1; i < nvpp; i++) {
    ximm = (double) (v + i - 1)->x;
    xi = (double) (v + i)->x;
    yimm = (double) (v + i - 1)->y;
    yi = (double) (v + i)->y;

    m00_sum = 0.5 * (yi * ximm - xi * yimm);
    m00 += m00_sum;

    m10_sum = 0.5 * (xi + ximm) * m00_sum;
    m10_sum -= 0.5 * ((yi - yimm) * (xi * xi + xi * ximm + ximm * ximm) / 6.0);
    m10 += m10_sum;

    m01_sum = 0.5 * (yi + yimm) * m00_sum;
    m01_sum += 0.5 * ((xi - ximm) * (yi * yi + yi * yimm + yimm * yimm) / 6.0);
    m01 += m01_sum;

    m11_sum = 0.5 * m00_sum;
    m11 += m11_sum * (2.0 * xi * yi + ximm * yi + xi * yimm + 2.0 * ximm * yimm) / 6.0;

    m20_sum = m00_sum * (xi * xi + xi * ximm + ximm * ximm) / 3.0;
    m20_sum -= 0.5 * (yi - yimm) * (xi * xi * xi + xi * xi * ximm + xi * ximm * ximm + ximm * ximm * ximm) / 6.0;
    m20 += m20_sum;

    m02_sum = m00_sum * (yi * yi + yi * yimm + yimm * yimm) / 3.0;
    m02_sum += 0.5 * (xi - ximm) * (yi * yi * yi + yi * yi * yimm + yi * yimm * yimm + yimm * yimm * yimm) / 6.0;
    m02 += m02_sum;

  }
  printf ("\nmoments:\n");
  printf ("...m00 = %lf\n", m00);
  printf ("...m10 = %lf  m01 = %lf\n", m10, m01);
  printf ("...m11 = %lf  m20 = %lf  m02 = %lf\n", m11, m20, m02);


/*
 * correct sign of raw moments if necessary
 * ( -->negative moments are obtained from Zahn's representation
 *      of an 'inner' boundary, traversed in CCW sense)
 */
  if (SIGN (m00) < ZERO) {
    m00 *= -1.0;
    m10 *= -1.0;
    m01 *= -1.0;
    m11 *= -1.0;
    m20 *= -1.0;
    m02 *= -1.0;
  }


/*
 * centroid 
 */
  pvc->x = (int) (m10 / m00);
  pvc->y = (int) (m01 / m00);
#ifdef CEN_DEBUG
  printf ("\nPOLY_MOMENT: centroid pos: (%3d, %3d)\n", pvc->x, pvc->y);
#endif

/*
 * mark centroid position with a cross
 */
  draw_cross (pvc->x, pvc->y, size, imgIO, value);


/*
 * find curvature points closest to and farthest from the centroid
 */
  i_max = i_min = 0;
  d_max = 0.0;
  d_min = 1000.0;
  for (i = 1; i < nvpp; i++) {
    xi = (double) (v + i)->x;
    yi = (double) (v + i)->y;
    d_xy = sqrt (SQR (xi - pvc->x) + SQR (yi - pvc->y));
    if (d_xy > d_max) {
      d_max = d_xy;
      i_max = i;
    }
    if (d_xy < d_min) {
      d_min = d_xy;
      i_min = i;
    }
  }
#ifdef DEBUG
  printf ("\n...d_min = %lf  d_max = %lf\n", d_min, d_max);
#endif

/*
 * central moments and radius of gyration
 * ref: Gonzalez & Wintz, "Digital Image Processing", chapt. 8.3
 *
 * at the expense of efficiency, work with normalized raw moments
 * where possible, to keep numbers small
 */
  mu = m00;
  mu11 = m11 - m00 * (m10 / m00) * (m01 / m00);
  mu20 = m20 - m00 * SQR (m10 / m00);
  mu02 = m02 - m00 * SQR (m01 / m00);

  rad_gyr = sqrt (FABS (mu20 + mu02) / mu);
  dent = FABS (((mu02 / mu20) - 1.0));

  printf ("\ncentral moments:\n");
  printf ("...mu00 = %lf\n", mu);
  printf ("...mu11 = %lf  mu20 = %lf  mu02 = %lf\n", mu11, mu20, mu02);
  printf ("...radius of gyration: %lf\n", rad_gyr);
  printf ("...(mu02 - mu20)/mu20 = %lf\n", dent);

  if ((dent < DENT_CUTOFF) && (FABS (mu11) < MU11_EPS)) {
    circle = ON;
    printf ("\n--->circle!!\n");
  }

/*
 * invariant moments
 * (reference: Gonzalez & Wintz, "Digital Image Processing", chapt. 8.3)
 */
  musq = SQR (mu);
  phi_1 = (mu20 + mu02) / musq;
  phi_2 = SQR ((mu20 - mu02) / musq) + 4.0 * SQR (mu11 / musq);

  printf ("\ninvariant moments:\n");
  printf ("...phi_1 = %lf  phi_2 = %lf\n", phi_1, phi_2);

/*
 * determine principal axes
 * ref: A. Rosenfeld, A. C. Kak, "Digital Picture Processing", vol.II 
 */
  mu02_div_mu20 = mu02 / mu20;
  tg_tth = 2.0 * (mu11 / mu20) / (1.0 - mu02_div_mu20);
  printf ("\n...tg_tth = %lf\n", tg_tth);

/*
 * check limits
 */
  if (FABS (tg_tth) < 0.01) {
    if (FABS (mu20) / FABS (mu02) >= 1.0)
      horizontal = ON;
    if (FABS (mu20) / FABS (mu02) <= 1.0)
      vertical = ON;
  }
  if ((circle == ON) || (horizontal == ON) || (vertical == ON)) {
    printf ("\n...circle = %d", circle);
    printf ("...horizontal = %d", horizontal);
    printf ("...vertical = %d", vertical);
    printf ("\n-->principal axes along screen coordinate system\n");
    if ((circle == ON) || (horizontal == ON)) {
      x_major = d_min + (double) pvc->x;
      y_major = (double) pvc->y;
      x_minor = (double) pvc->x;
      y_minor = d_min + (double) pvc->y;
      tg_th1 = ZERO;
      tg_th2 = TANGENT_LIMIT;
    }
    else if (vertical == ON) {
      x_major = (double) pvc->x;
      y_major = d_min + (double) pvc->y;
      x_minor = d_min + (double) pvc->x;
      y_minor = (double) pvc->y;
      tg_th1 = TANGENT_LIMIT;
      tg_th2 = ZERO;
    }
  }
  else {
    sq_root = sqrt (1.0 + 1.0 / SQR (tg_tth));

/*
 * determine proper direction of principal (major) axis 
 * (sign of tg_th1, below):
 *   -->check whether mu11 has same or opposite sign as do mu20 and m02
 */
    if (SIGN (mu20) * SIGN (mu02) < ZERO) {
      printf ("\n...mu20, mu02 differ in sign");
      printf (" -->something wrong?\n");
    }

    if ((mu11mu20_sign = SIGN (mu11) * SIGN (mu20)) > ZERO) {
      quad_IV = ON;             /* quadr II->IV */

      if (mu02_div_mu20 <= 1.0)
        tg_tth = -FABS (tg_tth);
      else
        tg_tth = FABS (tg_tth);

      tg_th1 = (-1.0 / tg_tth) - sq_root;
      tg_th2 = (-1.0 / tg_tth) + sq_root;

    }
    else if (mu11mu20_sign < ZERO) {
      quad_I = ON;              /* quadr III->I */

      if (mu02_div_mu20 <= 1.0)
        tg_tth = FABS (tg_tth);
      else
        tg_tth = -FABS (tg_tth);

      tg_th1 = (-1.0 / tg_tth) + sq_root;
      tg_th2 = (-1.0 / tg_tth) - sq_root;

    }
    else
      printf ("\n...unknown condition encountered\n");


    printf ("\nprincipal axes:\n");
    printf ("...tg_tth = %lf  tg_th1 = %lf  tg_th2 = %lf\n",
            tg_tth, tg_th1, tg_th2);

/*
 * determine coordinates of endpoints of line segments (of length 
 * d_min and 0.5*d_min) to be drawn in direction of principal axes
 */
    x_major = d_min / sqrt (1.0 + SQR (tg_th1));
    x_minor = 0.5 * d_min / sqrt (1.0 + SQR (tg_th2));
    if (quad_I == ON) {
      y_major = (double) pvc->y - FABS (tg_th1) * x_major;
      y_minor = (double) pvc->y + FABS (tg_th2) * x_minor;
    }
    if (quad_IV == ON) {
      y_major = (double) pvc->y + FABS (tg_th1) * x_major;
      y_minor = (double) pvc->y - FABS (tg_th2) * x_minor;
    }
    x_major += (double) pvc->x;
    x_minor += (double) pvc->x;
  }
  printf ("\n...x_major = %lf  y_major = %lf\n", x_major, y_major);
  printf ("...x_minor = %lf  y_minor = %lf\n", x_minor, y_minor);

/*
 * mark principal axis directions
 */
  draw_line (pvc->x, pvc->y, (int) x_major, (int) y_major, imgIO, value);
  draw_line (pvc->x, pvc->y, (int) x_minor, (int) y_minor, imgIO, value);

/*
 * save paramters related to moments for later reference
 */
  *(moments + 0) = (float) SAVE_MOMENTS;
  *(moments + 1) = (float) m00;
  *(moments + 2) = (float) m10;
  *(moments + 3) = (float) m01;
  *(moments + 4) = (float) m11;
  *(moments + 5) = (float) m20;
  *(moments + 6) = (float) m02;
  *(moments + 7) = (float) mu11;
  *(moments + 8) = (float) mu20;
  *(moments + 9) = (float) mu02;
  *(moments + 10) = (float) dent;
  *(moments + 11) = (float) phi_1;
  *(moments + 12) = (float) phi_2;
  *(moments + 13) = (float) tg_th1;
  *(moments + 14) = (float) tg_th2;

  return (pvc);
}
