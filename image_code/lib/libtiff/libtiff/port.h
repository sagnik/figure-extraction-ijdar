/*
 * Warning, this file was automatically created by the TIFF configure script
 * VERSION:	 v3.4033
 * DATE:	 Sun May 18 16:15:29 EDT 2008
 * TARGET:	 x86_64-unknown-linux
 * CCOMPILER:	 /usr/bin/gcc-4.1.2-14)
 */
#ifndef _PORT_
#define _PORT_ 1
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
#define HOST_FILLORDER FILLORDER_MSB2LSB
#define HOST_BIGENDIAN	0
#define HAVE_MMAP 1
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
typedef double dblparam_t;
#ifdef __STRICT_ANSI__
#define	INLINE	__inline__
#else
#define	INLINE	inline
#endif
#define GLOBALDATA(TYPE,NAME)	extern TYPE NAME
#ifdef __cplusplus
}
#endif
#endif
