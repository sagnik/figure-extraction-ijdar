/* 
 * drawline8.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* DRAWLINE8:   This function draws an 8-connected line of given intensity
 *            between given coordinates on input/output image
 *              The 8-connectedness of the line guarantees the minimum
 *              number of line points between 2 ends on a discrete 
 *              Cartesian grid.
 *                     usage: nPts = drawline8 (image, imgSize,
 *                                                      pt1, pt2, intensity)
 */

#include <images.h>             /* picture file properties */

long
drawline8 (image, imgSize, pt1, pt2, intensity)
     unsigned char **image;     /* input/output image array */
     struct point imgSize;      /* size of image array */
     struct point pt1,          /* coord.s of begin. and end. of line */
       pt2;
     unsigned char intensity;   /* intensity value of line */
{
  register int x, y,            /* x,y coord.s of line */
    xFinal, yFinal,             /* x,y final endpoint */
    dx, dy;                     /* x, y differences */
  long xInc, yInc,              /* x, y fixed increments */
    xRun, yRun,                 /* x, y cumulative runs */
    nPts;                       /* no. points drawn */

/* initialize endpoints */
  x = pt1.x;
  y = pt1.y;
  xFinal = pt2.x;
  yFinal = pt2.y;

/* determine x,y fixed increments */
  dx = xFinal - x;
  dy = yFinal - y;

  xInc = (dx > 0) ? 1 : -1;
  yInc = (dy > 0) ? 1 : -1;

/* initialize cumulative x,y increments */
  if (dx < 0)
    dx = -dx;
  if (dy < 0)
    dy = -dy;

  yRun = dx;
  xRun = dy;

/* join line endpoints */
  image[y][x] = intensity;
  nPts = 1;
  while (x != xFinal || y != yFinal) {
    if (xRun <= yRun) {
      xRun += dy;
      x += xInc;
    }
    if (xRun >= yRun) {
      yRun += dx;
      y += yInc;
    }
    image[y][x] = intensity;
    nPts++;
  }
  image[y][x] = intensity;
  nPts++;

  return (nPts);
}
