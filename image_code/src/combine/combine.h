/* 
 * combine.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */
#ifndef _COMBINE_H_
#define	_COMBINE_H_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#include "ip.h"

/*
 * Function prototypes
 */
extern void main (int, char **);
extern void usage (char *);
extern void add_image (Image *, Image *, Image *, unsigned char);

#endif
/*_COMBINE_H_ */
