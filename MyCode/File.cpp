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
#include<assert.h>
#include"GzipFile.h"
#include"list.h"
#include"memory_test_tool.h"

List<pfn_check_file> GCheckList;

SimpleFile::SimpleFile(const char *path){
    mfd =-1;
    memset(mfile_path,0,MAX_PATH_LENGTH);
    if(path != NULL){
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
}

SimpleFile::~SimpleFile(){
    if(fd >= 0){
        close(fd);
    }
}

int SimpleFile::Seek(int whence,int offset){
    if(fd >= 0){
        return ::lseek(fd,offset,whence);
    }else{
        printf("%s\n","fd is negative");
        return -1;
    }
}

int SimpleFile::Write(const unsigned char *buf,int len){
    int ret = -1;
    const unsigned char *ptr = buf;
    //printf("buf = %s len = %d ",buf,len);
    if(fd >= 0 && ptr != NULL){
        while(len > 0){
            ret = ::write(fd,ptr,len);
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
    if(fd >= 0){
       ret = ::read(fd,buf,len); 
    }else{
        ALOGE("%s","fd is negative");
    }
    return ret;
}

int File::open(int mode){
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

static int file_compare_func(void *data1,void *data2){
    pfn_check_file *tmp_check_item = (pfn_check_file *)data1;
    int buff_len = 1024;
    if(tmp_check_item->pfn((unsigned char*)data2,&buff_len)){
        return 0;
    }else{
        return 1;
    }
}

int File::get_file_type(const char *path){
    File tmp_file(path);
    unsigned char buff[1024]={0};
    tmp_file.open(0);
    tmp_file.read(buff,sizeof(buff));
    pfn_check_file *result = (pfn_check_file *)pcheck_list->find_list_item(buff);

    if(result != NULL){
        return result->type;
    }else{
        return ORDINARY_FILE_TYPE ;
    }
}

void File::Init_check_list(){
    if(pcheck_list == NULL){
        pcheck_list = new List(file_compare_func,NULL);
    }
}

void File::add_check_func(pfn_check_file_type pfn,DIC_FILE_TYPE_T type){
    Init_check_list();
    pfn_check_file *tmp = (pfn_check_file *)malloc(sizeof(pfn_check_file));
    if(tmp == NULL){
        printf("%s error %d \n",__func__,__LINE__);
        assert(0);
    }else{
        memset(tmp,0,sizeof(pfn_check_file));
        tmp->pfn = pfn;
        tmp->type = type;
        pcheck_list->insert_list_tail(tmp);
    }
}

void File::release_check_list(){
    delete pcheck_list;
    pcheck_list = NULL;
}

File* File:: MakeFileInstance(const void *data){
    File *tmp = NULL;
    Init_check_list();
    DIC_FILE_TYPE file_type = File::get_file_type(data);
    switch(file_type){
        case GZIP_FILE_TYPE:
            tmp = new GzipFile((char *)data);
            break;
        default:
            tmp = new File((char *)data);
    }
    return tmp;
}

/*
int readline(unsigned char *buf,int len){
    int ret = -1;
    unsigned char *ptr = buf;
    memset(buf,0,len);
    int i = 0;

    while((ret = ::read(fd,ptr,1) > 0) && (*ptr != '\n') && ++i < len){ 
        //printf("%c",*ptr);
        ptr++;
    }

    if(*ptr == '\n'){
        *ptr = '\0';
        return i;
    }else{
        *(buf+len-1)= '\0';
        return ret;
    }
}
*/

/*
int File::read_terminating_by(unsigned char *buf,int len,unsigned char terminate){
    int ret = -1;
    unsigned char *ptr = buf;
    memset(buf,0,len);
    int i = 0;

    while((ret = ::read(fd,ptr,1) > 0) && (*ptr != terminate ) && ++i < len){ 
        //printf("%c",*ptr);
        ptr++;
    }

    if(*ptr == terminate){
        *ptr = '\0';
        return i;
    }else{
        *(buf+len-1)= '\0';
        return ret;
    }
}
*/










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


int BufferCache::read(unsigned char *buf,int len){
    return 0;
}

int BufferCache::write(const unsigned char *buf,int len){
    return 0;
}
int BufferCache::lseek(int whence,int offset){
    return 0;
}

int BufferCache::readline(unsigned char *buf,int len){
    return 0;
}

