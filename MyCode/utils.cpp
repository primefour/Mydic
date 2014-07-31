#include<string>
#include"utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>
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

meta_data_t *get_new_meta_item(){
    meta_data_t *tmp_meta = (meta_data_t *)malloc(sizeof(meta_data_t));
    if(tmp_meta == NULL){
        printf("get item failed %s \n",__func__);
        assert(0);
    }
    memset(tmp_meta,0,sizeof(meta_data_t));
    init_list_head(&(tmp_meta->list));
    return tmp_meta ;
}

void dump_meta_item(meta_data_t *meta_item){
    if(meta_item->type != DICT_ATTACH_TYPE && meta_item->type != DICT_PIC_TYPE &&
            meta_item->type !=  DICT_SOUND_TYPE){
        printf("data length = %d ,data = %s type = %d \n",meta_item->data_length,meta_item->data,meta_item->type);
    }else{
        printf("###special type data length = %d , type = %d \n",meta_item->data_length,meta_item->type);
    }
}

meta_data_head *get_new_meta_head(){
    meta_data_head *tmp_meta_head = (meta_data_head *)malloc(sizeof(meta_data_head ));
    if(tmp_meta_head == NULL){
        printf("get head failed %s \n",__func__);
        assert(0);
    }
    memset(tmp_meta_head ,0,sizeof(meta_data_head));
    init_list_head(&(tmp_meta_head->head));
    return tmp_meta_head;
}

void head_release_func(void *data){
    meta_data_t *tmp_meta = contain_of(data,meta_data_t,list);
    free(tmp_meta);
}

void release_meta_head(meta_data_head *phead){
    release_list(&(phead->head),head_release_func);
    free(phead->data);
    free(phead);
}


void dump_meta_head(meta_data_head *phead){
    list_head_t *tmp_next = phead->head.next;
    while(tmp_next != &(phead->head)){
        meta_data_t *tmp_meta = contain_of(tmp_next,meta_data_t,list);
        dump_meta_item(tmp_meta);
        tmp_next = tmp_next->next;
    }
}
