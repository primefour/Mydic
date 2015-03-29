#include"GzipHeaderParser.h"
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include"String8.h"
#include"StandardIO.h"
#include"AVLTreeTemplate.h"


GZipHeader::GZipHeader(const char *gzip_path):file_path(gzip_path){
    unsigned char word_buff[12]={0};
    SimpleFile file_obj(file_path,O_RDONLY);
    int ret = file_obj.Read(word_buff,sizeof(word_buff));
    mExtraBuff = 0;
    int contain_length = 0;
    if(ret <=0){
        return ;
    }
    printf("check head %x   %x \n",word_buff[0],word_buff[1]);
    //check file type
    if(word_buff[0] == GZIP_ID1 && GZIP_ID2 == word_buff[1]){
        //check deflate compress
        if(word_buff[2] & 0x80){
            printf("mIsDeflate  is true \n");
            mIsDeflate = true;
        }
        //check flag
        if(word_buff[3] & GZIP_FTEXT){
            printf("this is probably ASCII text \n");
        }

        if(GZIP_FEXTRA & word_buff[3]){
            unsigned short xlen = word_buff[11]<<8 | word_buff[10];
            contain_length += 2;
            printf("xlen = %d \n",xlen);
            mExtraBuff = new unsigned char [xlen];
            mEXlength = xlen;
            if(mExtraBuff == NULL){ 
                printf("no memory for extra buff\n");
                return ;
            }else{
                memset(mExtraBuff,0,xlen);
                ret = file_obj.Read(mExtraBuff,xlen);
                if(ret != xlen){
                    printf("Read extra buff fail \n");
                    return ;
                }
            }
            contain_length += xlen;
        }
        if(GZIP_FNAME & word_buff[3]){
            char fname_buff[1024]={0};
            ret = file_obj.ReadTerminating((unsigned char *)fname_buff,sizeof(fname_buff),'\0');
            printf("pfname = %s \n",fname_buff);
            contain_length += strlen(fname_buff);
            contain_length ++;
        }

        if(GZIP_FCOMMENT & word_buff[3]){
            char fcomment_buff[1024]={0};
            ret = file_obj.ReadTerminating((unsigned char *)fcomment_buff,sizeof(fcomment_buff),'\0');
            printf("pfname = %s \n",fcomment_buff);
            contain_length += strlen(fcomment_buff);
            contain_length ++;
        }
        if(GZIP_FHCRC & word_buff[3]){
            contain_length += 2;
        }
        mHeadOffset = 10 + contain_length;
        //MTime skip
        //xfl
        mXFL = word_buff[8]; 
        //skip os
    }
    //parse file end
    memset(word_buff,0,sizeof(word_buff));
    ret = file_obj.Seek(SEEK_END,-8);
    if(ret < 0){
        printf("seek fail \n");
        return ;
    }
    ret = file_obj.Read(word_buff,8);
    if(ret != 8){
        return ;
    }
    mCRC32 = word_buff[3]<<24 | word_buff[2]<<16 | word_buff[1]<< 8 | word_buff[0];
    printf("mCRC32  = %u  %x \n",mCRC32,mCRC32);
    mFileSize = word_buff[7]<<24 | word_buff[6]<<16 | word_buff[5]<< 8 | word_buff[4];
    printf("mFileSize = %u \n",mFileSize);
}

