/* 
 * sgl_stat.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * SGL_STAT.H
 *
 * structure defs for sgl_stat.c
 */

#ifndef _SGL_STAT_H_
#define	_SGL_STAT_H_

#include "ph.h"

#define	SIGN(a)		( ((a) == 0.0) ? 0 : ( ((a) < 0.0) ? -1 : 1 ) )

#define MAX_REC_SIZE	1200       /* max number of segments */
#define	MIN_SGL_SIZE	4          /* min size of SGL to be processed */
#define	MIN_SGL_DISPL	5         /* min size of SGL to be displayed */

#define	ACCEPT_LEVEL	2          /* parameter controls acceptance of segm */
    /* into segm group lists in sgll.c */

/* structure definitions */
struct Segm {                   /* linear segment */
  Sp ptO;                       /* coord. of initial point of seg. */
  Sp ptF;                       /* coord. of final point of seg. */

  float slope;                  /* slope of segm {pt1, pt2} */

  int segm_ind;                 /* scan index (i) of segm under inspection */
  int line_ind;                 /* index of parent line */
};


struct Segmtype {               /* linear segm, list entry */

  float pij;                    /* overlap of cur segm i wrt segm j */
  float pji;                    /* inverse overlap */
  float dij;                    /* perp dist from segm i to midpt of ov_ij */

  int segm_ind;                 /* scan index (i) of segm under inspection */

  int sgl_level;                /* level of indirection in SGL assignment (0,1,2) */
  Boolean SalStat;              /* sgll(): when all segm in SAL<segm> InAct, InAct */
};

#endif /* _SGL_STAT_H_ */
