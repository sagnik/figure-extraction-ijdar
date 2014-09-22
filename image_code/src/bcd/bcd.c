/*
 * This program is used with permission from I. Cox.
 * Please reference:
 * R. A. Boie, I. Cox, Proc. IEEE 1st Int. Conf. Computer Vision,
 * London, 1987, pp. 450-456.
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#if defined(WIN32)
#include <io.h>
#endif
#include "edge_finder.h"
#include "ip.h"

#define UBYTE_HD 0x4500

#define	ON		1
#define	OFF		0

extern struct image *my_image;
extern short tiffInput;         /* flag=0 if no ImageIn to set tags; else =1 */
extern char *optarg;
extern int optind, opterr;

/*
 * usage of routine
 */
void
usage (char *progname)
{
  progname = last_bs (progname);
  printf ("USAGE: %s inimg outimg sigma [-h][-t][-T thld][-L]\n", progname);
  printf ("\n%s detects and marks contours of regions in a grayscale image\n", progname);
  printf ("by invoking Boie-Cox algorithm\n\n");
  printf ("ARGUMENTS:\n");
  printf ("    inimg: input image filename (TIF)\n");
  printf ("   outimg: output image filename (TIF)\n");
  printf ("    sigma: width of Gaussian filter (float)\n\n");
  printf ("OPTIONS:\n");
  printf ("     -h : do not apply hysteresis\n");
  printf ("     -t : do not thin image\n");
  printf ("-T thld : threshold value (int)\n");
  printf ("     -L : print Software License for this module\n");
  exit (1);
}

void
main (int argc, char *argv[])
{
  int nx, ny;
  static unsigned char *pic;
  float sigma;
  int threshold = 1;
  int hysteresis = 1;
  int thinning = 1;
  int i, j;

  unsigned char *edge_map;
  unsigned char *image_find_edges (float, int *);
  unsigned char *image_hysteresis ();
  unsigned char *image_thin ();
  Image *imgIn;
  char *input_file, *output_file;
  unsigned char **imgPtr;
  int i_arg;

/* 
 * cmd line options:
 */
  static char *optstring = "htT:L";

/*
 * parse command line
 */
  optind = 4;
  opterr = ON;                  /* give error messages */

  if (argc < 4)
    usage (argv[0]);

  while ((i_arg = getopt (argc, argv, optstring)) != EOF) {
    switch (i_arg) {
    case 'h':
      hysteresis = 0;
      break;
    case 't':
      thinning = 0;
      break;
    case 'T':
      threshold = atoi (optarg);
      break;
    case 'L':
      print_bcd_lic ();
      exit (0);
    default:
      usage (argv[0]);
      break;
    }
  }

  input_file = argv[1];
  output_file = argv[2];
  sigma = (float) atof (argv[3]);
/*
 * read input image
 */
  imgIn = ImageIn (input_file);
  if (imgIn->bps == 8 && imgIn->spp == 3) {
    printf ("Got RGB image!!!\nInput image must be Grayscale or B&W!!\n");
    exit (1);
  }


  imgPtr = ImageGetPtr (imgIn);
  nx = imgIn->width;
  ny = imgIn->height;
/*
 * now read in image
 */
  fprintf (stderr, "\nimage size is %d x %d\n", nx, ny);

  if ((pic = (unsigned char *) malloc (nx * ny * sizeof (unsigned char))) == 0) {
    fprintf (stderr,
             "%s: ERROR cannot allocate image array\n", argv[0]);
    exit (1);
  }

  for (i = 0; i < ny; i++)
    for (j = 0; j < nx; j++)
      *(pic + (i * nx + j)) = imgPtr[i][j];

  image_init (pic, nx, ny);

  edge_map = image_find_edges (sigma, &threshold);
  if (hysteresis) {
    fprintf (stderr, "\napplying hysteresis\n");
    edge_map = image_hysteresis (threshold / 3);
  }
  if (thinning) {
    fprintf (stderr, "\nthinning image\n");
    edge_map = image_thin ();
  }
  for (i = 0; i < ny; i++)
    for (j = 0; j < nx; j++)
      imgPtr[i][j] = *(edge_map + (i * nx + j));
  ImageOut (output_file, imgIn);
  image_cleanup ();
}
