/* 
 * draw.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1999 SOS Software
 */

#include "draw.h"
#include "mtables.c"

#define ERRORMEM(arg1) {fprintf (stderr,"%s: not enough memory -- sorry\n", arg1);exit (1);}
#define	SIGN(a)		( ((a) == 0.0) ? 0 : ( ((a) < 0.0) ? -1 : 1 ) )
#define F_TO_INT(x)     ( ((x)-(int)(x)<0.5) ? (int)(x) : (int)(x)+1 )
#define	CS30		0.8660254


/*
 * draw_line()
 *   DESCRIPTION:
 *     draw_line draws a line from point (x1,y1) to (x2,y2) using Bresenham's algorithm.
 *   ARGUMENTS:
 *     x1, y1, x2, y2(int) start and end points of line
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for line
 *   RETURN VALUE:
 *     none
 */
void
draw_line (int x1, int y1, int x2, int y2, Image * imgIO, int value)
{
  int x = x1;
  int y = y1;
  int D = 0;
  int dx = x2 - x1;
  int dy = y2 - y1;
  int c;
  int M;
  int xinc = 1;
  int yinc = 1;

  if (dx < 0) {
    xinc = -1;
    dx = -dx;
  }
  if (dy < 0) {
    yinc = -1;
    dy = -dy;
  }
  if (dy < dx) {
    c = 2 * dx;
    M = 2 * dy;
    while (x != x2) {
      setpixel (x, y, imgIO, value);
      x += xinc;
      D += M;
      if (D > dx) {
        y += yinc;
        D -= c;
      }
    }
  }
  else {
    c = 2 * dy;
    M = 2 * dx;
    while (y != y2) {
      setpixel (x, y, imgIO, value);
      y += yinc;
      D += M;
      if (D > dy) {
        x += xinc;
        D -= c;
      }
    }
  }
}

/*
 * draw_circle()
 *   DESCRIPTION:
 *     draw_circle draws a circle specified by a center point and radius.
 *   ARGUMENTS:
 *     xC, yC(int) center point of circle
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for circle
 *   RETURN VALUE:
 *     none
 */
void
draw_circle (int xC, int yC, int R, Image * imgIO, int value)
{
  int x = 0;
  int y = R;
  int u = 1;
  int v = 2 * R - 1;
  int E = 0;

  setpixel (xC, yC + R, imgIO, value);
  setpixel (xC, yC - R, imgIO, value);
  setpixel (xC + R, yC, imgIO, value);
  setpixel (xC - R, yC, imgIO, value);

  while (x < y) {
    x++;
    E += u;
    u += 2;
    if (v < 2 * E) {
      y--;
      E -= v;
      v -= 2;
    }
    if (x <= y) {
      setpixel (xC + x, yC + y, imgIO, value);
      setpixel (xC - x, yC + y, imgIO, value);
      setpixel (xC + x, yC - y, imgIO, value);
      setpixel (xC - x, yC - y, imgIO, value);
      if (x < y) {
        setpixel (xC + y, yC + x, imgIO, value);
        setpixel (xC - y, yC + x, imgIO, value);
        setpixel (xC + y, yC - x, imgIO, value);
        setpixel (xC - y, yC - x, imgIO, value);
      }
    }
  }
}
/*
 * draw_filled_circle()
 *   DESCRIPTION:
 *     draw_circle draws a circle specified by a center point and radius.
 *     fills the circle with value
 *   ARGUMENTS:
 *     xC, yC(int) center point of circle
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for circle
 *   RETURN VALUE:
 *     none
 */
void
draw_filled_circle (int xC, int yC, int R, Image * imgIO, int value)
{
  int x = 0;
  int y = R;
  int u = 1;
  int v = 2 * R - 1;
  int E = 0;

  draw_line (xC, yC + R, xC, yC - R, imgIO, value);
  draw_line (xC + R, yC, xC - R, yC, imgIO, value);

  while (x < y) {
    x++;
    E += u;
    u += 2;
    if (v < 2 * E) {
      y--;
      E -= v;
      v -= 2;
    }
    if (x <= y) {
      draw_line (xC + x, yC + y, xC + x, yC - y, imgIO, value);
      draw_line (xC - x, yC + y, xC - x, yC - y, imgIO, value);
      if (x < y) {
        draw_line (xC + y, yC + x, xC - y, yC + x, imgIO, value);
        draw_line (xC + y, yC - x, xC - y, yC - x, imgIO, value);
      }
    }
  }
}
/*
 * NOTE:  The functions
 * gdImageCharUp
 * gdImageCharUp
 * gdImageString
 * gdImageStringUp
 * draw_ellipse
 * gdImageFill
 * gdImageFillToBorder
 * are taken from the gd library and used with permission
 * from T. Boutell
 * * */

