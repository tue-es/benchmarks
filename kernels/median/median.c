#include <stdlib.h>

void
median(unsigned char * out, unsigned char * in, int w, int h) {

  int i, j, m, n;
  /* sorting array (optional) to find median */
  unsigned char sort[9];
  unsigned char tmp;

  for(i = 0; i < h; i ++) {
    for(j = 0; j < w; j ++) {
      if(i > 0 && i < h - 1 && j > 0 && j < w-1){ // avoid boarder
  	for(m = -1; m <= +1; m++){
	  for(n = -1; n <= +1; n++){
	    sort[(m+1)*3+(n+1)] = in[(i+m)*w+(j+n)];
	  }
  	}
  	for(m = 0; m < 8; m++){
	  for(n = 0; n < 8-m; n++){
	    if(sort[n] > sort[n+1]){
	      tmp = sort[n];
	      sort[n] = sort[n+1];
	      sort[n+1] = tmp;
	    }
	  }
	}
	out[i*w+j] = sort[4];
      }else{ // copy the boarder
	out[i*w+j] = in[i*w+j];
      }
    }
  }

}
