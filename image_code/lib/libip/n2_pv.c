/* 
 * n2_pv.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * N2_P(oly)V(ert)
 * Misc polygon/vertices functions
 *
 * find 2**n new vertices by resampling input polygon 
 * 
 * determine radius vector relative to centroid; shift to zero mean;
 * reconstruct angular bend function with respect to new set of vertices;
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ip.h"

#define ZERO		0.0

#define	F_TO_INT(x)	( ((x)-(int)(x)<0.5) ? (int)(x) : (int)(x)+1 )
#define	SQR(a)		( (a)*(a) )
/*#define PERP(a, b)    ( -((a)->y)*(b)->x+(a)->x*(b)->y ) */


#define LOOP_COMPLETE	8.0

#define ON		1
#define OFF		0
#define SHIFT_CENTROID	ON
#define	INQ_SHIFT_CTR	OFF
#define	X_SHIFT		0.4
#define	Y_SHIFT		0.4


#define	DRAW_NEW_PTS	ON
#define	RAD_CIRC	3

#define	ZERO_MEAN	0
#define	P_AREA		1               /* guarantees vanishing spectrum for circs */
#define	R_NORM		P_AREA          /* method of normalization for r_dev() */

#define	CHECK_CIRC
#undef	D_DEBUG


/*
 * tg_turn_an()
 *   DESCRIPTION:
 *     evaluate tangent of the angle subtended by segments with
 *     respective slopes m1, m2; two segments are perpendicular if m1*m2 = -1.0;
 *   ARGUMENTS:
 *     m1: first slope (double)
 *     m2: second slope (double)
 *   RETURN VALUE:
 *     tangent between m1 and m2 (double)
 */

double
tg_turn_an (double m1, double m2)
{
  double tg_th, den;

  den = m1 * m2 + 1.0;
  if ((-1.0e-10 < den) && (den < 1.0e-10))
    tg_th = 500.0;
  else
    tg_th = (m1 - m2) / den;

  return (tg_th);
}

/*
 * slope()
 *   DESCRIPTION:
 *     evaluate slope of linear segment
 *   ARGUMENTS:
 *     pt1: first point (spoint *)
 *     pt2: second point (spoint *)
 *   RETURN VALUE:
 *     slope between pt1 and pt2 (double)
 */

double
slope (struct spoint *pt1, struct spoint *pt2)
{
  double m;
  double max_slope = 500.0;     /* max. poss. slope */
  int x1, y1, x2, y2;

  x1 = F_TO_INT (pt1->x);
  y1 = F_TO_INT (pt1->y);
  x2 = F_TO_INT (pt2->x);
  y2 = F_TO_INT (pt2->y);

  if (F_TO_INT (x2 - x1) == 0) {
    if (F_TO_INT (y2 - y1) == 0)
      m = 0.0;
    else
      m = max_slope;
  }
  else
    m = ((double) (y2 - y1)) / ((double) (x2 - x1));

  return (m);
}

/*
 * vert_to_phi_star()
 *   DESCRIPTION:
 *     compute cumulative angular bend function for set of vertices
 *     by evaluating turn angles of contour at each vertex
 *   ARGUMENTS:
 *     v: vertices (spoint *)
 *     nv: # vertices (long)
 *     phi_star: turn angles (float *)
 *   RETURN VALUE:
 *     currently always 1
 */

int
vert_to_phi_star (struct spoint *v, long nv, float *phi_star)
{
  //int i;
  //float sign;
  float ang_step;
  float eps = (float) 0.5;

  printf ("\n...new version of function not complete\n");
  return (-1);

  ang_step = (float) (2.0 * M_PI / (float) nv);

/*
 * compute contour turn angle at point (xi, yi) from the 
 * triple of points (ximm, yimm), (xi, yi) and (xipp, yipp)
 * and collect results in phi_k;
 * sign convention:
 *   CW turn is assigned a negative turn angle
 *
 * (see poly_app.c, hsb)
 */


/* 
 * check for closure 
 * 
 * ang_offset = *(n_phi_k + 0);
 * for (i=0; i<=nv; i++)
 * *(n_phi_k + i) -= ang_offset;
 * 
 * cum_turn_angle = *(n_phi_k + nv);
 * printf("\n...cum_turn_angle = %f\n", cum_turn_angle);
 * if( cum_turn_angle > 0.0 ) sign = -1.0;
 * if( cum_turn_angle < 0.0 ) sign = 1.0;
 * if( fabs(cum_turn_angle ) - 2.0*PI > eps )
 * printf ("\n...total ang. bend not equal to two pi!!\n");
 * 
 * printf ("...sign = %f, ang_step = %f, ang_offset = %f\n",
 * sign, ang_step, ang_offset);
 */

/*
 * evaluate phi_star by properly normalizing phi_k
 * 
 * for(i=0; i<=nv; i++)
 * *(phi_star+i) = *(n_phi_k+i) + sign*((float)i)*ang_step;
 */
  return (+1);
}


/*
 * zero_mom()
 *   DESCRIPTION:
 *     evaluate polygon area from given set of vertices as moment of order zero
 *   ARGUMENTS:
 *     v: vertices (spoint *)
 *     nv: # vertices (long)
 *   RETURN VALUE:
 *     polygon area (double)
 */

