#include"File.h"
#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

BufferCache(unsigned int size,File *file_ops);
BufferCache();
~BufferCache();
int init();
int read(char *buf,int len);
int write(char *buf,int len);
int lseek(int where,int offset);
int readline(char *buf,int len);


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

int BufferCache::init(){
    if(cache == NULL){
        cache = (unsigned char *)malloc(cache_size);
        if(cache == NULL){
            ALOGE("buffer cache malloc failed");
            return -1;
        }
    }
    return 0;
}


int BufferCache::read(char *buf,int len){
}

int BufferCache::write(char *buf,int len){
}





File::File(char *path){
    fd =-1;
    cache_length = 0;
    memset(file_path,0,MAX_PATH_LENGTH);
    memset(cache,0,MAX_FILE_CACHE_SIZE);
    if(path != NULL){
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
}

File::File(){
    fd =-1;
    cache_length = 0;
    memset(file_path,0,MAX_PATH_LENGTH);
    memset(cache,0,MAX_FILE_CACHE_SIZE);
}

File::~File(){
    if(fd >= 0){
        close(fd);
    }
}

int File::check_file_type(){
    ALOGE("this is a empty function");
    return -1;
}

int File::readline(char *buf,int len){
    int ret = -1;
    char *ptr = buf;
    if(cache_size > 0){
    }
    memset(buf,len);
    int i = 0;
    while((ret = read(ptr,1) > 0) && (ptr != '\0') && ++i < len){ 
        ptr++;
    }

    if(ptr == '\0' && i != len){
        return i;
    }else{
        return -1;
    }
}


int File::lseek(int whence,int offset){
    if(fd >= 0){
        return lseek(fd,offset,whence);
    }else{
        ALOGE("fd is negative");
        return -1;
    }
}

int File::write(char *buf,int len){
    int ret = -1;
    char *ptr = buf;
    if(fd >= 0 && ptr != NULL){
        while(len <= 0){
            ret = write(fd,ptr,len);
            if(ret >= 0){
                len -= ret;
                ptr += ret;
            }else{
                ALOGE("write failed");
                return -1;
            }
        }
    }else{
        ALOGE("fd is negative");
    }
    return ret;
}


int File::read(char *buf,int len){
    int ret = -1;
    memset(buf,0,len);
    if(cache_length != 0){
        memcpy(buf,cache,cache_length );
        memset(cache,0,cache_length);
    }

    if(fd >= 0){
       ret = read(fd,buf,len); 
    }else{
        ALOGE("fd is negative");
    }
    return ret;
}

int File::open(char *path,int mode){
    if(path != NULL){
        memset(file_path,0,MAX_PATH_LENGTH);
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
    fd = open(file_path,O_RDWR);
    if(fd < 0){
        printf("open file error %s \n",file_path);
        perror();
        return -1;
    }
    return 0;
}





