#ifndef __GZIP_FILE_H__
#define __GZIP_FILE_H__
#include"File.h"
#include<unistd.h>
#include<time.h>
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




class GzipFile:public File{
    public:
        GzipFile(const char *file_path);
        GzipFile();
        virtual ~GzipFile();
        virtual int open(char *path,int mode);
        virtual int read(char *buf,int len);
        virtual int write(const char *buf,int len);
        virtual int lseek(int where,int offset);
        virtual int readline(char *buf,int len);
        static int check_file_type(char *buf,int len);
    protected:
        int ParserHeader();
        unsigned char fixed_head[10];
        char zip_name[1024];
        char comment[1024];
        unsigned char crc16_head[2];
        unsigned char crc32_info[8];//crc32,isize
        unsigned char extra_info_header[4];//si1,si2,len(2byte)
        int head_length;
};

#endif //
