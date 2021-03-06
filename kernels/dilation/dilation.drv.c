#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

int main(int argc, char* argv[]) {

  if(argc!=3){
    printf("Usage: dilation input.pgm output.pgm\n");
    return -1;
  }

  // pointer to the input image
  unsigned char *image_in;
  // pointer to the output image
  unsigned char *image_out;
  // image width (original width without padding)
  int w;
  // image height (original height without padding)
  int h;
  // max gray value of the PGM, usually it is 255. 
  int grayMax;

  readPGM(&image_in, argv[1], &w, &h, &grayMax);

  printf("Image File Name: %s\n",argv[1]);
  printf("Image Width: %d\n",w);
  printf("Image Height: %d\n",h);

  image_out=(unsigned char*)malloc(w*h*sizeof(unsigned char));

  dilation((unsigned char*)image_in, w, h, (unsigned char*)image_out, 2);

  writePGM(image_out, argv[2], w, h, grayMax);

  free(image_in);
  free(image_out);

  return 0;
}
