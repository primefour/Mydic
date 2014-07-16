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

typedef struct pfn_check_file_list{
    list_head list;
    pfn_check_file_type pfn;
    DIC_FILE_TYPE_T type;
}pfn_check_file_list;

//implements general file operations
class File{
    public :
        File(const char *path);
        virtual ~File();
        virtual int open(int mode);
        virtual int read(unsigned char *buf,int len);
        virtual int write(const unsigned char *buf,int len);
        virtual int lseek(int where,int offset);
        virtual int readline(unsigned char *buf,int len);

        static  int  check_file_type(const char *path);
        static  void add_check_func(pfn_check_file_type pfd,DIC_FILE_TYPE_T type);
        static File* MakeFileInstance(void *data,DIC_FILE_TYPE file_type);
        static list_head_t check_list; 
    protected:
        char file_path[MAX_PATH_LENGTH];
        DIC_FILE_TYPE_T file_type;
        int  fd;
};



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
