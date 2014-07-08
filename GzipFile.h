#ifndef __GZIP_FILE_H__
#define __GZIP_FILE_H__
#include"File.h"
#include<unistd.h>
#include<time.h>
extern "C"{
#include"zlib.h"
}

enum GZIP_FIXED_HEAD_INDEX{
    ID1,
    ID2,
    CM,
    FLG,
    MTIME,//4BYTE
    XFL=8,
    OS
};

#define  ID1_VALUE (0x1f)
#define  ID2_VAlUE (0x8b)

#define FLAG_TEXT_VALUE 1
#define FLAG_HCRC_VALUE (1<<1)
#define FLAG_EXTRA_VALUE (1<<2)
#define FLAG_NAME_VALUE (1<<3)
#define FLAG_COMMENT_VALUE (1<<4)

#define SPAN 1048576L       /* desired distance between access points */
#define WINSIZE 32768U      /* sliding window size */
#define CHUNK 16384         /* file input buffer size */


typedef struct ACCESS_PIONT{
    list_head list;
    int original_offset;
    int original_size;
    int file_chunk_offset;
    int file_chunk_size;
    int bits;
    unsigned char window[WINSIZE];
}access_point_t;


class GzipFile:public File{
    public:
        GzipFile(const char *file_path);
        virtual ~GzipFile();
        virtual int open(int mode);
        virtual int read(char *buf,int len);
        virtual int write(const char *buf,int len);
        virtual int lseek(int where,int offset);
        virtual int readline(char *buf,int len);
        static int check_file_type(char *buf,int len);
        int uncompress_file(File *outFile);
    private:
        int build_access_point();
        list_head access_point_list;

};

#endif //
