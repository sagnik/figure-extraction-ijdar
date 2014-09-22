
/* PROFILE:     program calculates horizontal or vertical profile of image
*                    usage: profile inimg 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tiffimage.h"          /* picfile info on images */
#include "images.h"


#define ON 0                    /* binarization values */
#define OFF 255					//should be checked!--!
#define PROFILE_DFLT 0          /* =0 for horizontal; =1 for vertical prof. */
#define PROFILE_HEIGHT 200      /* height of profile for display */
#define FALSE 0
#define TRUE 1

long usage (short);
long input (int, char **, short *, long *, short *);
int axis_width (long*, long, long*, long*);
void quickSort(long*[], long, int);
void q_sort(long*[], long, long);
long tic_frequency(long*, long);

main (argc, argv)
int argc;
char *argv[];
{
	Image *imgI, *imgOC, *imgOX, *imgOY, *imgOL;           /* input and output image structures */
	unsigned char **imgIn, **imgOutC, **imgOutX, **imgOutY, **imgOutL, *imgC="_Curve.pgm", 
		*imgX ="_Xaxis.pgm", *imgY="_Yaxis.pgm", *imgLeg="_legend.pgm";  /* input and output images */
	long *profileH, *profileV;                /* horizontal or vertical profile vector */
	long widthI, heightI, tempX, tempY;         /* image size */
	int axis_width_x, axis_width_y;
	short horizOrVert;            /* flag =0 for horiz; = 1 for vert. profile */
	long profLengthh, profLengthw;              /* length of profile */
	long profHeight;              /* height of profile for display */
	short printFlag;              /* to print out profile data */
	long sum, maxSum=0;             /* sum and max. sum of profile values */
	long x, y;
	long hx = 1,hy = 2,hx1 = -1, hy1 = -1; //numbered for axis
	long x_axis=0, y_axis=0;	

	/* user input */
	if (input (argc, argv, &horizOrVert, &profHeight, &printFlag) < 0)
		return (-1);

	imgI = ImageIn (argv[1]);
	imgIn = imgI->img;
	heightI = ImageGetHeight (imgI);
	widthI = ImageGetWidth (imgI);
#ifdef verbose
	printf ("image size is %dx%d\n", widthI, heightI);
#endif
	/*Prepare output image names */

	char *p, *q; p=q=argv[1];
	while(*p != '\0') p++;
	while(*p != '.') p--; *p='\0';
	//imgC = strcat(q,imgC);

	profLengthw = widthI;

	if ((profileH = (long *) calloc (profLengthw, sizeof (long))) == NULL) {
		printf ("PROFILE: not enough memory -- sorry.\n");
		return (-1);
	}

	for (x = 0; x < widthI; x++) {
		for (y = 0, sum = 0; y < heightI; y++) {
			if (imgIn[y][x] == OFF)
				sum++;
		}
		profileH[x] = sum;

	}
	// Process profile to find X axis width and co-ordinates 
	//axis_width_x = axis_width(profileH, profLength, &hx,&hx1);

	long *indexed_profilew[profile_lengthw];
	long *firstderivativew[profile_lengthw];
	int countw = 1; int countv = 1;
	int plotcount;
	for (i=0;i<profile_lengthw;i++)
	{	
		long *p = calloc(2,sizeof(long));
		p[0] = profileH[i];
		p[1] = i;
		indexed_profilew[i] = p;
	}
	for (i=0;i<profile_lengthw-1;i++)
	{	
		long *p = calloc(2,sizeof(long));
		p[0] = profileH[i] - profileH[i+1];
		p[1] = i;
		firstderivativew[i] = p;
	}
	int arrayw[20]; int *wp; wp = arrayw;	
	quickSort(indexed_profilew, profile_lengthw,1);
	quickSort(firstderivativew, profile_lengthw-1,1);
	for(i=0;i<10;i++){
		if((abs(firstderivativew[i][0]-firstderivativew[i+1][0]) <= 0.01*heightI) && (abs(firstderivativew[i][1] - firstderivativew[i+1][1]) >= 0.02*widthI)){
		countw++;
		*wp = i;
		wp++;
		}
	}

	profLengthh = heightI;

	if ((profileV = (long *) calloc (profLengthh, sizeof (long))) == NULL) {
		printf ("PROFILE: not enough memory -- sorry.\n");
		return (-1);
	}

	for (y = 0; y < heightI; y++) {
		for (x = 0, sum = 0; x < widthI; x++) {
			if (imgIn[y][x] == OFF)
				sum++;
		}
		profileV[y] = sum;
	}
	long *indexed_profilev[profile_lengthw];
	long *firstderivativev[profile_lengthw];
	
	for (i=0;i<profile_lengthh;i++)
	{	
		long *p = calloc(2,sizeof(long));
		p[0] = profileV[i];
		p[1] = i;
		indexed_profilev[i] = p;
	}
	for (i=0;i<profile_lengthh-1;i++)
	{	
		long *p = calloc(2,sizeof(long));
		p[0] = profileV[i] - profileV[i+1];
		p[1] = i;
		firstderivativev[i] = p;
	}
	int arrayv[20]; int *vp; vp = arrayv;	
	quickSort(indexed_profilev, profile_lengthh,1);
	quickSort(firstderivativev, profile_lengthh-1,1);
	for(i=0;i<10;i++){
		if((abs(firstderivativev[i][0]-firstderivativev[i+1][0]) <= 0.01*widthI) && (abs(firstderivativev[i][1] - firstderivativev[i+1][1]) >= 0.02*heightI)){
		countv++;
		*vp = i;
		vp++;
	}
	int flag;
	if(countv ==1 && countw == 1)
		plotcount = 1;
	else if ((countv ==4 && countw == 2) || (countv ==2 && countw == 1)){
		plotcount = 2; flag = 0;}//horizontally partition
	else if ((countv ==2 && countw == 4) || (countv ==1 && countw == 2)){
		plotcount = 2; flag = 1;}//vertically partition
	else if (countv ==4 && countw == 4)
		plotcount = 4;
	else if (countv ==2 && countw == 2)
		if((abs(firstderivativev[0][1]-firstderivativev[arrayv[0]][1]) * abs(firstderivativew[0][1]-firstderivativew[arrayw[0]][1]))>= 0.6* heightI* widthI)
			plotcount = 1;
		else
			plotcount = 4;
	else
		plotcount = 0;

	if(plotcount == 1)
		exit(0);
	else if(plotcount == 2 && flag == 0){
		imgOC1 = ImageAlloc (heightI/2 + 10, widthI, 8);
		imgOutC1 = ImageGetPtr (imgOC1);
		
		for (y = 0; y < heightI/2 + 10; y++)
			for (x = 0; x < widthI; x++)
				imgOutC1[y][x] = ON;

		for (y = 0; y < heightI/2 + 10; y++)
			for (x = 0; x < widthI; x++)
				if (imgIn[y][x] == OFF)
					imgOutC1[y][x] = OFF;

		imgOC2 = ImageAlloc (heightI/2 - 10, widthI, 8);
		imgOutC2 = ImageGetPtr (imgOC2);
		
		for (y = 0; y < heightI/2 - 10; y++)
			for (x = 0; x < widthI; x++)
				imgOutC2[y][x] = ON;

		for (y = heightI/2 + 10; y < heightI; y++)
			for (x = 0; x < widthI; x++)
				if (imgIn[y][x] == OFF)
					imgOutC2[y][x] = OFF;
		char *p, *q; p=q=argv[1];
		while(*p != '\0') p++;
		while(*p != '.') p--; *p='\0';
		q = strcat(q,"_1.pgm");
				
		ImageOut (q, imgOX);
		p=q;
		while(*p != '\0') p++;
		while(*p != '_') p--; *p='\0';
		q = strcat(q,"_2.pgm");
		ImageOut (q, imgOX);
		}

	else if(plotcount == 2 && flag == 1){
		imgOC1 = ImageAlloc (heightI, widthI/2 -10, 8);
		imgOutC1 = ImageGetPtr (imgOC1);
		
		for (y = 0; y < heightI; y++)
			for (x = 0; x < widthI/2 - 10; x++)
				imgOutC1[y][x] = ON;

		for (y = 0; y < heightI; y++)
			for (x = 0; x < widthI/2 - 10; x++)
				if (imgIn[y][x] == OFF)
					imgOutC1[y][x] = OFF;

		imgOC2 = ImageAlloc (heightI, widthI/2 + 10, 8);
		imgOutC2 = ImageGetPtr (imgOC2);
		
		for (y = 0; y < heightI; y++)
			for (x = 0; x < widthI/2  + 10; x++)
				imgOutC2[y][x] = ON;

		for (y = 0; y < heightI; y++)
			for (x = widthI/2 + 10; x < widthI; x++)
				if (imgIn[y][x] == OFF)
					imgOutC2[y][x] = OFF;
		char *p, *q; p=q=argv[1];
		while(*p != '\0') p++;
		while(*p != '.') p--; *p='\0';
		q = strcat(q,"_1.pgm");
				
		ImageOut (q, imgOX);
		p=q;
		while(*p != '\0') p++;
		while(*p != '_') p--; *p='\0';
		q = strcat(q,"_2.pgm");
		ImageOut (q, imgOX);
		}


	

	// Process profile to find Y axis width and co-ordinates 
	//axis_width_y = axis_width(profileV, profLength, &hy, &hy1);
	//printf("\norigin_x = %d, Origin_y = %d\n",hx,hy);
	//Calculate Horizontal axis profile to get tic frequency here.

	/*if ((profileXaxis = (long *) calloc (widthI-hx-ceil(axis_width_x/2), sizeof (long))) == NULL) {
		printf ("PROFILE: not enough memory -- sorry.\n");
		return (-1);
	}

	for (x = 0; x < widthI-hx-ceil(axis_width_x/2); x++) {
		for (y = hy-5, sum = 0; y < hy+6; y++) {
			if (imgIn[y][(int)(x+hx+ceil(axis_width_x/2))] == OFF)
				sum++;
		}
		profileXaxis[x] = sum;
	}
	printf("\nTic Frequency For X axis:%ld\n",abs(tic_frequency(profileXaxis,widthI-hx-ceil(axis_width_x/2))));
	//Calculate Vertical axis profile to get tic frequency here.

	if ((profileYaxis = (long *) calloc (hy-ceil(axis_width_y/2), sizeof (long))) == NULL) {
		printf ("PROFILE: not enough memory -- sorry.\n");
		return (-1);
	}

	for (y = hy - axis_width_y/2 - 1; y >= 0; y--) {
		for (x = hx-5, sum = 0; x < hx+6; x++) {
			if (imgIn[y][x] == OFF)
				sum++;
		}
		profileYaxis[y] = sum;
	}
	printf("\nTic Frequency For Y axis:%ld\n",abs(tic_frequency(profileYaxis,hy-ceil(axis_width_y/2))));
	*/
	imgOC = ImageAlloc (hy, widthI-hx, 8);
	imgOutC = ImageGetPtr (imgOC);
	
	//printf("hx1=%d, hy1=%d", hx1, hy1);
	if(hx1>0 && hy1>0)
	{	
		for (y = 0; y < hy; y++)
			for (x = 0; x < widthI-hx; x++)
				imgOutC[y][x] = ON;

		for (y = hy1+15; y < hy-15; y++)
			for (x = 20; x < hx1 - hx -20; x++)
				if (imgIn[y][hx+x] == OFF)
					imgOutC[y][x] = OFF;
	}
	else
	{
		for (y = 0; y < hy; y++)
			for (x = 0; x < widthI-hx; x++)
				imgOutC[y][x] = ON;

		for (y = 5; y < hy-10; y++)
			for (x = 10; x < widthI - hx ; x++)
				if (imgIn[y][hx+x] == OFF)
					imgOutC[y][x] = OFF;
	}	

	ImageOut (imgC, imgOC);

	p =q = imgC;
	while (*p != '\0') p++;
	while (*p != '_') p--; *p = '\0';
	imgX = strcat (q,imgX);

	imgOX = ImageAlloc (heightI-hy, widthI, 8);
	imgOutX = ImageGetPtr (imgOX);

	tempX = hx;
	tempY = heightI - hy;
	


	/*if(tempX > tempY)
	{	
		tempX = hx-tempY;
		tempY = heightI;
	}
	else
	{
		tempY = hy + hx;
		tempX = 0;
	}*/
	for (y = 0; y < heightI-hy; y++)
		for (x = 0; x < widthI; x++)
			imgOutX[y][x] = ON;

	for (y = 0; y < heightI-hy-5; y++)
		for (x = 0; x < widthI; x++)
			if (imgIn[y+hy+5][x] == OFF)
				imgOutX[y][x] = OFF;

	if (tempX > tempY)
	{
		for(x = hx;x>0;x--)
			for(y = 0;y<tempY;y++)
				if(y<hx-x)
					imgOutX[y][x] = ON;
	}
	else
	{
		for(x=0;x < hx;x++)
			for(y = 0;y<tempY;y++)
				if(y<hx-x)
					imgOutX[y][x] = ON;
	}


	ImageOut (imgX, imgOX);

	p =q = imgX;
	while (*p != '\0') p++;
	while (*p != '_') p--; *p = '\0';
	imgY = strcat (q,imgY);

	imgOY = ImageAlloc (heightI, hx, 8);
	imgOutY = ImageGetPtr (imgOY);

	for (y = 0; y < heightI; y++)
		for (x = 0; x < hx; x++)
			imgOutY[y][x] = ON;

	for (y = 0; y < heightI; y++)
		for (x = 0; x < hx-5; x++)
			if (imgIn[y][x] == OFF)
				imgOutY[y][x] = OFF;
	if (tempX > tempY)
	{
		for(x = hx; x>0; x--)
			for(y = hy; y < heightI; y++)
				if(y-hy > hx-x)
					imgOutY[y][x] = ON;
	}
	else
	{
		for(x=hx; x>0; x--)
			for(y = hy; y<heightI; y++)
				if(y-hy > hx-x)
					imgOutY[y][x] = ON;
	}


	ImageOut (imgY, imgOY);
#ifdef verbose
	//printf("%ld\n",axis_width_x );
	//printf("%ld\n",axis_width_y);
#endif
	return (0);
}



int axis_width(long* profile, long profile_length,long *axis, long *axis1)//axis 1 to be used if there is a bounding box around the curve region
{
	long i,j;
	int axis_width=1;
	long *indexed_profile[profile_length];
	long *firstderivative[profile_length];

	for (i=0;i<profile_length;i++)
	{	
		long *p = calloc(2,sizeof(long));
		p[0] = profile[i];
		p[1] = i;
		indexed_profile[i] = p;
	}

	for (i=0;i<profile_length-1;i++)
	{	
		long *p = calloc(2,sizeof(long));
		p[0] = profile[i] - profile[i+1];
		p[1] = i;
		firstderivative[i] = p;
	}
	quickSort(indexed_profile, profile_length,0);
	quickSort(firstderivative, profile_length-1,1);


#ifdef verbose
	FILE* fp = fopen("profile.txt","w");
	for(i = 0; i<profile_length;i++)
		fprintf(fp, "%ld\n", profile[i]);
	fclose(fp);
#endif

	for(i = profile_length-1;i>=0; i-- )
	{
		if((*indexed_profile[i] - *indexed_profile[i-1]< 0.05* *indexed_profile[profile_length-1]) && (abs(indexed_profile[i][1]-indexed_profile[i-1][1])<=5))
			axis_width++;
		else
			break;
	}
	//printf("firstderivative[0][0]=%d,firstderivative[1][0]=%d\n",firstderivative[0][0],firstderivative[1][0]);
	if((firstderivative[0][0] - firstderivative[1][0]) < 0.08* firstderivative[0][0]){
		if(*axis == 1){//for x axis
			if(firstderivative[0][1] > firstderivative[1][1]){
				*axis = firstderivative[1][1];
				*axis1 = firstderivative[0][1];}
			else{
				*axis = firstderivative[0][1];
				*axis1 = firstderivative[1][1];}
		}
		else { //for y axis
			if(firstderivative[0][1] > firstderivative[1][1]){
				*axis = firstderivative[0][1];
				*axis1 = firstderivative[1][1];}
			else{
				*axis = firstderivative[1][1];
				*axis1 = firstderivative[0][1];}
		}
	}
	else
		*axis = (indexed_profile[i][1]+indexed_profile[profile_length-1][1])/2;

	for(i=0;i<profile_length;i++)
	{
		free(indexed_profile[i]);
	}

	return axis_width;
}

void quickSort(long *numbers[], long array_size, int descending)
{
	q_sort(numbers, 0, array_size - 1);
	long i,j,k;
	if(descending)
	{
		for(i=0; i<array_size/2;i++)
		{
			j = numbers[array_size-i-1][0];
			k = numbers[array_size-i-1][1];
			numbers[array_size-i-1][0] = numbers[i][0];
			numbers[array_size-i-1][1] = numbers[i][1];
			numbers[i][0] = j;
			numbers[i][1] = k;
		}
	}
}



void q_sort(long *numbers[], long left, long right)
{
	long pivot,pivot_index, l_hold, r_hold;

	l_hold = left;
	r_hold = right;
	pivot = *numbers[left];
	pivot_index = numbers[left][1];
	while (left < right)
	{
		while ((*numbers[right] >= pivot) && (left < right))
			right--;
		if (left != right)
		{
			numbers[left][0] = numbers[right][0]; numbers[left][1] = numbers[right][1];
			left++;
		}
		while ((*numbers[left] <= pivot) && (left < right))
			left++;
		if (left != right)
		{
			numbers[right][0] = numbers[left][0]; numbers[right][1] = numbers[left][1];
			right--;
		}
	}
	*numbers[left] = pivot;
	numbers[left][1] = pivot_index;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot)
		q_sort(numbers, left, pivot-1);
	if (right > pivot)
		q_sort(numbers, pivot+1, right);
}


