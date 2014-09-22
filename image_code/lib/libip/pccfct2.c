/* 
 * pccfct2.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* PCCFCT2:     functions for PCC: miscellaneous or common to encode/decode
 *            (encoding functions in PCCFCT; decoding functions
 *              in PCCFCTDE)
 *      FUNCTIONS:
 *              PCCBRANCH, NBRTOXY
 */

#include <stdio.h>
#include <stdlib.h>
#include "pcc2.h"               /* header file for PCC programs */

/* PCCBRANCH:   function adds new branch information
 *                    usage: pccbranch (&branch, x, y, variable)
 */

pccbranch (branch, x, y, variable)
     struct branch1 **branch;   /* branch */
     long x, y;                 /* location of branch */
     long variable;             /* used for different things by
                                 * * diff. fcts: dirn or type */
{
  long temp;
  temp = (long) *branch;	
if( temp == 0x0){
	printf("null branch encountered\n");
	return(-1);
  }
  (*branch)->x = x;
  (*branch)->y = y;
  (*branch)->variable = variable;
  if (((*branch)->next = (struct branch1 *) malloc (sizeof (struct branch1)))
      == NULL) {
    printf ("PCCBRANCH: not enough memory -- sorry", 1);
    return (-1);
  }
  temp = (long) *branch;
  *branch = (*branch)->next;
  (*branch)->previous = (struct branch1 *) temp;
  return (0);
}



/* NBRTOXY:     function converts 5x5 neighborhood position to
 *            to x,y coordinates 
 *                      usage: nbrtoxy (nbrhd, xCenter, yCenter, &x, &y)
 *
 */

nbrtoxy (nbrhd, xCenter, yCenter, x, y)
     register long nbrhd,       /* neighborhood position number */
       xCenter, yCenter;        /* coordinates of center point */
     long *x, *y;               /* output coord.s of neighbor point */
{
  switch (nbrhd) {
  case 0:
    *x = xCenter;
    *y = yCenter;
    break;
  case 1:
    *x = xCenter;
    *y = yCenter - 1;
    break;
  case 2:
    *x = xCenter + 1;
    *y = yCenter - 1;
    break;
  case 3:
    *x = xCenter + 1;
    *y = yCenter;
    break;
  case 4:
    *x = xCenter + 1;
    *y = yCenter + 1;
    break;
  case 5:
    *x = xCenter;
    *y = yCenter + 1;
    break;
  case 6:
    *x = xCenter - 1;
    *y = yCenter + 1;
    break;
  case 7:
    *x = xCenter - 1;
    *y = yCenter;
    break;
  case 8:
    *x = xCenter - 1;
    *y = yCenter - 1;
    break;
  case 9:
    *x = xCenter;
    *y = yCenter - 2;
    break;
  case 10:
    *x = xCenter + 1;
    *y = yCenter - 2;
    break;
  case 11:
    *x = xCenter + 2;
    *y = yCenter - 2;
    break;
  case 12:
    *x = xCenter + 2;
    *y = yCenter - 1;
    break;
  case 13:
    *x = xCenter + 2;
    *y = yCenter;
    break;
  case 14:
    *x = xCenter + 2;
    *y = yCenter + 1;
    break;
  case 15:
    *x = xCenter + 2;
    *y = yCenter + 2;
    break;
  case 16:
    *x = xCenter + 1;
    *y = yCenter + 2;
    break;
  case 17:
    *x = xCenter;
    *y = yCenter + 2;
    break;
  case 18:
    *x = xCenter - 1;
    *y = yCenter + 2;
    break;
  case 19:
    *x = xCenter - 2;
    *y = yCenter + 2;
    break;
  case 20:
    *x = xCenter - 2;
    *y = yCenter + 1;
    break;
  case 21:
    *x = xCenter - 2;
    *y = yCenter;
    break;
  case 22:
    *x = xCenter - 2;
    *y = yCenter - 1;
    break;
  case 23:
    *x = xCenter - 2;
    *y = yCenter - 2;
    break;
  case 24:
    *x = xCenter - 1;
    *y = yCenter - 2;
    break;
  }
  return (0);
}