/*
 * gdImageChar()
 *   DESCRIPTION:
 *     gdImageChar draws a character at the specified point using the specified font.
 *   ARGUMENTS:
 *     f(gdFontPtr) pointer to the font (see gd.h)
 *     x, y(int) point of origin for character
 *     c(int) character to draw
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for character
 *   RETURN VALUE:
 *     none
 */
void
gdImageChar (gdFontPtr f, int x, int y, int c, Image * imgIO, int value)
{
  int cx, cy;
  int px, py;
  int fline;
  cx = 0;
  cy = 0;
  if ((c < f->offset) || (c >= (f->offset + f->nchars))) {
    return;
  }
  fline = (c - f->offset) * f->h * f->w;
  for (py = y; (py < (y + f->h)); py++) {
    for (px = x; (px < (x + f->w)); px++) {
      if (f->data[fline + cy * f->w + cx]) {
        setpixel (px, py, imgIO, value);
      }
      cx++;
    }
    cx = 0;
    cy++;
  }
}

/*
 * gdImageCharUp()
 *   DESCRIPTION:
 *     gdImageCharUp draws a character at the specified point using the specified font
 *     rotated 90 degrees.
 *   ARGUMENTS:
 *     f(gdFontPtr) pointer to the font (see gd.h)
 *     x, y(int) point of origin for character
 *     c(int) character to draw
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for character
 *   RETURN VALUE:
 *     none
 */
void
gdImageCharUp (gdFontPtr f, int x, int y, char c, Image * imgIO, int value)
{
  int cx, cy;
  int px, py;
  int fline;
  cx = 0;
  cy = 0;
  if ((c < f->offset) || (c >= (f->offset + f->nchars))) {
    return;
  }
  fline = (c - f->offset) * f->h * f->w;
  for (py = y; (py > (y - f->w)); py--) {
    for (px = x; (px < (x + f->h)); px++) {
      if (f->data[fline + cy * f->w + cx]) {
        setpixel (px, py, imgIO, value);
      }
      cy++;
    }
    cy = 0;
    cx++;
  }
}

/*
 * gdImageString()
 *   DESCRIPTION:
 *     gdImageCharUp draws a string at the specified point using the specified font.
 *   ARGUMENTS:
 *     f(gdFontPtr) pointer to the font (see gd.h)
 *     x, y(int) point of origin for character
 *     c(char *) string to draw
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for character
 *   RETURN VALUE:
 *     none
 */
void
gdImageString (gdFontPtr f, int x, int y, char *s, Image * imgIO, int value)
{
  int i;
  int l;
  l = strlen (s);
  for (i = 0; (i < l); i++) {
    gdImageChar (f, x, y, s[i], imgIO, value);
    x += f->w;
  }
}

/*
 * gdImageStringUp()
 *   DESCRIPTION:
 *     gdImageStringUp draws a string at the specified point using the specified font
 *     rotated 90 degrees.
 *   ARGUMENTS:
 *     f(gdFontPtr) pointer to the font (see gd.h)
 *     x, y(int) point of origin for character
 *     c(char *) string to draw
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for character
 *   RETURN VALUE:
 *     none
 */
void
gdImageStringUp (gdFontPtr f, int x, int y, char *s, Image * imgIO, int value)
{
  int i;
  int l;
  l = strlen (s);
  for (i = 0; (i < l); i++) {
    gdImageCharUp (f, x, y, s[i], imgIO, value);
    y -= f->w;
  }
}

