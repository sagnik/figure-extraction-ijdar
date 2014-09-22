/* 
 * getopt.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1999 SOS Software
 */

/*
 * GETOPT
 *
 * parse command line
 *
 * external variables:
 *         char *optarg      a pointer that is initialized to NULL on
 *                           entry to the function. If a command-line
 *                           option has an argument, optarg points to
 *                           the argument.
 *
 *         char *index       a pointer to the next character in the
 *                           command line.
 *
 *         int optind        an index into the argument vector
 *
 *         int opterr        a flag that, if set to 0, turns off the
 *                           display of a predefined error message
 *                           on stderr. If nonzero, the message is
 *                           displayed when an error occurs.
 *
 * in addition, the function uses the following variables in its 
 * argument list:
 *
 *   Argument list:    int argc          the argument count from the
 *                                       command line
 *
 *                     char *argv[]      the command-line vector
 *                     char *optstring   a list of valid command-line
 *                                       options
 *
 *   Return value:     int               the command-line option or EOF
 *                                       on error or when parsing is
 *                                       finished.
 *
 * (ref: J. Purdum, "C Programmer's Toolkit", chapt.5, listing 8)
 *
 */
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "getopt.h"

char *optarg;
static char *index = NULL;
int optind, opterr;

static void
get_next_index (void)
{
  ++optind;
  index = NULL;
}


int
getopt (int argc, char *argv[], char *optstring)
{
  int fd, i;
  char *ptr = NULL;

  optarg = NULL;
  if (!optind) {                /* If not set to 1, set it to 1  */
    index = (char *) NULL;
    optind++;
  }

  fd = fileno (stderr);
  while (argv[optind]) {        /* Used for the write() function */
    if (!index) {               /* If no index string yet   */
      index = argv[optind];
      if (!index || *index != '-') {  /*no index and  */
        index = NULL;           /* no dash: done */
        return (EOF);
      }
      if (*(++index) == '-') {  /* Double dash? */
        get_next_index ();      /* Don't parse any more */
        return EOF;
      }
      if (!*(index))            /* Ready for next iteration */
        get_next_index ();

      continue;
    }

    i = (int) *index++;         /* Look at next character */
    if (i != ':') {             /* No command-line argument */
      ptr = strchr (optstring, i);  /* Is i in options list? */
      if (ptr && *(ptr + 1) == ':') {  /* Yes, plus argument  */
        if (*index)             /* If non-NULL index...  */
          optarg = index;       /* set optarg to pt to it */
        else                    /* else get the next argv */
          optarg = argv[++optind];

        get_next_index ();

        if (!optarg) {          /* Colon but no argument */
          i = EOF;
          if (opterr) {
            write (fd, argv[0], strlen (argv[0]));
            write (fd, ": option requires argument ", 27);
            write (fd, &i, sizeof (char));
            write (fd, "\r\n", 2);
            exit (1);
          }
        }
        return (i);             /* Must be an error */
      }
    }

    if (!(*index))              /* If a null character */
      get_next_index ();

    if (ptr)                    /* Return the command option */
      return (i);

    else {
      if (opterr) {             /* Not in the list */
        write (fd, argv[0], strlen (argv[0]));
        write (fd, ": illegal option ", 17);
        write (fd, &i, sizeof (char));
        write (fd, "\r\n", 2);
        exit (1);
      }
      return ('?');
    }
  }
  return EOF;                   /* None left */
}
