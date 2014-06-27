#ifndef __DICT_ZIP_FILE__
#define __DICT_ZIP_FILE__
#include"GzipFile.h"
class DictzipFile:public GzipFile{
    public:
        virtual int open(char *path,int mode);
        virtual int read(char *buf,int len);
        virtual int write(const char *buf,int len);
        virtual int lseek(int where,int offset);
        virtual int readline(char *buf,int len);
        static int check_file_type(char *buf,int len);
};

#endif
