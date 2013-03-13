/******************************************************************
 *
 * A simple PGM reader/writer
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm.h"

int main(int argc, char *argv[]){

  // pointer to the image 
  unsigned char *image;
  // image width (original width without padding)
  int w;
  // image height (original height without padding)
  int h;
  // max gray value of the PGM, usually it is 255.
  int grayMax;

  /* output file pointer */
  FILE* out;
  /* meta file pointer */
  FILE* meta;
  /* output file size in bytes */
  int bytes;
  /* common variables */
  int i;

  if(argc!=4){
    printf("Usage: dmem_init input.pgm out.dmem_init out.dmem_meta\n");
    return -1;
  }

  readPGM(&image, argv[1], &w, &h, &grayMax);
  printf("Image File Name: %s\n",argv[1]);
  printf("Image Width: %d\n",w);
  printf("Image Height: %d\n",h);

  bytes = w*h;
  out = fopen(argv[2],"w");
  fprintf(out,"@%x\n",bytes);
  for(i = 0; i < bytes; i++){
    fprintf(out,"%02x\n",image[i]);
  }

  meta = fopen(argv[3],"w");
  fprintf(meta,"%d\n",w);
  fprintf(meta,"%d\n",h);

  free(image);
  fclose(out);
  fclose(meta);

  return 0;
}
