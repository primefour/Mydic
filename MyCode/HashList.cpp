#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include"HashList.h"
#include"memory_test_tool.h"


unsigned long default_string_hash_func(void *data){
    const char *ptr;
    unsigned int val;
    val = 0;
    ptr = (char *)data;
    while(*ptr != '\0'){
        unsigned int tmp = 0;
        val = (val<<4) + (*ptr);
        if(tmp = (val&0xf0000000)){
            val = val ^(tmp >> 24);
            val = val ^tmp;
        }
        ptr ++;
    }
    return val;
}

unsigned long HashList::default_hash(void *data){
    return (long)data;
}

int HashList::default_hash_compare(void *data,void *data2){
    if((long)data == (long)data2){
        return 0;
    }else{
        return 1;
    }
}

void HashList::default_hash_destroy(void *data){
    if(data != NULL){
        free(data);
    }
}

HashList::HashList(){
    array_size = DEFAULT_ARRAY_LENGTH ;
    hash_func = default_hash;
    compare_func = default_hash_compare;
    destroy_func = default_hash_destroy;
    array = (List **)malloc(array_size * sizeof(List *));
    int i = 0;
    while(i < array_size){
        array[i] = new List(default_hash_compare,default_hash_destroy);
    }
}

void HashList::set_pfn(pfn_hash func,pfn_list_compare compare,pfn_list_destroy destroy){
    hash_func = func;
    int i = 0;
    while(i < array_size){
        array[i]->set_fpn(compare,destroy);
    }
}


void HashList::hash_insert(void *data){
    int local = hash_func(data); 
    local %= array_size; 
    List *list = array[local];
    if(list->find_list_item(data) == NULL){
        list->insert_list_tail(data);
    }else{
        printf("item has already been in the list\n");
    }
}

void* HashList::hash_find(void *data){
    int local = hash_func(data); 
    local %= array_size; 
    List *list = array[local];
    return list->find_list_item(data);
}

void HashList::hash_remove(void *data){
    int local = hash_func(data); 
    local %= array_size; 
    List *list = array[local];
    if(list->find_list_item(data)){
        list->remove_list_item(data);
    }else{
        printf("there is no member equals to the item\n");
    }
}


HashList::HashList(pfn_hash func,pfn_list_compare compare,pfn_list_destroy destroy,long array_length){
    hash_func = func;
    destroy_func = destroy;
    compare_func = compare;
    array_size = array_length;
    array = (List **)malloc(array_size * sizeof(List *));
    int i = 0;
    while(i < array_size){
        array[i] = new List(compare,destroy);
    }
}


HashList::~HashList(){
    int i = 0 ;
    while(i < array_size){
        delete array[i];
    }

    if(array != NULL){
        free(array);
    }
}
