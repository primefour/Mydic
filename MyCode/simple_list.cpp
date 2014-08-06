#include"simple_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"memory_test_tool.h"


void init_simple_list_head(simple_list_head_t *simple_list_head_ptr){
    simple_list_head_ptr->prev = simple_list_head_ptr;
    simple_list_head_ptr->next = simple_list_head_ptr;
}


void release_list(simple_list_head_t *simple_list_head_ptr,release_func pfn){
    simple_list_head_t *tmp_head = simple_list_head_ptr->next; 
    while(tmp_head != simple_list_head_ptr){ 
        remove_list_item(tmp_head);
        if(pfn != NULL){
            pfn(tmp_head); 
        }else{
            printf("release list head point as default\n");
            free(tmp_head);
        }
        tmp_head = NULL;
        tmp_head = simple_list_head_ptr->next;
    } 
}



simple_list_head_t* find_list_item(simple_list_head_t *simple_list_head_ptr,void *data,compare_func func){
    simple_list_head_t *tmp = simple_list_head_ptr->next ; 
    //printf("simple_list_head_ptr = %ld ,tmp = %ld \n",simple_list_head_ptr,tmp);
    while(tmp != simple_list_head_ptr){
        if(func(tmp,data) == 0){
            return tmp;
        }
        tmp  = tmp->next;
    }
    return NULL;
}


simple_list_head_t *get_last_item(simple_list_head_t *simple_list_head_ptr){
    if(simple_list_head_ptr != NULL &&  simple_list_head_ptr != simple_list_head_ptr->prev){
        return simple_list_head_ptr->prev;
    }else{
        return NULL;
    }
}


void add_list_item(simple_list_head_t * prev_item,simple_list_head_t *next_item,simple_list_head_t *insert_item){
    prev_item->next = insert_item;
    insert_item->prev = prev_item;
    insert_item->next = next_item;
    next_item->prev = insert_item;
}


void insert_list_item_behind(simple_list_head_t *item,simple_list_head_t *insert_item){
    add_list_item(item,item->next,insert_item);
}

void insert_list_item_ahead(simple_list_head_t *item,simple_list_head_t *insert_item){
    add_list_item(item->prev,item,insert_item);
}


void remove_list_item(simple_list_head_t *prev_item,simple_list_head_t *next_item,simple_list_head_t *remove_item){
    prev_item->next = next_item;
    next_item->prev = prev_item;
    remove_item->next = remove_item;
    remove_item->prev = remove_item;
}

simple_list_head_t *remove_list_item(simple_list_head_t *remove_item){
    remove_list_item(remove_item->prev,remove_item->next,remove_item);
    return remove_item;
}

