/* 
 * tlc1fct.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* TLC1FCT:     functions for TLC1 line analysis on top of PCC coding
 *
 *      FUNCTIONS:
 *              TLC1ATTR, TLC1TRACK, TLC1DIRN, TLC1STORE, TLC1TAG, TLC1RID
 */

#include <stdio.h>
#include <stdlib.h>
#include <images.h>             /* images information file */
#include "pcc2.h"               /* header file for PCC programs */

extern unsigned char *fcCode;   /* code storage */
extern long nByteCode;          /* no. bytes in code storage */

/* TLC1ATTR:    function reads code from code storage, and writes
 *            out attributes of decoded fcc
 *                      usage: tlc1attr (&attr, &nAttr)
 *
 *              Note:   There is a little bit of ugly protocol in here
 *                      which needs to be explained.
 *                      The array, <attr[].inOut> contains the number of
 *                      branches leaving a node... sort of. That is,
 *                      for each branch leaving a node, +1 is added
 *                      to that variable; if a branch goes into that
 *                      node, +10 is added. (There can be only 0 or 
 *                      1 branches into a node.) The variable is 
 *                      associated with the FIRST node of a line
 *                      feature (e.g. the feature, CB has 1 entering
 *                      the first node, and 3 leaving the first node,
 *                      therefore the variable =10 + 3 = 13.)  For the
 *                      attr[] array, the FIRST OUTGOING branch of each
 *                      junction carries information of the junction.
 *                      For example, {EB, BE, BE} have stored inOut,
 *                      {1, 12, 0}. 
 *
 */

