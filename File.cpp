#include"File.h"
#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include"log.h"

BufferCache::BufferCache(unsigned int size,File *file_ops){
    cache = NULL;
    cache_size = size;
    this->file_ops = file_ops;
}

BufferCache::BufferCache(File *file_ops){
    cache = NULL;
    cache_size = MAX_CACHE_SIZE;
    this->file_ops = file_ops;
}
BufferCache::~BufferCache(){

}

int BufferCache::init(){
    if(cache == NULL){
        cache = (unsigned char *)malloc(cache_size);
        if(cache == NULL){
            ALOGE("%s","buffer cache malloc failed");
            return -1;
        }
    }
    return 0;
}


int BufferCache::read(char *buf,int len){
    return 0;
}

int BufferCache::write(char *buf,int len){
    return 0;
}
int BufferCache::lseek(int whence,int offset){
    return 0;
}

int BufferCache::readline(char *buf,int len){
    return 0;
}




File::File(const char *path){
    fd =-1;
    memset(file_path,0,MAX_PATH_LENGTH);
    if(path != NULL){
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
}

File::File(){
    fd =-1;
    memset(file_path,0,MAX_PATH_LENGTH);
}

File::~File(){
    if(fd >= 0){
        close(fd);
    }
}

int File::check_file_type(char *path){
    ALOGE("%s","this is a empty function");
    return -1;
}

int File::readline(char *buf,int len){
    int ret = -1;
    char *ptr = buf;
    memset(buf,0,len);
    int i = 0;

    while((ret = ::read(fd,ptr,1) > 0) && (*ptr != '\0') && ++i < len){ 
        printf("%c",*ptr);
        ptr++;
    }

    if(*ptr == '\0' && i != len){
        return i;
    }else{
        return ret;
    }
}


int File::lseek(int whence,int offset){
    if(fd >= 0){
        return ::lseek(fd,offset,whence);
    }else{
        ALOGE("%s","fd is negative");
        return -1;
    }
}

int File::write(const char *buf,int len){
    int ret = -1;
    const char *ptr = buf;
    printf("buf = %s len = %d ",buf,len);
    if(fd >= 0 && ptr != NULL){
        while(len > 0){
            ret = ::write(fd,ptr,len);
            if(ret >= 0){
                len -= ret;
                ptr += ret;
            }else{
                ALOGE("%s","write failed");
                return -1;
            }
        }
    }else{
        ALOGE("%s","fd is negative");
    }
    return ret;
}


int File::read(char *buf,int len){
    int ret = -1;
    memset(buf,0,len);
    printf("%s \n",__func__);
    if(fd >= 0){
       ret = ::read(fd,buf,len); 
    }else{
        ALOGE("%s","fd is negative");
    }
    return ret;
}

int File::open(char *path,int mode){
    if(path != NULL){
        memset(file_path,0,MAX_PATH_LENGTH);
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
    int default_mode = O_RDWR;
    if(mode != 0){
        default_mode = mode;
    }
    fd = ::open(file_path,default_mode);
    if(fd < 0){
        printf("open file error %s \n",file_path);
        return -1;
    }
    return 0;
}








