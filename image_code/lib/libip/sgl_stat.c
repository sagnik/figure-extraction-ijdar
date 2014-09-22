/* 
 * sgl_stat.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * SGL_STATS
 *
 * determine geometrical properties of a cluster of linear segments
 * in a given SGL
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "ip.h"

#define	TWO		2
#define	THREE		3
#define	DIM	 	TWO

#define	SN_LOLIM	0.002          /* lower limit: 1/512 */
#define	CS_LOLIM	0.002

#undef DEBUG

/*
 * nematic_op()
 *   DESCRIPTION:
 *     nematic_op evaluates nematic order parameter S = <3*cos_th*cos_th - 1>/2 (3d)
 *     or S = <2*cos_th*cos_th - 1> (2d) for the ensemble of clusters (SGLs);
 *   ARGUMENTS:
 *     n_sgl(int) number of segment group lists
 *     n_segm(int) number of clusters
 *     dirns(float *) cluster orientations
 *   RETURN VALUE:
 *     total angular bend for the contour
 *   COMMENTS:
 *     note: *dirns is a ptr to an array containing the slopes of the
 **             linear segments in a given SGL
 **        loop over the n_sgl <= n_segm of non_empty SGLs only:
 **             *dirns is expected to be initialized to 999.0; this
 **             serves to identify unused elements; 
 **             (see also: slope() in xsgll.c);
 **        for each SGL (cluster) the array *dirns holds the average slope 
 **             of the segments in that cluster; since there is no preferred
 **             orientation of segments, corresponding directions are
 **             defined to within modulo PI; it is with respect to the
 **             the average direction that the order parameter S is
 **             evaluated 
 */

float
nematic_op (int n_sgl, int n_segm, float *dirns)
{
  float slpi, av_slope;
  double sn_2th, cs_2th, th;
  double cs2_th, tg_th, s;
  float order_parm;
  int i;

#ifdef DEBUG
  printf ("\n...nematic order parameter for %d clusters:\n", n_segm);
  printf ("...cluster orientations:\n");
  for (i = 0; i < n_segm; i++) {
    if (*(dirns + i) < 999.0)
      printf ("	SGL<%d>: %6.2f\n", i, *(dirns + i));
  }
#endif

/* determine preferred direction */
  sn_2th = cs_2th = 0.0;
  for (i = 0; i < n_segm; i++) {
    if ((slpi = *(dirns + i)) < 999.0) {  /* valid entry for slope */
      cs_2th += (double) ((1.0 - slpi * slpi) / (1.0 + slpi * slpi));
      sn_2th += (double) (2.0 * slpi / (1.0 + slpi * slpi));
    }
  }
  sn_2th /= (double) n_sgl;
  cs_2th /= (double) n_sgl;
  if (fabs (cs_2th) < CS_LOLIM)
    cs_2th = SIGN (cs_2th) * CS_LOLIM;

  th = 0.5 * atan2 (sn_2th, cs_2th);

  if (fabs (sn_2th) < SN_LOLIM) {
    printf ("\n...no preferred direction!\n");
    th = 0.0;
  }
#ifdef DEBUG
  printf ("...sn_2th = %6.4lf, cs_2th = %6.4lf, th = %8.4lf deg\n",
          sn_2th, cs_2th, th);
#endif

  av_slope = (float) tan (th);


/* evaluate order parameter */
  order_parm = (float) 0.0;
  for (i = 0; i < n_segm; i++) {  /* deviations from av slope */
    if ((slpi = *(dirns + i)) < 999.0) {
      if (slpi * av_slope == -1.0)
        tg_th = 512.0;          /* perp orientation */
      else
        tg_th = (slpi - av_slope) / (1.0 + slpi * av_slope);

      cs2_th = 1.0 / (1.0 + tg_th * tg_th);
      if (DIM == THREE)
        s = 0.5 * (3.0 * cs2_th - 1.0);
      if (DIM == TWO)
        s = (2.0 * cs2_th - 1.0);
      order_parm += (float) s;
    }
  }
  order_parm /= (float) n_sgl;

  return (order_parm);
}


/*
 * eccentr()
 *   DESCRIPTION:
 *     eccentr evaluates aspect ratio of a given cluster (SGL) of segments
 *     as the ratio of the maximum longitudinal and transverse dimensions,
 *     the latter being identical to the maximum segment length in the SGL
 *   ARGUMENTS:
 *     segm(struct Segm *) pointer to segment structure (see sgl_stat.h)
 *     list(struct linklist *) pointer to linked list structure (see lldef.h)
 *     len(float *) length of SGL
 *     width(float *) width of SGL
 *   RETURN VALUE:
 *     aspect ratio of SGL (length/width) 
 */

