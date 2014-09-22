/* 
 * pccfctde.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* PCCFCTDE:    functions for PCC decoding
 *            (encoding functions in PCCFCT; and functions common
 *              to both encoding and decoding programs in PCCFCT2)
 *      FUNCTIONS:
 *              PCCREAD, PCCDECODES, PCCDECODE, PCCDETRACK, PCC2XY
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <images.h>             /* images file information */
#include "pcc2.h"               /* header file for PCC programs */

int deCode[NDECODE];            /* decode table */
extern unsigned char *fcCode;   /* code storage */
extern long nByteCode;          /* no. bytes in storage */


/* PCCREAD:     function reads PCC code from file
 *                usage: pccread (filename, &pcc, &nCode, &widthI, &heightI)
 *
 */

#define TYPE_STRING 9           /* string for PCC image type */

pccread (filename, pcc, nCode, widthI, heightI)
     char *filename;
     unsigned char **pcc;       /* PCC code */
     long *nCode;               /* no. bytes of code */
     long *widthI, *heightI;    /* image size */
{
  FILE *fpIn;
  unsigned char type[TYPE_STRING];
  char string1[20], string2[20];
  static char *typePCC = "TYPE=PCC";
  long w, h;

/* open input PCC file */
  if ((fpIn = fopen (filename, "rb")) == NULL) {
    printf ("PCCREAD: cannot open file %s\n", filename);
    return (-1);
  }

/* read PCC file header */
  fscanf (fpIn, "%8s", &type);
  //fscanf (fpIn, "%5s %5s %ld %ld", string1, string2, widthI, heightI);
  fscanf (fpIn, "%5s %5s %ld %ld", string1, string2, &w, &h);
  *widthI = w;
  *heightI = h;
  fscanf (fpIn, "%3s %7s %ld\n", string1, string2, nCode);

  if ((strcmp (type, typePCC)) != 0) {
    printf ("PCCREAD: input file is not in PCC format.", 1);
    return (-2);
  }

  if (((*pcc) = (unsigned char *) malloc (*nCode)) == NULL) {
    printf ("MALLOC: not enough memory -- sorry", 1);
    return (-3);
  }
  fread ((*pcc), sizeof (unsigned char), *nCode, fpIn);

  fclose (fpIn);
  return (0);
}



/* PCCDECODES:  function constructs table of PCC decodes
 *            corresponding to sequences of 0, 1, 2, or 3
 *              direction vectors and features endpoint, bifurcation,
 *              and cross
 *                      usage: pccdecodes ()
 *                              extern int decode;
 *
 */

int deCode[NDECODE];            /* decode table */

