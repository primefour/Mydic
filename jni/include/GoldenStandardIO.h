#ifndef __STANDARD_IO_H__
#define __STANDARD_IO_H__
#include<stdio.h>
#include"GoldenRef.h"
#include"String8.h"
#include<unistd.h>
#include<fcntl.h>

#define MAX_PATH_LENGTH 1024 
typedef enum STANDARDIO_TYPE{
    STANDARDIO_TYPE_FILE,
    STANDARDIO_TYPE_C_FILE,
    STANDARDIO_TYPE_SOCK,
    STANDARDIO_TYPE_HTTP,
    STANDARDIO_TYPE_FTP,
    STANDARDIO_TYPE_NETWORK,
    STANDARDIO_TYPE_MAX,
}STANDARDIO_TYPE;

class IOInterface{
    virtual int Seek(int where,int offset) {
        return 0;
    };

    virtual char ReadChar(){
        return 0;
    };
    virtual short ReadS16(){
        return 0;
    };
    virtual unsigned short ReadU16(){
        return 0;
    };
    virtual int ReadI32(){
        return 0;
    };
    virtual unsigned int ReadU32(){
        return 0;
    };
    virtual long long ReadI64(){
        return 0;
    };
    virtual unsigned long long ReadU64(){
        return 0;
    };
    virtual int Read(unsigned char *buf,int len){
        return 0;
    };
    virtual int ReadLine(unsigned char *buf,int len){
        return 0;
    };
    virtual int ReadTerminating(unsigned char *buff,int len,unsigned char terminate){
        return 0;
    };

    virtual char WriteChar(){
        return 0;
    };
    virtual short WriteS16(){
        return 0;
    };
    virtual unsigned short WriteU16(){
        return 0;
    };
    virtual int WriteI32(){
        return 0;
    };
    virtual unsigned int WriteU32(){
        return 0;
    };
    virtual long long WriteI64(){
        return 0;
    };
    virtual unsigned long long WriteU64(){
        return 0;
    };
    virtual int Write(const unsigned char *buf,int len){
        return 0;
    };
    virtual int WriteLine(unsigned char *buf,int len){
        return 0;
    };

};

class MemFile:public Ref,IOInterface{
    public :
        MemFile(const char *path,int mode=O_RDWR);
        ~MemFile();
        virtual int Read(unsigned char *buf,int len);
        virtual int Seek(int where,int offset);
        virtual int ReadLine(unsigned char *buf,int len);
        virtual int ReadTerminating(unsigned char *buff,int len,unsigned char terminate);
        virtual int Write(const unsigned char *buf,int len);
    protected:
        String8 file_path;
        unsigned char *file_root;
        size_t buff_len;
        size_t buff_offset;
        int file_des;
        size_t file_size;
};


class SimpleFile:public Ref,IOInterface{
    public :
        SimpleFile(const char *path,int mode=O_RDWR);
        ~SimpleFile();
        virtual int Read(unsigned char *buf,int len);
        virtual int Seek(int where,int offset);
        virtual int ReadLine(unsigned char *buf,int len);
        virtual int ReadTerminating(unsigned char *buff,int len,unsigned char terminate);
        virtual int Write(const unsigned char *buf,int len);
    protected:
        String8 file_path;
        int file_des;
};

#endif
