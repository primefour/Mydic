#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include"list.h"

/* functions of memory */
#define TOOLS_TEST_SPACE (sizeof(unsigned int))
#define TOOLS_INIT_PATTERN 0xff
#define CHAR_TYPE 4
#define PATH_LENGTH_LIMIT (4096)


typedef struct mem_item_info {
    list_head_t item;
    void *addr;
    long ref;
    char file[PATH_LENGTH_LIMIT];
    long line;
    long size;
}mem_item_info_t;


typedef struct mem_list{
    pthread_mutex_t mutex;
    list_head_t mem_head;
    int item_count;
}mem_list_t;

void tools_dump_item_error_info(mem_item_info_t *ptr,const char *str);
void init_global_env();
void release_global_env();
int mem_item_compare_func(list_head_t *list_item,void *find_item);
list_head_t *find_mem_list_item(mem_list_t *mem_list_head_ptr,list_head_t *item);
void insert_mem_list_item(mem_list_t *mem_list_head_ptr,list_head_t *insert_item);
mem_item_info_t *get_mem_list_item();
void *tools_malloc(int size,const char *file_name,int line);
int tools_check_free_point(mem_item_info_t *mem_ptr);
void tools_dump_item_info();
void tools_dump_item_error_info(mem_item_info_t *ptr,const char *str);
void tools_free(void *ptr);
void tools_get_leak_mem();
char* tools_strdup( const char *str, const char*file_name, int line);
//////////////////////////////////////////////////////////////////////////////////////////////
//global list
mem_list_t  mem_list_head;

void init_global_env(){
    mem_list_t* mem_head_ptr = &mem_list_head;
    memset(mem_head_ptr,0,sizeof(mem_list_t));
    pthread_mutex_init(&mem_head_ptr->mutex,NULL);
    init_list_head(&(mem_head_ptr->mem_head));
}

