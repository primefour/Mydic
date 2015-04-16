#include"StandardIO.h"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/mman.h>

#if 1
#define  LOG_TAG    "DICT2"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define printf LOGE
#endif
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
        unsigned char *file_position;
        unsigned char *buff_offset;
        int file_des;
        size_t file_size;
}



#define MEM_FILE_MAX_SIZE 7 * 1024 *1024

MemFile::MemFile(const char *path,int mode):file_path(path){
    file_des = 0;
    int def_mode = O_RDWR;
    if(mode != 0){
        def_mode = mode; 
    }
    file_des = ::open(path,def_mode);
    if(file_des < 0){
        printf("open file error %s \n",file_path.string());
    }
    //check the sizeof file 
    file_size = lseek(file_des,0,SEEK_END);
    lseek(file_des,0,SEEK_SET);
    buff_offset = 0;
    file_postion = 0;
    if(file_size <= mem_file_max_size){
        //using mmap
        file_root = (unsigned char *)mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_PRIVATE,file_des,0);
        if(file_root == NULL){
            LOGE("mmap file failed");
            close(file_des);
            return ;
        }
    }else{
        //using cache
        file_root = new unsigned char[1+MEM_FILE_MAX_SIZE];
        file_root[MEM_FILE_MAX_SIZE]= 0;
        if(file_root == NULL){
            LOGE("NO MEMORY FOR FILE");
            close(file_des);
            return;
        }
        int n = read(file_des,file_root,MEM_FILE_MAX_SIZE);
        if(n != MEM_FILE_MAX_SIZE){
            closs(file_des);
            delete file_root[];
            return ;
        }
        buff_offset = 0;
    }
}

MemFile::~MemFile(){
    if(file_size <= MEM_FILE_MAX_SIZE){
        //using mmap
        munmap(file_root,file_size);
    }else{
        if(file_root != NULL){
            delete file_root[];
        }
    }
    file_root = NULL;
    close(file_des);
}

int MemFile::Read(unsigned char *buf,int len){
    int rlen = 0;
    if(file_size < MEM_FILE_MAX_SIZE){
        if(buff != NULL && buff_offset + len > file_size){
            rlen = file_size - buff_offset;
        }else{
            rlen = len;
        }
        memcpy(buff,file_root + buff_offset,len);
        buff_offset += rlen;
    }else{

    }
}


int MemFile::Seek(int where,int offset){

}

int MemFile::ReadLine(unsigned char *buf,int len){

}
int MemFile::ReadTerminating(unsigned char *buff,int len,unsigned char terminate){

}

int MemFile::Write(const unsigned char *buf,int len){

}




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
