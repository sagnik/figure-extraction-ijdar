/* 
 * misc.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1999 SOS Software
 */
#ifndef _MISC_H_
#define	_MISC_H_

#include <stdio.h>
#include <string.h>
#if defined(WIN32)
#include <ctype.h>
#endif

#define IN_BUF_LEN 512

/* Function definitions for misc.c */
extern char *last_bs (char *);
extern int readlin (char *buf);

#endif /* _MISC_H_ */
