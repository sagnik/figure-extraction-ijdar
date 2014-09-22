/* 
 * pv.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * P(oly_)V(ert)
 */

#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "ip.h"


#define	ENLARGE		1              /* used for testing with xph.c */
#define LOOP_COMPLETE	8.0

#define SQ2		1.414213562
#define ZERO		0.0

#define ON		1
#define OFF		0

#undef	DEBUG_CURV
#undef	SHOW_PHIK
#undef	SHOW_ARCL

#undef	ECHO_INPUT
#undef	ECHO_VERT
#define FABS(a)		((a) > ZERO ? (a) : - (a))




/*
 * angular_bend()
 *   DESCRIPTION:
 *     angular_bend computes ZAHN's angular bend function
 *     phi_star = phi_star(arc_length) for a given contour
 *   ARGUMENTS:
 *     d_phik(float *) change in direction as measured in PI/4
 *     phi_k(float *) pointer to the differential values in angular direction
 *       along the contour from an arbitrarily chosen starting point
 *     nv(long) number of contour segments
 *   RETURN VALUE:
 *     total angular bend for the contour 
 */

double
angular_bend (float *d_phik, float *phi_k, long nv)
{
  int k, n_vertex = (int) nv + 1;
  double tot_phi;

/*
 * regarding turn angle at first vertex:
 * first vertex is counted as i = 0 and i = nv;
 */
  *(phi_k + 0) = (float) 0.0;
  for (k = 1; k <= nv; k++)
    *(phi_k + k) = *(phi_k + k - 1) + *(d_phik + k - 1);


  printf ("\n...total angle = %lf\n", tot_phi = *(phi_k + nv));


#ifdef SHOW_PHIK
  printf ("\n...phi_k:\n");
  for (k = 0; k <= nv; k++)
    printf ("%d %12.6f\n", k, *(phi_k + k));
#endif

  if ((tot_phi != LOOP_COMPLETE) && (tot_phi != -LOOP_COMPLETE)) {
    tot_phi = 99.0;
    printf ("\n...total angular bend not equal to two PI! ");
    printf ("-->something wrong!\n");
  }
  return (tot_phi);
}


/*
 * arc_length()
 *   DESCRIPTION:
 *     arc_length computes normalized contour segment ("edge") lengths
 *   ARGUMENTS:
 *     d_lk(float *) pointer to contour length segments
 *     arc_len(float *) pointer to normalized contour length segments to be filled
 *     nv(long) number of contour segments
 *   RETURN VALUE:
 *     contour length of polygon
 */
double
arc_length (float *d_lk, float *arc_len, long nv)
{
  int k, n_vertex = (int) nv + 1;
  double c_len;

/*
 * regarding turn length of edge ending in first vertex:
 * first vertex is counted as i = 0 and i = nv;
 */
  *(arc_len + 0) = (float) 0.0;
  for (k = 1; k <= nv; k++)
    *(arc_len + k) = *(arc_len + k - 1) + (float) *(d_lk + k - 1);

/*
 * normalize arc_length 
 */
  printf ("\n...contour_length = %lf\n", c_len = *(arc_len + nv));
  for (k = 0; k <= nv; k++)
    *(arc_len + k) *= (float) (100.0 / c_len);


#ifdef SHOW_ARCL
  printf ("\n...arc_len:\n");
  for (k = 0; k <= nv; k++)
    printf ("%d %12.6f\n", k, *(arc_len + k));
#endif

/*
 * before returning, correct contour_length for factor of two incurred
 * in ZAHN's half integer representation of curvature points
 * (see 'descript.c')
 */
  return (0.5 * c_len);
}

/*
 * vert_to_clen()
 *   DESCRIPTION:
 *     vert_to_clen computes arc_length (partial sums of segments lengths) for a polygon
 *     defined in terms of the sequence of its vertices
 *   ARGUMENTS:
 *     v(point *) pointer to point struct (see ph.h)
 *     s(float *) pointer to partial sums array (to be filled)
 *     nv(long) number of vertices
 *   RETURN VALUE:
 *     contour length of polygon
 */