/*
 * draw_ellipse()
 *   DESCRIPTION:
 *     draw_ellipse draws an ellipse.
 *   ARGUMENTS:
 *     cx, cy(int) point of origin for ellipse
 *     w, h(int) width and height for ellipse
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to use for character
 *   RETURN VALUE:
 *     none
 */

void
draw_ellipse (int cx, int cy, int w, int h, Image * imgIO, int value)
{
  int i;
  int lx = 0, ly = 0;
  int w2, h2;
  w2 = w / 2;
  h2 = h / 2;
  for (i = 0; (i <= 360); i++) {
    int x, y;
    x = ((long) cost[i % 360] * (long) w2 / costScale) + cx;
    y = ((long) sint[i % 360] * (long) h2 / sintScale) + cy;
    if (i) {
      draw_line (lx, ly, x, y, imgIO, value);
    }
    lx = x;
    ly = y;
  }
}

/*
 * gdImageFillToBorder()
 *   DESCRIPTION:
 *     gdImageFillToBorder floods a portion of the image with the specified value,
 *     beginning at the specified point and stopping at the specified border value.
 *   ARGUMENTS:
 *     x, y(int) point to start fill
 *     border(int) value of border at which to stop.
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for fill
 *   RETURN VALUE:
 *     # pixels filled
 */
long
gdImageFillToBorder (int x, int y, int border, Image * imgIO, int value)
{
  int lastBorder;
  /* Seek left */
  int leftLimit, rightLimit;
  int i;
  long nfill = 0;
  leftLimit = (-1);
  if (border < 0) {
    /* Refuse to fill to a non-solid border */
    return (nfill);
  }
  for (i = x; (i >= 0); i--) {
    //if (gdImageGetPixel(imgIO, i, y) == border) {
    if (getpixel (i, y, imgIO) == border) {
      break;
    }
    //gdImageSetPixel(im, i, y, color);
    setpixel (i, y, imgIO, value);
    nfill++;
    leftLimit = i;
  }
  if (leftLimit == (-1)) {
    return (nfill);
  }
  /* Seek right */
  rightLimit = x;
  for (i = (x + 1); (i < imgIO->width); i++) {
    //if (gdImageGetPixel(im, i, y) == border) {
    if (getpixel (i, y, imgIO) == border) {
      break;
    }
    //gdImageSetPixel(im, i, y, color);
    setpixel (i, y, imgIO, value);
    nfill++;
    rightLimit = i;
  }
  /* Look at lines above and below and start paints */
  /* Above */
  if (y > 0) {
    lastBorder = 1;
    for (i = leftLimit; (i <= rightLimit); i++) {
      int c;
      //c = gdImageGetPixel(im, i, y-1);
      c = getpixel (i, y - 1, imgIO);
      if (lastBorder) {
        if ((c != border) && (c != value)) {
          nfill += gdImageFillToBorder (i, y - 1,
                                        border, imgIO, value);
          lastBorder = 0;
        }
      }
      else if ((c == border) || (c == value)) {
        lastBorder = 1;
      }
    }
  }
  /* Below */
  if (y < ((imgIO->height) - 1)) {
    lastBorder = 1;
    for (i = leftLimit; (i <= rightLimit); i++) {
      int c;
      //c = gdImageGetPixel(im, i, y+1);
      c = getpixel (i, y + 1, imgIO);
      if (lastBorder) {
        if ((c != border) && (c != value)) {
          nfill += gdImageFillToBorder (i, y + 1,
                                        border, imgIO, value);
          lastBorder = 0;
        }
      }
      else if ((c == border) || (c == value)) {
        lastBorder = 1;
      }
    }
  }
  return (nfill);
}

/*
 * gdImageFill()
 *   DESCRIPTION:
 *     gdImageFill floods a portion of the image with the specified color,
 *     beginning at the specified point and flooding the surrounding region
 *     of the same color as the starting point.
 *   ARGUMENTS:
 *     x, y(int) point to start fill
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for fill
 *   RETURN VALUE:
 *     # pixels filled
 */
