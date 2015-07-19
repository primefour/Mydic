#ifndef __GZIP_INFLATE_H__
#define __GZIP_INFLATE_H__
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#include"GoldenGzipHeaderParser.h"
#include"GoldenStandardIO.h"
#include"GoldenRef.h"
#include"String8.h"

extern "C"{
#include"zlib.h"
}

class GzipInflate:public Ref,IOInterface{
    public:
        GzipInflate(const char *file_path,int mode = O_RDWR);
        virtual ~GzipInflate();
        virtual int Read(unsigned char *buf,int len);
        virtual int Seek(int where,int offset);
        virtual int ReadLine(unsigned char *buf,int len);
        virtual int ReadTerminating(unsigned char *buff,int len,unsigned char terminate);
        virtual int Write(const unsigned char *buf,int len);
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