tlc1attr (attr, nAttr)
     struct attributes **attr;  /* level 1 attributes */
     long *nAttr;               /* no. line structures in attr. array */
{
  register long iByteCode,      /* code storage incrementor */
    codeWord;                   /* code word contains up to 3 dirn.s */
  long xTrack, yTrack;          /* decode tracking  coord.s */
  struct branch1 *branch;       /* stack of branches */
  struct branch1 branchTop;     /* first branch */
  long nBranch;                 /* no. of branches in stack */
  struct attrVar attrVar;       /* variables to calculate level 1 attr.s */

/* allocate memory for level 1 attributes and begin linked list of branches */
  if ((*attr = (struct attributes *)
       calloc (nByteCode, sizeof (struct attributes))) == NULL) {
    printf ("TLC1ATTR: CALLOC -- not enough memory\n");
    return (-1);
  }
  branch = &branchTop;
  branch->previous = branch;

  *nAttr = 0;
  nBranch = 0;

/* decode from storage region and compute line attributes */

  for (iByteCode = 0; iByteCode < nByteCode;) {
    codeWord = (long) fcCode[iByteCode++];

    /* if it is a feature: find start location if break; push branches if
     * junction; pop branches if endpoint */

    if (codeWord >= MINFEATCODE) {

      switch (codeWord) {
      case BIFCODE:            /* push one more branch */
        pccbranch (&branch, xTrack, yTrack, BIFCODE);
        attrVar.feat2 = BIFCODE;
        attrVar.pt2.x = xTrack;
        attrVar.pt2.y = yTrack;
        nBranch++;
        attrVar.code2 = (long) fcCode[iByteCode - 2];

/*                    if (attrVar.length > 0 || attrVar.feat1 >= STARTCODE) */
        tlc1store (attrVar, *attr, nAttr);
        attrVar.iByteCode = iByteCode;
        attrVar.inOut = 12;
        attrVar.feat1 = BIFCODE;
        attrVar.pt1.x = xTrack;
        attrVar.pt1.y = yTrack;
        attrVar.code1 = (long) fcCode[iByteCode];
        attrVar.length = 0;
        attrVar.nPts = attrVar.sumPt.x = attrVar.sumPt.y = 0;
        attrVar.box.min.x = attrVar.box.max.x = xTrack;
        attrVar.box.min.y = attrVar.box.max.y = yTrack;
        attrVar.sumPt.x += xTrack;
        attrVar.sumPt.y += yTrack;
        attrVar.nPts++;
        if (xTrack < attrVar.box.min.x)
          attrVar.box.min.x = xTrack;
        if (yTrack < attrVar.box.min.y)
          attrVar.box.min.y = yTrack;
        if (xTrack > attrVar.box.max.x)
          attrVar.box.max.x = xTrack;
        if (yTrack > attrVar.box.max.y)
          attrVar.box.max.y = yTrack;
        break;

      case CROSSCODE:          /* push two more branches */
        pccbranch (&branch, xTrack, yTrack, CROSSCODE);
        attrVar.feat2 = CROSSCODE;
        attrVar.pt2.x = xTrack;
        attrVar.pt2.y = yTrack;
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, CROSSCODE);
        nBranch++;
        attrVar.code2 = (long) fcCode[iByteCode - 2];

/*                    if (attrVar.length > 0 || attrVar.feat1 >= STARTCODE) */
        tlc1store (attrVar, *attr, nAttr);
        attrVar.iByteCode = iByteCode;
        attrVar.inOut = 13;
        attrVar.feat1 = CROSSCODE;
        attrVar.pt1.x = xTrack;
        attrVar.pt1.y = yTrack;
        attrVar.code1 = (long) fcCode[iByteCode];
        attrVar.length = 0;
        attrVar.nPts = attrVar.sumPt.x = attrVar.sumPt.y = 0;
        attrVar.box.min.x = attrVar.box.max.x = xTrack;
        attrVar.box.min.y = attrVar.box.max.y = yTrack;
        attrVar.sumPt.x += xTrack;
        attrVar.sumPt.y += yTrack;
        attrVar.nPts++;
        if (xTrack < attrVar.box.min.x)
          attrVar.box.min.x = xTrack;
        if (yTrack < attrVar.box.min.y)
          attrVar.box.min.y = yTrack;
        if (xTrack > attrVar.box.max.x)
          attrVar.box.max.x = xTrack;
        if (yTrack > attrVar.box.max.y)
          attrVar.box.max.y = yTrack;
        break;

      case ENDCODE:            /* pop branches */
        attrVar.feat2 = ENDCODE;
        attrVar.pt2.x = xTrack;
        attrVar.pt2.y = yTrack;
        attrVar.code2 = (long) fcCode[iByteCode - 2];

/*                    if (attrVar.length > 0 || attrVar.feat1 >= STARTCODE) */
        tlc1store (attrVar, *attr, nAttr);

        if (nBranch > 0) {
          nBranch--;
          branch = branch->previous;
          attrVar.iByteCode = iByteCode;
          attrVar.inOut = 0;
          attrVar.feat1 = branch->variable;
          attrVar.pt1.x = xTrack = branch->x;
          attrVar.pt1.y = yTrack = branch->y;
          attrVar.code1 = (long) fcCode[iByteCode];
          attrVar.length = 0;
          attrVar.nPts = attrVar.sumPt.x = attrVar.sumPt.y = 0;
          attrVar.box.min.x = attrVar.box.max.x = xTrack;
          attrVar.box.min.y = attrVar.box.max.y = yTrack;
          attrVar.sumPt.x += xTrack;
          attrVar.sumPt.y += yTrack;
          attrVar.nPts++;
          if (xTrack < attrVar.box.min.x)
            attrVar.box.min.x = xTrack;
          if (yTrack < attrVar.box.min.y)
            attrVar.box.min.y = yTrack;
          if (xTrack > attrVar.box.max.x)
            attrVar.box.max.x = xTrack;
          if (yTrack > attrVar.box.max.y)
            attrVar.box.max.y = yTrack;
        }
        break;

      case STARTCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;

        attrVar.iByteCode = iByteCode;
        attrVar.inOut = 1;
        attrVar.feat1 = STARTCODE;
        attrVar.pt1.x = xTrack;
        attrVar.pt1.y = yTrack;
        attrVar.code1 = (long) fcCode[iByteCode];
        attrVar.length = 0;
        attrVar.nPts = attrVar.sumPt.x = attrVar.sumPt.y = 0;
        attrVar.box.min.x = attrVar.box.max.x = xTrack;
        attrVar.box.min.y = attrVar.box.max.y = yTrack;
        attrVar.sumPt.x += xTrack;
        attrVar.sumPt.y += yTrack;
        attrVar.nPts++;
        if (xTrack < attrVar.box.min.x)
          attrVar.box.min.x = xTrack;
        if (yTrack < attrVar.box.min.y)
          attrVar.box.min.y = yTrack;
        if (xTrack > attrVar.box.max.x)
          attrVar.box.max.x = xTrack;
        if (yTrack > attrVar.box.max.y)
          attrVar.box.max.y = yTrack;
        break;

      case LINEBRCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;

        pccbranch (&branch, xTrack, yTrack, LINEBRCODE);
        nBranch++;
        attrVar.iByteCode = iByteCode;
        attrVar.inOut = 2;
        attrVar.feat1 = LINEBRCODE;
        attrVar.pt1.x = xTrack;
        attrVar.pt1.y = yTrack;
        attrVar.code1 = (long) fcCode[iByteCode];
        attrVar.length = 0;
        attrVar.nPts = attrVar.sumPt.x = attrVar.sumPt.y = 0;
        attrVar.box.min.x = attrVar.box.max.x = xTrack;
        attrVar.box.min.y = attrVar.box.max.y = yTrack;
        attrVar.sumPt.x += xTrack;
        attrVar.sumPt.y += yTrack;
        attrVar.nPts++;
        if (xTrack < attrVar.box.min.x)
          attrVar.box.min.x = xTrack;
        if (yTrack < attrVar.box.min.y)
          attrVar.box.min.y = yTrack;
        if (xTrack > attrVar.box.max.x)
          attrVar.box.max.x = xTrack;
        if (yTrack > attrVar.box.max.y)
          attrVar.box.max.y = yTrack;
        break;

      case BIFBRCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;

        pccbranch (&branch, xTrack, yTrack, BIFBRCODE);
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, BIFBRCODE);
        nBranch++;
        attrVar.iByteCode = iByteCode;
        attrVar.inOut = 3;
        attrVar.feat1 = BIFBRCODE;
        attrVar.pt1.x = xTrack;
        attrVar.pt1.y = yTrack;
        attrVar.code1 = (long) fcCode[iByteCode];
        attrVar.length = 0;
        attrVar.width = attrVar.nWidth = 0;
        attrVar.nPts = attrVar.sumPt.x = attrVar.sumPt.y = 0;
        attrVar.box.min.x = attrVar.box.max.x = xTrack;
        attrVar.box.min.y = attrVar.box.max.y = yTrack;
        attrVar.sumPt.x += xTrack;
        attrVar.sumPt.y += yTrack;
        attrVar.nPts++;
        if (xTrack < attrVar.box.min.x)
          attrVar.box.min.x = xTrack;
        if (yTrack < attrVar.box.min.y)
          attrVar.box.min.y = yTrack;
        if (xTrack > attrVar.box.max.x)
          attrVar.box.max.x = xTrack;
        if (yTrack > attrVar.box.max.y)
          attrVar.box.max.y = yTrack;
        break;

      case CROSSBRCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;

        pccbranch (&branch, xTrack, yTrack, CROSSBRCODE);
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, CROSSBRCODE);
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, CROSSBRCODE);
        nBranch++;
        attrVar.iByteCode = iByteCode;
        attrVar.inOut = 4;
        attrVar.feat1 = CROSSBRCODE;
        attrVar.pt1.x = xTrack;
        attrVar.pt1.y = yTrack;
        attrVar.code1 = (long) fcCode[iByteCode];
        attrVar.length = 0;
        attrVar.width = attrVar.nWidth = 0;
        attrVar.nPts = attrVar.sumPt.x = attrVar.sumPt.y = 0;
        attrVar.box.min.x = attrVar.box.max.x = xTrack;
        attrVar.box.min.y = attrVar.box.max.y = yTrack;
        attrVar.sumPt.x += xTrack;
        attrVar.sumPt.y += yTrack;
        attrVar.nPts++;
        if (xTrack < attrVar.box.min.x)
          attrVar.box.min.x = xTrack;
        if (yTrack < attrVar.box.min.y)
          attrVar.box.min.y = yTrack;
        if (xTrack > attrVar.box.max.x)
          attrVar.box.max.x = xTrack;
        if (yTrack > attrVar.box.max.y)
          attrVar.box.max.y = yTrack;
        break;

      case LINECODE:
        break;

      case STOPCODE:
        tlc1dirn (*attr, *nAttr);
        *attr = (struct attributes *) realloc (*attr,
                                       *nAttr * sizeof (struct attributes));

        return (0);

      default:
        printf ("TLC1ATTR: ERROR - default feature\n");
        break;
      }
    }

    /* if it is a direction segment, write at proper location */
    else
      tlc1track (&xTrack, &yTrack, &attrVar, codeWord);
  }

  printf ("TLC1ATTR: ERROR - missing STOPCODE in PCC storage \n");

  return (0);
}



