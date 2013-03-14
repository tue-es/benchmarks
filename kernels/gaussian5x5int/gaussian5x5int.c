
void
gaussian5x5int(unsigned char * out, unsigned char * in, int w, int h) {

  int i, j, k;
  /* temperary image */
  unsigned char* tmp;

  tmp = (unsigned char *)malloc(w*h*sizeof(unsigned char));

  /* float point verion */
  /* float coef[5] = {0.061, 0.242, 0.383, 0.242, 0.061}; */

  /* fix point verion */
  /* int coef[5] = {62, 248, 392, 248, 62}; */
  /* multiply the floating point version by 1024 */
  /* requires shifting 10 bits to the right later */

  int coef[5] = {62, 248, 392, 248, 62};
  int accu;

  for(i = 0; i < h; i ++) {
    for(j = 0; j < w; j ++) {
      if(j > 1 && j < w-2){ // avoid boarder columns
  	accu = 0;
  	for(k = -2; k <= +2; k++){
  	  accu += (int)(in[i*w+j+k])*coef[k+2];
  	}
  	tmp[i*w+j] = (unsigned char)(accu>>10);
      }else{ // copy the boarder columns
	tmp[i*w+j] = in[i*w+j];
      }
    }
  }

  for(i = 0; i < h; i ++) {
    if(i > 1 && i < h-2){ // aoivd boarder rows
      for(j = 0; j < w; j ++) {
  	accu = 0;
  	for(k = -2; k <= +2; k++){
  	  accu += (int)(tmp[(i+k)*w+j])*coef[k+2];
  	}
  	out[i*w+j] = (unsigned char)(accu>>10);
      }
    }else{ //copy the boarder rows
      for(j = 0; j < w; j ++) {
	out[i*w+j] = tmp[i*w+j];
      }
    }
  }

  free(tmp);

}
