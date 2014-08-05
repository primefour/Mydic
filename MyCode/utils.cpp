#include<string>
#include"utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>
#include"utils.h"
#include"memory_test_tool.h"

int split_path_no_suffix(const char *file_path,char *file_main_path,int path_len ,char *file_name,int len){
    if(file_path == NULL){
        return -1;
    }
    const char *pdash = strrchr(file_path,'/');
    const char *pdot = strrchr(file_path,'.');
    const char *file_name_begin = NULL;
    const char *file_name_end = NULL;

    if(pdash){
        file_name_begin = (pdash+1);
    }else{
        file_name_begin = file_path;
    }
    if(pdot && pdot > pdash){
        file_name_end = pdot;
    }else{
        file_name_end = file_path + strlen(file_path) +1;
    }
    if(len < file_name_end - file_name_begin){
        printf("path_len is more small \n");
        return -1 ;
    }else{
        memcpy(file_name,file_name_begin,file_name_end - file_name_begin);
    }

    if(path_len < file_name_begin - file_path){
        printf("path_len is more small \n");
        return -1;
    }else{
        memcpy(file_main_path,file_path,file_name_begin - file_path);
    }

    printf("%s file_main_path = %s file_name = %s \n",__func__,file_main_path,file_name);
    return 0;
}


char *get_path_no_suffix(const char *file_path,char *file_name,int len){
    const char *pdash = strrchr(file_path,'/');
    if(pdash == NULL){
        pdash = file_path;
    }
    const char *pdot = strchr(pdash,'.');
    if(len < pdot - file_path){
        printf("len is very small \n");
        assert(0);
        return NULL;
    }else{
        strncpy(file_name,file_path, pdot - file_path);
    }
    printf("file_name = %s \n",file_name);
    return file_name;
}


char *get_path_suffix(const char *file_path,char *suffix,int len){
    const char *pdash = strrchr(file_path,'/');
    if(pdash == NULL){
        pdash = file_path;
    }
    const char *pdot = strchr(pdash,'.');
    if(pdot != NULL){
        strncpy(suffix,pdot,len);
    }else{
        return NULL;
    }
    printf("suffix = %s \n",suffix);
    return suffix;

}



MetaDataHeader::MetaDataHeader(off_t original_offset,int data_size){
    memset(&meta_data_head,0,sizeof(meta_data_head_t));
    meta_data_head.original_offset = original_offset;
    meta_data_head.data_size =data_size;
    meta_data_head.data = (unsigned char *)malloc(data_size);
}


void MetaDataHeader::update_meta_item(int type,unsigned char *data,int data_len){
    if(type > 0 && type < DICT_MAX_TYPE){
        meta_data_head.meta_data[type].data = data;
        meta_data_head.meta_data[type].data_length = data_len;
    }else{
        printf("get a error type \n");
    }
}

void MetaDataHeader::dump_meta_item(meta_data_t *meta_item,int type){
    if(type != DICT_ATTACH_TYPE && type != DICT_PIC_TYPE &&
            type !=  DICT_SOUND_TYPE){
        printf("data length = %d ,data = %s type = %d \n",meta_item->data_length,meta_item->data,type);
    }else{
        printf("###special type data length = %d , type = %d \n",meta_item->data_length,type);
    }
}

void MetaDataHeader::dump_meta_data_head(){
    int i = 0;
    while(i < DICT_MAX_TYPE){
        dump_meta_item(&meta_data_head.meta_data[i],i);
    }
}

MetaDataHeader::~MetaDataHeader(){
    free(meta_data_head.data);
}

