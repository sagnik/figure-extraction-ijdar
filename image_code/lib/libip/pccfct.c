/* 
 * pccft.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/* PCCFCT:      functions for PCC encoding
 *            (decoding functions in PCCFCTDE; and functions common
 *              to both encoding and decoding programs in PCCFCT2)
 *      FUNCTIONS:
 *              PCCCODES, PCCCODE, PCCTRACK, PCCRSTORE, PCCLSTORE, PCCFSTORE,
 *              PCCWRITE
 */

#include <stdio.h>
#include "pcc2.h"               /* header file for PCC programs */

struct code code;               /* structure contains codes for 
                                 * * direction sequences and features */
extern unsigned char *fcCode;   /* code storage */
extern int nByteCode;           /* no. bytes in storage */


/* PCCCODES:    function constructs table of PCC codes
 *            corresponding to sequences of 0, 1, 2, or 3
 *              direction vectors and features endpoint, bifurcation,
 *              and cross
 *                      usage: pcccodes ()
 *                              extern int decode;
 *
 */

pcccodes ()
{
/* DIRECTION SEGMENTS TO CODE TABLES */

/* 0-vector chains */
  code.code0[00] = 193;

/* 1-vector chains */
  code.code1[00] = 194;
  code.code1[01] = 195;
  code.code1[02] = 196;
  code.code1[03] = 197;
  code.code1[04] = 198;
  code.code1[05] = 199;
  code.code1[06] = 200;
  code.code1[07] = 201;

/* 2-vector chains */
  code.code2[00] = 202;
  code.code2[010] = 203;
  code.code2[020] = 204;
  code.code2[060] = 205;
  code.code2[070] = 206;
  code.code2[001] = 207;
  code.code2[011] = 208;
  code.code2[021] = 209;
  code.code2[031] = 210;
  code.code2[071] = 211;
  code.code2[002] = 212;
  code.code2[012] = 213;
  code.code2[022] = 214;
  code.code2[032] = 215;
  code.code2[042] = 216;
  code.code2[013] = 217;
  code.code2[023] = 218;
  code.code2[033] = 219;
  code.code2[043] = 220;
  code.code2[053] = 221;
  code.code2[024] = 222;
  code.code2[034] = 223;
  code.code2[044] = 224;
  code.code2[054] = 225;
  code.code2[064] = 226;
  code.code2[035] = 227;
  code.code2[045] = 228;
  code.code2[055] = 229;
  code.code2[065] = 230;
  code.code2[075] = 231;
  code.code2[006] = 232;
  code.code2[046] = 233;        /* oops -- this was 333 before */
  code.code2[056] = 234;
  code.code2[066] = 235;
  code.code2[076] = 236;
  code.code2[007] = 237;
  code.code2[017] = 238;
  code.code2[057] = 239;
  code.code2[067] = 240;
  code.code2[077] = 241;

/* 3-vector chains */
  code.code3[0000] = 1;
  code.code3[0100] = 2;
  code.code3[0200] = 3;
  code.code3[0600] = 4;
  code.code3[0700] = 5;
  code.code3[0010] = 6;
  code.code3[0110] = 7;
  code.code3[0210] = 8;
  code.code3[0310] = 9;
  code.code3[0710] = 10;
  code.code3[0020] = 11;
  code.code3[0120] = 12;
  code.code3[0220] = 13;
  code.code3[0320] = 14;
  code.code3[0060] = 15;
  code.code3[0560] = 16;
  code.code3[0660] = 17;
  code.code3[0760] = 18;
  code.code3[0070] = 19;
  code.code3[0170] = 20;
  code.code3[0570] = 21;
  code.code3[0670] = 22;
  code.code3[0770] = 23;
  code.code3[0001] = 24;
  code.code3[0201] = 25;
  code.code3[0101] = 26;
  code.code3[0601] = 27;
  code.code3[0701] = 28;
  code.code3[0011] = 29;
  code.code3[0111] = 30;
  code.code3[0211] = 31;
  code.code3[0311] = 32;
  code.code3[0711] = 33;
  code.code3[0021] = 34;
  code.code3[0121] = 35;
  code.code3[0221] = 36;
  code.code3[0321] = 37;
  code.code3[0421] = 38;
  code.code3[0131] = 39;
  code.code3[0231] = 40;
  code.code3[0331] = 41;
  code.code3[0431] = 42;
  code.code3[0531] = 43;
  code.code3[0071] = 44;
  code.code3[0171] = 45;
  code.code3[0571] = 46;
  code.code3[0671] = 47;
  code.code3[0771] = 48;
  code.code3[0002] = 49;
  code.code3[0102] = 50;
  code.code3[0202] = 51;
  code.code3[0702] = 52;
  code.code3[0012] = 53;
  code.code3[0112] = 54;
  code.code3[0212] = 55;
  code.code3[0312] = 56;
  code.code3[0712] = 57;
  code.code3[0022] = 58;
  code.code3[0122] = 59;
  code.code3[0222] = 60;
  code.code3[0322] = 61;
  code.code3[0422] = 62;
  code.code3[0132] = 63;
  code.code3[0232] = 64;
  code.code3[0332] = 65;
  code.code3[0432] = 66;
  code.code3[0532] = 67;
  code.code3[0242] = 68;
  code.code3[0342] = 69;
  code.code3[0442] = 70;
  code.code3[0542] = 71;
  code.code3[0013] = 72;
  code.code3[0113] = 73;
  code.code3[0213] = 74;
  code.code3[0313] = 75;
  code.code3[0713] = 76;
  code.code3[0023] = 77;
  code.code3[0123] = 78;
  code.code3[0223] = 79;
  code.code3[0323] = 80;
  code.code3[0423] = 81;
  code.code3[0133] = 82;
  code.code3[0233] = 83;
  code.code3[0333] = 84;
  code.code3[0433] = 85;
  code.code3[0533] = 86;
  code.code3[0243] = 87;
  code.code3[0343] = 88;
  code.code3[0443] = 89;
  code.code3[0543] = 90;
  code.code3[0643] = 91;
  code.code3[0353] = 92;
  code.code3[0453] = 93;
  code.code3[0553] = 94;
  code.code3[0653] = 95;
  code.code3[0753] = 96;
  code.code3[0124] = 97;
  code.code3[0224] = 98;
  code.code3[0324] = 99;
  code.code3[0424] = 100;
  code.code3[0134] = 101;
  code.code3[0234] = 102;
  code.code3[0334] = 103;
  code.code3[0434] = 104;
  code.code3[0534] = 105;
  code.code3[0244] = 106;
  code.code3[0344] = 107;
  code.code3[0444] = 108;
  code.code3[0544] = 109;
  code.code3[0644] = 110;
  code.code3[0354] = 111;
  code.code3[0454] = 112;
  code.code3[0554] = 113;
  code.code3[0654] = 114;
  code.code3[0754] = 115;
  code.code3[0464] = 116;
  code.code3[0564] = 117;
  code.code3[0664] = 118;
  code.code3[0764] = 119;
  code.code3[0135] = 120;
  code.code3[0235] = 121;
  code.code3[0335] = 122;
  code.code3[0435] = 123;
  code.code3[0535] = 124;
  code.code3[0245] = 125;
  code.code3[0345] = 126;
  code.code3[0445] = 127;
  code.code3[0545] = 128;
  code.code3[0645] = 129;
  code.code3[0355] = 130;
  code.code3[0455] = 131;
  code.code3[0555] = 132;
  code.code3[0655] = 133;
  code.code3[0755] = 134;
  code.code3[0065] = 135;
  code.code3[0465] = 136;
  code.code3[0565] = 137;
  code.code3[0665] = 138;
  code.code3[0765] = 139;
  code.code3[0075] = 140;
  code.code3[0175] = 141;
  code.code3[0575] = 142;
  code.code3[0675] = 143;
  code.code3[0775] = 144;
  code.code3[0006] = 145;
  code.code3[0106] = 146;
  code.code3[0606] = 147;
  code.code3[0706] = 148;
  code.code3[0346] = 149;
  code.code3[0446] = 150;
  code.code3[0546] = 151;
  code.code3[0646] = 152;
  code.code3[0356] = 153;
  code.code3[0456] = 154;
  code.code3[0556] = 155;
  code.code3[0656] = 156;
  code.code3[0756] = 157;
  code.code3[0066] = 158;
  code.code3[0466] = 159;
  code.code3[0566] = 160;
  code.code3[0666] = 161;
  code.code3[0766] = 162;
  code.code3[0076] = 163;
  code.code3[0176] = 164;
  code.code3[0576] = 165;
  code.code3[0676] = 166;
  code.code3[0776] = 167;
  code.code3[0007] = 168;
  code.code3[0107] = 169;
  code.code3[0207] = 170;
  code.code3[0607] = 171;
  code.code3[0707] = 172;
  code.code3[0017] = 173;
  code.code3[0117] = 174;
  code.code3[0217] = 175;
  code.code3[0317] = 176;
  code.code3[0717] = 177;
  code.code3[0357] = 178;
  code.code3[0457] = 179;
  code.code3[0557] = 180;
  code.code3[0657] = 181;
  code.code3[0757] = 182;
  code.code3[0067] = 183;
  code.code3[0467] = 184;
  code.code3[0567] = 185;
  code.code3[0667] = 186;
  code.code3[0767] = 187;
  code.code3[0077] = 188;
  code.code3[0177] = 189;
  code.code3[0577] = 190;
  code.code3[0677] = 191;
  code.code3[0777] = 192;

/* feature codes */
  code.codeFeat[0] = STOPCODE;
  code.codeFeat[1] = ENDCODE;
  code.codeFeat[2] = LINECODE;
  code.codeFeat[3] = BIFCODE;
  code.codeFeat[4] = CROSSCODE;
  code.codeFeat[5] = STARTCODE;
  code.codeFeat[6] = LINEBRCODE;
  code.codeFeat[7] = BIFBRCODE;
  code.codeFeat[8] = CROSSBRCODE;

  return (0);
}


