/* 
 * pcc2.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* PCC2.H:      header file includes former pcc.h and pccStruct.h
 *
 */


#ifndef _PCC2_H_
#define	_PCC2_H_

/* PCC.H:       include file for PCC programs  */

/* no. of 0, 1, 2, and 3 direction chain codes, and features */
#define NCODE0 1
#define NCODE1 8
#define NCODE2 64
#define NCODE3 512
#define NCODEF 9

#define CODE0 193               /* code for 0 segment code */
#define MINCODE1 194            /* min/max code values for   */
#define MAXCODE1 201            /*   1, 2, and 3 segment codes */
#define MINCODE2 202
#define MAXCODE2 241
#define MINCODE3 1
#define MAXCODE3 192
#define MINFEATCODE 242         /* min code value for features 
                                 * * * endpt, bifirc, cross */

/* branches */
#define NDIRNSPERFEATURE 3      /* no. directions per feature */
#define MAXBRANCH 300           /* max no. of branches on one chain */

/* feature codes */
#define STOPCODE 255            /* code after last codeword in storage */
#define ENDCODE 242             /* feature codes */
#define LINECODE 243
#define BIFCODE 244
#define CROSSCODE 245
#define STARTCODE 246           /* start code of structure */
#define LINEBRCODE 247          /* break feature codes */
#define BIFBRCODE 248
#define CROSSBRCODE 249

/* location in feature code array */
#define NSTOPCODE 0
#define NENDCODE 1
#define NLINECODE 2
#define NBIFCODE 3
#define NCROSSCODE 4
#define NSTARTCODE 5
#define NLINEBRCODE 6
#define NBIFBRCODE 7
#define NCROSSBRCODE 8

/* maximum number of code words */
#define NDECODE 255

/* for coding, feature junction points are set to not IMGOFF or IMGON */
#define ERASED 1                /* feature node erased when coding image */

/* maximum no. of level-1 lines per loop */
#define MAXPERLOOP 300

/* code for line type in level 1 attributes -- gives endpt. types */
#define EELINE 1                /* EE = End, End */
#define EBLINE 2                /* EB = End, Branch */
#define ECLINE 3                /* EC = End, Cross */
#define BELINE 4                /* BE = Branch, End */
#define BBLINE 5
#define BCLINE 6
#define CELINE 7                /* CE = Cross, End */
#define CBLINE 8
#define CCLINE 9
#define RLELINE 10              /* RLE = bReak, Line, End */
#define RLBLINE 11
#define RLCLINE 12
#define RBELINE 13
#define RBBLINE 14
#define RBCLINE 15
#define RCELINE 16
#define RCBLINE 17
#define RCCLINE 18




/* PCCSTRUCT.H  contains structures for TLC programs
 *
 */

#include <images.h>             /* image format information file */

/* structure contains PCC codes */
struct code {
  unsigned char code0[NCODE0],  /* 0-vector chains */
    code1[NCODE1],              /* 1-vector chains */
    code2[NCODE2],              /* 2-vector chains */
    code3[NCODE3],              /* 3-vector chains */
    codeFeat[NCODEF];           /* feature codes */
};

/* enough different branch structures to build a tree */
/* stack of branches waiting to be coded */

struct branch1 {                /* location of branches yet to code */
  long x, y;                    /* location of branch */
  long variable;                /* used for dirn or type in diff fcts */
  struct branch1 *next, *previous;  /* pointers to next/last branches */
};

/* line tolerances for line processing */
struct tolerances {
  long minEE,                   /* minimum endpt. to endpt. line length */
    minFE;                      /* end to/from feature minimum length */
};

/* variables to calculate level 1 attributes */
struct attrVar {
  long iByteCode,               /* byte location beginning line in code */
    iByteWidth,                 /* byte location beginning line in widths */
    inOut,                      /* see note above */
    feat1,                      /* start and end features of line */
    feat2, code1,               /* beginning and ending PCC of line */
    code2, width,               /* sum of line widths */
    nWidth,                     /* number of line widths */
    length,                     /* length [10 * pixel spacing] of line */
    nPts;                       /* no. points in line */
  struct point sumPt;           /* sums of x,y values */
  struct point pt1, pt2;        /* start and end image coordinates of line */
  struct rectangle box;         /* bounding box of line */
} *attrVar;                     /* input variables to calc. attr.s */

/* level 1 attributes */
struct attributes {
  long type,                    /* feature type */
    iByteCode,                  /* byte offset in fcCode beginning line */
    iByteWidth,                 /* byte offset in width array beginning line */
    inOut,                      /* input and output branches at node */
    width,                      /* average line width or EXO */
    length,                     /* line length in horiz/vert pixel spacing */
    nPts;                       /* number of points along line */
  struct point pt1, pt2;        /* start/end coord.s */
  unsigned char dirn1, dirn2;   /* endpoint directions */
  struct rectangle box;         /* bounding box of line */
  struct point sumPt;           /* sum of x,y points along line */
};

