#include"GoldenStandardIO.h"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<stdexcept>
#include"AngelLog.h"
#define MEM_FILE_MAX_SIZE 7 * 1024 *1024

using namespace std;

MemFile::MemFile(const char *path,int mode):file_path(path){
    file_des = -1;
    file_root = NULL;
    file_size = 0;

    int def_mode = O_RDWR;
    if(mode != 0){
        def_mode = mode; 
    }
    file_des = ::open(path,def_mode);
    if(file_des < 0){
        angel_printfe("open file error %s \n",file_path.string());
        throw exception();//"file open error");
    }

    //check the sizeof file 
    file_size = lseek(file_des,0,SEEK_END);
    lseek(file_des,0,SEEK_SET);

    if(file_size <= MEM_FILE_MAX_SIZE){
        //using mmap
        file_root = (unsigned char *)mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_PRIVATE,file_des,0);
        if(file_root == NULL){
            angel_printfe("mmap file failed");
            close(file_des);
            throw exception();//"mmap file failed");
        }
        buff_len = file_size;
        buff_offset = 0;
    }else{
        //using cache
        file_root = new unsigned char[1+MEM_FILE_MAX_SIZE];

        if(file_root == NULL){
            angel_printfe("NO MEMORY FOR FILE \n");
            close(file_des);
            throw exception();//"mmap file failed");
        }
        file_root[MEM_FILE_MAX_SIZE]= 0;
        int n = read(file_des,file_root,MEM_FILE_MAX_SIZE);
        if(n != MEM_FILE_MAX_SIZE){
            close(file_des);
            delete[] file_root;
            angel_printfe("read file failed \n");
            throw exception();//"read file failed");
        }
        buff_len = MEM_FILE_MAX_SIZE;
        buff_offset = 0;
    }
}

MemFile::~MemFile(){
    if(file_size <= MEM_FILE_MAX_SIZE){
        //using mmap
        munmap(file_root,file_size);
    }else{
        if(file_root != NULL){
            delete[] file_root;
        }
    }
    file_root = NULL;
    close(file_des);
    file_des = -1;
}


int MemFile::Read(unsigned char *buf,int len){
    int rlen = 0;
    if(buf == NULL){
        return 0;
    }

    if(file_size < MEM_FILE_MAX_SIZE){
        if(buff_len < len){
            rlen = buff_len ;
        }else{
            rlen = len;
        }
        memcpy(buf,file_root + buff_offset,rlen);
        buff_offset += rlen;
        buff_len -= rlen;
        return rlen;
    }else{
        //for cache
        unsigned char *pos = buf ;
        int copy_len = len ;
        angel_printfi("file_root = %p , buff_len = %ld buff_offset = %ld \n",file_root,buff_len,buff_offset);
        while(copy_len > 0){
            if(buff_len > 0){
                if(copy_len > buff_len){
                    memcpy(pos,file_root + buff_offset,buff_len);
                    buff_offset += buff_len;
                    copy_len -= buff_len ;
                    pos += buff_len;
                    buff_len = 0;
                }else{
                    memcpy(pos,file_root + buff_offset,copy_len);
                    buff_offset += copy_len;
                    pos += copy_len;
                    buff_len -= copy_len;
                    copy_len -= copy_len;
                }
            }else{
                //file root is empty need read file
                buff_len  = read(file_des,file_root,MEM_FILE_MAX_SIZE);
                if(buff_len == 0){
                    //empty file
                    break;
                }else{
                    buff_offset  = 0;
                }
            }
        }
        angel_printfi("len = %d copy_len = %d file_root = %p , buff_len = %ld buff_offset = %ld \n",len ,copy_len,file_root,buff_len,buff_offset);
        return len - copy_len;
    }
}


int MemFile::Seek(int where,int offset){
    if(file_size < MEM_FILE_MAX_SIZE){
        switch(where){
            case SEEK_SET:{
                buff_offset = offset;
            }
            break;
            case SEEK_CUR:{
                buff_offset += offset;
            }
            break;
            case SEEK_END:{
                buff_offset = file_size + offset;
            }
            break;
            default :{
                return 0;
            }
        }

        if(buff_offset < 0){
            buff_offset = 0;
        }else if(buff_offset > file_size){
            buff_offset = file_size;
        }
        buff_len = file_size - buff_offset;
        return buff_offset;
    }else{
        if(where == SEEK_CUR){
            offset -= buff_len ;
        }
        buff_len = 0;
        return lseek(file_des,offset,where);
    }
}


int MemFile::ReadLine(unsigned char *buf,int len){
    return ReadTerminating(buf,len,'\n');
}

int MemFile::ReadTerminating(unsigned char *buff,int len,unsigned char terminate){
    int rlen = 0;
    if(buff == NULL){
        return 0;
    }
    int i  = 0;

    unsigned char *buff_ptr = buff;
    unsigned char *ptr = file_root + buff_offset;

    if(file_size < MEM_FILE_MAX_SIZE){
        while(i < len && buff_len){ 
            *buff_ptr = *ptr ;
            i++;
            buff_len --;
            buff_offset ++;
            buff_ptr++;
            if(*(ptr ++) == terminate ){
                break;
            }
        }
        return i;
    }else{
        //for cache
        while(i < len){ 
            if(buff_len > 0){
                *buff_ptr = *ptr ;
                buff_ptr++;
                i++;
                buff_len --;
                buff_offset ++;
                if(*(ptr ++) == terminate ){
                    break;
                }
            }else{
                //file root is empty need read file
                buff_len = read(file_des,file_root,MEM_FILE_MAX_SIZE);
                if(buff_len == 0){
                    //empty file
                    break;
                }else{
                    buff_offset  = 0;
                    ptr = file_root + buff_offset;
                }
            }
        }
        return i;
    }
}

int MemFile::Write(const unsigned char *buf,int len){
    angel_printfe("write failed \n");
    return 0;
}

SimpleFile::SimpleFile(const char *path,int mode,int permision):file_path(path){
    file_des = 0;
    int def_mode = O_RDWR;
    if(mode != 0){
        def_mode = mode; 
    }
    file_des = ::open(path,def_mode,permision);
    if(file_des < 0){
        angel_printfe("open file error %s \n",file_path.string());
        throw exception();//"open file error");
    }

}




SimpleFile::SimpleFile(const char *path,int mode):file_path(path){
    file_des = 0;
    int def_mode = O_RDWR;
    if(mode != 0){
        def_mode = mode; 
    }
    if(def_mode|O_CREAT){
        file_des = ::open(path,def_mode,0664);
    }else{
        file_des = ::open(path,def_mode);
    }
    if(file_des < 0){
        angel_printfe("open file error %s \n",file_path.string());
        throw exception();//"open file error");
    }
}


SimpleFile::~SimpleFile(){
    close(file_des);
    file_des = -1;
}


int SimpleFile::Seek(int whence,int offset){
    return ::lseek(file_des,offset,whence);
}

int SimpleFile::Write(const unsigned char *buf,int len){
    int ret = -1;
    const unsigned char *ptr = buf;
    if(ptr != NULL){
        while(len > 0){
            ret = ::write(file_des,ptr,len);
            if(ret >= 0){
                len -= ret;
                ptr += ret;
            }else{
                angel_printfe("%s \n","write failed");
                return -1;
            }
        }
    }else{
        return 0;
    }
    return ret;
}


int SimpleFile::Read(unsigned char *buf,int len){
    int ret = -1;
    ret = ::read(file_des,buf,len); 
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
    while(((ret = ::read(file_des,ptr,1)) > 0) && (*ptr != terminate ) && ++i < len){ 
        ptr++;
    }
    return i;
}
