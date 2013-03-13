#include "driver_common.h"

int  dmem_sec_num = 1;
int  dmem_sec_size[1];

int main(int argc, char* argv[]) {

    if (argc != 4) {
        ARGC_ERROR(3);
        return -1;
    }

    int w;
    int h;

    printf("Openning meta file\n");
    FILE* meta = fopen(argv[2],"r");
    fscanf(meta,"%d",&w);
    fscanf(meta,"%d",&h);
    fclose(meta);

    printf("Image Width: %d\n",w);
    printf("Image Height: %d\n",h);

    dmem_sec_size[0] = w*(h+4)*sizeof(unsigned char);

    /* input secttion */
    dmem_section_t* secs
        = ReadDmemInitFile(argv[1], dmem_sec_size, dmem_sec_num);
    int n = secs[0].size/sizeof(unsigned char);

    /* output section */
    dmem_section_t out_sec;
    out_sec.start = 0;
    out_sec.size  = n*sizeof(unsigned char);
    out_sec.buff  = malloc(out_sec.size);

    /* section for temporary working set */
    dmem_section_t tmp_sec;
    tmp_sec.start = secs[0].start+secs[0].size;
    tmp_sec.size  = n*sizeof(unsigned char);
    tmp_sec.buff  = malloc(tmp_sec.size);
    
    gaussian5x5int((unsigned char*)out_sec.buff, (unsigned char*)tmp_sec.buff, (unsigned char*)secs[0].buff, w, h);
    FreeDmemSections(secs, dmem_sec_num);
    FILE* ofp = fopen(argv[3], "w");
    DumpDmemSection(ofp, out_sec);
    fclose(ofp);
    free(out_sec.buff);
    return 0;
}
