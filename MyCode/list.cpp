#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"memory_test_tool.h"


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



list_head_t* find_list_item(list_head_t *list_head_ptr,void *data,compare_func func){
    list_head_t *tmp = list_head_ptr->next ; 
    //printf("list_head_ptr = %ld ,tmp = %ld \n",list_head_ptr,tmp);
    while(tmp != list_head_ptr){
        if(func(tmp,data) == 0){
            return tmp;
        }
        tmp  = tmp->next;
    }
    return NULL;
}


list_head_t *get_last_item(list_head_t *list_head_ptr){
    if(list_head_ptr != NULL &&  list_head_ptr != list_head_ptr->prev){
        return list_head_ptr->prev;
    }else{
        return NULL;
    }
}


void add_list_item(list_head_t * prev_item,list_head_t *next_item,list_head_t *insert_item){
    prev_item->next = insert_item;
    insert_item->prev = prev_item;
    insert_item->next = next_item;
    next_item->prev = insert_item;
}


void insert_list_item_behind(list_head_t *item,list_head_t *insert_item){
    add_list_item(item,item->next,insert_item);
}

void insert_list_item_ahead(list_head_t *item,list_head_t *insert_item){
    add_list_item(item->prev,item,insert_item);
}


void remove_list_item(list_head_t *prev_item,list_head_t *next_item,list_head_t *remove_item){
    prev_item->next = next_item;
    next_item->prev = prev_item;
    remove_item->next = remove_item;
    remove_item->prev = remove_item;
}

list_head_t *remove_list_item(list_head_t *remove_item){
    remove_list_item(remove_item->prev,remove_item->next,remove_item);
    return remove_item;
}

