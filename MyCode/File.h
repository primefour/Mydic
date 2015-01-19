#ifndef __DIC_FILE_H__
#define __DIC_FILE_H__
#include"list.h"

const unsigned int MAX_PATH_LENGTH=1024;
const unsigned int MAX_CACHE_SIZE=2048;
class File;

typedef enum DIC_FILE_TYPE{
    ORDINARY_FILE_TYPE,
    DIRECTORY_FILE_TYPE,
    SOCKET_FILE_TYPE,
    GZIP_FILE_TYPE,
    DICTZIP_FILE_TYPE,
}DIC_FILE_TYPE_T;

class BufferCache{
    public:
        BufferCache(unsigned int size,File *file_ops);
        BufferCache(File *file_ops);
        ~BufferCache();
        int init();
        int read(unsigned char *buf,int len);
        int write(const unsigned char *buf,int len);
        int lseek(int where,int offset);
        int readline(unsigned char *buf,int len);
    private:
        File *file_ops;
        unsigned int cache_size;
        unsigned char *cache;
        unsigned char *cache_data_begin;
        unsigned char *cache_data_end;
};

typedef int (*pfn_check_file_type)(unsigned char *buff,int *len);

typedef struct pfn_check_file{
    pfn_check_file_type pfn;
    DIC_FILE_TYPE_T type;
}pfn_check_file;


class DicFileInterface{
    virtual char ReadChar();
    virtual short ReadS16();
    virtual unsigned short ReadU16();
    virtual int ReadI32();
    virtual unsigned int ReadU32();
    virtual long long ReadI64();
    virtual unsigned long long ReadU64();
    virtual int Read(unsigned char *buf,int len);
    virtual int Seek(int where,int offset);
    virtual int ReadLine(unsigned char *buf,int len);
    virtual int Read_Terminating(unsigned char *buff,int len,unsigned char terminate);
};



//implements general file operations
class SimpleFile{
    public :
        SimpleFile(const char *path);
        ~SimpleFile();
        int Read(unsigned char *buf,int len);
        int Write(const unsigned char *buf,int len);
        int Seek(int where,int offset);
    protected:
        char mfile_path[MAX_PATH_LENGTH];
        int  mfd;
};

///////////////////////////////////////////////////////////////////////////////////////

class dictionary{

};

class stardict_dict :public dictionary{
    public:


    private:
        File *finfo;
        File *fdict;
        File *fidx;
        File *fsync;
};


#endif 