double
vert_to_clen (struct spoint *v, float *s, long nv)
{
  int i;
  double delx, dely;
  double c_len;

/*
 * evaluate partial sums of edge lengths and accumulate in s
 * (note: s de facto becomes a unit offset array)
 */
  *(s + 0) = (float) 0.0;
  for (i = 0; i < nv; i++) {
    delx = (double) ((v + i + 1)->x - (v + i)->x);
    dely = (double) ((v + i + 1)->y - (v + i)->y);

    if (i == (nv - 1)) {        /* handle bdy closure */
      delx = (double) ((v + 0)->x - (v + i)->x);
      dely = (double) ((v + 0)->y - (v + i)->y);
    }
    if (FABS (delx) < 1.0)
      delx = 0.0;
    if (FABS (dely) < 1.0)
      dely = 0.0;

    *(s + i + 1) = *(s + i) + (float) sqrt (delx * delx + dely * dely);
  }

/* 
 * normalize
 */
  c_len = *(s + nv);
  for (i = 1; i <= nv; i++)
    *(s + i) *= (float) (100.0 / c_len);



#ifdef DEBUG_LENGTH
  printf ("\nVERT_TO_CLEN:\n");
  printf ("...contour length of polygon: %lf\n", c_len);
  printf ("...normalized cum. edge lengths:\n");
  for (i = 0; i <= nv; i++)
    printf ("s[%d]: %f\n", i, *(s + i));
#endif

  return (c_len);
}

/*
 * curvature_energy()
 *   DESCRIPTION:
 *     curvature_energy computes curvature energy for contour
 *     (ref: I.T.Young, J.E.Walker and J.E.Brown, 
 *     Inform. and Control 25, 357-370(1974)
 *   ARGUMENTS:
 *     d_phik(float *) change in direction as measured in PI/4
 *     d_lk(float *) pointer to contour length segments
 *     nv(long) number of contour segments
 *   RETURN VALUE:
 *     contour length of polygon
 */

double
curvature_energy (float *d_phik, float *d_lk, long nv)
{
  register int k;
  int del_phik, del_phikk;
  float zahn_c_len;
  float del_lk, del_lkk, del_pk;
  float del_ce;

  double curv_en;

/*
 *  evaluate curvature at ZAHN curvature points
 */
  zahn_c_len = (float) 0.0;
  curv_en = 0.0;
  del_lk = del_lkk = (float) 0.0;
  del_phik = del_phikk = 0;
  del_pk = (float) 0.0;

#ifdef DEBUG_CURV
  printf ("\n...curvature_energy, extracted from ZAHN code:\n");
  printf ("\n k    del_phik    del_lk     del_cesq    curv_en\n");
#endif

  for (k = 1; k <= nv; k++) {
    zahn_c_len += *(d_lk + k - 1);

    del_phik = (int) (*(d_phik + k - 1));
    if (del_phik % 2 != 0)
      del_lk = (float) (0.5 * SQ2);
    else
      del_lk = (float) 0.5;

    del_phikk = (int) (*(d_phik + k));
    if (del_phikk % 2 != 0)
      del_lkk = (float) (0.5 * SQ2);
    else
      del_lkk = (float) 0.5;

    del_pk = del_lk + del_lkk;
    del_ce = ((float) del_phik) / del_pk;
    curv_en += del_ce * del_ce;

#ifdef DEBUG_CURV
    printf ("%d  %d   %f  %f  %f\n",
            k, del_phik, del_lk, del_ce * del_ce, curv_en);
#endif

  }

/*
 * normalize
 */
  curv_en *= (45.0 * 45.0) / (zahn_c_len * ((float) nv));

  return (curv_en);
}

