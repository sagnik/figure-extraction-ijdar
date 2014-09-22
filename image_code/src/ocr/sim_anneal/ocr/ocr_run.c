/*
WJB 06/07
run OCR, based on ->


Fast Artificial Neural Network Library (fann)
Copyright (C) 2003 Steffen Nissen (lukesky@diku.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>

#include "fann.h"

double *a_ptr;

double *BinRead(FILE *fin, int n);
int FileOfDoublesSize(FILE *fin);
void DispVector(double *ptr, int n);

int main()
{

  FILE *fptr1;
  char filename1[]="ocr_data.bin";

 if ((fptr1 = fopen(filename1, "r+b")) == NULL){
    printf("Can't open input file\n");
    return 0;
  }
	 

	int f_size=FileOfDoublesSize(fptr1);


a_ptr = BinRead(fptr1,f_size);

DispVector(a_ptr,f_size);

printf("size of record is %i\n",f_size/3);

	fann_type *calc_out;
	fann_type input[3];

	unsigned int i;
	unsigned int j;	
	int ret = 0;

	struct fann *ann;
	
	printf("Running network.\n");

	ann = fann_create_from_file("ocr_dat.net");

	if(!ann)
	{
		printf("Error running ann --- ABORTING.\n");
		return 0;
	}

	fann_print_connections(ann);
	fann_print_parameters(ann);

	printf("Records->\n");

for(i=0;i<f_size/3;i++){

input[0]=*(a_ptr+i*3);
input[1]=*(a_ptr+i*3+1);
input[2]=*(a_ptr+i*3+2);

calc_out=fann_run(ann,input);

printf("%f, %f, %f, %f, %f, %f, %f, %f\n",round(calc_out[0]),round(calc_out[1]),round(calc_out[2]),round(calc_out[3]),round(calc_out[4]),round(calc_out[5]),round(calc_out[6]),round(calc_out[7]));
}

	

	printf("Cleaning up.\n");

fann_destroy(ann);

	return ret;
}

int FileOfDoublesSize(FILE *fin){
    
int n = -1; /* leaves off EOF */
    double x;
  while(!feof(fin)){
    fread(&x, sizeof(double), 1, fin); 
      n++;
      }
  
     /* reset the file pointer */
fseek(fin, 0, SEEK_SET);

  return n;

  }

double *BinRead(FILE *fin, int n)
      {
 
	
 double *x_ptr;
 
x_ptr = malloc(n * sizeof(double));
 

 fread(x_ptr, sizeof(double), n, fin);
 
  /* reset the file pointer */
	   fseek(fin, 0, SEEK_SET);

 return x_ptr;
	 }

void DispVector(double *ptr, int n)
{
     int i;
     for (i=0; i < n; i++){
       printf(" %f\n",*( ptr + i));

     }

return;
}