void release_global_env(){
    list_head_t *tmp_head = &(mem_list_head.mem_head);
    list_head_t *tmp_item = tmp_head->next;

    mem_item_info_t *tmp_mem_info_item= NULL;
    printf("item count = %d  \n",mem_list_head.item_count);
    while(tmp_item != tmp_head){
        mem_item_info_t *tmp_mem_info_item = contain_of(tmp_item,mem_item_info_t,item);
        if(tmp_mem_info_item->ref > 0){
            tools_dump_item_error_info(tmp_mem_info_item,"memory leak");
            printf("addr = %p ,ref = %ld ,file = %s ,line = %ld ",
                    tmp_mem_info_item->addr,tmp_mem_info_item->ref,tmp_mem_info_item->file,tmp_mem_info_item->line);
            printf("\n");
            free(tmp_mem_info_item->addr);
            tmp_mem_info_item->ref --;
        }
        tmp_item = tmp_item->next;
        //remove the item
        remove_list_item(&(tmp_mem_info_item->item));
        free(tmp_mem_info_item);

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
int mem_item_compare_func(list_head_t *list_item,void *find_item){
    mem_item_info_t *mem_list_item = contain_of(list_item,mem_item_info_t,item);
    mem_item_info_t *mem_find_item = (mem_item_info_t*) find_item;
    if(mem_list_item->addr == mem_find_item->addr){
        return 0;
    }else{
        return 1;
    }
}

list_head_t *find_mem_list_item(mem_list_t *mem_list_head_ptr,list_head_t *item){
    list_head_t *result = NULL;
    result = find_list_item(&(mem_list_head_ptr->mem_head),item,mem_item_compare_func);
    return result;
}


void insert_mem_list_item(mem_list_t *mem_list_head_ptr,list_head_t *insert_item){
    insert_list_item_behind(&(mem_list_head_ptr->mem_head),insert_item);
    mem_list_head_ptr->item_count ++;
}



mem_item_info_t *get_mem_list_item(){
    mem_item_info_t *mem_item_ptr = NULL;
    mem_item_ptr = (mem_item_info_t *)malloc(sizeof(mem_item_info_t));
    if(mem_item_ptr == NULL){
        printf("xxxx get a mem item failed,the result may be incorrect\n");
        assert(0);
        return NULL;
    }
    memset(mem_item_ptr,0,sizeof(mem_item_info_t));
    init_list_head(&mem_item_ptr->item);
    return mem_item_ptr;
}




void *tools_malloc(int size,const char *file_name,int line){
    if(size == 0){
        printf("xxxx get a allocation memory size is zero");
        return NULL;
    }
    int mem_size = size + TOOLS_TEST_SPACE *2;

    mem_item_info_t *mem_item_ptr = get_mem_list_item();

    strncpy(mem_item_ptr->file,file_name,PATH_LENGTH_LIMIT);
    mem_item_ptr->line = line;
    mem_item_ptr->size = size;
    mem_item_ptr->addr = malloc(mem_size);
    mem_item_ptr->ref ++;
    memset(mem_item_ptr->addr,TOOLS_INIT_PATTERN,mem_size);

    mem_item_info_t *result_mem_item_ptr = NULL;
    list_head_t *result_item_ptr = NULL;

    pthread_mutex_lock(&(mem_list_head.mutex));
    result_item_ptr = find_mem_list_item(&mem_list_head,&(mem_item_ptr->item));
    if(result_item_ptr != NULL){
        result_mem_item_ptr = contain_of(result_item_ptr,mem_item_info_t,item);
        if(result_mem_item_ptr->ref == 0){
            printf("remove a clean item \n");
        }else if(result_mem_item_ptr->ref > 0){
            printf("remove a dirty item and free buffer\n");
            free(result_mem_item_ptr->addr);
        }else{
            printf("remove a dirty item \n");
        }
        //remove the item
        remove_list_item(&(result_mem_item_ptr->item));
        free(result_mem_item_ptr);
        mem_list_head.item_count --;
    }
    //insert to queue
    insert_mem_list_item(&mem_list_head,&(mem_item_ptr->item));
    pthread_mutex_unlock(&(mem_list_head.mutex));
    return  (void *)(mem_item_ptr->addr + TOOLS_TEST_SPACE);
}


int tools_check_free_point(mem_item_info_t *mem_ptr){
    unsigned char *tmp_head = (unsigned char *)(mem_ptr->addr);
    //check head overwrite
    int i = 0;
    int ret = 0;
    while(i < TOOLS_TEST_SPACE){
        if(*tmp_head != TOOLS_INIT_PATTERN ){
            ret = -1;
        }
        tmp_head ++;
        i++;
    }
    //check tail overwrite
    unsigned char *tmp_tail = (unsigned char *)(mem_ptr->addr + mem_ptr->size +TOOLS_TEST_SPACE);
    i = 0;
    while(i < TOOLS_TEST_SPACE){
        if(*tmp_tail != TOOLS_INIT_PATTERN ){
            ret = -1;
        }
        tmp_tail ++;
        i++;
    }
    return ret;
}


void tools_dump_item_info(){
    list_head_t *tmp_head = &(mem_list_head.mem_head);
    list_head_t *tmp_item = tmp_head->next;

    mem_item_info_t *tmp_mem_info_item= NULL;
    printf("item count = %d  \n",mem_list_head.item_count);
    while(tmp_item != tmp_head){
        mem_item_info_t *tmp_mem_info_item = contain_of(tmp_item,mem_item_info_t,item);

        printf("addr = %p ,ref = %ld ,file = %s ,line = %ld ",
            tmp_mem_info_item->addr,tmp_mem_info_item->ref,tmp_mem_info_item->file,tmp_mem_info_item->line);
        tmp_item = tmp_item->next;
        printf("\n");
    }
}



void tools_dump_item_error_info(mem_item_info_t *ptr,const char *str){
    printf("%s error file %s line %ld \n",str,ptr->file,ptr->line);
}

void tools_free(void *ptr){
    int ret = 0;
    mem_item_info_t tmp_mem_item = {0};
    tmp_mem_item.addr = ptr - TOOLS_TEST_SPACE;
    mem_item_info_t *result_mem_item_ptr = NULL;
    list_head_t *result_item_ptr = NULL;

    pthread_mutex_lock(&(mem_list_head.mutex));
    result_item_ptr = find_mem_list_item(&mem_list_head,&(tmp_mem_item.item));
    if(result_item_ptr != NULL){
        result_mem_item_ptr = contain_of(result_item_ptr,mem_item_info_t,item);
        if(result_mem_item_ptr->ref <= 0){
            printf("xxxx get a multiple free point \n");
            tools_dump_item_error_info(result_mem_item_ptr,"multiple free");
        }else{
            //check head and tail overwrite
            if(tools_check_free_point(result_mem_item_ptr) < 0){
                tools_dump_item_error_info(result_mem_item_ptr,"overwrite");
            }
            //free the addr and don't assign NULL to it
            free(result_mem_item_ptr->addr);
        }
        result_mem_item_ptr->ref-- ;
    }else{
        //point from outside or error point
        printf("point from outside or error point %p",ptr);
        //try to free it
        free(ptr);
    }
    pthread_mutex_unlock(&(mem_list_head.mutex));
}



void tools_get_leak_mem(){
    list_head_t *tmp_head = &(mem_list_head.mem_head);
    list_head_t *tmp_item = tmp_head->next;

    mem_item_info_t *tmp_mem_info_item= NULL;
    printf("item count = %d  \n",mem_list_head.item_count);
    while(tmp_item != tmp_head){
        mem_item_info_t *tmp_mem_info_item = contain_of(tmp_item,mem_item_info_t,item);
        if(tmp_mem_info_item->ref > 0){
            tools_dump_item_error_info(tmp_mem_info_item,"memory leak");
            printf("addr = %p ,ref = %ld ,file = %s ,line = %ld ",
                    tmp_mem_info_item->addr,tmp_mem_info_item->ref,tmp_mem_info_item->file,tmp_mem_info_item->line);
            printf("\n");
        }
        tmp_item = tmp_item->next;
    }
}



char* tools_strdup( const char *str, const char*file_name, int line){
    if(str == NULL){
        printf("tools_strdup get a null point\n");
    }
    int length = strlen(str);
    //printf("length = %d \n",length);
    if(length > 1024 *8){
        printf("Atention get a very long string \n");
    }
    length += CHAR_TYPE;
    char *cpy_str = NULL;
    cpy_str = (char *)tools_malloc(length,file_name,line);
    memset(cpy_str,0,length);
    if(cpy_str != NULL){
        strncpy(cpy_str,str,strlen(str));
        //printf("cpy_str = %s \n",cpy_str);
    }
    return cpy_str;
}

















