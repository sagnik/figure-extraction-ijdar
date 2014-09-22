/* 
 * ph.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * P(oly_)H(ull)
 *
 */

/*
 * Code fragments for computation of convex hull of a given boundary.
 * To use, call routine convex_hull(), 
 * to obtain conv. hull of approximated polygon.
 *
 * construction of the convex hull of a polygon is accomplished by
 * employing convex hull routine in poly_approx.c; the 
 * Wall-Danielsson fitting routine poly_approx() is employed with a 
 * tolerance of zero and thus reproduces the input set of vertices 
 * (supplied in bdp->v) in the array ap; as in poly_edge, the input 
 * polygon is assumed to be closed, containing n_vert+1 points, last 
 * and first vertices being identical.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ip.h"


#define	APOLY		0
#define	HULLPOLY	1

#define	OFF		0
#define	ON		1

#undef	ECHO_INPUT

static struct spoint pnull;

/* globals */
extern int loop_switch;
extern int hull_switch;
extern int n_ap_max;

/*
 * fill_bdy_structure()
 *   DESCRIPTION:
 *     fill_bdy_structure fills the polygon boundary structure
 *     that is used in p_app.c, as defined in ph.h
 *     note:
 *     by default, it is assumed here (as in poly_approx() !!) that the 
 *     array {x_vertex, y_vertex} represents a closed polygon of n_vertex+1
 *     vertices; in struct bdp, vn is set to n_vertex!! (not n_vertex+1)
 *   ARGUMENTS:
 *     bdp(Bdy *) pointer tp polygon boundary struct to be filled (see ph.h)
 *     v(point *) pointer to vertices of polygon (see ph.h)
 *     nv(long) number of vertices
 *     tot_phi(double) total angular bend (not currently used)
 *   RETURN VALUE:
 *     none
 */
void
fill_bdy_structure (struct Bdy *bdp, struct spoint *v, long nv, double tot_phi)
{
  int i;
  struct spoint *temp_v;

  bdp->ident = 1;
  bdp->per = 1L;                /* assn dummy number of pixels in perimeter */
  bdp->vn = nv;                 /* input polygon */
  bdp->an = 0L;                 /* for polyapprox(): should be init to 0L */
  /* if not 0L, statement free(bdp->ap) in */
  /* poly_approx() leads to memory leaks!! */
  bdp->hn = 0;                  /* for convex_hull() */

/*
 * assign memory to (x,y) structure field
 */
  if ((bdp->v = (struct spoint *) malloc ((size_t) (bdp->vn + 1) * sizeof (struct spoint))) == NULL) {
    printf ("\n...memory allocation for bdp->v failed!!\n");
    exit (1);
  }

/*
 * assign vertex coordinates to (x,y) in bdp structure 
 */
  temp_v = bdp->v;              /* save v[] pointer */
  for (i = 0; i <= (int) bdp->vn; i++) {
    temp_v->x = (v + i)->x;
    temp_v->y = (v + i)->y;
    temp_v++;
  }
}

/*
 * poly_hull()
 *   DESCRIPTION:
 *     poly_hull implements smoothing of original polygon by edge fitting, employing
 *     routine poly_approx().
 *     note:
 *     the approximated polygon returned by poly_approx() is not(!) closed;
 *     if a closed polygon is desired (as for example for the purpose of
 *     plotting it; see poly_ovl), the last vertex must be explicitly set
 *     to be equal to the first vertex; the same applies, mutis mutandis,
 *     to the routine convex_hull();
 *   ARGUMENTS:
 *     bdp(Bdy *) pointer tp polygon boundary struct (see ph.h)
 *     v(point *) pointer to approximated vertices of polygon (see ph.h)
 *     av_dirn(double) average direction of polygon
 *     hull_area(int *) pointer to hull area
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for drawing
 *   RETURN VALUE:
 *     pointer to convex hull center point
 */
