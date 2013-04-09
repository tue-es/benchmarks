/*
 *  Eindhoven University of Technology, The Netherlands
 *
 *  Name            :   van_herk.cc
 *
 *  Author          :   Gert-Jan van den Braak (G.J.W.v.d.Braak@tue.nl)
 *
 *  Date            :   18 July 2012
 *
 *  Description     :   CPU implementation of the Van Herk / Gil-Werman morphology operations
 *
 */


/***************************************************************
 * Original paper of M. van herk:
 * A fast algorithm for local minimum and maximum filters on rectangular and octagonal kernels
 * in Pattern Recognition Letters 1992
 * http://dx.doi.org/10.1016/0167-8655(92)90069-C
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "van_herk.h"

#define MAX(a,b) ((a>b) ? a : b)
#define MIN(a,b) ((a<b) ? a : b)

#define N (2)

/*****
Compilation: g++ -O3 -Wall van_herk.cc -o van_herk
*****/


// erode and dilate only differ in MIN or MAX operator, use C++ templates to select the right one
unsigned char minMax(const unsigned char a, const unsigned char b, morphoperation op) {
    return (op == ERODE) ? MIN(a,b) : MAX(a,b);
}


void van_herk_h(unsigned char *image, int width, int height, unsigned char *output, morphoperation op)
{
	int i,x,y=0;
	
	// loop over all image lines
	for(y=0; y<height; y++) 
	{
		// loop over all row segments
		for(x=N; x<width-(3*N); x+=(2*N+1)) 
		{
			unsigned char s[2*N+1+1];
			unsigned char r[2*N+1+1];
			
			for(i=2*N; i>=0; i--) {
				if(i < 2*N) {
				  s[i]     = minMax(image[y*width+x -N+i],      s[i+1    ], op);
				  r[2*N-i] = minMax(image[y*width+x + (3*N-i)], r[2*N-i-1], op);
				}
				else {
					s[i] = image[y*width+x+N];
					r[0] = image[y*width+x+N];
				}
			}
		
			for(i=0; i<(2*N+1); i++) {
			  output[y*width+x+i] = minMax(s[i], r[i], op);
			}
		}
	}
}


void van_herk_v(unsigned char *image, int width, int height, unsigned char *output, morphoperation op)
{
	int i,x,y=0;
	
	// loop over all image lines
	for(y=N; y<height-(3*N); y+=(2*N+1))
	{
		// loop over all row segments
		for(x=0; x<width; x++)
		{			
			unsigned char s[2*N+1+1];
			unsigned char r[2*N+1+1];
			
			for(i=2*N; i>=0; i--) {
				if(i < 2*N) {
				  s[i]     = minMax(image[(y-N+i)*width+x],     s[i+1    ], op);
				  r[2*N-i] = minMax(image[(y+(3*N-i))*width+x], r[2*N-i-1], op);
				}
				else {
					s[i] = image[(y+N)*width+x];
					r[0] = image[(y+N)*width+x];
				}
			}
		
			for(i=0; i<(2*N+1); i++) {
			  output[(y+i)*width+x] = minMax(s[i], r[i], op);
			}
		}	
	}
}


