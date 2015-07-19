#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdexcept>

#include"GoldenGzipHeaderParser.h"
#include"GoldenStandardIO.h"
#include"GoldenDictLog.h"
#include"GoldenRef.h"
#include"String8.h"

using namespace std;

GZipHeader::GZipHeader(const char *gzip_path){
    unsigned char word_buff[12]={0};
    SObject<SimpleFile> file_obj = NULL;
    try{
        file_obj = new SimpleFile(gzip_path,O_RDONLY);
    }catch (exception & a){
        golden_printfd(" EXCEPTION %s \n",a.what());
        throw exception();//"new Simplefile fail!");
    }
    int ret = file_obj->Read(word_buff,sizeof(word_buff));
    mExtraBuff = 0;
    int contain_length = 0;
    if(ret <=0){
        throw exception();//"Simplefile read fail");
    }
    golden_printfi("check head %x   %x \n",word_buff[0],word_buff[1]);
    //check file type
    if(word_buff[0] == GZIP_ID1 && GZIP_ID2 == word_buff[1]){
        //check deflate compress
        if(word_buff[2] & 0x80){
            golden_printfi("mIsDeflate  is true \n");
            mIsDeflate = true;
        }
        //check flag
        if(word_buff[3] & GZIP_FTEXT){
            golden_printfi("this is probably ASCII text \n");
        }

        if(GZIP_FEXTRA & word_buff[3]){
            unsigned short xlen = word_buff[11]<<8 | word_buff[10];
            contain_length += 2;
            golden_printfi("xlen = %d \n",xlen);
            mExtraBuff = new unsigned char [xlen];
            mEXlength = xlen;
            if(mExtraBuff == NULL){ 
                golden_printfe("no memory for extra buff\n");
                throw exception();//"No memory for extra buff");
            }else{
                memset(mExtraBuff,0,xlen);
                ret = file_obj->Read(mExtraBuff,xlen);
                if(ret != xlen){
                    golden_printfe("Read extra buff fail \n");
                    delete mExtraBuff; 
                    throw exception();//"read file fail");
                }
            }
            contain_length += xlen;
        }
        if(GZIP_FNAME & word_buff[3]){
            char fname_buff[1024]={0};
            ret = file_obj->ReadTerminating((unsigned char *)fname_buff,sizeof(fname_buff),'\0');
            golden_printfi("pfname = %s \n",fname_buff);
            contain_length += strlen(fname_buff);
            contain_length ++;
        }

        if(GZIP_FCOMMENT & word_buff[3]){
            char fcomment_buff[1024]={0};
            ret = file_obj->ReadTerminating((unsigned char *)fcomment_buff,sizeof(fcomment_buff),'\0');
            golden_printfi("pfname = %s \n",fcomment_buff);
            contain_length += strlen(fcomment_buff);
            contain_length ++;
        }
        if(GZIP_FHCRC & word_buff[3]){
            contain_length += 2;
        }
        mHeadOffset = 10 + contain_length;
        golden_printfi("mHeadOffset  = %d \n",mHeadOffset);
        //MTime skip
        //xfl
        mXFL = word_buff[8]; 
        //skip os
    }
    //parse file end
    memset(word_buff,0,sizeof(word_buff));
    ret = file_obj->Seek(SEEK_END,-8);
    if(ret < 0){
        golden_printfe("seek fail \n");
        delete mExtraBuff; 
        throw exception();//"parse fail ");
    }
    ret = file_obj->Read(word_buff,8);
    if(ret != 8){
        delete mExtraBuff; 
        throw exception();//"parse fail ");
    }
    mCRC32 = word_buff[3]<<24 | word_buff[2]<<16 | word_buff[1]<< 8 | word_buff[0];
    golden_printfi("mCRC32  = %u  %x \n",mCRC32,mCRC32);
    mFileSize = word_buff[7]<<24 | word_buff[6]<<16 | word_buff[5]<< 8 | word_buff[4];
    golden_printfi("mFileSize = %u \n",mFileSize);
}

void GZipHeader::getExtraInfo(int &chunk_num,int &chunk_len,int & version){
    if(mExtraBuff != NULL){
        unsigned char *ptr = mExtraBuff ;
        golden_printfi("%c %c \n",*(char*)(ptr+1),*(char *)ptr);
        ptr+=2;
        int len = *(ptr +1)<<8 | *ptr;
        golden_printfi("len = %d \n",len);
        ptr += 2;
        unsigned short ver = *(ptr+1) << 8|*ptr;
        ptr += 2;
        unsigned short chlen =*(ptr+1) << 8|*ptr; 
        ptr += 2;
        unsigned short chcnt =*(ptr+1) << 8|*ptr; 
        ptr += 2;
        golden_printfi("ver = %u chlen = %u chcnt = %u \n",ver,chlen,chcnt);
        chunk_num = chcnt;
        chunk_len = chlen;
        version = ver;
    }
}

unsigned int GZipHeader::getChunkCode(int index){
    if(mExtraBuff != NULL){
        unsigned char *ptr = mExtraBuff + (index-1)*2 + 10;
        return *(ptr+1) << 8 |*ptr; 
    }
}

