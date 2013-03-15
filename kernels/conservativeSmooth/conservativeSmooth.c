#include <stdlib.h>

void
conservativeSmooth(unsigned char * out, unsigned char * in, int w, int h) {

  int i, j, m, n;

  unsigned char min, max;

  for(i = 0; i < h; i ++) {
    for(j = 0; j < w; j ++) {
      if(i > 0 && i < h - 1 && j > 0 && j < w-1){ // avoid boarder
  	min = 255;
	max = 0;
  	for(m = -1; m <= +1; m++){
	  for(n = -1; n <= +1; n++){
	    if(m != 0 && n != 0){ // skip center pixel
	      if (in[(i+m)*w+(j+n)] <= min ){
		min = in[(i+m)*w+(j+n)];
	      }
	      if (in[(i+m)*w+(j+n)] >= max ){
		max = in[(i+m)*w+(j+n)];
	      }
	    }
	  }
  	}
	if(in[i*w+j] > max){
	  out[i*w+j] = max;
	}else if(in[i*w+j] < min){
	  out[i*w+j] = min;
	}else{
	  out[i*w+j] = in[i*w+j];
	}
      }else{ // copy the boarder
	out[i*w+j] = in[i*w+j];
      }
    }
  }

}