long
gdImageFill (int x, int y, Image * imgIO, int value)
{
  int lastBorder;
  int old;
  int leftLimit, rightLimit;
  int i;
  int nfill = 0;
  old = getpixel (x, y, imgIO);
  //old = gdImageGetPixel(im, x, y);
  if (old == value) {
    /* Nothing to be done */
    return (nfill);
  }
  /* Seek left */
  leftLimit = (-1);
  for (i = x; (i >= 0); i--) {
    //if (gdImageGetPixel(im, i, y) != old) {
    if (getpixel (i, y, imgIO) != old) {
      break;
    }
    //gdImageSetPixel(im, i, y, color);
    setpixel (i, y, imgIO, value);
    nfill++;
    leftLimit = i;
  }
  if (leftLimit == (-1)) {
    return (nfill);
  }
  /* Seek right */
  rightLimit = x;
  for (i = (x + 1); (i < imgIO->width); i++) {
    //if (gdImageGetPixel(im, i, y) != old) {
    if (getpixel (i, y, imgIO) != old) {
      break;
    }
    //gdImageSetPixel(im, i, y, color);
    setpixel (i, y, imgIO, value);
    nfill++;
    rightLimit = i;
  }
  /* Look at lines above and below and start paints */
  /* Above */
  if (y > 0) {
    lastBorder = 1;
    for (i = leftLimit; (i <= rightLimit); i++) {
      int c;
      //c = gdImageGetPixel(im, i, y-1);
      c = getpixel (i, y - 1, imgIO);
      if (lastBorder) {
        if (c == old) {
          //gdImageFill(im, i, y-1, color);               
          nfill += gdImageFill (i, y - 1, imgIO, value);
          lastBorder = 0;
        }
      }
      else if (c != old) {
        lastBorder = 1;
      }
    }
  }
  /* Below */
  if (y < ((imgIO->height) - 1)) {
    lastBorder = 1;
    for (i = leftLimit; (i <= rightLimit); i++) {
      int c;
      //c = gdImageGetPixel(im, i, y+1);
      c = getpixel (i, y + 1, imgIO);
      if (lastBorder) {
        if (c == old) {
          //gdImageFill(im, i, y+1, color);               
          nfill += gdImageFill (i, y + 1, imgIO, value);
          lastBorder = 0;
        }
      }
      else if (c != old) {
        lastBorder = 1;
      }
    }
  }
  return (nfill);
}

/*
 * fill Voronoi diagram containing site (x, y)
 */
/*
 * fill_Voronoi()
 *   DESCRIPTION:
 *     fill Voronoi diagram containing site (x, y)
 *   ARGUMENTS:
 *     x, y(double) coordinate of Voronoi site
 *     n(int) coordination number
 *     mode(int) fill mode
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *   RETURN VALUE:
 *     none
 */


void
fill_Voronoi (double x, double y, int n, Image * imgIO, int mode)
{
  int ix, iy;

  int ind_5 = 3 * PIX_RANGE / 8;
  int ind_7 = 5 * PIX_RANGE / 8;
  int ind_4 = PIX_RANGE / 8;
  int ind_8 = 7 * PIX_RANGE / 8;
  ix = F_TO_INT (x);
  iy = F_TO_INT (y);
  ix += 3;
  iy += 3;
  if (mode == DISC_ONLY) {
    if (n == 5)
      gdImageFill (ix, iy, imgIO, ind_5);
    if (n == 7)
      gdImageFill (ix, iy, imgIO, ind_7);
    if (n == 4)
      gdImageFill (ix, iy, imgIO, ind_4);
    if (n == 8)
      gdImageFill (ix, iy, imgIO, ind_8);
  }
}

/*
 * draw_poly()
 *   DESCRIPTION:
 *     draw_poly draws a closed polygon with the specified value.
 *   ARGUMENTS:
 *     x, y(int *) list of (x,y) points for vertices
 *     n(int) number of (x,y) points
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for polygon border
 *   RETURN VALUE:
 *     none
 */
void
draw_poly (int *x, int *y, int n, Image * imgIO, int value)
{
  int X;
  int Y;
  int i;

  X = x[n - 1];
  Y = y[n - 1];
  for (i = 0; i < n; i++) {
    draw_line (X, Y, x[i], y[i], imgIO, value);
    X = x[i];
    Y = y[i];
  }
}

