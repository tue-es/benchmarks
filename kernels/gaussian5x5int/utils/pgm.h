#ifndef _PGM_H_
#define _PGM_H_

int readPGM(unsigned char **image, char *filename,
	    int *imageWidth, int *imageHeight, int *grayMax);

int writePGM(unsigned char *image, char *filename,
	     int imageWidth, int imageHeight, int grayMax);

#endif//_PGM_H_
