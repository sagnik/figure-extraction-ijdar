
/*Purpose: */
/*Binarize gray-level images */

/*Features: */
/* Global threshold: One threshold value is used for every pixel in an image */
/* Adaptive threshold selection: A global threshold value is calculated based on the intensity histogram of an image */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* If verbose is defined, there are screen ouputs followed by each step which are useful for debugging purposes*/
//#define verbose


#define EDGE 255
#define NOEDGE 0 //black

// Let the percentage of black pixels in an image falls into a predefined range
// after binarization

/* The percentage of black pixels in one image should be less than HIGH_PERCNETILE*/
#define HIGH_PERCENTILE 0.6

/* The percentage of black pixels in one image is hopefully above the LOW_PERCENTILE */
#define LOW_PERCENTILE 0.08

/* Measuring the percentage of black pixels with a particular intensity value */
#define MIN_PERCENTILE 0.01

/* #define THRESHOLD 220 */
// Do not use fixed threshold
// Adaptively select the threshold value instead



/*Function declaration*/
int read_pgm_image(char *infilename, unsigned char **image, int *rows,
		   int *cols);
int write_pgm_image(char *outfilename, unsigned char *image, int rows,
		    int cols, char *comment, int maxval);
/*Function declaration ends*/

main(int argc, char *argv[])
{
   char *infilename = NULL;  /* Name of the input image */
   char *outfilename = NULL; /* Name of the output image */

   unsigned char *image;

   int rows, cols;           /* The dimensions of the image. */
   int tmp;
   int i,j;

   unsigned char threshold, tmp_intensity;
   int hist[256]; /* histogram of the intensity values in the image */
   int accum_hist[256];
 /* accumulated histogram: records the number of pixels with intensity values less than or 
    equal */
   int size, high_cut_point,low_cut_point;
   unsigned char high_threshold, low_threshold;

   int peak;
   unsigned char peak_intensity;


   /****************************************************************************
   * Get the command line arguments.
   ****************************************************************************/
   if(argc < 3)
     {
       fprintf(stderr,"\n<USAGE> %s infilename outfilename\n",argv[0]);     
       exit(1);
     }

   infilename = argv[1];
   outfilename = argv[2];


   /****************************************************************************
   * Read in the image. This read function allocates memory for the image.
   ***************************************************************************/

   if(read_pgm_image(infilename, &image, &rows, &cols) == 0){
      fprintf(stderr, "Error reading the input image, %s.\n", infilename);
      exit(1);
   }

#ifdef verbose
   printf("rows: %d, cols: %d\n",rows,cols);
#endif

   /* hist stores the number of pixels with each intensity value */
   /* accum_hist stores the number of pixels with intensity equal or less than each value */

   /*initialize hist and accum_hist*/
   for(i=0;i<256;i++)
     {
       hist[i]=0;
       accum_hist[i]=0;
     }

   /*calculate the statistics of pixel intensity values */
   size=rows*cols;
   for(i=0;i<size;i++)
     {
       tmp_intensity=image[i];
       hist[tmp_intensity]++;
       for(j=tmp_intensity;j<256;j++)
	 {
	   accum_hist[j]++;
	 }
     }


   /* calculate the peak intensity based on the histogram */
   peak=hist[0];

   for(i=1;i<255;i++)
     {
       if(hist[i]>peak)
	 {
	   peak=hist[i];
	   peak_intensity=i;	   
	 }
     }

   /*select threshold value */
   high_cut_point=HIGH_PERCENTILE*size;
   low_cut_point=LOW_PERCENTILE*size;

   

#ifdef verbose
   printf("rows:%d cols:%d size: %d low_cut:%d high_cut:%d\n",rows,cols,size,low_cut_point,high_cut_point);
   for(i=0;i<256;i++)
     {
       printf("hist[%d]=%d\n",i,hist[i]);
     }

   printf("peak:%d peak_intensity:%d\n",peak,peak_intensity);
#endif

   //binarization based on intensity distribution
   //Case 1: based on percentile
   low_threshold=0;
   while(accum_hist[low_threshold]<low_cut_point)
     {
       low_threshold++;
       }

   high_threshold=low_threshold;
   while(accum_hist[high_threshold]<high_cut_point)
     {
       high_threshold++;
     }

   if(low_threshold==high_threshold)
     {
       threshold=low_threshold;
     }
   else
     {
       if((accum_hist[low_threshold]-hist[low_threshold])>=(MIN_PERCENTILE*size))
	 {
	   threshold=low_threshold;
	 }
       else
	 {
	   threshold=high_threshold;
	 }
     }

#ifdef verbose
   printf("%d %d %d\n",low_threshold,high_threshold,threshold);
#endif

   //Case 2: based on the peak in the histogram
   /*   threshold=peak_intensity-1; */

#ifdef verbose
   printf("threshold:%d\n",threshold);
#endif

	long background =0;
   /*threshold value based binarization */
   for(i=0;i<size;i++)
     {
       if(image[i]<threshold)
	     {
	       image[i]=EDGE;
	     }
	   else
	     {
	       image[i]=NOEDGE;
		background++;
	     }
     }
	printf("\nBlack area:%f\n",((float)background/(float)size)*100);

   write_pgm_image(outfilename,image,rows,cols,NULL,255);

	


}


