#ifndef _DRIVER_COMMON_H_
#define _DRIVER_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGC_ERROR(n) printf("ERROR: number of arguments should be %d\n", n)

typedef struct _dmem_section {
    int start;
    int size;
    unsigned char* buff;
} dmem_section_t;

dmem_section_t* ReadDmemInitFile(char fname[], int sec_size[], int n);
void FreeDmemSections(dmem_section_t* secs, int n);
void DumpDmemSection(FILE* fp, dmem_section_t sec);

#endif//_DRIVER_COMMON_H_
