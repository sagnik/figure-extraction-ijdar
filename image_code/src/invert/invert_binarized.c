#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "images.h"
#include "tiffimage.h"          /* tiff file format info */
/* extern void print_sos_lic (); */
unsigned char **image;
int main(argc, argv)
	int argc;
	char *argv[];
{
Image *imgIO;
imgIO = ImageIn (argv[1]);
image = imgIO->img;
long width = ImageGetWidth(imgIO);
long height = ImageGetHeight(imgIO);
long x,y;
for (y = 0; y < height; y++)
   for (x = 0; x < width; x++)
     image[y][x] = 255 - image[y][x];
 ImageOut (argv[2], imgIO);
  free(imgIO->img[0]);
  free(imgIO);
 return(0);
}