/*
 * find_interior_pt()
 *   DESCRIPTION:
 *     find_interior_pt finds an interior point of polygon,
 *     given as a sequence of vertices
 *   ARGUMENTS:
 *     v(point *) pointer to vertices (see ph.h)
 *     nv(int) number of vertices
 *     xi, yi(int *) interior point found
 *     e_out(int *) pointer to edge out array
 *     tot_phi(double) total angular bend (currently not used)
 *   RETURN VALUE:
 *     1 if interior point found, 0 otherwise
 */

int
find_interior_pt (struct spoint *v, int nv, int *xi, int *yi, int *e_out, double tot_phi)
{
  int segm_found;
  register int k;

  k = 0;
  segm_found = 0;
  while ((segm_found == 0) && (k <= nv)) {
    if (tot_phi < 0.0) {
      if ((*(e_out + k) > *(e_out + k + 1)) &&
          (*(e_out + k + 1) > *(e_out + k + 2))) {
        segm_found = 1;
        *yi = ((v + k)->y + (v + k + 2)->y) / 2;
        *xi = ((v + k)->x + (v + k + 2)->x) / 2;
      }
    }
    else {
      if ((*(e_out + k + 2) > *(e_out + k + 1)) &&
          (*(e_out + k + 1) > *(e_out + k))) {
        segm_found = 1;
        *yi = ((v + k)->y + (v + k + 2)->y) / 2;
        *xi = ((v + k)->x + (v + k + 2)->x) / 2;
      }
    }
    k++;
  }
  return (segm_found);

}


/*
 * reconstruct polygon
 */
/*
 * reconstruct_poly()
 *   DESCRIPTION:
 *     reconstruct_poly reconstructs a polygon,
 *     given a tanential representation of the object
 *   ARGUMENTS:
 *     d_phik(double *) change in direction as measured in PI/4
 *     d_lk(double *) pointer to contour length segments
 *     nv(int) number of vertices
 *     v(point *) pointer to vertices to be filles (see ph.h)
 *     porg(point *) pointer to origin of polygon (see ph.h)
 *     e_outk(int *) edge out
 *     tot_phi(double) total angular bend (currently not used)
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for drawing
 *   RETURN VALUE:
 *     area in pixels of reconstructed polygon
 */

