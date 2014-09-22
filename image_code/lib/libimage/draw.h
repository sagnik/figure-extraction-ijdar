/* 
 * draw.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1999 SOS Software
 */

#ifndef _DRAW_H_
#define	_DRAW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tiffimage.h"
#include "gd.h"
#include "misc.h"

/*
 *   Function prototypes     for Draw.c
 */
void setpixel (int x, int y, Image * imgIO, int value);
unsigned char getpixel (int x, int y, Image * imgIO);
void getrow (unsigned char *row_p, int row, Image * imgIO);
void draw_border (int jmin, int imin, int jmax, int imax, Image * imgIO, int value);
void zero_border (Image * imgIO, int pix);
void reset_image (Image * imgIO, int value);
void draw_line (int x1, int y1, int x2, int y2, Image * imgIO, int value);
void draw_circle (int xC, int yC, int R, Image * imgIO, int value);
void draw_filled_circle (int xC, int yC, int R, Image * imgIO, int value);
void gdImageChar (gdFontPtr f, int x, int y, int c, Image * imgIO, int value);
void gdImageCharUp (gdFontPtr f, int x, int y, char c, Image * imgIO, int value);
void gdImageString (gdFontPtr f, int x, int y, char *s, Image * imgIO, int value);
void gdImageStringUp (gdFontPtr f, int x, int y, char *s, Image * imgIO, int value);
void draw_ellipse (int cx, int cy, int w, int h, Image * imgIO, int value);
void fill_Voronoi (double x, double y, int n, Image * imgIO, int mode);
long gdImageFill (int x, int y, Image * imgIO, int value);
long gdImageFillToBorder (int x, int y, int border, Image * imgIO, int value);
void draw_cross (int x, int y, int size, Image * imgIO, int value);
void draw_poly (int *X, int *Y, int n, Image * imgIO, int value);
unsigned long draw_polyfill (int *X, int *Y, int n, Image * imgIO, int value);
void draw_square (int x, int y, int size, Image * imgIO, int value);
void draw_rect (int x1, int y1, int x2, int y2, Image * imgIO, int value);
void draw_up_triang (int x, int y, int offset, Image * imgIO, int value);
void draw_dn_triang (int x, int y, int offset, Image * imgIO, int value);
void draw_horline (int xmin, int xmax, int y, Image * imgIO, int value);
void draw_verline (int x, int ymin, int ymax, Image * imgIO, int value);
void draw_poly_ovl (int *x, int *y, int n,
                    int xc, int yc,
                    double av_dirn, int polytype,
                    Image * imgIO, int value);
void draw_normal (int x, int y, double m, Image * imgIO, int value);

/*
 *   Some convenient definitions
 */
#define PIX_RANGE       256
#define WHITE		255
#define BLACK		0
#define GRAY		128
#define	APOLY		0
#define	HULLPOLY	1

#define DISC_ONLY       1       /* label modes for fill_Voronoi */
#define HEXA_ONLY       2

#define HEIGHT		512             /*default y allocation of graphics buffer */
#define WIDTH		512              /*default x allocation of graphics buffer */
#define BPS			8                 /*default bits per sample for graphics buffer */
        /*(set=1 for binary image) */

#endif /* _DRAW_H_ */
