#include "driver_common.h"

dmem_section_t* ReadDmemInitFile(char fname[], int sec_size[], int n) {
    FILE* dm_file = fopen(fname, "r");
    if (dm_file == NULL) {
        printf("ERROR: fail to open dmem file %s\n", fname);
        return NULL;
    }
    dmem_section_t* res = malloc(sizeof(dmem_section_t)*n);
    char ln[128];
    int idx = -1;
    int bidx = 0;
    while (fgets (ln, sizeof(ln), dm_file) != NULL) {
        if (ln[0] == '@') {
            int st;
            sscanf(ln, "@%x", &st);
            res[++idx].start = st;
            res[idx].size = sec_size[idx];
            res[idx].buff = malloc(sec_size[idx]);
            bidx = 0;
            printf("dmem sec %d: start = %d, size = %d\n",
                   idx, st, sec_size[idx]);
        } else {
            int val;
            sscanf(ln, "%x", &val);
            res[idx].buff[bidx++] = val;
        }
    }
    fclose(dm_file);
    return res;
}// ReadDmemInitFile()

void FreeDmemSections(dmem_section_t* secs, int n) {
    int i;
    for (i = 0; i < n; ++i)
        free(secs[i].buff);
    free(secs);
}

void DumpDmemSection(FILE* fp, dmem_section_t sec) {
    int i, n = (sec.size + sizeof(unsigned char)/2)/sizeof(unsigned char);
    fprintf(fp, "@%x\n", sec.start);
    for (i = 0; i < n; ++i) {
        fprintf(fp, "%02x\n", sec.buff[i]);
    }
}