double
zero_mom (struct spoint *v, long nv)
{
  int i;
  double m00;
  double ximm, xi, yimm, yi;

  m00 = 0.0;
  for (i = 1; i <= (int) nv; i++) {
    ximm = (double) (v + i - 1)->x;
    xi = (double) (v + i)->x;
    yimm = (double) (v + i - 1)->y;
    yi = (double) (v + i)->y;

    m00 += yi * ximm - xi * yimm;
  }
  return (0.5 * fabs (m00));
}


/*
 * shape_parm()
 *   DESCRIPTION:
 *     evaluate global shape parameter
 *   ARGUMENTS:
 *     c_len: curvature length (double)
 *     moments: moments array (float *)
 *   RETURN VALUE:
 *     shape parameter (double)
 */

double
shape_parm (double c_len, float *moments)
{
  return (c_len * c_len / (4.0 * M_PI * (*(moments + 1))));
}


/*
 * E_dist()
 *   DESCRIPTION:
 *     evaluate Euclidean distance between two points
 *   ARGUMENTS:
 *     pt1: first point (spoint *)
 *     pt2: second point (spoint *)
 *   RETURN VALUE:
 *     distance between pt1 and pt2 (double)
 */

double
E_dist (struct spoint *pt1, struct spoint *pt2)
{
  double delx, dely, d;

  if (fabs (delx = (double) (pt2->x - pt1->x)) < 1.0)
    delx = 0.0;
  if (fabs (dely = (double) (pt2->y - pt1->y)) < 1.0)
    dely = 0.0;
  d = sqrt (SQR (delx) + SQR (dely));

#ifdef D_DEBUG
  printf ("...d( (%3d,%3d), (%3d,%3d) ): %lf\n",
          pt1->x, pt1->y, pt2->x, pt2->y, d);
#endif
  return (d);
}

/*
 * E_dist()
 *   DESCRIPTION:
 *     evaluate vector (cross) product of two input vectors
 *   ARGUMENTS:
 *     pt1: first point (spoint *)
 *     pt2: second point (spoint *)
 *   RETURN VALUE:
 *     cross product between pt1 and pt2 (double)
 */

double
vcp (struct spoint *v1, struct spoint *v2)
{
  return (-(v1->y) * (v2->x) + (v1->x) * (v2->y));
}


/*
 * cont_bend_en()
 *   DESCRIPTION:
 *     determine bending energy of closed contour by summing the square
 *     of the curvature, based on the evaluation of the local radius of 
 *     curvature, R, as the radius of the osculating circle, defined by 
 *     a triplet of successive points on the contour; for three such points, 
 *     v0, v1, v2, the radius R is given as R = d(v2, v0)/(2*sin th), where
 *     th denotes the angle subtended by the segments s(v1, v0) and s(v2, v1),
 *     and it is related to the contour turn angle by PI-th;
 *
 *     ref: D. J. Struik, ``Lectures on Classical Diff. Geometry'', Ch. 1-4
 *         Addison-Wesley Publ. Co, 1961;
 *   ARGUMENTS:
 *     v: array of points (spoint *)
 *     n: length of array (long)
 *   RETURN VALUE:
 *     bending energy of the cloaed contour (double)
 */

double
cont_bend_en (struct spoint *v, long n)
{
  int i;
  double sn_th, dm, dp;
  double kap, e_bend;
  struct spoint *pvmm, *pv, *pvpp;
  struct spoint sm, *psm = &sm, sp, *psp = &sp;

  e_bend = 0.0;
  for (i = 0; i < n; i++) {
    pv = &v[i];
    if (i == 0)
      pvmm = &v[n - 1];
    else
      pvmm = &v[i - 1];
    if (i == n - 1)
      pvpp = &v[0];
    else
      pvpp = &v[i + 1];

    psm->x = pv->x - pvmm->x;
    psm->y = pv->y - pvmm->y;
    psp->x = pvpp->x - pv->x;
    psp->y = pvpp->y - pv->y;

/* 
 * evaluate square of local curvature
 */
    dm = E_dist (pv, pvmm);
    dp = E_dist (pvpp, pv);
    sn_th = vcp (psm, psp) / (dm * dp);
    kap = 2.0 * (sn_th / E_dist (pvpp, pvmm));

    printf ("...kap(%3d): %f\n", i, (float) kap);

    e_bend += (double) (SQR (kap) * 0.5 * (dm + dp));
  }
  return (e_bend);
}



/*
 * r_dev()
 *   DESCRIPTION:
 *     evaluate the function (r(s) - rbar)/rbar for poly {v} with centroid vc;
 *
 *     note:
 *      ---> the radial function can become multivalued if "overhangs" occur,
 *      even if the contour is a Jordan curve (enclosing a singly
 *      connected region)!!
 *      ---> the centroid does not in general coincide with the point with
 *      respect to which r(s) must be evaluated to ensure
 *      the vanishing of the first Fourier component of (r(s) - rbar)!!
 *   ARGUMENTS:
 *     vc: centroid (spoint *)
 *     v: polygon vertices (spoint *)
 *     r: (r(s) - rbar)/rbar (float *)
 *     nv: # vertices in v (long)
 *     moments: (float *)
 *     imgIO: output image (Image *)
 *     value: grayscale for drawing 0-255 (int)
 *   RETURN VALUE:
 *     none
 */

