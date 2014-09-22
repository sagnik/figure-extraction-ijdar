/* 
 * tiffimage.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1999 SOS Software
 */

#ifndef _TIFFIMAGE_H_
#define	_TIFFIMAGE_H_

typedef struct Image {
  unsigned char **img;
  unsigned char **imgR;         /*RED   for color image */
  unsigned char **imgG;         /*GREEN for color image */
  unsigned char **imgB;         /*BLUE  for color image */
  long height, width, bps, spp;
} Image;


/*
 *   Function prototypes     for tiffimage.c
 *  defined in tiffimage.c
 */
Image *ImageAlloc (long, long, long);
void ImageCopy (Image *, int, int, int, int, Image *, int, int);
void ImageFree (Image *);
long ImageGetWidth (Image *);
long ImageGetHeight (Image *);
long ImageGetDepth (Image *);
unsigned char **ImageGetPtr (Image *);
Image *ImageIn (char *);
int ImageIsGray (Image *);
int ImageOut (char *, Image *);
void ImageSetBWOutput (Image *);
void ImageSetGrayOutput (Image *);
void ImageSetHeight (Image *, long);
void ImageSetWidth (Image *, long);

#endif /* _TIFFIMAGE_H_ */