float
eccentr (struct Segm *segm, struct linklist *list, float *len, float *width)
{
  struct Segmtype *cSegm;
  float del_x, del_y;
  float d_min, d_max;
  float csegm_len, max_segm_len;


/* length */
  llhead (list);
  cSegm = (struct Segmtype *) list->clp->item;
  d_min = cSegm->dij;
  lltail (list);
  cSegm = (struct Segmtype *) list->clp->item;
  d_max = cSegm->dij;
  *len = d_max - d_min;

/* width */
  max_segm_len = (float) 0.0;
  llhead (list);
  do {
    cSegm = (struct Segmtype *) list->clp->item;

    del_x = (float) ((segm + cSegm->segm_ind)->ptF.x - (segm + cSegm->segm_ind)->ptO.x);
    del_y = (float) ((segm + cSegm->segm_ind)->ptF.y - (segm + cSegm->segm_ind)->ptO.y);
    csegm_len = (float) sqrt (del_x * del_x + del_y * del_y);
    if (csegm_len > max_segm_len)
      max_segm_len = csegm_len;

  } while (llnext (list) == True);
  *width = max_segm_len;

  return (*len / (*width));
}

/*
 * find_ex_hist()
 *   DESCRIPTION:
 *     find_ex_hist constructs a histogram of SGL (cluster) aspect ratios
 *     (ex refers to eccentricity for which the aspect ratio is a crude measure)
 *   ARGUMENTS:
 *     n_segm(int) number of SGLs to calculate histogram for
 *     asp_ratio(float *) array of aspect ratios for SGLs
 *     ex_hist(int *) output histogram
 *     bw(double) bin width of the histogram
 *     ar_base(double) minimum aspect ratio (base)
 *   RETURN VALUE:
 *     none 
 */

void
find_ex_hist (int n_segm, float *asp_ratio, int *ex_hist, double bw, double ar_base)
{
  int i, ibin;

  for (i = 0; i < n_segm; i++) {
    if (*(asp_ratio + i) != 0.0) {
      ibin = 1;
      while (*(asp_ratio + i) > ar_base + ibin * bw)
        ibin++;
      *(ex_hist + ibin - 1) += 1;
    }
  }
}


/*
 * find_lsz_hist()
 *   DESCRIPTION:
 *     find_lsz_hist constructs a histogram of SGL (cluster) longitudinal sizes (no of segm)
 *   ARGUMENTS:
 *     n_segm(int) number of SGLs to calculate histogram for
 *     lsize(int *) array of longitudinal for SGLs
 *     lsz_hist(int *) calculated histogram for SGLs
 *     nbins(int) currently not used
 *     lsz_base(int) base of the histogram
 *   RETURN VALUE:
 *     none 
 */

void
find_lsz_hist (int n_segm, int *lsize, int *lsz_hist, int nbins, int lsz_base)
{
  int i, ibin;

  for (i = 0; i < n_segm; i++) {
    if (*(lsize + i) != 0) {
      ibin = 1;
      while (*(lsize + i) >= lsz_base + ibin)
        ibin++;
      *(lsz_hist + ibin - 1) += 1;
    }
  }
}


/*
 * zero_moment()
 *   DESCRIPTION:
 *     zero_moment evaluates zero order moment: x_vert and y_vert are assumed to represent
 *     a closed polygon (last vertex assumed identical with first vertex)
 *   ARGUMENTS:
 *     nv(int) number of vertices in polygon
 *     xv, yv(int *) (x,y) points of vertices
 *   RETURN VALUE:
 *     zero order moment of polygon 
 */

int
zero_moment (int nv, int *xv, int *yv)
{
  register int i;

  double xim1, xi, yim1, yi;
  double m00, m00_sum;

  m00 = m00_sum = 0.0;
  for (i = 1; i <= nv; i++) {
    xim1 = (double) (*(xv + i - 1));
    xi = (double) (*(xv + i));
    yim1 = (double) (*(yv + i - 1));
    yi = (double) (*(yv + i));

    m00_sum = 0.5 * (yi * xim1 - xi * yim1);
    m00 += m00_sum;
  }

  return ((int) fabs (m00));
}


/*
 * find_area_hist()
 *   DESCRIPTION:
 *     find_area_hist constructs histogram of SGL (cluster) areas
 *   ARGUMENTS:
 *     n_segm(int) number of SGLs to calculate histogram for
 *     area(int *) SGL array of areas
 *     area_hist(int *) array of histograms filled
 *     bw(int) bin width of the histogram
 *     area_base(int) minimum aspect ratio (base)
 *   RETURN VALUE:
 *     zero order moment of polygon 
 */

void
find_area_hist (int n_segm, int *area, int *area_hist, int bw, int area_base)
{
  int i, ibin;
  int up_bw;


  up_bw = (int) bw + 1;
  for (i = 0; i < n_segm; i++) {
    if (*(area + i) != 0) {
      ibin = 1;
      while (*(area + i) > area_base + ibin * up_bw)
        ibin++;
      *(area_hist + ibin - 1) += 1;
    }
  }
}
