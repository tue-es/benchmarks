//########################################################################
//### Program:   Algorithms
//### Author:    C. Nugteren
//### Institute: Eindhoven University of Technology
//### Date:      15-03-2011
//### Filename:  config.h
//### Contents:  This file contains some configuration options
//### Reference: http://parse.ele.tue.nl/
//########################################################################

#ifndef __CONFIG_H
#define __CONFIG_H

//########################################################################
//### General configuration options
//########################################################################

#define VERBOSE
#define NUM_TIMERS 6
//#define TIMERS

//########################################################################
//### Settings
//########################################################################

#define BLOCKSIZE 8
#define RANDOMVECTORS
#define TWODIRECTIONS
#define PENALTIES
#define MEANDERING

//########################################################################
//### Image sequence settings
//########################################################################

#define IMAGES 28
#define IMAGE_START 501		// Renata motion

//########################################################################
//### Type definitions
//########################################################################

#define TYPE uint
#define TYPE4 uchar4

typedef unsigned int uint;
typedef struct {
	char x;
	char y;
} char2;

typedef struct {
  unsigned char x, y, z, w;
} uchar4;

//########################################################################

#endif