pccdecodes ()
{
/* CODE TO PACKED DIRECTION SEGMENTS TABLE */

  deCode[1] = 0000;
  deCode[2] = 0100;
  deCode[3] = 0200;
  deCode[4] = 0600;
  deCode[5] = 0700;
  deCode[6] = 0010;
  deCode[7] = 0110;
  deCode[8] = 0210;
  deCode[9] = 0310;
  deCode[10] = 0710;
  deCode[11] = 0020;
  deCode[12] = 0120;
  deCode[13] = 0220;
  deCode[14] = 0320;
  deCode[15] = 0060;
  deCode[16] = 0560;
  deCode[17] = 0660;
  deCode[18] = 0760;
  deCode[19] = 0070;
  deCode[20] = 0170;
  deCode[21] = 0570;
  deCode[22] = 0670;
  deCode[23] = 0770;
  deCode[24] = 0001;
  deCode[25] = 0201;
  deCode[26] = 0101;
  deCode[27] = 0601;
  deCode[28] = 0701;
  deCode[29] = 0011;
  deCode[30] = 0111;
  deCode[31] = 0211;
  deCode[32] = 0311;
  deCode[33] = 0711;
  deCode[34] = 0021;
  deCode[35] = 0121;
  deCode[36] = 0221;
  deCode[37] = 0321;
  deCode[38] = 0421;
  deCode[39] = 0131;
  deCode[40] = 0231;
  deCode[41] = 0331;
  deCode[42] = 0431;
  deCode[43] = 0531;
  deCode[44] = 0071;
  deCode[45] = 0171;
  deCode[46] = 0571;
  deCode[47] = 0671;
  deCode[48] = 0771;
  deCode[49] = 0002;
  deCode[50] = 0102;
  deCode[51] = 0202;
  deCode[52] = 0702;
  deCode[53] = 0012;
  deCode[54] = 0112;
  deCode[55] = 0212;
  deCode[56] = 0312;
  deCode[57] = 0712;
  deCode[58] = 0022;
  deCode[59] = 0122;
  deCode[60] = 0222;
  deCode[61] = 0322;
  deCode[62] = 0422;
  deCode[63] = 0132;
  deCode[64] = 0232;
  deCode[65] = 0332;
  deCode[66] = 0432;
  deCode[67] = 0532;
  deCode[68] = 0242;
  deCode[69] = 0342;
  deCode[70] = 0442;
  deCode[71] = 0542;
  deCode[72] = 0013;
  deCode[73] = 0113;
  deCode[74] = 0213;
  deCode[75] = 0313;
  deCode[76] = 0713;
  deCode[77] = 0023;
  deCode[78] = 0123;
  deCode[79] = 0223;
  deCode[80] = 0323;
  deCode[81] = 0423;
  deCode[82] = 0133;
  deCode[83] = 0233;
  deCode[84] = 0333;
  deCode[85] = 0433;
  deCode[86] = 0533;
  deCode[87] = 0243;
  deCode[88] = 0343;
  deCode[89] = 0443;
  deCode[90] = 0543;
  deCode[91] = 0643;
  deCode[92] = 0353;
  deCode[93] = 0453;
  deCode[94] = 0553;
  deCode[95] = 0653;
  deCode[96] = 0753;
  deCode[97] = 0124;
  deCode[98] = 0224;
  deCode[99] = 0324;
  deCode[100] = 0424;
  deCode[101] = 0134;
  deCode[102] = 0234;
  deCode[103] = 0334;
  deCode[104] = 0434;
  deCode[105] = 0534;
  deCode[106] = 0244;
  deCode[107] = 0344;
  deCode[108] = 0444;
  deCode[109] = 0544;
  deCode[110] = 0644;
  deCode[111] = 0354;
  deCode[112] = 0454;
  deCode[113] = 0554;
  deCode[114] = 0654;
  deCode[115] = 0754;
  deCode[116] = 0464;
  deCode[117] = 0564;
  deCode[118] = 0664;
  deCode[119] = 0764;
  deCode[120] = 0135;
  deCode[121] = 0235;
  deCode[122] = 0335;
  deCode[123] = 0435;
  deCode[124] = 0535;
  deCode[125] = 0245;
  deCode[126] = 0345;
  deCode[127] = 0445;
  deCode[128] = 0545;
  deCode[129] = 0645;
  deCode[130] = 0355;
  deCode[131] = 0455;
  deCode[132] = 0555;
  deCode[133] = 0655;
  deCode[134] = 0755;
  deCode[135] = 0065;
  deCode[136] = 0465;
  deCode[137] = 0565;
  deCode[138] = 0665;
  deCode[139] = 0765;
  deCode[140] = 0075;
  deCode[141] = 0175;
  deCode[142] = 0575;
  deCode[143] = 0675;
  deCode[144] = 0775;
  deCode[145] = 0006;
  deCode[146] = 0106;
  deCode[147] = 0606;
  deCode[148] = 0706;
  deCode[149] = 0346;
  deCode[150] = 0446;
  deCode[151] = 0546;
  deCode[152] = 0646;
  deCode[153] = 0356;
  deCode[154] = 0456;
  deCode[155] = 0556;
  deCode[156] = 0656;
  deCode[157] = 0756;
  deCode[158] = 0066;
  deCode[159] = 0466;
  deCode[160] = 0566;
  deCode[161] = 0666;
  deCode[162] = 0766;
  deCode[163] = 0076;
  deCode[164] = 0176;
  deCode[165] = 0576;
  deCode[166] = 0676;
  deCode[167] = 0776;
  deCode[168] = 0007;
  deCode[169] = 0107;
  deCode[170] = 0207;
  deCode[171] = 0607;
  deCode[172] = 0707;
  deCode[173] = 0017;
  deCode[174] = 0117;
  deCode[175] = 0217;
  deCode[176] = 0317;
  deCode[177] = 0717;
  deCode[178] = 0357;
  deCode[179] = 0457;
  deCode[180] = 0557;
  deCode[181] = 0657;
  deCode[182] = 0757;
  deCode[183] = 0067;
  deCode[184] = 0467;
  deCode[185] = 0567;
  deCode[186] = 0667;
  deCode[187] = 0767;
  deCode[188] = 0077;
  deCode[189] = 0177;
  deCode[190] = 0577;
  deCode[191] = 0677;
  deCode[192] = 0777;
  deCode[193] = 00;
  deCode[194] = 00;
  deCode[195] = 01;
  deCode[196] = 02;
  deCode[197] = 03;
  deCode[198] = 04;
  deCode[199] = 05;
  deCode[200] = 06;
  deCode[201] = 07;
  deCode[202] = 00;
  deCode[203] = 010;
  deCode[204] = 020;
  deCode[205] = 060;
  deCode[206] = 070;
  deCode[207] = 001;
  deCode[208] = 011;
  deCode[209] = 021;
  deCode[210] = 031;
  deCode[211] = 071;
  deCode[212] = 002;
  deCode[213] = 012;
  deCode[214] = 022;
  deCode[215] = 032;
  deCode[216] = 042;
  deCode[217] = 013;
  deCode[218] = 023;
  deCode[219] = 033;
  deCode[220] = 043;
  deCode[221] = 053;
  deCode[222] = 024;
  deCode[223] = 034;
  deCode[224] = 044;
  deCode[225] = 054;
  deCode[226] = 064;
  deCode[227] = 035;
  deCode[228] = 045;
  deCode[229] = 055;
  deCode[230] = 065;
  deCode[231] = 075;
  deCode[232] = 006;
  deCode[233] = 046;
  deCode[234] = 056;
  deCode[235] = 066;
  deCode[236] = 076;
  deCode[237] = 007;
  deCode[238] = 017;
  deCode[239] = 057;
  deCode[240] = 067;
  deCode[241] = 077;

  return (0);
}



