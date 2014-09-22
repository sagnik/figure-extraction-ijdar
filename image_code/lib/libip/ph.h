/* 
 * ph.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * P(oly_)H(ull).H
 *
 */

#ifndef _PH_H_
#define	_PH_H_


/*
 * point struct
 */
typedef struct spoint {
  short x;
  short y;
} Sp;



/*
 * boundary struct
 */
typedef struct Bdy {
  int ident;                    /* Bit Bdy_ccw tells whether it's counterclockwise */
  /* Needed for convex_hull() only */
  long per;                     /* no. pixels in 8-connected perimeter */
  /* Never used in current version of polyapprox.c */
  long vn;                      /* no. distinct vertices in v[] */
  Sp *v;                        /* array of vn+1 vertices, v[0]==v[vn] (malloc spc) */
  long an;                      /* no. vertices in polygonal approximation */
  Sp **ap;                      /* approx'n: ary of 'an' ptrs into v[](malloc spc) */
  float err;                    /* approximation error tolerance */
  /* output parameter = 
   * -1 (set initially)
   * 0 (no error in the pol approx
   * >0 = tol, actual tolerance
   */
  int hn;                       /* no. vertices in convex hull of polyg. approx'n */
  /* used in convex_hull() only */
  Sp ***hpp;                    /* convex hull: ary of hn ptrs into ap[] */
  /* used in convex_hull() only */
} Bdy;

#endif /* _PH_H_ */
