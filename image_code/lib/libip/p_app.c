/* 
 * p_app.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * P(oly_)APP(roximation)
 *
 */


/* Code fragments for computation of polygonal approximation and convex hull
 * of a given boundary.  To use, first write a routine to supply the boundary,
 * as decribed in struct Bdy.  To compute an approximation, choose an error
 * tolerance (say 1.5 pixels), and call
 *   poly_approx(&bdy,tolerance);
 * which will enrich Bdy bdy with an approximation.  To compute the hull of 
 * the approximation, call:
 *   convex_hull(&bdy);
 *
 * Assumes the availability of a sorting function qsort() defined as follows:
 *   qsort(base, nel, width, compar)
 *   char *base;
 *   int (*compar)();
 *   
 * The first argument is a pointer to the base of the data; the second is
 * the number of elements; the third is the width of an element in bytes;
 * the last is the name of the comparison routine to be called with two 
 * arguments which are pointers to the elements being compared.  It should 
 * be declared as:
 *  compar(a, b)
 *  char *a, *b;
 * 
 * The routine must return an integer less than, equal to, or greater than 0
 * according as the first argument is to be considered less than, equal to,
 * or greater than the second.
 *
 * Also assumes the availability of a square-root function sqrt(), taking a
 * double argument and returing a double value.  This may be a fast 
 * approximate implementation.  It is used rarely.
 *
 * Also assumes memory allocation functions malloc() and free(), and stdio.
 */
/* 
 * A boundary is an ordered list of vertices, assumed to close.  `vn' counts
 * the vertices.  We use 8-connected boundaries, but that is immaterial
 * to the code.  For the convenience of poly_approx(), the 1st vertex must be
 * duplicated at the end (but `vn' doesn't count the redundant vertex).
 * Except for this case, the input boundary has no consecutive duplicate
 * vertices, and horizontal and vertical runs may (or may not, as you wish)
 * be compressed by omission of their interior colinear vertices.  The winding
 * order of the boundary must be specified by the Bdy_ccw bit in ident (our
 * convention is that counter-clockwise boundaries enclose black regions,
 * and clockwise boundaries enclose holes, but this is immaterial here).
 * `per' counts the no. of pixels on the 8-connected boundary.
 * (definition in bdy_struct.h or sgl_stat.h)
 *
 * NOTE:
 * Original code by H. S. Baird (Spring 1987).
 * Substantially revised, speeded up, and improved by R J Elliott (Spring 1988).
 * Further bug fixes and speedups by H. S. Baird (Fall 1989).
 * Thorsten von Eiken suggests:  backup trick might be sharper 
 *  if you backup only as long as the incremental area is falling fast;  
 *  when it knees, stop.
 */


#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#include "ip.h"

#undef	DEBUG

#define Bdy_ccw	0000000001      /* winding order is counter-clockwise */

#define BACKUP_F (0.75)         /* break if distance from the last breakpoint turns
                                 * * * around and shortens by more than BACKUP_F *
                                 * * * effective tolerance, compared to the longest so 
                                 * * * far
                                 */

#define RAMER_F (3)             /* the number of backup points traversed
                                 * * * after the length of the dist starts decreasing
                                 * * * is RAMER_F * effective tolerance
                                 */


/*
 * poly_approx()
 *   DESCRIPTION:
 *     (Re)Compute a polygonal (straight-line segment) approximation to a given
 *     2D boundary.
 *   ARGUMENTS:
 *     bdp(Bdy *) pointer polygon boundary struct (see ph.h)
 *     tol(double) tolerance in pixels
 *   RETURN VALUE:
 *     none
 *   COMMENTS:
 *     The breakpoint vertices are chosen from among the given 
 *     vertices.
 *     In vestigial cases an empty approximation may be returned; otherwise, the
 *     approximation will have at least two vertices.  The original boundary need 
 *     not be connected; but the 1st boundary vertex must be repeated after the 
 *     last (simplifying this code).
 *     Uses the fast merging method of Wall & Danielsson (CVGIP 28, pp 220-227,
 *     1984) followed by local Ramer-like corrections.  W&D guarantees that the
 *     ``included area'' between the original boundary and each approximation edge
 *     is less than maxarea.  In an extension to the original algorithm 
 *     description, we also ensure that the approximation never backs up:  
 *     i.e. turns around and shortens the maximum distance seen so far from the 
 *     last breakpoint by more than BACKUP_F times the tolerance.
 *     Also, W&D tends to overshoot.  Each breakpoint is therefore adjusted by
 *     backing up to a local maximum perpendicular distance from the line between
 *     the prior (already-corrected) breakpoint and the next (not yet corrected)
 *     breakpoint.  The interval looked back on stretches from the current 
 *     breakpoint through at most BKUP*maxarea pixels of monotonically 
 *     non-increasing perp. distance.  This is a kind of local Ramer correction.
 *     Finally, the firstbreakpoint may be adjusted  or even deleted if in its
 *     absence no breakpoint would occur.
 *     If there is already an approximation, it is deleted and replaced.
 *     Does not ensure that the approximation has no two consecutive identical
 *     breakpoints (hard to do on the fly).
 *     Absolutely fast implementation:  uses no sqrt() or transcendental fns.
 *     Uses floating-point arithmetic sparingly.
 */

