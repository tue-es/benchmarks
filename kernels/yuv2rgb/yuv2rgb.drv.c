#include "driver_common.h"

extern void yuv2rgb(unsigned int* out, unsigned int* in, int n);

int  dmem_sec_num = 1;
int  dmem_sec_size[] = {3072*sizeof(int)};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        ARGC_ERROR(2);
        return -1;
    }
    dmem_section_t* secs
        = ReadDmemInitFile(argv[1], dmem_sec_size, dmem_sec_num);
    int n = secs[0].size/sizeof(int);
    dmem_section_t out_sec;
    out_sec.start = 0;
    out_sec.size  = n*sizeof(int);
    out_sec.buff  = malloc(out_sec.size);
    yuv2rgb((unsigned int*)out_sec.buff, (unsigned int*)secs[0].buff, n/3);
    FreeDmemSections(secs, dmem_sec_num);
    FILE* ofp = fopen(argv[2], "w");
    DumpDmemSection(ofp, out_sec);
    fclose(ofp);
    free(out_sec.buff);
    return 0;
}