/* PCCODE:      function performs PCC coding on thin line image
 *                    usage: pccode (image, nX, nY)
 *
 */

#define E 3                     /* neighborhood pixel in E dirn */
#define SE 4                    /* neighborhood pixel in SE dirn */
#define S 5                     /* neighborhood pixel in S dirn */

pcccode (image, nX, nY)
     unsigned char **image;     /* image region to be coded */
     long nX, nY;               /* image region size */
{
  register long x, y,           /* image coordinates */
    nXm1, nYm1;                 /* x-width minus 1 */
  long direction,               /* direction from center of current pt */
    xTrack, yTrack,             /* tracking coordinates */
    chain,                      /* flag = 1 to chain code, 0 to stop */
    nFeature;                   /* no. emanations from center pt. */
  long nDirns,                  /* no. dirn.s in current feature */
    dirns[NDIRNSPERFEATURE],    /* array of dirns per feature */
    junctionFlag;               /* see note above (21-Mar-85) */
  long branchNMax;              /* diagnostic to monitor max branch no. */
  struct branch1 *branch;       /* stack of branches */
  struct branch1 branchTop;     /* first branch */
  long nBranch;                 /* no. of branches in stack */
  long i;
  long Xmax = 0;
  long Ymax = 0;

/* initialize */
  nXm1 = nX - 1;
  nYm1 = nY - 1;
  junctionFlag = 0;
  branch = &branchTop;
  branch->previous = branch;

/* zero 3 pixel boundary on analysis region */
  for (y = 0; y < nY; y++) {
    image[y][0] = image[y][nXm1] = IMGOFF;
    image[y][1] = image[y][nXm1 - 1] = IMGOFF;
    image[y][2] = image[y][nXm1 - 2] = IMGOFF;
  }
  for (x = 1; x < nXm1; x++) {
    image[0][x] = image[nYm1][x] = IMGOFF;
    image[1][x] = image[nYm1 - 1][x] = IMGOFF;
    image[2][x] = image[nYm1 - 2][x] = IMGOFF;
  }

/* sequentially search for ON point, and when found perform
 * feature chain coding */

  chain = nBranch = branchNMax = nDirns = 0;

  xTrack = 0;
  yTrack = 0;
  for (y = 1; y < nYm1; y++) {
    for (x = 1; x < nXm1; x++) {
      if (xTrack > Xmax)
        Xmax = xTrack;
      if (yTrack > Ymax)
        Ymax = yTrack;
      if (image[y][x] == IMGON) {
        direction = SE;
        chain = 1;
        xTrack = x;
        yTrack = y;

        /* check if first feature is start code or line break code */
        if ((image[y - 1][x] + image[y - 1][x + 1]
             + image[y][x + 1] + image[y + 1][x + 1]
             + image[y + 1][x] + image[y + 1][x - 1]
             + image[y][x - 1] + image[y - 1][x - 1])
            > IMGON) {
          pccbranch (&branch, xTrack, yTrack, S);
          nBranch++;
          direction = E;        /* so PCCTRACK finds only 1 branch */
          image[y][x] = ERASED; /* set break node to ERASED */

          pccrstore (NLINEBRCODE, xTrack, yTrack);
        }
        else {
          /* printf ("\nstart chain x=%ld, y=%ld\n", xTrack, yTrack); */
          pccrstore (NSTARTCODE, xTrack, yTrack);
        }

        while (chain) {

          nFeature = pcctrack (image, &xTrack, &yTrack,
                               &direction, &branch, &nBranch);

          if (nBranch > branchNMax)
            branchNMax = nBranch;

          /* immediately after cross, TLC1TRACK will call the
           * two remaining branches of the cross a bifurcation
           * (unless cross contains loop); correct for this */
          if (junctionFlag == 1) {
            if (nFeature > 1) {
              for (i = nFeature - 1; i > 0; --i) {
                --nBranch;
                branch = branch->previous;
              }
              nFeature = 1;
            }
            junctionFlag = 0;
          }

          /* depending on feature (or no. of emanations) from
           * center, do following */

          switch (nFeature) {
            /* if hit endpoint, store it and pop next branch */
          case 0:

            pcclstore (dirns, nDirns);
            nDirns = 0;

            pccfstore (NENDCODE);

            if (branch->previous != branch) {
              branch = branch->previous;
              nBranch--;
              xTrack = branch->x;
              yTrack = branch->y;
              direction = branch->variable;
              junctionFlag = 1;
            }
            else {
              chain = 0;
              /* printf ("\nchain=0 at x=%ld, y=%ld\n", xTrack, yTrack); */
            }
            break;

            /* if not feature, then temporarily store direction of
             * new point and after NDIRNSPERFEATURE, store feature */
          case 1:
            dirns[nDirns++] = direction;

            if (nDirns == NDIRNSPERFEATURE) {
              pcclstore (dirns, nDirns);
              nDirns = 0;
            }
            break;

            /* if hit other feature (bifirc., cross), store it
             * and continue on */

          case 2:
            pcclstore (dirns, nDirns);
            nDirns = 0;
            pccfstore (NBIFCODE);

            dirns[nDirns++] = direction;
            break;

          case 3:
            pcclstore (dirns, nDirns);
            nDirns = 0;
            pccfstore (NCROSSCODE);

            dirns[nDirns++] = direction;
            break;

          default:
            break;
          }
        }
      }
    }
  }
/* write terminator to storage region */
  pccfstore (NSTOPCODE);
  /* printf ("\nx_max stored = %ld y_max stored = %ld\n", Xmax, Ymax); */

  /* printf ("(PCCCODE: max branching number = %d)\n", branchNMax); */
  return (0);
}