/* TLC1TRACK:   function decodes codeword and tracks directions,
 *            keeping track of line length (where length is measured
 *              in units of 10 * pixel spacing: 10 for vert/horiz, 
 *              14 for diagonal
 *                      usage: nDirns = tlc1track (&x, &y, &attrVar, codeWord)
 */

extern int deCode[NDECODE];     /* decode table */

#define DECODE(BITSHIFT) \
		dirn = ((deCode[codeWord] >> BITSHIFT) & 07) + 1; \
		attrVar->length += ((dirn % 2) == 0) ? 14:10; \
		nbrtoxy (dirn, *x, *y, x, y); \
		if (*x < attrVar->box.min.x) attrVar->box.min.x = *x; \
		else if (*x > attrVar->box.max.x) attrVar->box.max.x = *x; \
		if (*y < attrVar->box.min.y) attrVar->box.min.y = *y; \
		else if (*y > attrVar->box.max.y) attrVar->box.max.y = *y; \
  		attrVar->sumPt.x += *x; \
  		attrVar->sumPt.y += *y; \
  		(attrVar->nPts)++; \
  		if (*x < attrVar->box.min.x) attrVar->box.min.x = *x; \
  		if (*y < attrVar->box.min.y) attrVar->box.min.y = *y; \
  		if (*x > attrVar->box.max.x) attrVar->box.max.x = *x; \
  		if (*y > attrVar->box.max.y) attrVar->box.max.y = *y