void
poly_approx (bdp, tol)
     Bdy *bdp;
     double tol;                /* tolerance, in pixels */

{
  int rx, ry, il2, ll2;
  Sp *or, *ip, *lp, *eip;
  double f, a2;
  double efftol;                /* effective tolerance (larger for half-pixel bdys) */
  Sp *maxp;
  int maxd, pdist;
  int backcnt, cnt;             /* limit backup by this many pixels */

#ifdef DEBUG
  printf ("\n...arrived in poly_appox()");
  printf ("	tol: %lf", tol);
  printf ("	bdp->an initialized to: %ld\n", bdp->an);
#endif

  if (bdp->an > 0 && bdp->ap != NULL) {
    /* free any prior approximation */
    bdp->an = 0;
    free (bdp->ap);
    bdp->err = (float) -1.0;
  };
  if (bdp->vn < 2)
    return;

  if ((bdp->ap = (Sp **) malloc ((bdp->vn + 1) * sizeof (Sp *))) == NULL)
    abort1 ("can't alloc Bdy.ap[%d]", bdp->vn + 1,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  if (bdp->vn <= 4 || tol == (double) 0) {
    /* don't approximate - make every vertex a breakpoint */

#ifdef DEBUG
    printf ("...no approximation: every vertex is a breakpoint\n");
    printf ("	bdp->vn =%ld tol = %lf", bdp->vn, tol);
#endif

    for (bdp->an = 0, ip = bdp->v; bdp->an < bdp->vn; bdp->an++) {
      bdp->ap[bdp->an] = ip++;
    }
    bdp->err = (float) 0;
    return;
  };

  efftol = tol;
  a2 = efftol * efftol;
  if ((backcnt = (int) (RAMER_F * efftol)) < 1)
    backcnt = 1;
  else if (backcnt > bdp->vn / 2)
    backcnt = bdp->vn / 2;

  /* 1st breakpoint is (provisionally) the 1st vertex */
  eip = (ip = bdp->ap[0] = bdp->v) + bdp->vn;
  bdp->an = 1;
  while (ip < eip) {
    or = ip++;
    for (f = 0.0, ll2 = 0, lp = ip++; ip <= eip; lp = ip++) {
      /* next point relative to origin */
      rx = ip->x - or->x;
      ry = ip->y - or->y;
      il2 = rx * rx + ry * ry;
      if (il2 >= ll2)
        ll2 = il2;
      else {                    /* fast, approximate test for backing up */
        double a, b;
        a = (double) (ll2 - il2);
        a = a * a;
        b = (4.0 * BACKUP_F * BACKUP_F) * efftol * efftol * ll2;
        if (a > b) {
          break;
        };
      };
      /* discrepancy area so far */
      f += (double) (rx * (ip->y - lp->y) - ry * (ip->x - lp->x));
      if ((f * f) > (a2 * il2)) {
        break;
      }
    };
    if (ip <= eip) {
      /* backing up or exceeding threshold: a new breakpt */
      bdp->ap[bdp->an++] = --ip;

      /* Attempt to adjust prior breakpt bdp->ap[bdp->an-2]
       * by backing it up until its perpendicular distance 
       * from the line between its neighboring breakpoints 
       * is maximum.
       * Only look back a distance bounded by 
       * RAMER_F*efftol^2.
       * Among those with equal perpendicular distance,
       * choose the one farthest along the boundary. */
      if (bdp->an > 2) {
        or = bdp->ap[bdp->an - 3];
        rx = ip->x - or->x;
        ry = ip->y - or->y;
        for (cnt = 0, maxd = 0, maxp = ip = bdp->ap[bdp->an - 2];
             ip != or; ip--) {
          pdist = rx * (ip->y - or->y) - ry * (ip->x - or->x);
          pdist = abs (pdist);
          if (pdist > maxd) {
            maxd = pdist;
            maxp = ip;
            cnt = 0;
          }
          else if (pdist < maxd) {
            if (++cnt >= backcnt)
              break;
          }
          else
            cnt = 0;
        };
        bdp->ap[bdp->an - 2] = maxp;
      };
      ip = bdp->ap[bdp->an - 1];
    };
  };
  /* Have arrived back at 1st vertex, the 1st breakpoint */

  /* Try deleting the 1st breakpoint.  Look past it to test
   * whether a breakpoint is called for:  if not, delete it. */
  if (bdp->an >= 2) {
    or = bdp->ap[bdp->an - 1];
    if ((ip = or + 1) >= bdp->v + bdp->vn)
      ip = bdp->v;
    if ((eip = bdp->ap[1] + 1) >= bdp->v + bdp->vn)
      eip = bdp->v;
    f = 0.0;
    ll2 = 0;
    lp = ip++;
    while (ip != eip) {
      /* next point relative to origin */
      rx = ip->x - or->x;
      ry = ip->y - or->y;
      il2 = rx * rx + ry * ry;
      if (il2 >= ll2)
        ll2 = il2;
      else {                    /* fast, approximate test for backing up */
        double a, b;
        a = (double) (ll2 - il2);
        a = a * a;
        b = (4.0 * BACKUP_F * BACKUP_F) * efftol * efftol * ll2;
        if (a > b)
          break;
      };
      /* discrepancy area so far */
      f += (double) (rx * (ip->y - lp->y) - ry * (ip->x - lp->x));
      if ((f * f) > (a2 * il2))
        break;
      if (ip >= (bdp->v + bdp->vn)) {
        lp = ip;
        ip = bdp->v;
      }
      else
        lp = ip++;
    };
    if (ip == eip) {
      /*  No need for a breakpoint: delete 1st breakpoint */
      bdp->ap[0] = bdp->ap[bdp->an - 1];
      bdp->an -= 1;

#ifdef DEBUG
      printf ("...upon closure: no need for a breakpt\n");
      printf ("  after deleting 1st breakpt: an = %ld\n",
              bdp->an);
#endif

      if (bdp->an > 2) {        /* Try adjusting new 1st breakpoint */
        or = bdp->ap[bdp->an - 1];
        rx = bdp->ap[1]->x - or->x;
        ry = bdp->ap[1]->y - or->y;
        for (cnt = 0, maxd = 0, maxp = ip = bdp->ap[0]; ip != or; ip--) {
          if (ip == bdp->v)
            ip = bdp->v + bdp->vn;
          pdist = rx * (ip->y - or->y) - ry * (ip->x - or->x);
          pdist = abs (pdist);
          if (pdist > maxd) {
            maxd = pdist;
            maxp = ip;
            cnt = 0;
          }
          else if (pdist < maxd) {
            if (++cnt >= backcnt)
              break;
          }
          else
            cnt = 0;
        };
        bdp->ap[0] = maxp;
      };
    }
    else {                      /* Try adjusting last breakpoint */
      or = bdp->ap[bdp->an - 2];
      rx = bdp->ap[0]->x - or->x;
      ry = bdp->ap[0]->y - or->y;
      for (cnt = 0, maxd = 0, maxp = ip = bdp->ap[bdp->an - 1]; ip != or; ip--) {
        if (ip == bdp->v)
          ip = bdp->v + bdp->vn;
        pdist = rx * (ip->y - or->y) - ry * (ip->x - or->x);
        pdist = abs (pdist);
        if (pdist > maxd) {
          maxd = pdist;
          maxp = ip;
          cnt = 0;
        }
        else if (pdist < maxd) {
          if (++cnt >= backcnt)
            break;
        }
        else
          cnt = 0;
      };
      bdp->ap[bdp->an - 1] = maxp;

      /* Try adjusting 1st breakpoint */
      or = bdp->ap[bdp->an - 1];
      rx = bdp->ap[1]->x - or->x;
      ry = bdp->ap[1]->y - or->y;
      for (cnt = 0, maxd = 0, maxp = ip = bdp->ap[0]; ip != or; ip--) {
        if (ip == bdp->v)
          ip = bdp->v + bdp->vn;
        pdist = rx * (ip->y - or->y) - ry * (ip->x - or->x);
        pdist = abs (pdist);
        if (pdist > maxd) {
          maxd = pdist;
          maxp = ip;
          cnt = 0;
        }
        else if (pdist < maxd) {
          if (++cnt >= backcnt)
            break;
        }
        else
          cnt = 0;
      };
      bdp->ap[0] = maxp;
    };
  };

  /* Force approximation to have >= 2 breakpoints; also, check for and
   * correct bug where the 1st or last breakpoint is off the end of v[] */
  if (bdp->an >= 2) {
    if (bdp->ap[0] == (bdp->v + bdp->vn))
      bdp->ap[0] = bdp->v;
    else if (bdp->an > 1) {
      if (bdp->ap[bdp->an - 1] == (bdp->v + bdp->vn))
        bdp->ap[bdp->an - 1] = bdp->v;
    };
    if ((bdp->ap = (Sp **) realloc (bdp->ap, bdp->an * sizeof (Sp *))) == NULL)
      abort1 ("can't realloc Bdy.ap[%d]", bdp->an,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    bdp->err = (float) tol;
  }
  else {
    if (bdp->ap != NULL) {
      free (bdp->ap);
      bdp->ap = NULL;
    };
    bdp->an = 0;
  };

#ifdef DEBUG
  printf ("...reached end of poly_approx():bdp->an = %ld", bdp->an);
#endif
}


#define old_BACKUP_F (0.5)      /* break if distance from the last breakpoint turns
                                 * * * around and shortens by more than BACKUP_F *
                                 * * * tolerance compared to the longest seen */
#define old_RAMER_F (5)         /* vary the number of backup points traversed
                                 * * * after the length of the dist starts decreasing
                                 * * * with RAMER_F * tolerance */


void
err (s, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12)
     char *s;
     int a1, a2, a3, a5, a6, a7, a8, a9, a10, a11, a12;
     double a4;

{
  char m[100];
  strcpy (m, "polyapprox: ");
  strcat (m, s);
  strcat (m, "\n");
  fprintf (stderr, m, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}

void
abort1 (s, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12)
     char *s;
     double a4;
{
  static char m[100];
  strcpy (m, s);
  strcat (m, " - abort");
  err (m, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
  exit (1);
}



/* 
 *Globals used by convex_hull functions 
 */

Sp HULL_c, HULL_o;              /* center of bdy bx and origin vector */

/* macros for use within winding order function */
/* dot product */
#define dot(a,b) ( (a).x*(b).x+(a).y*(b).y )

/* perp product */
#define perp(a,b) (  -((a).y)*(b).x+(a).x*(b).y )

/* 
 * return the quadrant no: 0,1,2,3 of pt `a' wrt to the X-Y coordinate system
 * defined by aligning the positive X-axis along vector `o' (`a' is a vector
 * wrt to `o') 
 */
#define sgn(a) ( ((a) > 0) ? +1 : -1)
#define quad(a,o) (  ((dot((o),(a)))>=0) ?  ( (perp((o),(a))>=0) ? 0 : 3)  :  ( (perp((o),(a))>=0) ? 1 : 2) )

int
winding_ccw (appp, bppp)
     Sp ***appp, ***bppp;
{
  Sp a, b;
  int qa, qb;

/* 
 * return -1,0,1 as pt `a' is less than, equal to, or greater than pt `b' in
 * counterclockwise winding order about an (implicit) center `HULL_c', where
 * the vector `o' defines the `origin' direction. 
 */
#define wind(a,b,o) (  ((qa=quad((a),(o))) == (qb=quad((b),(o)))) ?  sgn(perp((a),(b)))  :  sgn(qb-qa) )

  a.x = (**appp)->x - HULL_c.x;
  a.y = (**appp)->y - HULL_c.y;
  b.x = (**bppp)->x - HULL_c.x;
  b.y = (**bppp)->y - HULL_c.y;
  return (wind (a, b, HULL_o));
}


int
winding_cw (appp, bppp)
     Sp ***appp, ***bppp;
{
  return (-winding_ccw (appp, bppp));
}

/*
 * convex_hull()
 *   DESCRIPTION:
 *     (Re)Compute the convex non-collinear hull of the polygonal approximation
 *     of a given boundary.  Uses a sort in winding order about the center,
 *     followed by a Graham scan.
 *     The hull vertices are chosen from the vertices of the approximation.
 *     Assumes that the first approximation point is on the hull.
 *     Does not delete the first point if it turns out that it is on the line from
 *     last to second (in short, if the first point is not on the non-collinear hull);
 *   ARGUMENTS:
 *     bdp(Bdy *) pointer polygon boundary struct (see ph.h)
 *   RETURN VALUE:
 *     none
 */

void
convex_hull (bdp)
     Bdy *bdp;
{
  int pi;
  Sp **pp, ***ppp, ***top, ***next;
  static Sp or =
  {0, 0};

  if (bdp->hn > 0 && bdp->hpp != NULL)
    free (bdp->hpp);
  if (bdp->an < 2) {
    bdp->hn = 0;
    bdp->hpp = NULL;
    return;
  };

  if ((bdp->hpp = (Sp ***) malloc ((int) (bdp->an * sizeof (Sp **)))) == NULL)
    abort1 ("can't alloc bdp->hpp[%d]", (int) bdp->an,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  /* start with the assumption that every vertex in the polygonal
   * approximation is on the hull */
  /* also, find "center" of approximation:  */
  /* need some point guaranteed to fall inside the hull */
  HULL_c.x = 0;
  HULL_c.y = 0;
  for (bdp->hn = 0, pp = bdp->ap; bdp->hn < (int) bdp->an; bdp->hn++) {
    HULL_c.x += (*pp)->x;
    HULL_c.y += (*pp)->y;
    bdp->hpp[bdp->hn] = pp++;
  };
  if (bdp->an < 4)
    return;                     /* too small */
  HULL_c.x /= (short) bdp->an;
  HULL_c.y /= (short) bdp->an;

#ifdef DEBUG
  printf ("\n HULL_center = (%d,%d)\n", HULL_c.x, HULL_c.y);
#endif

#define init_scan {top=bdp->hpp-1; next=top-1; bdp->hn=0;}
#define push(pp) {next=top++; *top=(pp); bdp->hn++;}
#define pop {top=next--; bdp->hn--;}

/* 
 * interior(a,b,c) - T iff point *a is ``interior'' of the line from *b to *c, that
 * is, in the closed half-plane to the left of b-->c if the winding
 * order is counterclockwise; else in the right half-plane.  The use of closed
 * half-planes implies that only non-collinear hull points are selected. 
 */
#define leftof(a,b,c) (  (bdp->ident&Bdy_ccw) ?  ((-((c)->y-(b)->y))*((a)->x-(b)->x)+((c)->x-(b)->x)*((a)->y-(b)->y)) <= 0  :  ((-((c)->y-(b)->y))*((a)->x-(b)->x)+((c)->x-(b)->x)*((a)->y-(b)->y)) >= 0 )

  /* define the ``origin'' vector from `c' to the 1st point */
  HULL_o.x = (**bdp->hpp)->x - HULL_c.x;
  HULL_o.y = (**bdp->hpp)->y - HULL_c.y;
  if (HULL_o.x == 0 && HULL_o.y == 0)
    return;                     /* too small */

  /* sort approximation pts about center in winding order (1st as 0) */
  if (bdp->ident & Bdy_ccw)
#if defined(LINUX)
    qsort (bdp->hpp + 1, (size_t) bdp->hn - 1, sizeof (Sp ***), (__compar_fn_t) winding_ccw);
  else
    qsort (bdp->hpp + 1, (size_t) bdp->hn - 1, sizeof (Sp ***), (__compar_fn_t) winding_cw);
#else
    qsort (bdp->hpp + 1, (size_t) bdp->hn - 1, sizeof (Sp ***), winding_ccw);
  else
    qsort (bdp->hpp + 1, (size_t) bdp->hn - 1, sizeof (Sp ***), winding_cw);
#endif

  /* Graham scan */
  ppp = bdp->hpp;
  init_scan;
  push (*(ppp++));
  push (*(ppp++));
  for (pi = 2; pi < bdp->an; pi++, ppp++) {
    while (bdp->hn > 1 && leftof (**top, **next, **ppp))
      pop;
    push (*ppp);
  };
  while (bdp->hn > 1 && leftof (**top, **next, **(bdp->hpp)))
    pop;
  if (bdp->hn < bdp->an) {
    if ((bdp->hpp = (Sp ***) realloc (bdp->hpp, bdp->hn * sizeof (Sp **))) == NULL)
      abort1 ("can't realloc bdp->hpp[%d]", bdp->hn,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  };

}

/*
 * report coordinates of HULL center 
 */
Sp *
reprt_hull_center ()
{
  return (&HULL_c);
}
