#include"Stardict.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

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
        printf("data length = %d ,data = %s type = %d ",meta_item->data_length,meta_item->data,meta_item->type);
    }else{
        printf("###special type data length = %d , type = %d ",meta_item->data_length,meta_item->type);
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
    }
}
