#define MAX(a,b) ((a>b) ? a : b)

// basic dilation function
void dilation(unsigned char *image, int width, int height, unsigned char *output, int N)
{
	int i,j=0,x,y;
	
	for(y=N; y<height-N; y++) {
		for(x=N; x<width-N; x++) {
			
			unsigned char maxval = 0;
			for(j=-N; j<=N; j++) {
				for(i=-N; i<=N; i++) {
					maxval = MAX(maxval, image[(y+j)*width+(x+i)]);
				}
			}
			output[y*width+x] = maxval;
		}	
	}
}