/* PCCDECODE:   function reads PCC code from code storage, and writes
 *            out decoded image
 *                      usage: pccdecode (image, nX, nY, countflag)
 *              If countflag = 0, lines are decoded to value 255; if 
 *              countflag != 0, lines are decoded into values 1-255
 *              so different lines have different values.
 *
 */

pccdecode (image, nX, nY, countflag)
     unsigned char **image;     /* image region to be decoded */
     register long nX, nY;      /* image region size */
     int countflag;             /* different numbers for lines? */
{
  register int iByteCode,       /* code storage incrementor */
    codeWord,                   /* code word contains up to 3 dirn.s */
    x, y;                       /* feature coordinates */
  struct branch1 *branch;       /* stack of branches to be decoded */
  struct branch1 branchTop;     /* first branch */
  long nBranch;                 /* no. of branches in stack */
  int xTrack, yTrack;           /* decode tracking  coord.s */

  int imgon = IMGON;

/* initialize branches and zero image region */
  nBranch = 0;
  branch = &branchTop;
  branch->previous = branch;

  for (y = 0; y < nY; y++)
    for (x = 0; x < nX; x++)
      image[y][x] = 0;

/* decode from storage region to original position on screen */

  for (iByteCode = 0; iByteCode < nByteCode;) {
    codeWord = (int) fcCode[iByteCode++];

    /* if it is a feature: find start location if break, push branches
     *        if junction, pop branches if endpoint */

    if (codeWord >= MINFEATCODE) {
      if (countflag) {
        imgon++;
        if (imgon >= 255)
          imgon = 1;
      }
      switch (codeWord) {
      case BIFCODE:
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        break;
      case CROSSCODE:
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        break;
      case ENDCODE:            /* pop branches */
        if (nBranch > 0) {
          nBranch--;
          branch = branch->previous;
          xTrack = branch->x;
          yTrack = branch->y;
        }
        break;
      case STARTCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        image[yTrack][xTrack] = imgon;
        break;
      case LINEBRCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        image[yTrack][xTrack] = imgon;
        break;
      case BIFBRCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;

        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        image[yTrack][xTrack] = imgon;
        break;
      case CROSSBRCODE:
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        pccbranch (&branch, xTrack, yTrack, 0);
        nBranch++;
        image[yTrack][xTrack] = imgon;
        break;
      case LINECODE:
        break;
      case STOPCODE:
        return (0);
      default:
        break;
      }
    }

    /* if it is a direction segment, write at proper location */
    else
      pccdetrack (image, &xTrack, &yTrack, codeWord, nX, nY, imgon);
  }

  printf ("PCCDECODE: missing STOPCODE in PCC storage \n");

  return (0);
}



