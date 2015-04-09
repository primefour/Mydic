#ifndef __GZIP_DEFLATE_H__
#define __GZIP_DEFLATE_H__
#include"String8.h"
#include"GzipHeaderParser.h"
#include<stdio.h>
#include"StandardIO.h"
#include"Ref.h"
#include"String8.h"
#include<unistd.h>
#include<fcntl.h>

extern "C"{
#include"zlib.h"
}

class GzipDeflate:public IOInterface,Ref{
    public:
        GzipDeflate(const char *file_path,int mode = O_RDWR);
        virtual ~GzipDeflate();
        virtual int Read(unsigned char *buf,int len);
        virtual int Seek(int where,int offset);
        virtual int ReadLine(unsigned char *buf,int len);
        virtual int ReadTerminating(unsigned char *buff,int len,unsigned char terminate);
        //virtual int Write(const unsigned char *buf,int len);
    private:
        int mPos;
        int mOffset;
        int mbegin;
        int mEnd;
        int mCheckCount;
        int mCheckLength;
        int mVersion;
        int mHeaderLength;
        int *mChunkArray;
        String8 file_path;
};
#endif
