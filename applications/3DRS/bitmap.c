//########################################################################
//### Program:   Algorithms
//### Author:    C. Nugteren
//### Institute: Eindhoven University of Technology
//### Date:      22-02-2011
//### Filename:  bitmap.cu
//### Contents:  This file contains the BMP I/O functions. It includes a
//###            function to read BMP data to file.
//### Reference: http://parse.ele.tue.nl/
//########################################################################

//########################################################################
//### Includes
//########################################################################

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#pragma pack(1)

//########################################################################
//### Structures used in the BMP functions
//########################################################################

typedef struct {
	short type;
	int size;
	short reserved1;
	short reserved2;
	int offset;
} BMPHeader;
typedef struct {
	int size;
	int width;
	int height;
	short planes;
	short bitsPerPixel;
	unsigned compression;
	unsigned imageSize;
	int xPelsPerMeter;
	int yPelsPerMeter;
	int clrUsed;
	int clrImportant;
} BMPInfoHeader;

//########################################################################
//### Function to save BMP data to a file (RGBA)
//########################################################################

void save_bitmap_RGBA(TYPE4 ** image, unsigned int number, char* dir, char* name, unsigned int width, unsigned int height) {

	// Variable declarations
	FILE *fd_out;
	char filename[500];
  unsigned long ulBitmapSize = (height * width * 3)+54; 
  char ucaBitmapSize[4];
  ucaBitmapSize[3]= (ulBitmapSize & 0xFF000000) >> 24;
  ucaBitmapSize[2]= (ulBitmapSize & 0x00FF0000) >> 16;
  ucaBitmapSize[1]= (ulBitmapSize & 0x0000FF00) >> 8;
  ucaBitmapSize[0]= (ulBitmapSize & 0x000000FF);
  	
	// Load output file
  sprintf(filename, "%s/o%02d_%s.bmp", dir, number, name);
	fd_out = fopen(filename, "wb");
 		
	// Write BMP header
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 66, 77, ucaBitmapSize[0], ucaBitmapSize[1], ucaBitmapSize[2], ucaBitmapSize[3], 0, 0, 0, 0); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 54, 0, 0, 0, 40, 0 , 0, 0, (width & 0x00FF), (width & 0xFF00)>>8); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 0, 0, (height & 0x00FF), (height & 0xFF00) >> 8, 0, 0, 1, 0, 24, 0); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	fprintf(fd_out,"%c%c%c%c", 0, 0 ,0, 0);

	// Save RGB data to output file	
	for(unsigned int y=0;y<height;y++) {
		for(unsigned int x=0;x<width;x++)	{
			fputc(image[x][y].z,fd_out);
			fputc(image[x][y].y,fd_out);
			fputc(image[x][y].x,fd_out);
		}
		for(unsigned int j=0;j<width%4;j++) {
			fputc(0,fd_out);
		}
	}

	// Clean up
	fclose(fd_out);
}

//########################################################################
//### Function to save BMP data to a file (grayscale)
//########################################################################

void save_bitmap_GS(TYPE ** image, unsigned int number, char* dir, char* name, unsigned int width, unsigned int height) {

	// Variable declarations
	FILE *fd_out;
	char filename[500];
  unsigned long ulBitmapSize = (height * width * 3)+54; 
  char ucaBitmapSize[4];
  ucaBitmapSize[3]= (ulBitmapSize & 0xFF000000) >> 24;
  ucaBitmapSize[2]= (ulBitmapSize & 0x00FF0000) >> 16;
  ucaBitmapSize[1]= (ulBitmapSize & 0x0000FF00) >> 8;
  ucaBitmapSize[0]= (ulBitmapSize & 0x000000FF);
  	
	// Load output file
  sprintf(filename, "%s/o%02d_%s.bmp", dir, number, name);
	fd_out = fopen(filename, "wb");
 		
	// Write BMP header
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 66, 77, ucaBitmapSize[0], ucaBitmapSize[1], ucaBitmapSize[2], ucaBitmapSize[3], 0, 0, 0, 0); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 54, 0, 0, 0, 40, 0 , 0, 0, (width & 0x00FF), (width & 0xFF00)>>8); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 0, 0, (height & 0x00FF), (height & 0xFF00) >> 8, 0, 0, 1, 0, 24, 0); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
	fprintf(fd_out,"%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	fprintf(fd_out,"%c%c%c%c", 0, 0 ,0, 0);

	// Save RGB data to output file	
	for(unsigned int y=0;y<height;y++) {
		for(unsigned int x=0;x<width;x++)	{
			fputc(image[x][y],fd_out);
			fputc(image[x][y],fd_out);
			fputc(image[x][y],fd_out);
		}
		for(unsigned int j=0;j<width%4;j++) {
			fputc(0,fd_out);
		}
	}

	// Clean up
	fclose(fd_out);
}

//########################################################################
//### Function to load BMP data from a file (grayscale)
//########################################################################

TYPE ** load_bitmap_GS(uint *width, uint *height, char* dir, uint id) {

	// Variable declarations
	BMPHeader hdr;
	BMPInfoHeader infoHdr;
	FILE *fd;
	uint i, y, x;
	
	// Select input file
	if (id == 1) { fd = fopen("images/input1.bmp","rb"); }
	else if (id == 2) { fd = fopen("images/input2.bmp","rb"); }
	else if (id == 3) { fd = fopen("images/input3.bmp","rb"); }
	else if (id >= 500 && id < 600) {
	  char filename[500]; sprintf(filename,"%s/renata%03d.bmp", dir ,id-500);
		fd = fopen(filename,"rb");	
	}
	
	// Open the file and scan the contents
	if(!(fd)) { printf("***BMP load error: file access denied***\n"); exit(0);	}
	fread(&hdr, sizeof(hdr), 1, fd);
	if(hdr.type != 0x4D42) { printf("***BMP load error: bad file format***\n"); exit(0); }
	fread(&infoHdr, sizeof(infoHdr), 1, fd);
	if(infoHdr.bitsPerPixel != 24) { printf("***BMP load error: invalid color depth*** \n"); exit(0); }
	if(infoHdr.compression) { printf("***BMP load error: compressed image***\n"); exit(0); }
	(*width)  = infoHdr.width;
	(*height) = infoHdr.height;

	// Allocate memory to store the BMP's contents
	TYPE ** image = (TYPE **)malloc((*width) * sizeof(*image));
	TYPE * image_1D = (TYPE *)malloc((*width) * (*height) * sizeof(TYPE));
	for(i=0; i<(*width); i++) {
		image[i] = &image_1D[i*(*height)];
	}

	// Read the BMP file and store the contents
	fseek(fd, hdr.offset - sizeof(hdr) - sizeof(infoHdr), SEEK_CUR);
	for(y = 0; y < (*height); y++) {
		for(x = 0; x < (*width); x++)	{
			image[x][y] = ((TYPE)fgetc(fd));
			fgetc(fd);
			fgetc(fd);
		}
		for(x = 0; x < (4 - (3 * (*width)) % 4) % 4; x++)	{
			fgetc(fd);
		}
	}

	// Exit the function and clean-up
	if(ferror(fd)) {
		printf("***Unknown BMP load error.***\n");
		free(image[0]);
		free(image);
		exit(0);
	}
	fclose(fd);
	return image;
}

//########################################################################