tlc1track (x, y, attrVar, codeWord)
     long *x, *y;               /* input/output line coordinates */
     struct attrVar *attrVar;   /* variables to calculate level 1 attr.s */
     register int codeWord;     /* code word contains up to 3 directions */
{
  register long dirn;           /* direction of next segment */

/* 3 direction segments per code word */
  if (MINCODE3 <= codeWord && MAXCODE3 >= codeWord) {
    DECODE (0);
    DECODE (3);
    DECODE (6);
    return (3);
  }

/* 2 direction segments per code word */
  if (MINCODE2 <= codeWord && MAXCODE2 >= codeWord) {
    DECODE (0);
    DECODE (3);
    return (2);
  }

/* 1 direction segment per code word */
  if (MINCODE1 <= codeWord && MAXCODE1 >= codeWord) {
    DECODE (0);
    return (1);
  }

/* 0 direction segment per code word */
  if (codeWord == CODE0) {
    return (0);
  }
}



/* TLC1DIRN:    function calculates directions of ends of line segment
 *            from list of line segments. The length in samples
 *              on which the direction measurements are made is given.
 *              The directions are calculated as endpoint fits, and
 *              quantized to [degrees/2].
 *                      usage: tlc1dirn (&attr, nAttr)
 *
 */

/* segment length upon which directions are calculated [pixels * 10] */
#define DIRNLENGTH 100

tlc1dirn (attr, nAttr)
     struct attributes *attr;   /* level 1 attributes */
     long nAttr;                /* no. attributed lines in attr[] */
{
  register long iAttr,          /* attribute list incrementor */
    iCode,                      /* code incrementor */
    iCodeBegin,                 /* begin and end of segment in code */
    iCodeEnd;
  long deltaX,                  /* x,y increment of segment slope */
    deltaY;
  long dirncalc ();             /* given x,y increments, returns direction */
  struct attrVar attrVar;       /* variables to calculate level 1 attr.s */

  for (iAttr = 0; iAttr < nAttr; iAttr++) {
    /* calculate beginning and end of code for line segment */

    iCodeBegin = attr[iAttr].iByteCode;

    if (iAttr == nAttr - 1)     /* STOPCODE */
      iCodeEnd = nByteCode - 2;
    else {
      if (attr[iAttr + 1].inOut > 0 && attr[iAttr + 1].inOut <= 4)
        /* source node */
        iCodeEnd = attr[iAttr + 1].iByteCode - 6;
      else                      /* not source node */
        iCodeEnd = attr[iAttr + 1].iByteCode - 2;
    }

    /* find directions at beginning and end of line segment */

    deltaX = deltaY = attrVar.length = 0;
    for (iCode = iCodeBegin;
         (iCode <= iCodeEnd) && (attrVar.length < DIRNLENGTH);
         iCode++)
      tlc1track (&deltaX, &deltaY, &attrVar, (long) fcCode[iCode]);
    attr[iAttr].dirn1 = (dirncalc (deltaX, deltaY) + 90) % 180;

    deltaX = deltaY = attrVar.length = 0;
    for (iCode = iCodeEnd;
         (iCode >= iCodeBegin) && (attrVar.length < DIRNLENGTH);
         iCode--)
      tlc1track (&deltaX, &deltaY, &attrVar, fcCode[iCode]);
    attr[iAttr].dirn2 = (unsigned char) dirncalc (deltaX, deltaY);

  }
  return (0);
}

/* DIRNCALC: function calculates directions from x,y increments
 *         Directions are in [degrees/2].
 *                      usage: direction = dirncalc (deltaX, deltaY)
 *                                      long direction;
 */
#include <math.h>

#define NODIRN 180              /* no direction */
#if defined(WIN32)
#define PI 3.1415927
#endif

long
dirncalc (deltaX, deltaY)
     long deltaX, deltaY;       /* x, y increments */