/* USAGE:       function gives instructions on usage of program
*                    usage: usage (flag)
*              When flag is 1, the long message is given, 0 gives short.
*/

long
usage (flag)
short flag;                /* flag =1 for long message; =0 for short message */
{

	/* print short usage message or long */
	printf ("USAGE: profile inimg outimg out_content_img [-h || -v] [-s SIZE] [-p] [-L]\n");
	if (flag == 0)
		return (-1);

	printf ("\nprofile determines the horizontal or vertical profile\n");
	printf ("of a binary image, that is the summation of ON pixel values along\n");
	printf ("the y-axis or the x-axis respectively; default is horizontal.\n\n");
	printf ("ARGUMENTS:\n");
	printf ("    inimg: input image filename (TIF)\n");
	printf ("   outimg: output image filename (TIF)\n\n");
	printf ("OPTIONS:\n");
	printf ("  [-h || -v]: horizontal or vertical profile respectively.\n");
	printf ("     -s SIZE: height of horizontal profile or width of vertical\n");
	printf ("              profile (default = %d)\n", PROFILE_HEIGHT);
	printf ("          -p: PRINT DATA FLAG if set, prints profile heights.\n");
	printf ("          -L: print Software License for this module\n");

	return (-1);
}


/* INPUT:       function reads input parameters
*                  usage: input (argc, argv, &horizOrVert, &profHeight)
*/

#define USAGE_EXIT(VALUE) {usage (VALUE); return (-1);}

long
input (argc, argv, horizOrVert, profHeight, printFlag)
int argc;
char *argv[];
short *horizOrVert;        /* flag =0 for horizontal or =1 for vertical */
long *profHeight;          /* height of profile for display */
short *printFlag;          /* if =1, prints profile data; otherwise no */
{
	long n;

	if (argc == 1)
		USAGE_EXIT (1);

	return (0);
}
