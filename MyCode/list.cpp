#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"memory_test_tool.h"


List::List(const List &list){
    head.next = list.head.next;
    head.prev = list.head.prev;
}

List::List(){
    compare_func = default_list_compare;
    destroy_func = default_list_destroy;
    init_list_head();
}

List::List(pfn_list_compare compare,pfn_list_destroy destroy){
    if(compare != NULL){
        compare_func = compare;
    }else{
        compare_func = default_list_compare;
    }
    if(destroy != NULL){
        destroy_func = destroy;
    }else{
        destroy_func = default_list_destroy;
    }
    init_list_head();
}

List::~List(){
    release_list();
}

void List::set_fpn(pfn_list_compare compare,pfn_list_destroy destroy){
    if(compare != NULL){
        compare_func = compare;
    }else{
        compare_func = default_list_compare;
    }
    if(destroy != NULL){
        destroy_func = destroy;
    }else{
        destroy_func = default_list_destroy;
    }
}

void List::init_list_item(list_head_t *item){
    memset(item,0,sizeof(list_head_t));
    item->prev = item;
    item->next = item;
}


void List::init_list_head(){
    init_list_item(&head);
}

void List::remove_list_item_(list_head_t *prev_item,list_head_t *next_item,list_head_t *remove_item){
    prev_item->next = next_item;
    next_item->prev = prev_item;
    remove_item->next = remove_item;
    remove_item->prev = remove_item;
}


void List::release_list(){
    list_head_t *tmp_head = head.next; 
    while(tmp_head != &head){ 
        remove_list_item_(tmp_head->prev,tmp_head->next,tmp_head);
        destroy_func(tmp_head->data);
        free(tmp_head);
        tmp_head = head.next;
    } 
}

void List::dump_list(){
    list_head_t *tmp_head = head.next; 
    while(tmp_head != &head){ 
        printf("%ld  ",(long)(tmp_head->data));
        tmp_head = tmp_head->next;
    } 
}


void* List::find_list_item(void *data){
    list_head_t *tmp = head.next ; 
    while(tmp != &head){
        if(compare_func(tmp->data,data) == 0){
            return tmp->data;
        }
        tmp  = tmp->next;
    }
    return NULL;
}


void List::add_list_item_(list_head_t * prev_item,list_head_t *next_item,list_head_t *insert_item){
    prev_item->next = insert_item;
    insert_item->prev = prev_item;
    insert_item->next = next_item;
    next_item->prev = insert_item;
}

list_head_t* List::get_new_item(){
    list_head_t *new_item = (list_head_t *)malloc(sizeof(list_head_t));
    init_list_item(new_item);
    return new_item;
}

void List::insert_list_tail(void *data){
    list_head_t *new_item = get_new_item();
    assert(new_item != NULL);
    new_item->data = data;
    add_list_item_(head.prev,&head,new_item);
}

void List::insert_list_head(void *data){
    list_head_t *new_item = get_new_item();
    assert(new_item != NULL);
    new_item->data = data;
    add_list_item_(&head,head.next,new_item);
}

void* List::get_prev_item(void *data){
    list_head_t *tmp = head.next ; 
    while(tmp != &head){
        if(compare_func(tmp->data,data) == 0){
            if(tmp->prev != &head){
                return tmp->prev->data;
            }else{
                return NULL;
            }
        }
        tmp  = tmp->next;
    }
    if(&head != head.prev){
        return head.prev->data;
    }
}

void* List::get_next_item(void *data){
    list_head_t *tmp = head.next ; 
    while(tmp != &head){
        if(compare_func(tmp->data,data) == 0){
            if(tmp->next != &head){
                return tmp->next->data;
            }else{
                return NULL;
            }
        }
        tmp  = tmp->next;
    }
    if(&head != head.next){
        return head.next->data;
    }
}


void* List::insert_list_local(void *prev_data,void *data){
    list_head_t *tmp = head.next ; 
    while(tmp != &head){
        if(compare_func(tmp->data,data) == 0){
            list_head_t *new_item = get_new_item();
            assert(new_item != NULL);
            new_item->data = data;
            add_list_item_(tmp,tmp->next,new_item);
            return data;
        }
        tmp  = tmp->next;
    }
    return NULL;
}

void List::remove_list_item(void *data){
    list_head_t *tmp = head.next ; 
    while(tmp != &head){
        if(compare_func(tmp->data,data) == 0){
            remove_list_item_(tmp->prev,tmp->next,tmp);
            destroy_func(tmp->data);
            free(tmp);
            return;
        }
        tmp  = tmp->next;
    }
}

int List::default_list_compare(void *data1,void *data2){
    if(data1 == data2){
        return 0;
    }else if(data1 < data2){
        return -1;
    }else{
        return 1;
    }
}

void List::default_list_destroy(void *data){
    if(data != NULL){
        free(data);
    }
}
