/* 
 * license.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

#include <stdio.h>
#define SOS_LIC "\n\
This program is free software; you can redistribute it and/or\n\
modify it under the terms of the GNU General Public License\n\
as published by the Free Software Foundation; either version 2\n\
of the License, or (at your option) any later version.\n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program; if not, write to the Free Software\n\
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\n"

#define BCD_LIC "\
No end-user licensing for this program is needed.  This program\n\
is used with permission from I. Cox.  Please reference:\n\
R. A. Boie, I. Cox, Proc. IEEE 1st Int. Conf. Computer Vision,\n\
London, 1987, pp. 450-456.\n"


void
print_sos_lic ()
{
  printf (SOS_LIC);
}

void
print_bcd_lic ()
{
  printf (BCD_LIC);
}
