/******************************************************************
 *
 * A simple PGM reader/writer
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm.h"
#include "driver_common.h"

int main(int argc, char *argv[]){

  // pointer to the image 
  unsigned char *image;
  // image width (original width without padding)
  int w;
  // image height (original height without padding)
  int h;
  // max gray value of the PGM, usually it is 255.
  int grayMax;

  /* meta file pointer */
  FILE* meta;

  /* common variables */
  int i;

  int  dmem_sec_num=1;
  int  dmem_sec_size[1];

  if(argc!=4){
    printf("Usage: dmem_dump input.dmem_result input.dmem_meta output.pgm\n");
    return -1;
  }

  meta = fopen(argv[2],"r");

  fscanf(meta,"%d",&w);
  fscanf(meta,"%d",&h);

  dmem_sec_size[0] = w*h*sizeof(unsigned char);

  dmem_section_t* secs = ReadDmemInitFile(argv[1],dmem_sec_size,dmem_sec_num);


  image = (unsigned char*)malloc(w*h*sizeof(unsigned char));
  grayMax = 255;
  for(i = 0; i < w*h; i++){
    image[i] = secs[0].buff[i];
  }

  writePGM(image, argv[3], w, h, grayMax);

  free(image);
  fclose(meta);

  return 0;
}