/*
 * draw_poly_ovl()
 *   DESCRIPTION:
 *     draw_poly_ovl draws features over an existing polygon depending on polytype.
 *   ARGUMENTS:
 *     x, y(int *) list of (x,y) points for vertices
 *     n(int) number of (X,Y) points
 *     xc, yc(int) centroid of polygon
 *     av_dirn(double) average direction of polygon
 *     polytype(int) type of polygon
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for drawing
 *   RETURN VALUE:
 *     none
 */
void
draw_poly_ovl (int *x, int *y, int n,
               int xc, int yc,
               double av_dirn, int polytype,
               Image * imgIO, int value)
{
  int radius = 4;

  int i;

  if (polytype == APOLY) {
    for (i = 0; i < n; i++)
      draw_filled_circle (*(x + i), *(y + i), radius, imgIO, value);
  }
  else {
    draw_poly (x, y, n, imgIO, value);

    draw_square (xc, yc, radius, imgIO, value);
    draw_normal (xc, yc, av_dirn, imgIO, value);
  }
}

/*
 * draw_polyfill()
 *   DESCRIPTION:
 *     draw_polyfill draws a closed polygon and fills it with the specified value.
 *   ARGUMENTS:
 *     x, y(int *) list of (x,y) points for vertices
 *     n(int) number of (x,y) points
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for polygon border and fill
 *   RETURN VALUE:
 *     number of pixels filled
 */
unsigned long
draw_polyfill (int *X, int *Y, int n, Image * imgIO, int value)
{
  int x;
  int y;
  int i;
  int ymin = 10000;
  int ymax = 0;
  int j;
  int ny;
  int i1;
  int xP;
  int yP;
  int xQ;
  int yQ;
  int temp;
  int dx;
  int dy;
  int m;
  int dyQ;
  int E;
  int xleft;
  int xright;

  typedef struct element {
    int xP;
    int yQ;
    int dx;
    int dy;
    int E;
    struct element *next;
  } element;
  element **table, *p, *start, *end, *p0, *q;
  unsigned long n_pixels;

  n_pixels = 0;
  x = X[n - 1];
  y = Y[n - 1];
  for (i = 0; i < n; i++) {
    draw_line (x, y, X[i], Y[i], imgIO, value);
    x = X[i];
    y = Y[i];
    if (y < ymin)
      ymin = y;
    if (y > ymax)
      ymax = y;
  }
  ny = ymax - ymin + 1;
  if ((table = (element **) calloc (ny, sizeof (element **))) == 0)
    ERRORMEM ("draw_polyfill")
      for (j = 0; j < ny; j++)
      table[j] = NULL;
  for (i = 0; i < n; i++) {
    i1 = i + 1;
    if (i1 == n)
      i1 = 0;
    xP = X[i];
    yP = Y[i];
    xQ = X[i1];
    yQ = Y[i1];
    if (yP == yQ)
      continue;
    if (yQ < yP) {
      temp = xP;
      xP = xQ;
      xQ = temp;
      temp = yP;
      yP = yQ;
      yQ = temp;
    }
    if ((p = (element *) calloc (1, sizeof (element))) == 0)
      ERRORMEM ("draw_polyfill")
        p->xP = xP;
    p->dx = xQ - xP;
    p->yQ = yQ;
    p->dy = yQ - yP;
    j = yP - ymin;
    p->next = table[j];
    table[j] = p;
  }
  if ((start = end = (element *) calloc (1, sizeof (element))) == 0)
    ERRORMEM ("draw_polyfill")
      for (j = 0; j < ny; j++) {
      y = ymin + j;
      p = start;
      while (p != end) {
        if (p->yQ == y) {
          if ((q = p->next) == end)
            end = p;
          else
            *p = *q;
          free (q);
        }
        else {
          if ((dx = p->dx) != 0) {
            x = p->xP;
            dy = p->dy;
            E = p->E;
            m = dx / dy;
            dyQ = 2 * dy;
            x += m;
            E += 2 * dx - m * dyQ;
            if (E > dy || E < -dy) {
              if (dx > 0) {
                x++;
                E -= dyQ;
              }
              else {
                x--;
                E += dyQ;
              }
            }
            p->xP = x;
            p->E = E;
          }
          p = p->next;
        }
      }
      p = table[j];
      while (p != NULL) {
        x = end->xP = p->xP;
        yQ = p->yQ;
        dx = p->dx;
        dy = p->dy;
        q = start;
        while (q->xP < x ||
               q->xP == x && q != end &&
               (long) q->dx * dy < (long) dx * q->dy)
          q = q->next;
        p0 = p;
        p = p->next;
        if (q == end)
          end = p0;
        else
          *p0 = *q;
        q->xP = x;
        q->yQ = yQ;
        q->dx = dx;
        q->dy = dy;
        q->E = 0;
        q->next = p0;
      }
      for (p = start; p != end; p = p->next) {
        xleft = p->xP + 1;
        p = p->next;
        xright = p->xP - 1;
        if (xleft <= xright) {
          draw_horline (xleft, xright, y, imgIO, value);
          /* calculate # pixels filled for area */
          n_pixels = n_pixels + xright - xleft + 2;
        }
      }
    }
  p = start;
  while (p != end) {
    p0 = p;
    p = p->next;
    free (p0);
  }
  free (start);
  free (table);
  return (n_pixels);
}