void
r_dev (struct spoint *vc, struct spoint *v,
       float *r, long nv, float *moments, Image * imgIO, int value)
{
  int i;
  float xfc, yfc;
  float xcc = (float) X_SHIFT, ycc = (float) Y_SHIFT;
  float rbar = (float) 0.0;
  double delx, dely;
  double m00 = -1.0;

  xfc = (float) vc->x;
  yfc = (float) vc->y;
  printf ("\nR_DEV: centroid (%3d, %3d)\n", vc->x, vc->y);
/* 
 * shift centroid coordinates to minimize first Fourier mode 
 * (determine required shift by trial and error)
 */
  if (SHIFT_CENTROID == ON) {
    if (INQ_SHIFT_CTR == ON) {
      printf ("\n...current centroid position (xc, yc)\n");
      printf ("-->correct xc by:");
      scanf ("%f", &xcc);
      printf ("-->correct yc by:");
      scanf ("%f", &ycc);
    }
    xfc += xcc;
    yfc += ycc;
    printf ("...corrected centroid position: (%f, %f)", xfc, yfc);
  }

  rbar = (float) 0.0;
  for (i = 0; i < nv; i++) {
    delx = (v + i)->x - xfc;
    dely = (v + i)->y - yfc;
    *(r + i) = (float) sqrt (delx * delx + dely * dely);

    rbar += *(r + i);
  }


  switch (R_NORM) {
  case ZERO_MEAN:              /* shift r to zero mean and normalize */
    rbar /= (float) nv;
    break;
  case P_AREA:                 /* compare with circle of equal area */
    rbar = (float) sqrt (*(moments + 1) / M_PI);
    break;
  }
  for (i = 0; i < nv; i++)
    *(r + i) = (float) ((*(r + i) / rbar) - 1.0);

#ifdef CHECK_CIRC
  printf ("\n...reference circle (method: %d):", R_NORM);
  printf (" rbar: %f\n", rbar);

  draw_circle ((int) xfc, (int) yfc, (int) rbar, imgIO, value);
#endif
}

/*
 * n2_vert()
 *   DESCRIPTION:
 *     find 2**n new vertices by resampling input polygon 
 *     construct new vertices (spaced in equi_distant steps along the contour)
 *     by simple linear interpolation
 *   ARGUMENTS:
 *     v: input polygon (spoint *)
 *     s: pointer to partial sums array (float *)
 *     nv: # vertices in v (long)
 *     v_n2: resampled polygon (spoint *)
 *     nv2: length of v_n2 (long)
 *     imgIO: output image (Image *)
 *     value: grayscale for drawing 0-255 (int)
 *   RETURN VALUE:
 *     none
 */

void
n2_vert (struct spoint *v, float *s, long nv, struct spoint *v_n2, long nv2, Image * imgIO, int value)
{
  int i, i_n2;
  double cl_in2, delta_cl;
  double xi, ximm, delx;
  double yi, yimm, dely;
  double si, simm, dels;

  double eps = 0.01;

  int c_index = 127;


  (v_n2 + 0)->x = (v + 0)->x;
  (v_n2 + 0)->y = (v + 0)->y;
  delta_cl = 100.0 / ((double) nv2);
  for (i_n2 = 0; i_n2 <= nv2; i_n2++) {
    i = 1;
    cl_in2 = ((double) i_n2) * delta_cl;  /*norm. cont. len */
    while ((cl_in2 - *(s + i)) > eps)
      i++;                      /* find edge */

    /* new vertex may be close to an existing one */
    if (fabs (*(s + i) - cl_in2) <= eps) {
      (v_n2 + i_n2)->x = (v + i)->x;
      (v_n2 + i_n2)->y = (v + i)->y;
    }
    /* in general, it won't be: interpolate */
    else if (fabs (*(s + i) - cl_in2) > eps) {
      xi = (double) (v + i)->x;
      ximm = (double) (v + i - 1)->x;
      delx = xi - ximm;
      yi = (double) (v + i)->y;
      yimm = (double) (v + i - 1)->y;
      dely = yi - yimm;
      si = *(s + i);
      simm = *(s + i - 1);
      dels = si - simm;

      (v_n2 + i_n2)->x = F_TO_INT (delx * (cl_in2 - simm) / dels + ximm);
      (v_n2 + i_n2)->y = F_TO_INT (dely * (cl_in2 - simm) / dels + yimm);
    }
  }

/* 
 * overlay new nv2 vertices on displayed polygon 
 */
  if (DRAW_NEW_PTS == ON) {
    for (i_n2 = 0; i_n2 < nv2; i_n2++)
      draw_circle ((int) (v_n2 + i_n2)->x, (int) (v_n2 + i_n2)->y, (int) RAD_CIRC, imgIO, value);
  }
}
