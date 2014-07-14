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

int BufferCache::write(unsigned char *buf,int len){
    return 0;
}
int BufferCache::lseek(int whence,int offset){
    return 0;
}

int BufferCache::readline(unsigned char *buf,int len){
    return 0;
}




File::File(const char *path){
    fd =-1;
    file_type = ORDINARY_FILE_TYPE;
    memset(file_path,0,MAX_PATH_LENGTH);
    if(path != NULL){
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
}


File::~File(){
    if(fd >= 0){
        close(fd);
    }
}

int file_compare_func(list_head_t *item1,void *data){
    pfn_check_file_list *tmp_check_item = contain_of(item1,pfn_check_file_list,list);
    if(tmp_check_item->pfn((unsigned char*)data)){
        return 0;
    }else{
        return 1;
    }
}


int File::readline(unsigned char *buf,int len){
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

int File::write(const unsigned char *buf,int len){
    int ret = -1;
    const char *ptr = buf;
    //printf("buf = %s len = %d ",buf,len);
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


int File::read(unsigned char *buf,int len){
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

int File::check_file_type(char *path){
    File tmp_file(path);
    unsigned char buff[1024]={0};
    tmp_file.open(0);
    tmp_file.read(buff,sizeof(buff));
    list_head_t *result = find_list_item(&check_list,buff,file_compare_func,);
    if(result != NULL){
        pfn_check_file_list *tmp_check_item = contain_of(result,pfn_check_file_list,list);
        return tmp_check_item->type;
    }else{
        return  ORDINARY_FILE_TYPE ;
    }
}

static  void add_check_func(pfn_check_file_type pfn,int type){
    pfn_check_file_list *tmp = (pfn_check_file_list *)malloc(sizeof(pfn_check_file_list));
    if(tmp == NULL){
        printf("%s error %d \n",__func__,__LINE__);
        assert(0);
    }else{
        memset(tmp,0,sizeof(pfn_check_file_list));
        init_list_head(&(tmp->list));
        tmp->pfn = pfn;
        tmp->type = type;
    }
}

static File* MakeFileInstance(void *data,DIC_FILE_TYPE file_type){
    File *tmp = NULL:
    switch(file_type){
        case GZIP_FILE_TYPE:
            tmp = new GzipFile((char *)data);
            break;
        default:
            tmp = new File((char *)data);
    }
    return tmp;
}

