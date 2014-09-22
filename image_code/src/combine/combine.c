/* 
 * combine.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * COMBINE (Image addition)
 *
 *  Adds two input images and places the resulting
 *  image in the output file
 *  Image addition is clipped at 255 by default
 */

#include "combine.h"

#define  NOLOOP		0
#define INDEX_SCALE 255

#define	 ON		1
#define	 OFF		0

/*
 * global variables
 */
extern char *optarg;
extern int optind, opterr;
extern short tiffInput;         /* flag=0 if no ImageIn to set tags; else =1 */

int BINARIZE = OFF;

/*
 * usage of routine
 */
void
usage (char *progname)
{
  progname = last_bs (progname);
  printf ("USAGE: %s in1img in2img outimg [-c clip][-L]\n", progname);
  printf ("\n%s adds two images and writes the resulting\n", progname);
  printf ("image to the specified output file.\n\n");
  printf ("ARGUMENTS:\n");
  printf ("   in1img: first input image filename (TIF)\n");
  printf ("   in2img: second input image filename (TIF)\n");
  printf ("   outimg: output image filename (TIF)\n\n");
  printf ("OPTIONS:\n");
  printf ("  -c clip: clipping factor for output image 0-255(default=%d)\n", INDEX_SCALE);
  printf ("       -L: print Software License for this module\n");
  exit (1);
}

void
add_image (Image * imgIn1, Image * imgIn2, Image * imgOut, unsigned char clip_factor)
{
  int ix, iy;
  int max_x, max_y;
  unsigned long pixelOut;

  max_y = ImageGetHeight (imgIn1);
  max_x = ImageGetWidth (imgIn1);
  for (ix = 0; ix < max_x; ix++)
    for (iy = 0; iy < max_y; iy++) {
      pixelOut = getpixel (ix, iy, imgIn1) + getpixel (ix, iy, imgIn2);
      setpixel (ix, iy, imgOut, (pixelOut > clip_factor ? clip_factor : (unsigned char) pixelOut));
    }
}

void
main (int argc, char *argv[])
{
  Image *imgIn1;
  Image *imgIn2;
  Image *imgOut;

  int i_arg;
  int clip_factor = INDEX_SCALE;
  int binarize = 0;
  int outheight;
  int outwidth;

/*
 * cmd line options
 */
  static char *optstring = "c:bL";


/*
 * parse command line
 */
  optind = 4;                   /* set getopt to point to the 4th arg */
  opterr = ON;                  /* give error messages */


  if (argc < 4)
    usage (argv[0]);

  while ((i_arg = getopt (argc, argv, optstring)) != EOF) {
    switch (i_arg) {
    case 'b':
      printf ("\n...option %c: generate binary output\n", i_arg);
      binarize = 1;
      break;
    case 'c':
      if ((clip_factor = atoi (optarg)) > 255) {
        printf ("Clipping factor must be <= 255\n");
        printf ("Defaulting to clipping factor = %d\n", INDEX_SCALE);
        clip_factor = INDEX_SCALE;
      }
      break;
    case 'L':
      print_sos_lic ();
      exit (0);
    default:
      printf ("\ngetopt: unknown condition encountered\n");
      exit (1);
      break;
    }
  }

/*
 * Read input image
 */
  imgIn1 = ImageIn (argv[1]);

  if (imgIn1->bps == 8 && imgIn1->spp == 3) {
    printf ("Got RGB image!!!\nInput image must be Grayscale or B&W!!\n");
    exit (1);
  }

/*
 * Read reference image
 */
  imgIn2 = ImageIn (argv[2]);

  if (imgIn2->bps == 8 && imgIn2->spp == 3) {
    printf ("Got RGB image!!!\nInput image must be Grayscale or B&W!!\n");
    exit (1);
  }

  if (ImageGetHeight (imgIn1) != ImageGetHeight (imgIn2) ||
      ImageGetWidth (imgIn1) != ImageGetWidth (imgIn2)) {
    printf ("Input and Reference images have different sizes\n");
    printf ("Minimum size will be chosen for output image\n");
  }
  outheight = (ImageGetHeight (imgIn1) > ImageGetHeight (imgIn2)) ? ImageGetHeight (imgIn2) : ImageGetHeight (imgIn1);
  outwidth = (ImageGetWidth (imgIn1) > ImageGetWidth (imgIn2)) ? ImageGetWidth (imgIn2) : ImageGetWidth (imgIn1);

/*
 * Allocate memory for output image
 */
  imgOut = ImageAlloc ((long) outheight, (long) outwidth, (long) BPS);

/*
 * perform background illumination correction 
 */
  add_image (imgIn1, imgIn2, imgOut, (unsigned char) clip_factor);

/* 
 * reset tiffInput so that we write a grayscale file (i.e tags are not copied)
 */
  tiffInput = 0;

/*
 * Write the output image
 */
  ImageOut (argv[3], imgOut);
}
