/* 
 * ip.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * General purpose functions contained here
 */

#include "ip.h"

/*
 * exitmess()
 *   DESCRIPTION:
 *     exitmess exits the current program with the supplied status code
 *   ARGUMENTS:
 *     prompt(char *) message to print on STDOUT
 *     status(int) exit code for current program
 *   RETURN VALUE:
 *     none
 */

void
exitmess (char *prompt, int status)
{
  printf ("%s\n", prompt);
  exit (status);
}
