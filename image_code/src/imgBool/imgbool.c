/* 
 * imgbool.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* IMGBOOL:     program combines two images by boolean operation of
 *            AND, OR, or XOR
 *          usage: imgbool in1img in2img outimg [-o OPERAND] [-x X] [-y Y] [-L]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tiffimage.h>          /* picfile info on images */
#include <images.h>             /* for sun images */
extern void print_sos_lic ();

int usage (short);
int input (int, char **, char *, long *, long *);

main (argc, argv)
     int argc;
     char *argv[];
{
  register int x1, y1, x2, y2;  /* image incrementors */
  register long temp;
  Image *imgI1, *imgI2;         /* 2 input images, first is also output */
  unsigned char **image1,       /* first and second input image */
  **image2;                     /* first is also output image */
  struct point imgSize1, imgSize2;  /* image dimensions */
  char oper;                    /* operand */
  long x0, y0;                  /* x,y offset of second image in first */
  long endX, endY;              /* end coord.s of image2 in image1 */

/* read user parameter values */
  if ((input (argc, argv, &oper, &x0, &y0)) < 0)
    return (-1);

/* open images */
  imgI1 = ImageIn (argv[1]);
  if (imgI1->bps == 8 && imgI1->spp == 3) {
    printf ("Got RGB image!!!\nInput image must be Grayscale or B&W!!\n");
    exit (1);
  }
  image1 = imgI1->img;
  imgSize1.y = ImageGetHeight (imgI1);
  imgSize1.x = ImageGetWidth (imgI1);

  imgI2 = ImageIn (argv[2]);
  if (imgI2->bps == 8 && imgI2->spp == 3) {
    printf ("Got RGB image!!!\nInput image must be Grayscale or B&W!!\n");
    exit (1);
  }
  image2 = imgI2->img;
  imgSize2.y = ImageGetHeight (imgI2);
  imgSize2.x = ImageGetWidth (imgI2);

  printf ("input/output image size is %dx%d\n", imgSize1.x, imgSize1.y);
  if (imgSize1.x != imgSize2.x || imgSize1.y != imgSize2.y)
    printf ("(second image size is %dx%d)\n", imgSize2.x, imgSize2.y);

/* perform boolean operation */

  endX = (imgSize2.x + x0 > imgSize1.x) ? imgSize1.x : imgSize2.x + x0;
  endY = (imgSize2.y + y0 > imgSize1.y) ? imgSize1.y : imgSize2.y + y0;

  for (y1 = y0, y2 = 0; y1 < endY; y1++, y2++) {
    for (x1 = x0, x2 = 0; x1 < endX; x1++, x2++) {
      switch (oper) {
      case 'A':
        temp = (image1[y1][x1] != 0 && image2[y2][x2] != 0) ? 255 : 0;
        break;
      case 'O':
        temp = (image1[y1][x1] != 0 || image2[y2][x2] != 0) ? 255 : 0;
        break;
      case 'X':
        temp = ((image1[y1][x1] != 0 && image2[y2][x2] == 0)
                || (image1[y1][x1] == 0 && image2[y2][x2] != 0)) ? 255 : 0;
        break;
      }
      image1[y1][x1] = (unsigned char) temp;
    }
  }

/* write output image */
  ImageOut (argv[3], imgI1);
  return (0);
}


/* USAGE:       function gives instructions on usage of program
 *                    usage: usage (flag)
 *              When flag is 1, the long message is given, 0 gives short.
 */

int
usage (flag)
     short flag;                /* flag =1 for long message; =0 for short message */
{

/* print short usage message or long */
  printf ("usage: imgbool in1img in2img outimg [-o OPERAND] [-x X] [-y Y] [-L]\n");
  if (flag == 0)
    return (-1);

  printf ("\nimgbool performs boolean combination between two\n");
  printf ("images: OR, AND, or XOR\n\n");
  printf ("ARGUMENTS:\n");
  printf ("   in1img: first input image filename (TIF)\n");
  printf ("   in2img: second input image filename (TIF)\n");
  printf ("   outimg: output image filename (TIF)\n\n");
  printf ("OPTIONS:\n");
  printf ("       -o: OPERAND <O,A,X> for OR, AND, or XOR.\n");
  printf ("           Default is OR (O).\n");
  printf ("     -x X: X-offset location of second image in first.\n");
  printf ("     -y Y: Y-offset location of second image in first.\n");
  printf ("           Default = (0,0).\n");
  printf ("           Note that for images of different sizes, the resultant image\n");
  printf ("           will be the size of the first specified image.\n");
  printf ("       -L: print Software License for this module\n");

  return (-1);
}


/* INPUT:       function reads input parameters
 *                  usage: input (argc, argv, &oper, &x0, &y0)
 */

#define USAGE_EXIT(VALUE) {usage (VALUE); return (-1);}

int
input (argc, argv, oper, x0, y0)
     int argc;
     char *argv[];
     char *oper;                /* operand */
     long *x0, *y0;             /* offset of second image in first */
{
  long n;

  if (argc == 1)
    USAGE_EXIT (1);
  if (argc == 2 || argc == 3)
    USAGE_EXIT (0);

  *oper = 'O';
  *x0 = *y0 = 0;

  for (n = 4; n < argc; n++) {
    if (strcmp (argv[n], "-o") == 0) {
      if (++n == argc || argv[n][0] == '-')
        USAGE_EXIT (0);
      *oper = *(argv[n]);
    }
    else if (strcmp (argv[n], "-x") == 0) {
      if (++n == argc || argv[n][0] == '-')
        USAGE_EXIT (0);
      *x0 = atol (argv[n]);
    }
    else if (strcmp (argv[n], "-y") == 0) {
      if (++n == argc || argv[n][0] == '-')
        USAGE_EXIT (0);
      *y0 = atol (argv[n]);
    }
    else if (strcmp (argv[n], "-L") == 0) {
      print_sos_lic ();
      exit (0);
    }
    else
      USAGE_EXIT (0);
  }

  if (*oper != 'O' && *oper != 'A' && *oper != 'X')
    USAGE_EXIT (0);

  return (0);
}