/* level 3 structures */
struct structures {             /* level 3 connected line structures */
  long iAttr,                   /* list of <iAttr> of beginning of structs */
    nLines,                     /* no. level 1 lines in structure */
    nEnds,                      /* no. endlines in structure */
    nLoops,                     /* no. loops in structure */
    width,                      /* average width of lines in structure */
    length,                     /* total length of lines in structure */
    maxLength;                  /* max. length of lines in structure */
  double centroidX, centroidY;  /* x,y centroid of all lines in structure */
  struct rectangle box;         /* bounding box of structure */
};

/* level 3 nearest neighbor structure */
struct nn {                     /* data structure for each NN */
  long iStrct;                  /* index of structure */
  long dist;                    /* distance */
};
struct strctNN {
  long nNN;                     /* no. nearest nbrs */
  struct nn *nn;                /* list of nearest nbrs */
};

/* level 2 loops */
struct loop {                   /* level 2 loops */
  long *iAttr,                  /* <iAttr> list per loop */
    n;                          /* no. level 1 lines per loop */
};

/* PCC features */
struct pccfeat {
  long *iAttrEnd,               /* line list number + 1 of end,  */
   *iAttrBif,                   /* bif., cross, loop  */
   *iAttrCross,                 /* +ve if pt1, -ve if pt2 in <attr> */
   *iAttrLoop;
  long nEnd,                    /* no. of endpoints */
    nBif,                       /* no. of bifurations */
    nCross,                     /* no. of crosses */
    nLoop;                      /* no. of junctions within loops */
};

/* array of near endpt. pairs */
struct nearEnds {
  struct point ptI,             /* coord.s of 2 endpoints */
    ptJ;
};

/* boundary points */
struct bound {
  long *iAttr;                  /* <iAttr> list of boundary pts. */
};

/* level 2 endlines */
struct endLine {
  struct point locn1,           /* location of one end of line */
    locn2;                      /* location of end which actually ends */
  int iAttr1,                   /* level 1 index of line */
    iAttr2,                     /* level 1 index of line if 2 break lines make
                                 * * up line; else -1 */
    type;                       /* feature type */
  long length;                  /* line length [x10] */
  unsigned char dirn1,          /* endpoint direction */
    dirn2;                      /* endpoint direction at end which ends */
};

/* level 2 bifurcations (3 branches per bifurcation) */
struct bif {
  struct point locn;            /* location of bifurcation junction */
  int iAttr[3],                 /* level 1 index of branch */
    type[3];                    /* feature type */
  long length[3];               /* line length [x10] */
  unsigned char dirn1[3],       /* endpoint direction at bifurc. */
    dirn2[3];                   /* endpoint direction away from bifurc. */
};

/* segment structure contains information on endpoints which
 * are located within square, non-overlapped image regions (segments) */
struct segment {
  short **list;                 /* pointer to list of iAttr for endpts */
  long nX, nY,                  /* no. segments per width (x), length (y) */
    size,                       /* sidelength of each segment */
   *nPer;                       /* no. endpt.s per each segment */
};



/* WW.H contains structures for line fitting programs
 *
 */

#define ABS(A) (((A) >= 0) ? (A): -(A))  /* integer absolute value */
#define ABSF(A) (((A) >= 0.0) ? (A): -(A))  /* floating absolute value */

#define DIAG 1.4142135          /* diagonal dist between pixels */

/* distances are kept *100 to obtain 2 digit precision for diagonals */
#define HORIZVERT 100           /* unit length of segment times 100 */
#define DIAG100 141             /* unit diagonal distance times 100 */

#define MDFLT 5                 /* max length of corner curvature */

#define L_DFLT 13               /* min arc-length between features */
#define L_MIN 5                 /* min user-choice of arc-length parameter */
#define M_MAX 3                 /* max arc-length of corner */

#define MAXPERCODE 6            /* 3 coords per PCC * 2 no.s per coord */
#define MAXBRPERNODE 4          /* maximum branches from a node */

/* node types */
/*
 * #define ENDCOORD -1
 * #define BIFCOORD -2
 * #define CROSSCOORD -3
 * #define STARTCOORD -4
 * #define LINEBRCOORD -5
 * #define BIFBRCOORD -6
 * #define CROSSBRCOORD -7
 */

#define MAXADJEDGES 3           /* max adjacent edges to another edge */