struct spoint *
poly_hull (struct Bdy *bdp, struct spoint *v_ap,
           double av_dirn, int *hull_area,
           Image * imgIO, int value)
{
  struct spoint ***temp_h;
  struct spoint *hullctr;

  int *x_ap, *y_ap;
  int *x_hp, *y_hp;
  int n_ap, n_hp;
  int apoly = 0, hullpoly = 1;
  int i;
  int skip = 1;
  char c = '\0';
  double tol = 1.0;
  char in_buf[IN_BUF_LEN];


  do {
    printf ("\n...enter tolerance for polyg approx(float):");
    readlin (in_buf);
    sscanf (in_buf, "%lf", &tol);

    poly_approx (bdp, (float) tol);

/* 
 * copy the output of polyapprox() into the (x_ap, y_ap) format
 * and into
 * struct v_ap, for later use in calling function;   
 * n_ap is preserved through the process; 
 */
    n_ap = (int) bdp->an;
    printf ("\n...%d vertices in approx. polygon", n_ap);

    skip = 0;
    if (n_ap > n_ap_max) {
      printf ("...exceeds max of %d vertices\n", n_ap_max);
      skip = 1;
    }

    if (n_ap < 1) {
      printf ("...no vertices to plot\n");
      return (&pnull);
    }

    if (skip == 0) {
      if ((x_ap = (int *) calloc ((size_t) (n_ap + 1), sizeof (int))) == NULL)
          exitmess ("\n...mem allocation for x_ap failed\n", 1);
      if ((y_ap = (int *) calloc ((size_t) (n_ap + 1), sizeof (int))) == NULL)
          exitmess ("\n...mem allocation for y_ap failed\n", 1);


      for (i = 0; i < n_ap; i++) {
        *(x_ap + i) = (v_ap + i)->x = bdp->ap[i]->x;
        *(y_ap + i) = (v_ap + i)->y = bdp->ap[i]->y;
      }

/* 
 * close approx. polygon:
 * set last point equal to first point: tot #pts = n_ap+1!! 
 */
      *(x_ap + n_ap) = (v_ap + n_ap)->x = bdp->ap[0]->x;
      *(y_ap + n_ap) = (v_ap + n_ap)->y = bdp->ap[0]->y;

/* 
 * draw new vertices
 */
      draw_poly_ovl (x_ap, y_ap, n_ap + 1,
                     0, 0,
                     av_dirn, APOLY,
                     imgIO, value);
    }
    printf ("\n...repeat(y/n)?");
  } while ((loop_switch != OFF) && ((c = readlin (in_buf)) != 'n'));


/*
 * compute and display convex hull
 */
  if (hull_switch == OFF) {
    free (x_ap);
    free (y_ap);
    return (&pnull);
  }
  else if (hull_switch == ON) {
    printf ("\n...compute convex hull:\n");

    convex_hull (bdp);

/* obtain location of convex hull center (as evaluated in convex_hull()) */
    hullctr = reprt_hull_center ();

/* 
 * copy the output of convex_hull() into the (x_hp, y_hp) format
 * n_hp is preserved through the process 
 */
    n_hp = (int) bdp->hn;
    if (n_hp < 1) {
      printf ("\n no vertices to plot\n");
      return (&pnull);
    }

/*
 * allocate memory   
 */
    if ((x_hp = (int *) calloc ((size_t) (n_hp + 1), sizeof (int))) == NULL)
        exitmess ("\n...mem allocation for x_hp failed\n", 1);
    if ((y_hp = (int *) calloc ((size_t) (n_hp + 1), sizeof (int))) == NULL)
        exitmess ("\n...mem allocation for y_hp failed\n", 1);

    temp_h = (bdp->hpp);
    for (i = 0; i < n_hp; i++) {
      *(x_hp + i) = (**temp_h)->x;
      *(y_hp + i) = (**temp_h)->y;
      temp_h++;
    }

/* 
 * close convex_hull:
 * set last point equal to first point: tot #pts = n_hp+1!! 
 */
    *(x_hp + n_hp) = (**(bdp->hpp))->x;
    *(y_hp + n_hp) = (**(bdp->hpp))->y;

/* 
 * evaluate convex hull area (function zero_moment() in sgl_stats.c)
 */
    *hull_area = zero_moment (n_hp, x_hp, y_hp);


/* overlay new vertices on existing image */
    draw_poly_ovl (x_hp, y_hp, n_hp + 1,
                   hullctr->x, hullctr->y,
                   av_dirn, HULLPOLY,
                   imgIO, value);


    free (x_hp);
    free (y_hp);
    if (!skip) {
      free (x_ap);
      free (y_ap);
    }

    return (hullctr);
  }
}

/*
 * poly_hull_tol()
 *   DESCRIPTION:
 *     variation on poly_hull()
 *     does not ask for tolerance.
 *     instead, tolerance is in argument list.
 *   ARGUMENTS:
 *     bdp(Bdy *) pointer tp polygon boundary struct (see ph.h)
 *     v(point *) pointer to approximated vertices of polygon (see ph.h)
 *     av_dirn(double) average direction of polygon
 *     hull_area(int *) pointer to hull area
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for drawing
 *   RETURN VALUE:
 *     pointer to convex hull center point
 */

