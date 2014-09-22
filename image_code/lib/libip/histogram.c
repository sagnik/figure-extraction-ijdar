/* 
 * histogram.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* HISTOGRAM: program calculates intensity histogram for input byte array
 * usage: histogram(array,n,hist)       */


#define INT(A) (((int)A)&0xff)  /* character to integer conversion */

int
histogram (array, n, hist)
     char *array;               /* input data array */

     int n,                     /* no. elements in input array */
      *hist;                    /* I/O histogram array */

{
  int i;

  for (i = 0; i < n; i++)
    hist[INT (*array++)]++;

  return (0);
}
