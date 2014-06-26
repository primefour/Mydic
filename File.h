#ifndef __DIC_FILE_H__
#define __DIC_FILE_H__

typedef enum DIC_FILE_TYPE{
    ORDINARY_FILE_TYPE,
    DIRECTORY_FILE_TYPE,
    SOCKET_FILE_TYPE,
    GZIP_FILE_TYPE,
    DICTZIP_FILE_TYPE,
}DIC_FILE_TYPE;



const unsigned int MAX_PATH_LENGTH=1024;
const unsigned int MAX_CACHE_SIZE=2048;

class BufferCache{
    public:
        BufferCache(unsigned int size,File *file_ops);
        BufferCache();
        ~BufferCache();
        int init();
        int read(char *buf,int len);
        int write(char *buf,int len);
        int lseek(int where,int offset);
        int readline(char *buf,int len);
    private:
        File *file_ops;
        unsigned int cache_size;
        unsigned char *cache;
        unsigned char *cache_data_begin;
        unsigned char *cache_data_end;
};


//implements genera file operations
class File{
    public :
        File(char *path);
        File();
        virtual int open(char *path,int mode);
        virtual int read(char *buf,int len);
        virtual int write(char *buf,int len);
        virtual int lseek(int where,int offset);
        virtual int readline(char *buf,int len);
        static  int check_file_type(char *path);
        static File* MakeFileInstance(void *data,file_type_t);
    protected:
        unsigned char cache[MAX_FILE_CACHE_SIZE]
        int  cache_begin_cursor,cache_end_cursor;
        char file_path[MAX_PATH_LENGTH];
        int  fd;
};

//using genera file operations to implements 
//file opt interface
class DictzipFile:public File{
    static int check_file_type(char *buf,int len);
};

class GzipFile:public File{
    static int check_file_type(char *buf,int len);
};


class dictionary{

}

class stardict_dict :public dictionary{
    public:


    private:
        File *finfo;
        File *fdict;
        File *fidx;
        File *fsync;
};



#endif 