/* Funciton: read_pgm_iamge */
/* Purpose: */
/* Open a binary PGM image file */
/* Allocate memory for storing the image file */
/* Extract the numbe of rows, cols of the image */
/* Return 1 upon sucess, otherwise return 0 */

int read_pgm_image(char *infilename, unsigned char **image, int *rows,
    int *cols)
{
   FILE *fp;
   char buf[71];

   /* Open the input image file*/


   if((fp = fopen(infilename, "r")) == NULL)
     {

         fprintf(stderr, "Error reading the file %s in read_pgm_image().\n",
            infilename);
         return(0);
     }


   /* Verify the magic number of the PGM image file */

   fgets(buf, 70, fp);
   if(strncmp(buf,"P5",2) != 0){
      fprintf(stderr, "The file %s is not in PGM format in ", infilename);
      fprintf(stderr, "read_pgm_image().\n");
      fclose(fp);
      return(0);
   }

   /* Skip all comment lines */
   do
     {
       fgets(buf, 70, fp);
     }while((buf[0] == '#')||(buf[0]=='\n'));

   /* Read in number of cols and number of rows*/
   sscanf(buf, "%d %d", cols, rows);

   /* Skip all comment lines */
   do
     {
       fgets(buf, 70, fp);
     }while(buf[0] == '#');


   /* Allocate memory to store the content of image */

   if(((*image) = (unsigned char *) malloc((*rows)*(*cols))) == NULL){
      fprintf(stderr, "Memory allocation failure in read_pgm_image().\n");
      fclose(fp);
      return(0);
   }

   /* Read in image data */
   if((*rows) != fread((*image), (*cols), (*rows), fp)){
      fprintf(stderr, "Error reading the image data in read_pgm_image().\n");
      fclose(fp);
      free((*image));
      return(0);
   }

   fclose(fp);
   return(1);
}

/* Funciton: write_pgm_iamge */
/* Purpose: */
/* write a binary PGM image file */
/* Input: */
/* output image name, buffer address, number of rows and cols, comment, and the maximum intensity value */
/* Return 1 upon sucess, otherwise return 0 */

int write_pgm_image(char *outfilename, unsigned char *image, int rows,
    int cols, char *comment, int maxval)
{
   FILE *fp;

   /* open the output image file for writing */

   if(outfilename == NULL) fp = stdout;
   else{
      if((fp = fopen(outfilename, "w")) == NULL){
         fprintf(stderr, "Error writing the file %s in write_pgm_image().\n",
            outfilename);
         return(0);
      }
   }

   /* Write the header into the image output file */   

   fprintf(fp, "P5\n%d %d\n", cols, rows);
   if(comment != NULL)
      if(strlen(comment) <= 70) fprintf(fp, "# %s\n", comment);
   fprintf(fp, "%d\n", maxval);

   /* Write the image data to the file */  

   if(rows != fwrite(image, cols, rows, fp)){
      fprintf(stderr, "Error writing the image data in write_pgm_image().\n");
      if(fp != stdout) fclose(fp);
      return(0);
   }

   if(fp != stdout) fclose(fp);
   return(1);
}
