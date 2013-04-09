#define MIN(a,b) ((a<b) ? a : b)

// basic erosion function
void erosion(unsigned char *image, int width, int height, unsigned char *output, int N)
{
	int i,j=0,x,y;
	
	for(y=N; y<height-N; y++) {
		for(x=N; x<width-N; x++) {
			
			unsigned char minval = 255;
			for(j=-N; j<=N; j++) {
				for(i=-N; i<=N; i++) {
					minval = MIN(minval, image[(y+j)*width+(x+i)]);
				}
			}
			output[y*width+x] = minval;
		}	
	}
}