{
  register long direction;      /* resultant direction */

  double slope;                 /* slope of segment */
  double atan ();

/* find directions associated with slopes */

  if (deltaX == 0) {
    if (deltaY > 0)
      return (45);
    if (deltaY < 0)
      return (135);
    if (deltaY == 0)
      return (NODIRN);
  }

  slope = ((double) deltaY) / ((double) deltaX);
  direction = (long) (atan (slope) * 180.0 / M_PI);

  if (deltaX < 0)
    direction += 180;
  direction = (direction + 360) % 360;
  direction /= 2;

  return (direction);
}



 /* TLC1STORE:  function takes variables associated with the
  * *           line, calculates line attributes, and stores them
  * *                   usage: tlc1store (attrVar, attr, &nAttr)
  * *
  * *           Note that two attributes are stored as approximations 
  * *           for the sake of coding and computation ease. The line
  * *           length ending at a branch or a cross is in error by 0.2
  * *           pixel units (that is, the average difference between
  * *           a diagonal and vert/horiz length). Line lengths
  * *           beginning at a branch or cross have the same approximation.
  * *           Line lengths beginning and ending at a cross or branch
  * *           have maximum error of 0.4. For the above conditions,
  * *           the end directions are also approximate. The last
  * *           vector in the 3 vector code is actually beyond the
  * *           branch or cross point, but is used in the direction
  * *           determination for the line end at this point.
  * *
  */

#define MOD8(A,B) ((((A) + (B) - 1) % 8) + 1)
    /* mod 8 addition, where result = [1,8] */

tlc1store (attrVar, attr, nAttr)
     struct attrVar attrVar;    /* variables to calculate level 1 attr.s */
     struct attributes *attr;   /* level 1 attributes */
     long *nAttr;               /* no. attributed lines in attr[] */
{

/* line type */
  switch (attrVar.feat1) {
  case STARTCODE:
    switch (attrVar.feat2) {
    case ENDCODE:
      attr[*nAttr].type = EELINE;
      break;
    case BIFCODE:
      attr[*nAttr].type = EBLINE;
      break;
    case CROSSCODE:
      attr[*nAttr].type = ECLINE;
      break;
    default:
      printf ("TLC1STORE: error\n");
      break;
    }
    break;

  case LINEBRCODE:
    switch (attrVar.feat2) {
    case ENDCODE:
      attr[*nAttr].type = RLELINE;
      break;
    case BIFCODE:
      attr[*nAttr].type = RLBLINE;
      break;
    case CROSSCODE:
      attr[*nAttr].type = RLCLINE;
      break;
    default:
      printf ("TLC1STORE: error\n");
      break;
    }
    break;

  case BIFCODE:
    switch (attrVar.feat2) {
    case ENDCODE:
      attr[*nAttr].type = BELINE;
      break;
    case BIFCODE:
      attr[*nAttr].type = BBLINE;
      break;
    case CROSSCODE:
      attr[*nAttr].type = BCLINE;
      break;
    default:
      printf ("TLC1STORE: error\n");
      break;
    }
    break;

  case BIFBRCODE:
    switch (attrVar.feat2) {
    case ENDCODE:
      attr[*nAttr].type = RBELINE;
      break;
    case BIFCODE:
      attr[*nAttr].type = RBBLINE;
      break;
    case CROSSCODE:
      attr[*nAttr].type = RBCLINE;
      break;
    default:
      printf ("TLC1STORE: error\n");
      break;
    }
    break;

  case CROSSCODE:
    switch (attrVar.feat2) {
    case ENDCODE:
      attr[*nAttr].type = CELINE;
      break;
    case BIFCODE:
      attr[*nAttr].type = CBLINE;
      break;
    case CROSSCODE:
      attr[*nAttr].type = CCLINE;
      break;
    default:
      printf ("TLC1STORE: error\n");
      break;
    }
    break;

  case CROSSBRCODE:
    switch (attrVar.feat2) {
    case ENDCODE:
      attr[*nAttr].type = RCELINE;
      break;
    case BIFCODE:
      attr[*nAttr].type = RCBLINE;
      break;
    case CROSSCODE:
      attr[*nAttr].type = RCCLINE;
      break;
    default:
      printf ("TLC1STORE: error\n");
      break;
    }
    break;

  default:
    printf ("TLC1STORE: not end, branch, or cross -- Problems\n");
  }

/* location in <fcCode[]> of this attributed line 
 * Note that this is the line beginning location - i.e. after
 * the stored codes for: feature, x, y */

  attr[*nAttr].iByteCode = attrVar.iByteCode;

/* branches to/from beginning of line, where +10 for input to
 * beginning of line, +1 for output from beginning of line */

  attr[*nAttr].inOut = attrVar.inOut;

/* pixel length of line: horiz/vert = 10, diag length = 14
 * See note regarding approximate lengths in heading */

  attr[*nAttr].length = attrVar.length;

/* start and end image coordinates */

  attr[*nAttr].pt1.x = attrVar.pt1.x;
  attr[*nAttr].pt1.y = attrVar.pt1.y;
  attr[*nAttr].pt2.x = attrVar.pt2.x;
  attr[*nAttr].pt2.y = attrVar.pt2.y;

/* sum and bounding box info */
  attr[*nAttr].box = attrVar.box;
  attr[*nAttr].sumPt = attrVar.sumPt;
  attr[*nAttr].nPts = attrVar.nPts;

  (*nAttr)++;

  return (0);
}