/* PCCTRACK:    function tracks thin lines to produce PCC
 *                usage: nFound = pcctrack (image, &xCenter, 
 *                                    &yCenter, &direction, &branch, &nBranch)
 */

#define MOD8(A,B)  ((((A) + (B) - 1) % 8) + 1)
    /* mod 8 addition, where result = [1,8] */

#define NPOTD 5                 /* no. potential nbrs in direction of chain */
#define NDIRNS 9                /* no. direction codes */

pcctrack (image, xCenter, yCenter, direction, branch, nBranch)
     unsigned char **image;     /* image array */
     long *xCenter,             /* input coord.s of center point */
      *yCenter,                 /* and output coord.s of next point */
      *direction;               /* input and output direction of chain */
     struct branch1 **branch;   /* for branches from current chain */
     long *nBranch;             /* no. of branches in stack */
{
  register long i, dirnIn,      /* incoming direction */
    iDirn,                      /* no. of neighborhood element */
    nFound,                     /* no. ONs in nbrhood; no. 4-conn. groups */
    nNbrs,                      /* no. neighbors to central pixel */
    nAdjacent;                  /* no. of 4-conn pix in group of nbrhood */
  struct point nbrs[NDIRNS];    /* ON pixels neighboring central pixel */
  long nbrDirns[NDIRNS];        /* directions of neighbors */
  struct point ring[NDIRNS];    /* cw ring of potential nbrs around pix */
  long xCenterOld,              /* coord.s of original center pt. */
    yCenterOld, dirnOld;        /* direction into center pixel */

  static int dSequence[NDIRNS][NPOTD] =
  {                             /* direction sequence:      */
    {0, 0, 0, 0, 0},
    {5, 7, 3, 6, 4},            /*  neighborhood directions are checked  */
    {7, 5, 6, 8, 4},            /*  in sequence depending on incoming    */
    {7, 1, 5, 8, 6},            /*  direction, so that current chain     */
    {1, 7, 8, 2, 6},            /*  follows straightest line             */
    {1, 3, 7, 2, 8},            /*  e.g. - if incoming direction is 1,   */
    {3, 1, 2, 4, 8},            /*  outgoing direction 5 is checked      */
    {3, 5, 1, 4, 2},            /*  first, then 6, and 4                 */
    {5, 3, 4, 6, 2}
  };
  static int dRing[NDIRNS][NPOTD] =
  {                             /* semi-rings of dirns around pix */
    {0, 0, 0, 0, 0},
    {3, 4, 5, 6, 7},
    {4, 5, 6, 7, 8},
    {5, 6, 7, 8, 1},
    {6, 7, 8, 1, 2},
    {7, 8, 1, 2, 3},
    {8, 1, 2, 3, 4},
    {1, 2, 3, 4, 5},
    {2, 3, 4, 5, 6}
  };

/* find coordinates of ring around central pixel in potential directions */
  xCenterOld = *xCenter;
  yCenterOld = *yCenter;
  dirnOld = *direction;
  dirnIn = MOD8 (*direction, 4);

  for (i = 0; i < NPOTD; i++) {
    iDirn = dRing[dirnIn][i];
    nbrtoxy (iDirn, xCenterOld, yCenterOld,
             (long *) &(ring[iDirn].x), (long *) &(ring[iDirn].y));
  }

/* find all ON or ERASED neighbors in potential directions in dirn priority */
  *direction = 0;
  for (i = 0, nNbrs = 0, nFound = 0; i < NPOTD; i++) {
    iDirn = dSequence[dirnIn][i];
    if (image[ring[iDirn].y][ring[iDirn].x] != IMGOFF) {
      nbrs[nNbrs] = ring[iDirn];
      nbrDirns[nNbrs++] = iDirn;
      if (image[ring[iDirn].y][ring[iDirn].x] == IMGON) {
        if (nFound == 0) {
          *direction = iDirn;
          *xCenter = ring[iDirn].x;
          *yCenter = ring[iDirn].y;
        }
        nFound++;
      }
    }
  }

/* if more than one point is found, then find no. of 4-connected groups */
  if (nFound > 0 && nNbrs > 1) {
    nAdjacent = 0;
    for (i = 0, nFound = 0; i < NPOTD; i++) {
      iDirn = dRing[dirnIn][i];
      if (image[ring[iDirn].y][ring[iDirn].x] != IMGOFF) {
        if (nAdjacent == 0)
          nFound++;
        nAdjacent++;
      }
      else
        nAdjacent = 0;
    }
    /* for extra groups beyond branching pixel, push branches */
    for (i = nFound - 1; i > 0; --i) {
      pccbranch (branch, xCenterOld, yCenterOld, dirnOld);
      (*nBranch)++;
    }
  }

/* set value to ERASED if it is a feature node */
  if (nFound > 1)
    image[yCenterOld][xCenterOld] = ERASED;
/* if it is not a feature point, and not a break point, set value 
 * to 0 (break point has already been set to ERASED in PCCCODE) */
  else if (image[yCenterOld][xCenterOld] != ERASED)
    image[yCenterOld][xCenterOld] = IMGOFF;

  return (nFound);
}




