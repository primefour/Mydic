#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include"HashList.h"
#include"memory_test_tool.h"



HashList::HashList(pfn_hash func,pfn_hash_compare compare,pfn_hash_destroy destroy,long array_length){
    hash_func = func;
    destroy_func = destroy;
    compare_func = compare;
    if(array_length < 0){
        array_size  = DEFAULT_ARRAY_LENGTH;
    }else{
        array_size = array_length;
    }
    head_array = (hash_head_t*)malloc(array_size * sizeof(hash_head_t)); 
    item_count = 0;
    memset(head_array,0,sizeof(hash_head_t) * array_size);
}


HashList::~HashList(){
    int i = 0 ;
    while(i < array_size){
        hash_item_t *tmp = head_array[i].next;
        hash_item_t *tmp_next = NULL;
        while(tmp != NULL){
            destroy_func(tmp->data);
            tmp_next = tmp->next;
            free(tmp);
            tmp = tmp_next;
        }
        i++;
    }
    free(head_array);
}

void HashList::hash_insert(void *data){
    int local = hash_func(data); 
    local %= array_size; 
    //only insert at the head
    if(hash_find(data) == NULL){
        hash_item_t *tmp = (hash_item_t *)malloc(sizeof(hash_item_t));
        memset(tmp,0,sizeof(hash_item_t));
        tmp->data = data;
        tmp->next = head_array[local].next ;
        head_array[local].next = tmp;
        item_count ++;
    }else{
        printf("item has already been in the list\n");
    }
}

void* HashList::hash_find(const void *data){
    int local = hash_func(data); 
    local %= array_size; 
    hash_item_t *tmp = head_array[local].next;
    while(tmp != NULL){
        if(compare_func != NULL){
            if(compare_func(data,tmp->data) == 0){
                break;
            }
        }else{
            printf("no compare function error \n");
            tmp = NULL;
            break;
        }
        tmp = tmp->next;
    }
    return (tmp == NULL) ?NULL:tmp->data;
}

void HashList::hash_remove(const void *data){
    int local = hash_func(data); 
    local %= array_size; 
    hash_item_t *tmp = head_array[local].next;
    hash_item_t *prev = tmp;
    while(tmp != NULL){
        if(compare_func != NULL){
            if(compare_func(data,tmp->data) == 0){
                break;
            }
        }else{
            printf("no compare function error\n");
            tmp = NULL;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp != NULL){
        if(tmp == prev){
            head_array[local].next = NULL;
        }else{
            prev->next = tmp->next;
        }
        destroy_func(tmp->data);
        free(tmp);
        item_count --;
    }else{
        printf("no the item \n");
    }
}

int HashList::get_size(){
    return item_count;
}