/* TLC1TAG:     function cleans up line ends, tagging them for removal if
 *            their length is below minimum tolerance
 *                      usage:  tlc1tag (attr, nAttr, minEE, minFE)
 *
 *              Note:   There is a little bit of ugly protocol in here
 *                      which needs to be explained.
 *                      The array, <attr[].inOut> contains the number of
 *                      branches leaving a node... sort of. That is,
 *                      for each branch leaving a node, +1 is added
 *                      to that variable; if a branch goes into that
 *                      node, +10 is added. (There can be only 0 or 
 *                      1 branches into a node.) The variable is 
 *                      associated with the FIRST node of a line
 *                      feature (e.g. the feature, CB has 1 entering
 *                      the first node, and 3 leaving the first node,
 *                      therefore the variable =10 + 3 = 13.)  For the
 *                      attr[] array, the FIRST OUTGOING branch of each
 *                      junction carries information of the junction.
 *                      For example, {EB, BE, BE} have stored inOut,
 *                      {1, 12, 0}. 
 *
 */

tlc1tag (attr, nAttr, minEE, minFE)
     struct attributes *attr;   /* level 1 attributes */
     register long nAttr;       /* no. of line structures in attr. array */
     long minEE, minFE;         /* minimum EE and FE line thresholds */
{
  register long iAttr,          /* incrementor for attributes */
    iBranchBreak;               /* down counter for no. of branches from
                                 * * break, not already tested */

  struct branch1 *branch;       /* stack for branches */
  struct branch1 branchTop;     /* first branch */
  long nBranch;                 /* no. of branches in stack */

/* initialize */
  branch = &branchTop;
  branch->previous = branch;
  iBranchBreak = 0;
  nBranch = 0;

/* test each line feature */

  for (iAttr = 0; iAttr < nAttr; iAttr++) {

    switch (attr[iAttr].type) {

    case EELINE:
      if (attr[iAttr].length < minEE) {
        attr[iAttr].type *= -1;
        attr[iAttr].inOut -= 1;
      }
      break;

    case ECLINE:
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;

    case EBLINE:
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      if (attr[iAttr].length < minFE) {
        attr[iAttr].type *= -1;
        attr[iAttr].inOut -= 1;
        attr[iAttr + 1].inOut -= 10;
      }
      break;

    case BELINE:
    case CELINE:
      nBranch--;
      branch = branch->previous;
      if (attr[iAttr].length < minFE
          && attr[iAttr].length > 0
          && looptest (attr, iAttr, branch, nBranch) == 0) {
        attr[iAttr].type *= -1;
        if (iAttr == branch->variable)
          attr[iAttr].inOut -= 1;
        else
          attr[branch->variable].inOut -= 1;
      }
      break;

    case BBLINE:
    case CBLINE:
      nBranch--;
      branch = branch->previous;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      break;

    case BCLINE:
    case CCLINE:
      nBranch--;
      branch = branch->previous;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      break;

    case RBELINE:
      /* if first (and only) break in structure, push branches */
      if (iBranchBreak == 0) {  /* first feature in break */
        iBranchBreak = 3;       /* 3 branches */
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
      }
      iBranchBreak--;
      nBranch--;
      branch = branch->previous;
      if (attr[iAttr].length < minFE
          && attr[iAttr].length > 0
          && looptest (attr, iAttr, branch, nBranch) == 0) {
        attr[iAttr].type *= -1;
        if (iAttr == branch->variable)
          attr[iAttr].inOut -= 1;
        else
          attr[branch->variable].inOut -= 1;
      }
      break;

    case RCELINE:
      /* if first (and only) break in structure, push branches */
      if (iBranchBreak == 0) {
        iBranchBreak = 4;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
      }
      iBranchBreak--;
      nBranch--;
      branch = branch->previous;
      if (attr[iAttr].length < minFE
          && attr[iAttr].length > 0
          && looptest (attr, iAttr, branch, nBranch) == 0) {
        attr[iAttr].type *= -1;
        if (iAttr == branch->variable)
          attr[iAttr].inOut -= 1;
        else
          attr[branch->variable].inOut -= 1;
      }
      break;

    case RLELINE:
    case RLBLINE:
    case RLCLINE:
      /* if first break (of pair), push it and continue */
      if (iBranchBreak == 0) {
        iBranchBreak = 1;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
      }
      else {
        iBranchBreak--;
        nBranch--;
        branch = branch->previous;
        /* if single line (endpt at each end) */
        if (
             (attr[iAttr].type == RLELINE && attr[iAttr].length != 0)
             && (attr[branch->variable].type == RLELINE
                 && attr[branch->variable].length != 0)) {
          if ((attr[iAttr].length
               + attr[branch->variable].length)
              < minEE
              && looptest (attr, iAttr, branch, nBranch) == 0) {
            attr[iAttr].type *= -1;
            attr[branch->variable].type *= -1;
            attr[branch->variable].inOut -= 2;
          }
        }
        /* if line attached to rest of structure at one end */
        else if (attr[iAttr].type == RLELINE
                 || attr[branch->variable].type
                 == RLELINE) {

          if (attr[iAttr].length != 0 &&
              attr[branch->variable].length != 0) {

            if ((attr[iAttr].length
                 + attr[branch->variable].length)
                < minFE
                && looptest (attr, iAttr, branch, nBranch) == 0) {
              /* change following feature first, if need be */
              if (attr[iAttr].type == RLBLINE
                  || attr[iAttr].type == RLCLINE)
                attr[iAttr + 1].inOut -= 10;
              else if (attr[branch->variable].type
                       == RLBLINE
                       || attr[branch->variable].type
                       == RLCLINE)
                attr[branch->variable + 1].inOut
                  -= 10;

              attr[iAttr].type *= -1;
              attr[branch->variable].type *= -1;
              attr[branch->variable].inOut -= 2;
            }
          }
        }
      }
      if (attr[iAttr].type == RLBLINE
          || attr[iAttr].type == -RLBLINE) {
        pccbranch (&branch, 0, 0, iAttr + 1);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr + 1);
        nBranch++;
      }
      if (attr[iAttr].type == RLCLINE
          || attr[iAttr].type == -RLCLINE) {
        pccbranch (&branch, 0, 0, iAttr + 1);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr + 1);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr + 1);
        nBranch++;
      }

      break;

    case RBBLINE:
      /* if first (and only) break in structure, push branches */
      if (iBranchBreak == 0) {
        iBranchBreak = 3;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
      }
      iBranchBreak--;
      nBranch--;
      branch = branch->previous;

      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      break;

    case RBCLINE:
      /* if first (and only) break in structure, push branches */
      if (iBranchBreak == 0) {
        iBranchBreak = 3;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
      }
      iBranchBreak--;
      nBranch--;
      branch = branch->previous;

      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      break;

    case RCBLINE:
      /* if first (and only) break in structure, push branches */
      if (iBranchBreak == 0) {
        iBranchBreak = 4;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
      }
      iBranchBreak--;
      nBranch--;
      branch = branch->previous;

      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      break;

    case RCCLINE:
      /* if first (and only) break in structure, push branches */
      if (iBranchBreak == 0) {
        iBranchBreak = 4;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
        pccbranch (&branch, 0, 0, iAttr);
        nBranch++;
      }
      iBranchBreak--;
      nBranch--;
      branch = branch->previous;

      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      pccbranch (&branch, 0, 0, iAttr + 1);
      nBranch++;
      break;

    default:
      printf ("TLC1TAG: error default type\n");
      break;
    }
  }
  return (0);
}


