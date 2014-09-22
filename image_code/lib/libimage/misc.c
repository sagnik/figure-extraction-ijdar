/* 
 * misc.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1999 SOS Software
 */

/*
 * Miscellaneous routines
 */

#include "misc.h"

/*
 * last_bs finds the last backslash character '\' in in_str
 * It also converts in_str to lower case.
 *
 * This is useful for extracting out the program
 * name in DOS-based environments.
 *
 */

char *
last_bs (char *in_str)
{
  char *p;
  int i;

  i = 0;
  while (*(in_str + i) != '\0') {
    *(in_str + i) = tolower (*(in_str + i));
    i++;
  }
  /* get rid of .exe */
  if ((p = strrchr (in_str, '.')))
    *p = '\0';
  if ((p = strrchr (in_str, '\\')) == NULL)
    return in_str;
  else
    return ++p;
}

/*
 * readlin reads a line from stdin up to and
 * including \n.  It then replaces \n with \0
 * and returns the first character in buf.
 * NOTE: this uses fgets instead of gets()
 * because in some cases gets() can be unsecure.
 */

int
readlin (char *buf)
{
  char loc_buf[IN_BUF_LEN];

  fgets (loc_buf, IN_BUF_LEN, stdin);
  loc_buf[strlen (loc_buf) - 1] = '\0';
  strcpy (buf, loc_buf);
  return (buf[0]);
}
