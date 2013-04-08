//########################################################################
//### Type definitions
//########################################################################

/* typedef unsigned int uint; */
/* typedef struct { */
/* 	char x; */
/* 	char y; */
/* } char2; */

//########################################################################
//### Includes
//########################################################################

#include "config.h"
#include <stdlib.h>

//########################################################################
//### Helper functions
//########################################################################

// Absolute value
int absolute(int in) {
	if (in >= 0) { return in; }
	else { return -in; }
}

//########################################################################
//### Block matcher based on SAD (uses penalties)
//########################################################################

float CPU_blockmatching(char2 candidate, uint type, uint w, uint h, uint width, uint height, TYPE* previous_frame, TYPE* current_frame) {

	// Perform the SAD computation
	float difference = 0;
	
	for (uint hl=0;hl<BLOCKSIZE;hl++) {
		uint hgc = hl+h+candidate.y;
		uint hg = hl+h;
		if (hg > 0 && hg < height && hgc > 0 && hgc < height) {
	
			for (uint wl=0;wl<BLOCKSIZE;wl++) {
				uint wgc = wl+w+candidate.x;
				uint wg = wl+w;
				if (wg > 0 && wg < width && wgc > 0 && wgc < width) {
					uint pc = hgc+wgc*height;
					uint p = hg+wg*height;
					difference = difference + absolute((int)previous_frame[p] - (int)current_frame[pc]);
				}
				else {
					difference = difference + 128;
				}
			}
		}
		else { difference = difference + 128*BLOCKSIZE; }
	}
	
	// Set the penalty
	float penalty = 0;
	#ifdef PENALTIES
		if (type == 3 || type == 5 || type == 6 || type == 7 || type == 8) { penalty = 0.5*BLOCKSIZE*BLOCKSIZE; }
		if (type == 9) { penalty = 2*BLOCKSIZE*BLOCKSIZE; }	
	#endif
	return difference + penalty;
}

//########################################################################
//### Recursive search block matching core function (CPU)
//########################################################################

void CPU_3DRS(TYPE* previous_frame, TYPE* current_frame, char2* vectors, uint width, uint height, uint frame) {
	uint blocks_w = width/BLOCKSIZE;
	uint blocks_h = height/BLOCKSIZE;
	
	// Initialize 'random' vectors
	int ri = 0;
	char2 rv[8];
	rv[0].x = +0; rv[0].y = -1;
	rv[1].x = +0; rv[1].y = +1;
	rv[2].x = -1; rv[2].y = +0;
	rv[3].x = +1; rv[3].y = +0;
	rv[4].x = +0; rv[4].y = -2;
	rv[5].x = +0; rv[5].y = +2;
	rv[6].x = -3; rv[6].y = +0;
	rv[7].x = +3; rv[7].y = +0;
	 
	// For each row (of blocksize pixels high) - goes into two directions
	for(uint hvloop=0;hvloop<blocks_h;hvloop++) {
		
		// Loop goes into two directions (upwards and downwards)
		uint hv;
		#ifdef TWODIRECTIONS
			if (frame%2 == 0) { hv = hvloop; }
			else { hv = (blocks_h-1)-hvloop; }		
		#else
			hv = hvloop;
		#endif
		uint h=hv*BLOCKSIZE;
		
		// For each block in the row (of blocksize pixels wide) - goes into two directions
		for (uint wvloop=0;wvloop<blocks_w;wvloop++) {
		
			// Loop goes into two directions (meandering)
			uint wv;
			#ifdef MEANDERING
				if (hv%2 == 0) { wv = wvloop; }
				else { wv = (blocks_w-1)-wvloop; }		
			#else
				wv = wvloop;
			#endif
			uint w=wv*BLOCKSIZE;
			
			// Load the spatial, temporal and zero vectors as candidates
			char2 cv[10];
			uint i=0;
			for (int hn=-1;hn<=1;hn++) {
				for (int wn=-1;wn<=1;wn++) {
					int indexh = hv+hn;
					int indexw = wv+wn;
					if ((hn==0 && wn==0) || (indexh < 0) || (indexh >= blocks_h) || (indexw < 0) || (indexw >= blocks_w)) {
						cv[i].x = 0; cv[i].y = 0;
					}
					else {
						cv[i] = vectors[indexh+indexw*blocks_h];
					}
					i++;
				}
			}
	
			// Create the noise vector (based on the first spatial vector)
			#ifdef RANDOMVECTORS
				cv[9].x = rv[ri%8].x + cv[0].x;
				cv[9].y = rv[ri%8].y + cv[0].y;
				ri++;
			#else
				cv[9].x = (rand()%100-50)%3 + cv[0].x;
				cv[9].y = (rand()%100-50)%3 + cv[0].y;
			#endif
	
			// For candidate vector perform blockmatching (sum of absolute difference)
			float sad[10];
			for (uint vi=0;vi<10;vi++) {
				sad[vi] = CPU_blockmatching(cv[vi],vi,w,h,width,height,previous_frame,current_frame);
			}
			
			// Find the best candidate (reduction)
			float smallest_difference = 1000000;
			uint best_id;
			for (uint di=0;di<10;di++) {
				if (smallest_difference > sad[di]) {
					smallest_difference = sad[di];
					best_id = di;
				}
			}
		
			// Update the vector
			vectors[hv+wv*blocks_h] = cv[best_id];
		}
	}
}

//########################################################################i