/* PCCDETRACK:  function decodes codeword and tracks directions
 *            writing back thin lines as original
 *                      usage: nDirns = pccdetrack (image, &x, &y, codeWord)
 *
 */

#define DECODE(BITSHIFT) \
		dirn = ((deCode[codeWord] >> BITSHIFT) & 07) + 1; \
		nbrtoxy (dirn, *x, *y, (long *)x, (long *)y); \
if (*x < 0 || *x >= nX){ \
/*  printf ("PCCDETRACK: out of bounds (%4d, %4d)\n", *x, *y); */ \
  *x = nX - 1; \
} \
if (*y < 0 || *y >= nY){ \
/*  printf ("PCCDETRACK: out of bounds (%4d, %4d)\n", *x, *y); */ \
  *y = nY - 1; \
} \
		image[*y][*x] = (unsigned char) imgon

pccdetrack (image, x, y, codeWord, nX, nY, imgon)
     long nX, nY;               /* image region size */
     unsigned char **image;     /* image array */
     int *x, *y;                /* input/output line coordinates */
     register long codeWord;    /* code word contains up to 3 directions */
     long imgon;                /* image color  */
{
  register long dirn;           /* direction of next segment */

/* 3 direction segments per code word */
  if (MINCODE3 <= codeWord && MAXCODE3 >= codeWord) {
    DECODE (0);
    DECODE (3);
    DECODE (6);
    return (3);
  }

/* 2 direction segments per code word */
  if (MINCODE2 <= codeWord && MAXCODE2 >= codeWord) {
    DECODE (0);
    DECODE (3);
    return (2);
  }

/* 1 direction segment per code word */
  if (MINCODE1 <= codeWord && MAXCODE1 >= codeWord) {
    DECODE (0);
    return (1);
  }

/* 0 direction segment per code word */
  if (codeWord == CODE0) {
    return (0);
  }
}


/* PCC2XY:      function reads PCC code from code storage, and lists
 *            features and chain codes
 *                      usage: pcc2xy (data, &nData)
 *
 */