/*
 * draw_square()
 *   DESCRIPTION:
 *     draw_square draws a square with center at (x,y) and sides of size.
 *   ARGUMENTS:
 *     x, y(int) center point of square
 *     size(int) length of square sides
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for border
 *   RETURN VALUE:
 *     none
 */
void
draw_square (int x, int y, int size, Image * imgIO, int value)
{
  draw_horline (x - size / 2, x + size / 2, y - size / 2, imgIO, value);
  draw_horline (x - size / 2, x + size / 2, y + size / 2, imgIO, value);
  draw_verline (x - size / 2, y - size / 2, y + size / 2, imgIO, value);
  draw_verline (x + size / 2, y - size / 2, y + size / 2, imgIO, value);
}

/*
 * draw_rect()
 *   DESCRIPTION:
 *     draw_rect draws a rectangle specified by an upper left point and a lower right point.
 *   ARGUMENTS:
 *     x1, y1(int) upper left point
 *     x2, y2(int) lower right point
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for border
 *   RETURN VALUE:
 *     none
 */
void
draw_rect (int x1, int y1, int x2, int y2, Image * imgIO, int value)
{
  draw_horline (x1, x2, y1, imgIO, value);
  draw_horline (x1, x2, y2, imgIO, value);
  draw_verline (x1, y1, y2, imgIO, value);
  draw_verline (x2, y1, y2, imgIO, value);
}

/*
 * draw_cross()
 *   DESCRIPTION:
 *     draw_cross draws a cross with at the point (x,y).
 *   ARGUMENTS:
 *     x, y(int) center point of cross
 *     size(int) length in pixels for cross legs
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for border
 *   RETURN VALUE:
 *     none
 */
void
draw_cross (int x, int y, int size, Image * imgIO, int value)
{
  draw_line (x - size / 2, y - size / 2, x + size / 2, y + size / 2, imgIO, value);
  draw_line (x + size / 2, y - size / 2, x - size / 2, y + size / 2, imgIO, value);
}

/*
 * draw_up_triang()
 *   DESCRIPTION:
 *     draw_up_triang draws an up triangle at the point (x,y).
 *   ARGUMENTS:
 *     x, y(int) center point of triangle
 *     offset(int) size of triangle in pixels
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for border
 *   RETURN VALUE:
 *     none
 */
void
draw_up_triang (int x, int y, int offset, Image * imgIO, int value)
{
  int x_up, x_ll, x_lr, y_up, y_ll, y_lr;

  x_up = x;
  x_ll = x - (int) (offset * CS30);
  x_lr = x + (int) (offset * CS30);
  y_up = y - offset;
  y_ll = y_lr = y + (offset / 2);
  draw_line (x_up, y_up, x_ll, y_ll, imgIO, value);
  draw_line (x_ll, y_ll, x_lr, y_lr, imgIO, value);
  draw_line (x_lr, y_lr, x_up, y_up, imgIO, value);
}



/*
 * draw_dn_triang()
 *   DESCRIPTION:
 *     draw_up_triang draws a down triangle at the point (x,y).
 *   ARGUMENTS:
 *     x, y(int) center point of triangle
 *     offset(int) size of triangle in pixels
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for border
 *   RETURN VALUE:
 *     none
 */
