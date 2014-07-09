#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void init_list_head(list_head_t *list_head_ptr){
    list_head_ptr->prev = list_head_ptr;
    list_head_ptr->next = list_head_ptr;
}


void release_list(list_head_t *list_head_ptr,release_func pfn){
    list_head_t *tmp_head = list_head_ptr->next; 
    while(tmp_head != list_head_ptr){ 
        remove_list_item(tmp_head);
        if(pfn != NULL){
            pfn(tmp_head); 
        }else{
            printf("release list head point as default\n");
            free(tmp_head);
        }
        tmp_head = NULL;
        tmp_head = list_head_ptr->next;
    } 
}



list_head_t* find_list_item(list_head_t *list_head_ptr,list_head_t *item,compare_func func){
    list_head_t *tmp = list_head_ptr->next ; 
    while(tmp != list_head_ptr){
        if(func(tmp,item) == 0){
            return tmp;
        }
        tmp  = tmp->next;
    }
    return NULL;
}


void insert_list_item_behind(list_head_t *item,list_head_t *insert_item){
    insert_item->prev = item;
    insert_item->next = item->next;
    item->next = insert_item;
}

void insert_list_item_before(list_head_t *item,list_head_t *insert_item){
    insert_item->next = item;
    insert_item->prev = item->prev;
    item->prev = insert_item;
}

list_head_t *remove_list_item(list_head_t *remove_item){
    if(remove_item->prev == remove_item){
        printf("xxxx get a unqueue item or head \n");
        return remove_item;
    }
    remove_item->prev->next = remove_item->next;
    remove_item->next->prev = remove_item->prev;
    return remove_item;
}