/* wing-walk feature types */
#define WWSTRT 1
#define WWCORNER 2
#define WWCURVE  3
#define WWEND 0

#define EPSILON1 0.0            /* tolerance on min peak width */
#define EPSILON2 0.0            /* tolerance on corner/curve arc length */

#define BORDERTHETA 50.0        /* flag (anything > PI) indicates that theta
                                 * * * has not been calculated because border /*
                                 * * * 
                                 * * * /* curve sweep -- indicates if the curve arc sweeps <180, >180, =180,
                                 * * * or an entire 360 degrees, ie a circle */
#define CURVELT180 0
#define CURVEGT180 1
#define CURVEEQ180 2            /* semicircle */
#define CURVEEQ360 3            /* circle */

/* Wing-Walk Structures */

struct wwPar {
  long m,                       /* middle segment length */
    l,                          /* total wing-walk length */
    w;                          /* 'wing' length */
};

/* coords in double floating precision  */
/* already defined in images.h
 * struct dpoint{
 * double x, y;
 * };
 */

struct wwfeats {
  struct point strt,            /* starting and ending coord.s of feature */
    end;
  struct dpoint center;         /* center of curvature for curve */
  double radius;                /* radius of curvature (=0 for strt line) */
};

struct edge {                   /* data indices between ends or jcts */
  long iLow,                    /* low and high indices in data array */
    iHigh;
};

struct theta {                  /* theta plot */
  double theta,                 /* theta curvature value */
    length;                     /* arclength from beginning to current */
};


/* structures for feature linked list */

struct featNode {               /* feature nodes pointing to feature par.s */
  int type;                     /* type of wing-walk feature */
  struct dpoint intrsct;        /* intersection point of tangents to curve */
  char *info;                   /* contains parameter information */
  struct featNode *next,        /* next node */
   *previous;                   /* previous node */
};

struct featK {                  /* corner feature parameters */
  struct point coord;           /* coordinate of corner feature */
};

struct featC {                  /* curve feature parameters */
  struct point trans1, trans2;  /* beginning and ending transition points */
  struct dpoint center;         /* coord. of center of circle of curvature */
  double radiusC;               /* radius of curvature */
  short dirn;                   /* trans pts. in CCW order (1), or CW (-1) */
};

/* structures for graph representation */

struct edgeList {               /* list of graph edges */
  struct edge edge;             /* data indices of ends of edge */
  long node1, node2;            /* index of start/end nodes, -1 if no node */
  long adjEdge1[MAXADJEDGES],   /* edge indices of start and end adjacent */
    adjEdge2[MAXADJEDGES],      /*   edges: +ve if entering, -ve if leaving */
    nAdjEdge1, nAdjEdge2;       /* no. of start and end adjacent edges */
  long length;                  /* length * 100 */
};

struct nodeList {               /* list of graph nodes */
  long type;                    /* node type */
  struct point locn;            /* x,y location */
  long incEdge[4],              /* edges incident to node */
    nEdges;                     /* no. edges incident to node */
  struct featNode *wwFeatPtr[2];  /* ptr to ww features in linked list */
  long nWWFeatPtr;              /* no. of ww features pointed to */
};


struct strghtEdges {            /* edge list of adjacent straight edges */
  long front, end;              /* straight edge at front and end of edge */
  int flag;                     /* used for marking edge already counted */
};

/* Function Definitions */
int pcccodes ();
int pcccode (unsigned char **, long, long);
int pcctrack (unsigned char **, long *, long *, long *, struct branch1 **, long *);
int pccrstore (long, long, long);
int pcclstore (long *, long);
int pccfstore (long);
int pccwrite (char *, unsigned char *, long, long, long);
int pccbranch (struct branch1 **, long, long, long);
int nbrtoxy (long, long, long, long *, long *);
int pccread (char *, unsigned char **, long *, long *, long *);
int pccdecodes ();
int pccdecode (unsigned char **, long, long, int);
int pccdetrack (unsigned char **, int *, int *, long, long, long, long);
int pcc2xy (struct point *, long *);
int detrack (int *, int *, int, struct point *, long *);
int tlc1attr (struct attributes **, long *);
int tlc1track (long *, long *, struct attrVar *, int);
int tlc1dirn (struct attributes *, long);
long dirncalc (long, long);
int tlc1store (struct attrVar, struct attributes *, long *);
int tlc1tag (struct attributes *, long, long, long);
int looptest (struct attributes *, long, struct branch1 *, long);
int tlc1rid (struct attributes *, long);
int tlc3structs (struct attributes *, long, struct structures **, long *);
int tlc3feats (struct attributes *, long, struct structures *, long);

#endif /* _PCC2_H_ */