/* PCCRSTORE:   function stores feature codes and locations for
 *            start and break (R) features
 *                      usage: pccrstore (feature, xFeature, yFeature)
 *
 */

pccrstore (feature, xFeature, yFeature)
     register long feature,     /* feature type */
       xFeature, yFeature;      /* coord.s of feature */
{
/* store feature code and x,y coordinates */
  fcCode[nByteCode++] = code.codeFeat[feature];

  fcCode[nByteCode++] = (unsigned char) (xFeature & 0xff);
  fcCode[nByteCode++] = (unsigned char) ((xFeature >> 8) & 0xff);
  fcCode[nByteCode++] = (unsigned char) (yFeature & 0xff);
  fcCode[nByteCode++] = (unsigned char) ((yFeature >> 8) & 0xff);

  return (0);
}


/* PCCLSTORE:   function performs line storage by taking up to 3
 *            direction vectors and storing them as a single
 *              feature chain code
 *                      usage: pcclstore (dirns, nDirns)
 *                              int *dirns;
 *
 */

pcclstore (dirns, nDirns)
     long dirns[NDIRNSPERFEATURE];  /* array of dirn.s per feature */
     register long nDirns;      /* no. directions in current feature */
{
/* store feature code */
  switch (nDirns) {
  case 0:
    break;
  case 1:
    fcCode[nByteCode++] = code.code1[dirns[0] - 1];
    break;
  case 2:
    fcCode[nByteCode++] = code.code2[(dirns[0] - 1)
                                     + ((dirns[1] - 1) << 3)];
    break;
  case 3:
    fcCode[nByteCode++] = code.code3[(dirns[0] - 1)
                                     + ((dirns[1] - 1) << 3)
                                     + ((dirns[2] - 1) << 6)];
    break;
  default:
    break;
  }

  return (0);
}


/* PCCFSTORE:   function stores feature codes for non-break PCC features
 *            i.e. those that are not the source of a structure
 *                      usage: pccfstore (feature)
 *
 */

pccfstore (feature)
     register long feature;     /* feature type */
{

/* store feature code */
  fcCode[nByteCode++] = code.codeFeat[feature];

  return (0);
}


/* PCCWRITE:    function writes PCC code to file
 *                    usage: pccwrite (filename, pcc, nCode, width, height)
 *
 */

pccwrite (filename, pcc, nCode, width, height)
     char *filename;
     unsigned char *pcc;        /* PCC code */
     long nCode;                /* no. bytes of code */
     long width, height;        /* image size */
{
  FILE *fpOut;

/* open output file */
  if ((fpOut = fopen (filename, "wb")) == NULL) {
    printf ("PCCWRITE: cannot open file", 1);
    return (-1);
  }

/* write output header and image */

  fprintf (fpOut, "TYPE=%s\n", "PCC");
  fprintf (fpOut, "IMAGE SIZE=%d %d\n", width, height);
  fprintf (fpOut, "PCC LENGTH=%d\n", nByteCode);
  fwrite (fcCode, sizeof (unsigned char), nByteCode, fpOut);

  fclose (fpOut);

  return (1);
}
