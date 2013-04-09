/*
 *  Eindhoven University of Technology, The Netherlands
 *
 *  Name            :   histogram.c
 *
 *  Author          :   Gert-Jan van den Braak (G.J.W.v.d.Braak@tue.nl)
 *
 *  Date            :   9 April 2013
 *
 *  Description     :   Basic CPU histogram implementation
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

#define BINS (256)

void histogram_calculation(unsigned char *image, int width, int height, 
                           unsigned int *histogram)
{
	int x,y;
	for(y=0; y<height; y++) {
		for(x=0; x<width; x++) {
			unsigned int index = image[y*width+x];
			histogram[index]++;
		}
	}
}

int main(int argc, char* argv[])
{
  int i;
  
  if(argc!=2){
    printf("Usage: histogram input.pgm\n");
    return -1;
  }

  // pointer to the input image
  unsigned char *image;
  // image width (original width without padding)
  int width;
  // image height (original height without padding)
  int height;
  // max gray value of the PGM, usually it is 255. 
  int grayMax;

  readPGM(&image, argv[1], &width, &height, &grayMax);

  printf("Image File Name: %s\n",argv[1]);
  printf("Image Width: %d\n",width);
  printf("Image Height: %d\n",height);

  // allocate the final histogram
  unsigned int *histogram = (unsigned int*)malloc(BINS*sizeof(unsigned int));
  memset(histogram, 0, BINS*sizeof(unsigned char));
  
  // calculate the histogram
  histogram_calculation(image, width, height, histogram);

  // print the results
  printf("\n");
  printf("index - occurance\n");
  printf("=================\n");
  for(i=0; i<BINS; i++) {
	printf(" %3d  %8d\n", i, histogram[i]);
  }
  
  // clean up 
  free(image);
  free(histogram);
  return 0;
}