void
draw_dn_triang (int x, int y, int offset, Image * imgIO, int value)
{
  int x_lw, x_ul, x_ur, y_lw, y_ul, y_ur;

  x_lw = x;
  x_ul = x - (int) (offset * CS30);
  x_ur = x + (int) (offset * CS30);
  y_lw = y + offset;
  y_ul = y_ur = y - (offset / 2);
  draw_line (x_lw, y_lw, x_ul, y_ul, imgIO, value);
  draw_line (x_ul, y_ul, x_ur, y_ur, imgIO, value);
  draw_line (x_ur, y_ur, x_lw, y_lw, imgIO, value);
}

/*
 * draw_horline()
 *   DESCRIPTION:
 *     draw_horline draws a horizontal line.
 *   ARGUMENTS:
 *     xmin, xmax(int) min and max values for line
 *     y(int) y value for line
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for line
 *   RETURN VALUE:
 *     none
 */
void
draw_horline (int xmin, int xmax, int y, Image * imgIO, int value)
{
  while (xmin <= xmax)
    setpixel (xmin++, y, imgIO, value);
}

/*
 * draw_verline()
 *   DESCRIPTION:
 *     draw_verline draws a vertical line.
 *   ARGUMENTS:
 *     x(int) x value for line
 *     ymin, ymax(int) ymin and ymax values for line
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for line
 *   RETURN VALUE:
 *     none
 */
void
draw_verline (int x, int ymin, int ymax, Image * imgIO, int value)
{
  while (ymin <= ymax)
    setpixel (x, ymin++, imgIO, value);
}

/*
 * draw_normal()
 *   DESCRIPTION:
 *     draw_normal draws the direction normal to the average direction of segments in the
 *     present group list (given by their average slope, m) at the specified point;
 *     the slope of the normal is given by: mn = -1.0/m;
 *   ARGUMENTS:
 *     x, y(int) point to draw normal
 *     m(double) average slope
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) value to use for line
 *   RETURN VALUE:
 *     none
 */
void
draw_normal (int x, int y, double m, Image * imgIO, int value)
{
  int offset = 10;
  double foffset;
  double fdelx, fdely;
  int x_mn, x_pl, y_mn, y_pl;
  int delx, dely;
  double lolim = 0.01, uplim = 200.0;

  if (fabs (m) < lolim) {       /* horizontal segm */
    x_mn = x_pl = x;
    y_mn = y - offset;
    y_pl = y + offset;
  }
  else if (fabs (m) > uplim) {  /* vertical segm */
    x_mn = x - offset;
    x_pl = x + offset;
    y_mn = y_pl = y;
  }
  else {
    foffset = (double) offset;
    fdely = foffset / sqrt (m * m + 1.0);
    fdelx = fabs (m) * fdely;
    if ((fdelx - (int) fdelx) < 0.5)
      delx = (int) fdelx;
    else
      delx = (int) fdelx + 1;
    if ((fdely - (int) fdely) < 0.5)
      dely = (int) fdely;
    else
      dely = (int) fdely + 1;

    y_mn = y - dely;
    y_pl = y + dely;
    if ((int) SIGN (m) > 0) {   /* normal slope: SIGN(mn) < 0 */
      x_mn = x + delx;
      x_pl = x - delx;
    }
    else {                      /* normal slope: SIGN(mn) > 0 */
      x_mn = x - delx;
      x_pl = x + delx;
    }
  }
  draw_line (x_mn, y_mn, x_pl, y_pl, imgIO, value);
}

/*
 * setpixel()
 *   DESCRIPTION:
 *     setpixel sets the pixel at (x,y) with the supplied value
 *   ARGUMENTS:
 *     x, y(int) pixel point
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to set
 *   RETURN VALUE:
 *     none
 */
void
setpixel (int x, int y, Image * imgIO, int value)
{
  unsigned char **image;        /* input/output image */

  image = imgIO->img;
  if (x < 0 || x >= imgIO->width || y < 0 || y >= imgIO->height) {
    return;
  }
  else {
    /*image is indexed by y first */
    image[y][x] = (unsigned char) value;
  }
}

