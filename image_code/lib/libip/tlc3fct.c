/* 
 * tlc3fct.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* TLC3FCT:     functions for TLC3 line structure analysis on top of PCC coding
 *
 *      FUNCTIONS:
 *              TLC3STRUCTS, TLC3FEATS
 */

#include <stdio.h>
#include <stdlib.h>
#include "pcc2.h"               /* header file for PCC programs */

/* TLC3STRUCTS: function reads through level 1 line list, finding
 *            beginning of each connected structure, and returning
 *              array of this list of <iAttr>.
 *              usage: tlc3structs (attr, nAttr, &strct, &nStrct)
 *
 */

tlc3structs (attr, nAttr, strct, nStrct)
     struct attributes *attr;   /* level 1 attributes */
     register long nAttr;       /* no. of line structures in attr. array */
     struct structures **strct; /* level 3 connected line structures */
     long *nStrct;              /* no. of connected structures in image */
{
  register long iAttr,          /* incrementor for line list */
    iStrct,                     /* incrementor for structure list */
    iBranchBreak;               /* no. of remaining branches in start
                                 * * or break code */
  long nPts;                    /* no. x,y points in object */
  double sumX, sumY;            /* sum of coordinates for centroid */

/* allocate memory for level 3 structures */
  if ((*strct = (struct structures *)
       calloc (nAttr, sizeof (struct structures))) == NULL) {
    printf ("TLC3STRUCTS: CALLOC -- not enough memory");
    return (-1);
  }

  *nStrct = 0;
  iBranchBreak = 0;

/* first find the tlc1 line index where each structure begins */

  for (iAttr = 0; iAttr < nAttr; iAttr++) {
    if ((attr[iAttr].type >= EELINE && attr[iAttr].type <= ECLINE)
        || attr[iAttr].type >= RLELINE && attr[iAttr].type <= RCCLINE) {

      if (iBranchBreak == 0) {
        (*strct)[(*nStrct)++].iAttr = iAttr;

        /* set <iBranchCode> equal to remaining no. of branches for
         * start or break code */
        if (attr[iAttr].type >= EELINE && attr[iAttr].type <= ECLINE)
          iBranchBreak = 0;
        else if (attr[iAttr].type >= RLELINE
                 && attr[iAttr].type <= RLCLINE)
          iBranchBreak = 1;
        else if (attr[iAttr].type >= RBELINE
                 && attr[iAttr].type <= RBCLINE)
          iBranchBreak = 2;
        else if (attr[iAttr].type >= RCELINE
                 && attr[iAttr].type <= RCCLINE)
          iBranchBreak = 3;
        else {
          printf ("TLC3STRUCTS: error, not legal attr type\n");
          return (-1);
        }
      }
      else
        iBranchBreak -= 1;
    }
  }

/* reallocate structure memory -- Note that in TLC2LOOP, this
 * requires (nStrct + 1) elements in strct array */

  *strct = (struct structures *) realloc (*strct,
                                (*nStrct + 1) * sizeof (struct structures));
  (*strct)[*nStrct].iAttr = 10000000;

/* now calculate level 3 attributes from level 1 */
  for (iStrct = 0; iStrct < *nStrct; iStrct++) {
    (*strct)[iStrct].nLines = (*strct)[iStrct].nEnds =
      (*strct)[iStrct].nLoops = (*strct)[iStrct].width =
      (*strct)[iStrct].length = (*strct)[iStrct].maxLength = 0;
    sumX = sumY = 0.0;
    nPts = 0;
    (*strct)[iStrct].box.min.x = (*strct)[iStrct].box.min.y = 100000000;
    (*strct)[iStrct].box.max.x = (*strct)[iStrct].box.max.y = -1;
    for (iAttr = (*strct)[iStrct].iAttr;
         (iAttr < (*strct)[iStrct + 1].iAttr && iAttr < nAttr); iAttr++) {
      (*strct)[iStrct].nLines++;
      if (attr[iAttr].type == EELINE)
        (*strct)[iStrct].nEnds += 2;
      else if (attr[iAttr].type == EBLINE || attr[iAttr].type == ECLINE
               || attr[iAttr].type == BELINE || attr[iAttr].type == CELINE
               || attr[iAttr].type == RLELINE || attr[iAttr].type == RBELINE
               || attr[iAttr].type == RCELINE)
        (*strct)[iStrct].nEnds++;
      (*strct)[iStrct].width += attr[iAttr].width;
      (*strct)[iStrct].length += attr[iAttr].length;
      if (attr[iAttr].length > (*strct)[iStrct].maxLength)
        (*strct)[iStrct].maxLength = attr[iAttr].length;
      sumX += attr[iAttr].sumPt.x;
      sumY += attr[iAttr].sumPt.y;
      nPts += attr[iAttr].nPts;
      if (attr[iAttr].box.min.x < (*strct)[iStrct].box.min.x)
        (*strct)[iStrct].box.min.x = attr[iAttr].box.min.x;
      if (attr[iAttr].box.min.y < (*strct)[iStrct].box.min.y)
        (*strct)[iStrct].box.min.y = attr[iAttr].box.min.y;
      if (attr[iAttr].box.max.x > (*strct)[iStrct].box.max.x)
        (*strct)[iStrct].box.max.x = attr[iAttr].box.max.x;
      if (attr[iAttr].box.max.y > (*strct)[iStrct].box.max.y)
        (*strct)[iStrct].box.max.y = attr[iAttr].box.max.y;
    }
    (*strct)[iStrct].width /= (*strct)[iStrct].nLines;
    (*strct)[iStrct].centroidX = sumX / (double) nPts;
    (*strct)[iStrct].centroidY = sumY / (double) nPts;
  }
  return (0);
}


