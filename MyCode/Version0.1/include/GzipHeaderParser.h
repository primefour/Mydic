#ifndef __GZIP_HEADER_PARSER_H__
#define __GZIP_HEADER_PARSER_H__
#include<stdio.h>
#include"String8.h"
#define GZIP_ID1  (0x1f)
#define GZIP_ID2  (0x8b)

enum {
    GZIP_FTEXT  = 0,
    GZIP_FHCRC  = 1<<1,
    GZIP_FEXTRA = 1<<2,
    GZIP_FNAME  = 1<<3,
    GZIP_FCOMMENT = 1<<4
};

class GZipHeader:public Ref{
    public:
        GZipHeader(const char *gzip_path);
        virtual ~GZipHeader(){
            if(mExtraBuff != NULL){
                delete mExtraBuff;
                mExtraBuff = NULL;
            }
        }
        void getExtraInfo(int &chunk_num,int &chunk_len,int & version);
        unsigned int getChunkCode(int index);
        bool getDeflateFlag(){
            return mIsDeflate;
        }

        int getDataOffset(){
            return mHeadOffset;
        }

        unsigned int getCRC32(){
            return mCRC32;
        }
        unsigned int getFileSize(){
            return mFileSize;
        }

    private:
        bool mIsDeflate;
        unsigned char *mExtraBuff;
        int  mEXlength;
        int  mXFL;
        int  mHeadOffset;
        unsigned int mCRC32;
        unsigned int mFileSize;;
};

#endif//GZIP_HEADER_PARSER_H__
