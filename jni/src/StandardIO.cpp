#include"StandardIO.h"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

SimpleFile::SimpleFile(const char *path,int mode):file_path(path){
    file_des = 0;
    int def_mode = O_RDWR;
    if(mode != 0){
        def_mode = mode; 
    }
    file_des = ::open(path,def_mode);
    if(file_des < 0){
        printf("open file error %s \n",file_path.string());
    }
}


SimpleFile::~SimpleFile(){
    if(file_des >= 0){
        close(file_des);
        file_des = -1;
    }
}


int SimpleFile::Seek(int whence,int offset){
    if(file_des >= 0){
        return ::lseek(file_des,offset,whence);
    }else{
        printf("%s\n","fd is negative");
        return -1;
    }
}

int SimpleFile::Write(const unsigned char *buf,int len){
    int ret = -1;
    const unsigned char *ptr = buf;
    //printf("buf = %s len = %d ",buf,len);
    if(file_des >= 0 && ptr != NULL){
        while(len > 0){
            ret = ::write(file_des,ptr,len);
            if(ret >= 0){
                len -= ret;
                ptr += ret;
            }else{
                printf("%s \n","write failed");
                return -1;
            }
        }
    }else{
        printf("%s\n","fd is negative");
    }
    return ret;
}


int SimpleFile::Read(unsigned char *buf,int len){
    int ret = -1;
    memset(buf,0,len);
    //printf("%s \n",__func__);
    if(file_des >= 0){
       ret = ::read(file_des,buf,len); 
    }else{
        printf("%s\n","fd is negative");
    }
    return ret;
}

int SimpleFile::ReadLine(unsigned char *buf,int len){
    int ret = -1;
    unsigned char *ptr = buf;
    memset(buf,0,len);
    int i = 0;

    while(((ret = ::read(file_des,ptr,1)) > 0) && (*ptr != '\n') && ++i < len){ 
        ptr++;
    }
    return i;
}


int SimpleFile::ReadTerminating(unsigned char *buf,int len,unsigned char terminate){
    int ret = -1;
    unsigned char *ptr = buf;
    memset(buf,0,len);
    int i = 0;
    //printf("file_des = %d len = %d \n",file_des,len);
    while(((ret = ::read(file_des,ptr,1)) > 0) && (*ptr != terminate ) && ++i < len){ 
        ptr++;
    }
    //printf("%s  %s",__func__,buf);
    return i;
}