struct spoint *
poly_hull_tol (struct Bdy *bdp, struct spoint *v_ap,
               double av_dirn, int *hull_area, float tol,
               Image * imgIO, int value)
{
  struct spoint ***temp_h;
  struct spoint *hullctr;

  int *x_ap, *y_ap;
  int *x_hp, *y_hp;
  int n_ap, n_hp;
  int apoly = 0, hullpoly = 1;
  int i;
  int skip = 1;
  char c = '\0';


  poly_approx (bdp, (float) tol);

/* 
 * copy the output of polyapprox() into the (x_ap, y_ap) format
 * and into
 * struct v_ap, for later use in calling function;   
 * n_ap is preserved through the process; 
 */
  n_ap = (int) bdp->an;
  skip = 0;
  if (n_ap > n_ap_max) {
    printf ("...exceeds max of %d vertices\n", n_ap_max);
    skip = 1;
  }

  if (n_ap < 1) {
    printf ("...no vertices to plot\n");
    return (&pnull);
  }

  if (skip == 0) {
    if ((x_ap = (int *) calloc ((size_t) (n_ap + 1), sizeof (int))) == NULL)
        exitmess ("\n...mem allocation for x_ap failed\n", 1);
    if ((y_ap = (int *) calloc ((size_t) (n_ap + 1), sizeof (int))) == NULL)
        exitmess ("\n...mem allocation for y_ap failed\n", 1);


    for (i = 0; i < n_ap; i++) {
      *(x_ap + i) = (v_ap + i)->x = bdp->ap[i]->x;
      *(y_ap + i) = (v_ap + i)->y = bdp->ap[i]->y;
    }

/* 
 * close approx. polygon:
 * set last point equal to first point: tot #pts = n_ap+1!! 
 */
    *(x_ap + n_ap) = (v_ap + n_ap)->x = bdp->ap[0]->x;
    *(y_ap + n_ap) = (v_ap + n_ap)->y = bdp->ap[0]->y;

/* 
 * draw new vertices
 */
    draw_poly_ovl (x_ap, y_ap, n_ap + 1, 0, 0, av_dirn, APOLY, imgIO, value);
  }


/*
 * compute and display convex hull
 */
  if (hull_switch == OFF) {
    free (x_ap);
    free (y_ap);
    return (&pnull);
  }
  else if (hull_switch == ON) {

    convex_hull (bdp);

/* obtain location of convex hull center (as evaluated in convex_hull()) */
    hullctr = reprt_hull_center ();

/* 
 * copy the output of convex_hull() into the (x_hp, y_hp) format
 * n_hp is preserved through the process 
 */
    n_hp = (int) bdp->hn;
    if (n_hp < 1) {
      printf ("\n no vertices to plot\n");
      return (&pnull);
    }

/*
 * allocate memory   
 */
    if ((x_hp = (int *) calloc ((size_t) (n_hp + 1), sizeof (int))) == NULL)
        exitmess ("\n...mem allocation for x_hp failed\n", 1);
    if ((y_hp = (int *) calloc ((size_t) (n_hp + 1), sizeof (int))) == NULL)
        exitmess ("\n...mem allocation for y_hp failed\n", 1);

    temp_h = (bdp->hpp);
    for (i = 0; i < n_hp; i++) {
      *(x_hp + i) = (**temp_h)->x;
      *(y_hp + i) = (**temp_h)->y;
      temp_h++;
    }

/* 
 * close convex_hull:
 * set last point equal to first point: tot #pts = n_hp+1!! 
 */
    *(x_hp + n_hp) = (**(bdp->hpp))->x;
    *(y_hp + n_hp) = (**(bdp->hpp))->y;

/* 
 * evaluate convex hull area (function zero_moment() in sgl_stats.c)
 */
    *hull_area = zero_moment (n_hp, x_hp, y_hp);


/* overlay new vertices on existing image */
    draw_poly_ovl (x_hp, y_hp, n_hp + 1,
                   hullctr->x, hullctr->y,
                   av_dirn, HULLPOLY,
                   imgIO, value);


    free (x_hp);
    free (y_hp);
    if (!skip) {
      free (x_ap);
      free (y_ap);
    }

    return (hullctr);
  }
}
