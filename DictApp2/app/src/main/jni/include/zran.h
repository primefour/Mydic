#ifndef __DICT_ZRAN_H__
#define __DICT_ZRAN_H__

#define local static

#define SPAN 1048576L       /* desired distance between access points */
#define WINSIZE 32768U      /* sliding window size */
#define CHUNK 16384         /* file input buffer size */

/* access point entry */
struct point {
    off_t out;          /* corresponding offset in uncompressed data */
    off_t in;           /* offset in input file of first full byte */
    int bits;           /* number of bits (1-7) from byte at in - 1, or 0 */
    unsigned char window[WINSIZE];  /* preceding 32K of uncompressed data */
};

/* access point list */
struct access {
    int have;           /* number of list entries filled in */
    int size;           /* number of list entries allocated */
    struct point *list; /* allocated list */
};

int zran_build_access_file(const char *file_name,struct access **ppindex);
int zran_extract_file(FILE *file,struct access *index,int offset,unsigned char *buff,int buff_size);
void zran_free_access(struct access *index);

#endif 
