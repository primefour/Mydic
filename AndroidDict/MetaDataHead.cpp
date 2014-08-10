#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>
#include"MetaDataHead.h"
#include"memory_test_tool.h"

MetaDataHeader::MetaDataHeader(){
    memset(&meta_data_head,0,sizeof(meta_data_head_t));
}

void MetaDataHeader::update_meta_data_head(off_t offset,int data_len){
    printf("%s offset = %ld  data lenght = %d \n",__func__,offset,data_len);
    if(meta_data_head.data != NULL){
        free(meta_data_head.data);
        meta_data_head.data = NULL;
        memset(&meta_data_head,0,sizeof(meta_data_head_t));
    }
    meta_data_head.original_offset = offset;
    meta_data_head.data_size = data_len;
    meta_data_head.data = (unsigned char *)malloc(data_len +1);
    memset(meta_data_head.data,0,data_len+1);
}
off_t MetaDataHeader::get_original_offset(){
    return meta_data_head.original_offset;
}

unsigned char *MetaDataHeader::get_data_ptr(){
    return meta_data_head.data;
}
int MetaDataHeader::get_data_length(){
    return meta_data_head.data_size;
}


MetaDataHeader::MetaDataHeader(off_t original_offset,int data_size){
    memset(&meta_data_head,0,sizeof(meta_data_head_t));
    meta_data_head.original_offset = original_offset;
    meta_data_head.data_size =data_size;
    meta_data_head.data = (unsigned char *)malloc(data_size +1);
    memset(meta_data_head.data,0,data_size +1);
}


void MetaDataHeader::update_meta_item(int type,unsigned char *data,int data_len){
    printf("type = %d meta_item->data = %s \n datalen = %d ",type,data,data_len);
    if(type >= 0 && type < DICT_MAX_TYPE){
        meta_data_head.meta_data[type].data = data;
        meta_data_head.meta_data[type].data_length = data_len;
    }else{
        printf("get a error type \n");
    }
}

void MetaDataHeader::dump_meta_item(meta_data_t *meta_item,int type){
    if(meta_item->data != NULL){
        if(type != DICT_ATTACH_TYPE && type != DICT_PIC_TYPE &&
                type !=  DICT_SOUND_TYPE){
            printf("data length = %d ,data = %s type = %d \n",meta_item->data_length,meta_item->data,type);
        }else{
            printf("###special type data length = %d , type = %d \n",meta_item->data_length,type);
        }
    }
}

void MetaDataHeader::dump_meta_data_head(){
    int i = 0;
    while(i < DICT_MAX_TYPE){
        dump_meta_item(&meta_data_head.meta_data[i],i);
        i++;
    }
}

MetaDataHeader::~MetaDataHeader(){
    if(meta_data_head.data != NULL){
        free(meta_data_head.data);
    }
}