/*
 * getpixel()
 *   DESCRIPTION:
 *     getpixel gets the pixel at (x,y)
 *   ARGUMENTS:
 *     x, y(int) pixel point
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *   RETURN VALUE:
 *     pixel value(unsigned char)
 */
unsigned char
getpixel (int x, int y, Image * imgIO)
{
  unsigned char **image;        /* input/output image */

  image = imgIO->img;
  if (x < 0 || x >= imgIO->width || y < 0 || y >= imgIO->height) {
    return (0);
  }
  else {
    /*image is indexed by y first */
    return (image[y][x]);
  }
}

/*
 * getrow()
 *   DESCRIPTION:
 *     getrow gets the row of pixels 
 *   ARGUMENTS:
 *     row_p(unsigned char *) pointer to row buffer
 *     row(int) which row to get
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *   RETURN VALUE:
 *     none
 */
void
getrow (unsigned char *row_p, int row, Image * imgIO)
{
  unsigned char **image;        /* input/output image */
  int ix;

  image = imgIO->img;
  for (ix = 0; ix < imgIO->width; ix++, row_p++) {
    *row_p = image[row][ix];
  }
}

/*
 * draw_border()
 *   DESCRIPTION:
 *     draw_border sets a border defined by the
 *     upper left corner (jmin, imin) and
 *     lower right corner (jmax, imax) with value
 *   ARGUMENTS:
 *     (jmin, imin), (jmax, imax) bounding box
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value(int) pixel value to set
 *   RETURN VALUE:
 *     none
 */
void
draw_border (int jmin, int imin, int jmax, int imax, Image * imgIO, int value)
{
  int ibmin, jbmin, ibmax, jbmax;
  int ir, jc;

  ibmin = 0;
  ibmax = imgIO->height;
  jbmin = 0;
  jbmax = imgIO->width;

  if (jmin < 0)
    jmin = 0;
  if (imin < 0)
    imin = 0;
  if (jmax >= imgIO->width)
    jmax = imgIO->width;
  if (imax >= imgIO->height)
    imax = imgIO->height;

  /* horizontal lines */
  for (ir = ibmin; ir < imin; ir++)
    draw_line (jbmin, ir, jbmax, ir, imgIO, value);
  for (ir = imax + 1; ir < ibmax; ir++)
    draw_line (jbmin, ir, jbmax, ir, imgIO, value);

  /* vertical lines */
  for (jc = jbmin; jc < jmin; jc++)
    draw_line (jc, ibmin, jc, ibmax, imgIO, value);
  for (jc = jmax + 1; jc < jbmax; jc++)
    draw_line (jc, ibmin, jc, ibmax, imgIO, value);
}

/*
 * zero_border()
 *   DESCRIPTION:
 *     zero_border sets a n-pixel wide border around the image to zero
 *   ARGUMENTS:
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     npix border width in pixels
 *   RETURN VALUE:
 *     none
 */
void
zero_border (Image * imgIO, int npix)
{
  int i;

  if (npix <= 0)
    npix = 1;
  for (i = 0; i < npix; i++) {
    draw_line (i, i, imgIO->width - (1 + i), i, imgIO, BLACK);
    draw_line (i, imgIO->height - (1 + i), imgIO->width - (1 + i), imgIO->height - (1 + i), imgIO, BLACK);
    draw_line (i, i, i, imgIO->height - (1 + i), imgIO, BLACK);
    draw_line (imgIO->width - (1 + i), i, imgIO->width - (1 + i), imgIO->height - (1 + i), imgIO, BLACK);
  }
}

/*
 * reset_image()
 *   DESCRIPTION:
 *     reset_image sets all the pixels in the entire image to value
 *   ARGUMENTS:
 *     imgIO(Image *) pointer to Image struct (see tiffimage.h)
 *     value grayscale value to use (0-255)
 *   RETURN VALUE:
 *     none
 */
void
reset_image (Image * imgIO, int value)
{
  int ix;
  int iy;

  for (ix = 0; ix < imgIO->width; ix++)
    for (iy = 0; iy < imgIO->height; iy++)
      setpixel (ix, iy, imgIO, value);

}