unsigned int
reconstruct_poly (float *d_phik, float *d_lk,
                  long nv, struct spoint *v, struct spoint *porg,
                  int e_outk, double tot_phi,
                  Image * imgIO, int value)
{
  unsigned int p_area;

  int deltalk;
  int *d_l, *e_out;
  int *xv, *yv;
  int nvc;

  int xi, yi;
  int col_index;
  int status;

  register int k;


  if ((d_l = (int *) calloc (((int) nv + 1), sizeof (int))) == NULL)
      exitmess ("\n...mem allocation for d_l failed\n", 1);
  if ((e_out = (int *) calloc (((int) nv + 1), sizeof (int))) == NULL)
      exitmess ("\n...mem allocation for edge_out failed\n", 1);

  nvc = nv + 1;

/*
 * reconstruct polygon in form {xk, yk}, 
 * pick arbitrary starting point  
 */
  *(d_l + 0) = 0;
  *(e_out + 0) = e_outk;
  (v + 0)->x = porg->x;
  (v + 0)->y = porg->y;


#ifdef ECHO_INPUT
  printf ("\n...input data:\n");
  printf ("...first vertex: (%3d,%3d)\n", (v + 0)->x, (v + 0)->y);
  printf ("...edge_out at first vertex: %d\n", e_outk);
  printf ("...total turn angle: %f\n", tot_phi);
  for (k = 0; k <= nv; k++)
    printf (" %d      %f      %f\n", k, *(d_phik + k), *(d_lk + k));
#endif

  for (k = 1; k <= nv; k++) {
    if (e_outk % 2 != 0)
      deltalk = (int) ((*(d_lk + k - 1) / SQ2) * ENLARGE + 0.5);
    else
      deltalk = (int) ((*(d_lk + k - 1)) * ENLARGE + 0.5);

    switch (e_outk) {
    case 0:
      (v + k)->x = (v + k - 1)->x + deltalk;
      (v + k)->y = (v + k - 1)->y;
      break;
    case 4:
      (v + k)->x = (v + k - 1)->x - deltalk;
      (v + k)->y = (v + k - 1)->y;
      break;
    case 2:
      (v + k)->x = (v + k - 1)->x;
      (v + k)->y = (v + k - 1)->y - deltalk;
      break;
    case 6:
      (v + k)->x = (v + k - 1)->x;
      (v + k)->y = (v + k - 1)->y + deltalk;
      break;
    case 1:
      (v + k)->x = (v + k - 1)->x + deltalk;
      (v + k)->y = (v + k - 1)->y - deltalk;
      break;
    case 5:
      (v + k)->x = (v + k - 1)->x - deltalk;
      (v + k)->y = (v + k - 1)->y + deltalk;
      break;
    case 3:
      (v + k)->x = (v + k - 1)->x - deltalk;
      (v + k)->y = (v + k - 1)->y - deltalk;
      break;
    case 7:
      (v + k)->x = (v + k - 1)->x + deltalk;
      (v + k)->y = (v + k - 1)->y + deltalk;
      break;
    }

    e_outk = e_outk + (int) (*(d_phik + k - 1));
    if (e_outk < 0)
      e_outk = e_outk + 8;
    else if (e_outk >= 8)
      e_outk = e_outk % 8;

    *(e_out + k) = e_outk;
    *(d_l + k) = deltalk;
  }
  *(d_l + 0) = *(d_l + nv);
  *(e_out + 0) = *(e_out + nv);

  for (k = 0; k <= nv; k++) {
    (v + k)->x = (v + k)->x / 2;
    (v + k)->y = (v + k)->y / 2;
    *(d_l + k) = *(d_l + k) / 2;
  }

#ifdef ECHO_VERT
  printf ("\n    k     x_vert     y_vert     d_lk    edge_outk\n\n");
  for (k = 0; k <= nv; k++)
    printf (" %4d      %4d       %4d       %4d         %4d\n",
            k, (v + k)->x, (v + k)->y, *(d_l + k), *(e_out + k));
#endif

  if (((v + nv)->x != (v + 0)->x) || ((v + nv)->y != (v + 0)->y))
    exitmess ("\n...polygon is not closed! something wrong!\n", 1);


/*
 * set up graphics and fill polygon, including its edges
 */

  if ((xv = (int *) calloc ((size_t) (nv + 1), sizeof (int))) == NULL)
      exitmess ("\n...mem allocation for xv failed\n", 1);
  if ((yv = (int *) calloc ((size_t) (nv + 1), sizeof (int))) == NULL)
      exitmess ("\n...mem allocation for yv failed\n", 1);

  for (k = 0; k <= nv; k++) {
    *(xv + k) = (v + k)->x;
    *(yv + k) = (v + k)->y;
  }
/*
 * Draw and fill the polygon
 */
  p_area = draw_polyfill (xv, yv, nvc, imgIO, value);

/*
 * move cursor to point inside the polygon 
 */
  if ((status = find_interior_pt (v, (int) nv, &xi, &yi, e_out, tot_phi)) == 0)
    exitmess ("...no convex vertex found!\n", 1);

#ifdef FOO
/*
 * invoke flood function and determine pixel count (area) 
 */
  col_index = 0;
  p_area = flood_region (xi, yi, col_index);
#endif

/* 
 * overlay border on displayed polygon 
 */
  col_index = GRAY;
  draw_poly (xv, yv, nvc, imgIO, col_index);
/*
 * deallocate memory 
 */
  free (d_l);
  free (e_out);
  free (xv);
  free (yv);

  return (p_area);
}