/* LOOPTEST:    function tests to see if current end line is end of loop
 *                    usage: loop = looptest (attr, iAttr, branch, nBranch)
 */

int
looptest (attr, iAttr, branch, nBranch)
     struct attributes *attr;   /* level 1 attributes */
     register long iAttr;       /* current line no. of endline to be tested */
     struct branch1 *branch;    /* stack for branches */
     long nBranch;              /* no. of branches in stack */
{
  register long iBranch,        /* branch stack incrementor */
    xDist,                      /* x,y distances of endpt. from branch pt */
    yDist;
  struct branch1 *pBranch;      /* pointer to branch stack */

/* test through all pushed branches whether current endpointis end of loop */
  pBranch = branch;
  for (iBranch = nBranch - 1; iBranch >= 0; iBranch--) {
    pBranch = pBranch->previous;
    if (pBranch->variable != iAttr) {
      xDist = attr[iAttr].pt2.x - attr[pBranch->variable].pt1.x;
      yDist = attr[iAttr].pt2.y - attr[pBranch->variable].pt1.y;
      xDist = (xDist < 0) ? -xDist : xDist;
      yDist = (yDist < 0) ? -yDist : yDist;
      if (xDist <= 1 && yDist <= 1)
        return (1);
    }
  }
  return (0);
}