pcc2xy (data, nData)
     struct point *data;        /* data curve */
     long *nData;               /* no. coords. in data curve */
{
  register int iByteCode,       /* code storage incrementor */
    codeWord;                   /* code word contains up to 3 dirn.s */
  long maxBranch;               /* maximum branching number */
  long maxEdges;                /* total number of edges in graph */

  struct branch1 *branch;       /* stack of branches to be decoded */
  struct branch1 branchTop;     /* first branch */
  long nBranch;                 /* no. of branches in stack */
  int xTrack, yTrack;           /* decode tracking  coord.s */

/* initialize branches */
  *nData = 0;
  maxBranch = 0;
  maxEdges = 0;
  nBranch = 0;
  branch = &branchTop;
  branch->previous = branch;

/* decode from storage region to original position on screen */
  FILE *tempfp= fopen("temp.txt","w");
  long temp;
  for (iByteCode = 0; iByteCode < nByteCode;) {
    codeWord = (int) fcCode[iByteCode++];

    /* if it is a feature: find start location if break, push branches
     *        if junction, pop branches if endpoint */

    if (codeWord >= MINFEATCODE) {
	temp = (long) branch;
	if (temp == 0x0){
		printf("temp=%ld\n", temp);
		fclose(tempfp);
		return(0);
		}//if++
	else {	fprintf(tempfp,"branch pointer=%ld, branch.x=%ld, branch.y=%ld\n", temp, branch->x,branch->y);
      switch (codeWord) {
      case BIFCODE:
	//fprintf(tempfp,"BIFCODE1S:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
	pccbranch (&branch, xTrack, yTrack, 0);
        //fprintf(tempfp,"BIFCODE1E:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
	nBranch++;
        if (nBranch > maxBranch)
          maxBranch = nBranch;
        data[(*nData)++].x = -BIFCODE;
        maxEdges++;
        break;
      case CROSSCODE:
	//fprintf(tempfp,"CROSSCODE1:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"CROSSCODE1:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
	//fprintf(tempfp,"CROSSCODE2S:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"CROSSCODE2E:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
        if (nBranch > maxBranch)
          maxBranch = nBranch;
        data[(*nData)++].x = -CROSSCODE;
        maxEdges++;
        break;
      case ENDCODE:            /* pop branches */
        if (nBranch > 0) {
          nBranch--;
          branch = branch->previous;
          xTrack = branch->x;
          yTrack = branch->y;
          maxEdges++;
        }
        data[(*nData)++].x = -ENDCODE;
        break;
      case STARTCODE:
        data[(*nData)++].x = -STARTCODE;
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        data[(*nData)].x = xTrack;
        data[(*nData)++].y = yTrack;
        maxEdges++;
        break;
      case LINEBRCODE:
        data[(*nData)++].x = -LINEBRCODE;
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
	//fprintf(tempfp,"LINEBRCODES:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"LINEBRCODEE:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
        if (nBranch > maxBranch)
          maxBranch = nBranch;
        data[(*nData)].x = xTrack;
        data[(*nData)++].y = yTrack;
        maxEdges++;
        break;
      case BIFBRCODE:
        data[(*nData)++].x = -BIFBRCODE;
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
	//fprintf(tempfp,"BIFRCODE1S:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"BIFRCODE1E:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
	//fprintf(tempfp,"BIFRCODE2S:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"BIFRCODE2E:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
        if (nBranch > maxBranch)
          maxBranch = nBranch;
        data[*nData].x = xTrack;
        data[(*nData)++].y = yTrack;
        maxEdges++;
        break;
      case CROSSBRCODE:
        data[(*nData)++].x = -CROSSBRCODE;
        xTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
        yTrack = (long) *(fcCode + iByteCode)
          | ((long) *(fcCode + iByteCode + 1) << 8);
        iByteCode += 2;
	//fprintf(tempfp,"1S:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"1E:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
	//fprintf(tempfp,"2S:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"2E:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
	//fprintf(tempfp,"3S:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        pccbranch (&branch, xTrack, yTrack, 0);
	//fprintf(tempfp,"3E:branch.x=%ld, branch.y=%ld", branch->x,branch->y);
        nBranch++;
        if (nBranch > maxBranch)
          maxBranch = nBranch;
        data[*nData].x = xTrack;
        data[(*nData)++].y = yTrack;
        maxEdges++;
        break;
      case LINECODE:
        break;
      case STOPCODE:
        return (0);
      default:
        break;
      }
     }//else++
    }
	
    /* if it is a direction segment, write at proper location */
    else {
      detrack (&xTrack, &yTrack, codeWord, data, nData);
    }
	//fclose(tempfp);
  }

  printf ("PCCDECODE: missing STOPCODE in PCC storage \n");

  return (0);
}



/* DETRACK:     function decodes PCC codeword and tracks directions
 *            writing output array of coords.
 *                      usage: nDirns = detrack (&x, &y, codeWord, data,
 *                                              &nData)
 *
 */

extern int deCode[NDECODE];     /* decode table */

#define DECODE2(BITSHIFT) \
		dirn = ((deCode[codeWord] >> BITSHIFT) & 07) + 1; \
		nbrtoxy (dirn, *x, *y, (long *)x, (long *)y); \
		data[*nData].x = *x; \
		data[(*nData)++].y = *y;

detrack (x, y, codeWord, data, nData)
     int *x,                    /* input/output line coordinates */
      *y;

     register int codeWord;     /* code word contains up to 3 directions */

     struct point *data;        /* data curve */
     long *nData;               /* no. coords. in data curve */

{
  register int dirn;            /* direction of next segment */

/* 3 direction segments per code word */
  if (MINCODE3 <= codeWord && MAXCODE3 >= codeWord) {
    DECODE2 (0);
    DECODE2 (3);
    DECODE2 (6);
    return (3);
  }

/* 2 direction segments per code word */
  if (MINCODE2 <= codeWord && MAXCODE2 >= codeWord) {
    DECODE2 (0);
    DECODE2 (3);
    return (2);
  }

/* 1 direction segment per code word */
  if (MINCODE1 <= codeWord && MAXCODE1 >= codeWord) {
    DECODE2 (0);
    return (1);
  }

/* 0 direction segment per code word */
  if (codeWord == CODE0) {
    return (0);
  }
}
