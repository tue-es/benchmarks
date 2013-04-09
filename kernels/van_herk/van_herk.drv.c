/*
 *  Eindhoven University of Technology, The Netherlands
 *
 *  Name            :   van_herk.cc
 *
 *  Author          :   Gert-Jan van den Braak (G.J.W.v.d.Braak@tue.nl)
 *
 *  Date            :   18 July 2012
 *
 *  Description     :   CPU implementation of the Van Herk / Gil-Werman morphology operations
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

#include "van_herk.h"

int main(int argc, char* argv[])
{

  if(argc!=4){
    printf("Usage: van_herk input.pgm opening.pgm closing.pgm\n");
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


  // allocate all possible output and intermediate data, init to 0 to detect bugs
  unsigned char *vh_inter    = (unsigned char*)malloc(width*height*sizeof(unsigned char));
  unsigned char *vh_output = (unsigned char*)malloc(width*height*sizeof(unsigned char));
  unsigned char *vh_opening   = (unsigned char*)malloc(width*height*sizeof(unsigned char));
  unsigned char *vh_closing   = (unsigned char*)malloc(width*height*sizeof(unsigned char));

  memset(vh_inter,    0, width*height*sizeof(unsigned char));
  memset(vh_output,    0, width*height*sizeof(unsigned char));
  memset(vh_opening,   0, width*height*sizeof(unsigned char));
  memset(vh_closing,   0, width*height*sizeof(unsigned char));
	
  // OPENING
  //erosion
  van_herk_h(image, width, height, vh_inter, ERODE);
  van_herk_v(vh_inter, width, height, vh_output, ERODE);
  //dilation
  van_herk_h(vh_output, width, height, vh_inter, DILATE);
  van_herk_v(vh_inter, width, height, vh_opening, DILATE);

  // CLOSING
  //dilation
  van_herk_h(image, width, height, vh_inter, DILATE);
  van_herk_v(vh_inter, width, height, vh_output, DILATE);
  //erosion
  van_herk_h(vh_output, width, height, vh_inter, ERODE);
  van_herk_v(vh_inter, width, height, vh_closing, ERODE);


  writePGM(vh_opening, argv[2], width, height, grayMax);
  writePGM(vh_closing, argv[3], width, height, grayMax);
	
  // clean up 
  if(vh_inter)    free(vh_inter);
  if(vh_output)   free(vh_output);
  if(vh_opening)   free(vh_opening);
  if(vh_closing)   free(vh_closing);

  free(image);

  return 0;

}