/* TLC3FEATS:   function determines level 3 attributes
 *                    usage: tlc3feats (attr, nAttr, structs, nStructs)
 *
 */

tlc3feats (attr, nAttr, structs, nStructs)
     struct attributes *attr;   /* level 1 attributes */
     long nAttr;                /* no. level 1 attributes */
     struct structures *structs;  /* level 3 attributes */
     long nStructs;             /* no. level 3 attributes */
{
  long iStructs,                /* level 3 increment */
    iAttr,                      /* level 1 increment */
    iAttrEnd;                   /* end + 1 line 1 attribute in structure */

  for (iStructs = 0; iStructs < nStructs; iStructs++) {
    structs[iStructs].nLines = structs[iStructs].nEnds = 0;
    structs[iStructs].nLoops = structs[iStructs].length = 0;
    structs[iStructs].width = structs[iStructs].maxLength = 0;
    iAttrEnd = (iStructs + 1 < nStructs) ? structs[iStructs + 1].iAttr : nAttr;
    structs[iStructs].box.min.x = structs[iStructs].box.min.y = 100000;
    structs[iStructs].box.max.x = structs[iStructs].box.max.y = 0;
    for (iAttr = structs[iStructs].iAttr; iAttr < iAttrEnd; iAttr++) {
      if (attr[iAttr].length != 0) {
        structs[iStructs].width += attr[iAttr].width;
        structs[iStructs].length += attr[iAttr].length;
        if (structs[iStructs].maxLength < attr[iAttr].length)
          structs[iStructs].maxLength = attr[iAttr].length;
        structs[iStructs].nLines++;
        if (attr[iAttr].type == EELINE || attr[iAttr].type == EBLINE
            || attr[iAttr].type == ECLINE || attr[iAttr].type == BELINE
            || attr[iAttr].type == CELINE || attr[iAttr].type == RLELINE
            || attr[iAttr].type == RBELINE || attr[iAttr].type == RCELINE)
          structs[iStructs].nEnds++;
      }
      if (attr[iAttr].box.min.x < structs[iStructs].box.min.x)
        structs[iStructs].box.min.x = attr[iAttr].box.min.x;
      if (attr[iAttr].box.min.y < structs[iStructs].box.min.y)
        structs[iStructs].box.min.y = attr[iAttr].box.min.y;
      if (attr[iAttr].box.max.x > structs[iStructs].box.max.x)
        structs[iStructs].box.max.x = attr[iAttr].box.max.x;
      if (attr[iAttr].box.max.y > structs[iStructs].box.max.y)
        structs[iStructs].box.max.y = attr[iAttr].box.max.y;
    }
    structs[iStructs].width = (long) ((double) structs[iStructs].width /
                                   (double) structs[iStructs].nLines + 0.5);
  }
  return (0);
}
