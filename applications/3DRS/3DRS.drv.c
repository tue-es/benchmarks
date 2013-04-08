//########################################################################
//### Program:   Algorithms
//### Author:    C. Nugteren
//### Institute: Eindhoven University of Technology
//### Date:      15-03-2011
//### Filename:  main.cu
//### Contents:  This file contains the CPU host code. It calls the load
//###            BMP functions multiple times and executes the algorithms.
//###            It prints out all the performance data.
//### Reference: http://parse.ele.tue.nl/
//########################################################################

//########################################################################
//### Includes
//########################################################################

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
//#include "timers.cu"

//########################################################################
//### Settings
//########################################################################

bool verbose = true;

//########################################################################
//### Helper functions
//########################################################################

// Bound function (to edges of image)
int clip(char value, int lower, int upper) {
	if (value >= upper) {			return (int)upper-1;	}
	else if (value < lower) {	return (int)lower;	}
	else {										return (int)value;	}
}

//########################################################################
//### Recursive search block matching extra kernels (CPU)
//########################################################################

void CPU_initialize_vectors_zero(char2* vectors, uint blocks_w, uint blocks_h) {
	for (uint hv=0;hv<blocks_h;hv++) {
		for (uint wv=0;wv<blocks_w;wv++) {
			vectors[hv+wv*blocks_h].x = 0;
			vectors[hv+wv*blocks_h].y = 0;
		}
	}
}

//########################################################################
//### Function declarations from bitmap.cu
//########################################################################

TYPE ** load_bitmap_GS(uint *width, uint *height, char* dir, uint id);
void save_bitmap_GS(TYPE ** image, uint number, char* dir, char* name, uint width, uint height);
void save_bitmap_RGBA(TYPE4 ** image, uint number, char* dir, char* name, uint width, uint height);

//########################################################################
//### Function declarations from kernel_cpu.cu
//########################################################################

void CPU_3DRS(TYPE* previous_frame, TYPE* current_frame, char2* vectors, uint width, uint height, uint frame);

//########################################################################
//### Forward declarations from main.cu
//########################################################################

void start_3DRS(char* input_dir, char* output_dir, char * name);

//########################################################################
//### Main function (loads data and calls the body function multiple times)
//########################################################################

int main(int argc, char* argv[]) {

  char* input_dir;
  char* output_dir;

  if(argc!=3){
    printf("Usage: 3DRS input_dir output_dir\n");
    return -1;
  }
  input_dir=argv[1];
  output_dir=argv[2];

  // Initialization code
  if(verbose) {	printf("###Starting program.\n"); }

  // Start the 3DRS function
  start_3DRS(input_dir,output_dir,"CPU_3DRS");
		
  // Exit	
  if(verbose) {	printf("###Finished program.\n"); }	else { printf("\n"); }
}

//########################################################################
//### Special body function for 3D recursive search block matching (CPU/GPU)
//########################################################################

void start_3DRS(char* input_dir, char* output_dir, char * name) {

	// Timers
	float timer = 0;
	float timers[NUM_TIMERS];
	for (uint i=0;i<NUM_TIMERS;i++) { timers[i] = 0; }
	
	// Pre-load one frame from disk
	uint width = 0;
	uint height = 0;
	if(verbose) {	printf("###Loading frame %d...", 0); }
	TYPE ** previous_frame = load_bitmap_GS(&width, &height, input_dir, IMAGE_START);
	TYPE ** current_frame = 0;
	
	// Pre-defined variables
	uint blocks_w = width/BLOCKSIZE;
	uint blocks_h = height/BLOCKSIZE;
		
	// Create space for the motion vectors
	char2 ** vectors = (char2 **)malloc(blocks_w*sizeof(*vectors));
	char2 * vectors_1D = (char2 *)malloc(blocks_w*blocks_h*sizeof(char2));
	for(uint i=0;i<blocks_w;i++)	{ vectors[i] = &vectors_1D[i*blocks_h];	}
	
	// Create space for the visualization image and output file
	TYPE4 ** visualization = (TYPE4 **)malloc(width*sizeof(*visualization));
	TYPE4 * visualization_1D = (TYPE4 *)malloc(width*height*sizeof(TYPE));
	for(uint i=0;i<width;i++)	{ visualization[i] = &visualization_1D[i*height];	}
		
	// Initialize motion vectors to zero
	CPU_initialize_vectors_zero(vectors[0], blocks_w, blocks_h);	
	
	// Start 3DRS
	if(verbose) {	printf("###Starting kernel..."); }

		
		// For each frame in the image
		for (uint frame=0;frame<IMAGES;frame++) {
		  if(verbose) {	printf("###Loading frame %d...", frame+1); }
	
			// Load the current frame from disk
			//event_timer = start_timer();
		  current_frame = load_bitmap_GS(&width, &height, input_dir, IMAGE_START+frame+1);
			//timers[0] = timers[0] + stop_timer(event_timer);
			
			// Run the kernel for this frame				
			//start = start_timer();		
			CPU_3DRS(previous_frame[0], current_frame[0], vectors[0], width, height, frame);
			//timer = timer + stop_timer(start);
			
			// Print the vector data and save to disk
			if(verbose) {
				for(uint h=0;h<height;h++) {
					for(uint w=0;w<width;w++) {
						visualization[h][w].x = current_frame[h][w]*0.5+64+clip(16*vectors[h/BLOCKSIZE][w/BLOCKSIZE].x,-64,64);
						visualization[h][w].y = current_frame[h][w]*0.5+64;
						visualization[h][w].z = current_frame[h][w]*0.5+64+clip(16*vectors[h/BLOCKSIZE][w/BLOCKSIZE].y,-64,64);
						visualization[h][w].w = 0;
					}
				}		
				save_bitmap_RGBA(visualization,frame,output_dir, name,width,height);
			}
		
			// Save the current frame as the previous frame for the next iteration
			free(previous_frame[0]);
			free(previous_frame);
			previous_frame = current_frame;			
		}
				
	// Free the current frame
	free(current_frame[0]);
	free(current_frame);
	
	// Stop the timer and print the results
	timer = timer/IMAGES;
	uint complexity = 1;
	double gflop = (complexity/1000000.0)*width*height;
	double datatransfer = width*height*sizeof(TYPE)*2;
	if(verbose) {	printf("..Time: %2.3lf ms (%2.3lf GB/s, %3.3lf GFLOPS) [%s].\n", timer, datatransfer/(1048576*timer), gflop/timer, name); }
	else { printf("%d %2.3lf\n",complexity,timer); }
	
	// Print extra timers
	#ifdef TIMERS
		if(verbose) {
			if (name[0] == 71 || name[0] == 78) {
				for (uint i=0; i<NUM_TIMERS; i++) { printf("###Extra timer%d: %2.3lf ms.\n",i,timers[i]/IMAGES); }
			}
		}
	#endif
	
	// Free CPU data
	free(vectors[0]);
	free(vectors);
	free(visualization);
}

//########################################################################