/* TLC1RID:     function edits fcc code, removing lines and modifying
 *            feature codes on basis of array of junction
 *              branches and lines to be omitted. Function returns
 *              number of code bytes after ridding lines.
 *                      usage: nByteCode = tlc1rid (attr, nAttr)
 */

#define NFEATJCTS 14            /* max. no. in featJcts array */

tlc1rid (attr, nAttr)
     struct attributes *attr;   /* level 1 attributes */
     register long nAttr;       /* no. of line structures in attr. array */
{
  long featJcts[NFEATJCTS],     /* array positions are junction numbers
                                 * * corresponding to node feature codes */
    source,                     /* flag: (=1) => stored source point,
                                 * * (=0) => no stored source point */
    nBreakPerStruct;            /* no. breaks remaining in current struct
                                 * * (if new break, then source of structure) */
  register long iAttr,          /* incrementor for attributes */
    nByteFeatM1,                /* no. bytes in fcc for (feat, x, y) - 1 */
    iCodeIn,                    /* incrementor for read input fcc */
    iCodeOut,                   /* incrementor for write output fcc */
    type;                       /* absolute value of line type */
  unsigned char *fcCodeOut;     /* ptr to output fcc written over input */

/* initialize */
  iCodeOut = 0;
  source = 0;
  nBreakPerStruct = 0;
  fcCodeOut = fcCode;
  nByteFeatM1 = 1 + 2 * 2 - 1;

/* initialize array of features corresponding to junction branches,
 * where entering branch has value of (+10), exiting branches (+1) each */
  featJcts[1] = STARTCODE;
  featJcts[2] = LINEBRCODE;
  featJcts[3] = BIFBRCODE;
  featJcts[4] = CROSSBRCODE;
  featJcts[10] = ENDCODE;
  featJcts[11] = LINECODE;
  featJcts[12] = BIFCODE;
  featJcts[13] = CROSSCODE;

/* test for each line */
  for (iAttr = 0; iAttr < nAttr; iAttr++) {

    /* for original code of start or break, set <source> flag */
    type = ABS (attr[iAttr].type);
    if (type >= EELINE && type <= ECLINE)
      source = 1;
    else if (type >= RLELINE && type <= RCCLINE) {
      if (nBreakPerStruct == 0) {
        source = 1;
        if (type >= RLELINE && type <= RLCLINE)
          nBreakPerStruct = 1;
        else if (type >= RBELINE && type <= RBCLINE)
          nBreakPerStruct = 2;
        else if (type >= RCELINE && type <= RCCLINE)
          nBreakPerStruct = 3;
      }
      else {
        nBreakPerStruct -= 1;
      }
    }

    /* for what is now: a start or break code, store (feature, x, y);
     * another feature type, store (feature); 
     * a linebreak or nothing, store no feature 
     * If there is no stored source point (source = 0),
     * then next line is a branch from a previous junction */

    if (attr[iAttr].inOut > 0 && attr[iAttr].inOut <= 4) {
      if (source == 1) {
        fcCodeOut[iCodeOut++] =
          (unsigned char) featJcts[attr[iAttr].inOut];
        fcCode[iCodeOut++]
          = (unsigned char) (attr[iAttr].pt1.x & 0xff);
        fcCode[iCodeOut++]
          = (unsigned char) ((attr[iAttr].pt1.x >> 8) & 0xff);
        fcCode[iCodeOut++]
          = (unsigned char) (attr[iAttr].pt1.y & 0xff);
        fcCode[iCodeOut++]
          = (unsigned char) ((attr[iAttr].pt1.y >> 8) & 0xff);
        source = 0;
      }
    }
    else if (attr[iAttr].inOut >= 10 && attr[iAttr].inOut != 11)
      fcCodeOut[iCodeOut++] =
        (unsigned char) featJcts[attr[iAttr].inOut];
    else if (attr[iAttr].inOut == 0 || attr[iAttr].inOut == 11);
    else
      printf ("TLC1RID: ERROR: attr[%3d].inOut = %3d\n", iAttr,
              attr[iAttr].inOut);

    /* if line not tagged to be eliminated, then read/write until feature */

    iCodeIn = attr[iAttr].iByteCode;
    if (attr[iAttr].type > 0) {
      for (; fcCode[iCodeIn] < MINFEATCODE; iCodeIn++)
        fcCodeOut[iCodeOut++] = fcCode[iCodeIn];

      if (fcCode[iCodeIn] == ENDCODE)
        fcCodeOut[iCodeOut++] = fcCode[iCodeIn];
    }
  }

/* write stop code */
  fcCodeOut[iCodeOut++] = STOPCODE;

  return (iCodeOut);
}
