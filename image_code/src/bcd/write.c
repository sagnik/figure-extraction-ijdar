
/*
 * This program is used with permission from I. Cox.
 * Please reference:
 * R. A. Boie, I. Cox, Proc. IEEE 1st Int. Conf. Computer Vision,
 * London, 1987, pp. 450-456.
 */
#include <stdio.h>
#include <math.h>
#if defined(WIN32)
#include <io.h>
#endif
#include "edge_finder.h"

extern struct image *my_image;

void
image_Write_int (char *name, int *pointer)
{
  short header[5];
  int fd;

  header[0] = 0x4513;
  header[1] = my_image->nx;
  header[2] = my_image->ny;
  header[3] = header[4] = 0;
  fd = creat (name, 0666);
  write (fd, (char *) header, 10);
  write (fd, (char *) pointer, my_image->nx * my_image->ny * 4);
  close (fd);
}

void
image_Write_char (char *name, unsigned char *pointer)
{
  short header[5];
  int fd;

  header[0] = 0x4500;
  header[1] = my_image->nx;
  header[2] = my_image->ny;
  header[3] = header[4] = 0;
  fd = creat (name, 0666);
  write (fd, (char *) header, 10);
  write (fd, (char *) pointer, my_image->nx * my_image->ny);
  close (fd);
}
