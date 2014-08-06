#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include"simple_list.h"
#include<assert.h>
#include"BinTree.h"
#include"AvlTree.h"

/* functions of memory */
#define TOOLS_TEST_SPACE (sizeof(unsigned int))
#define TOOLS_INIT_PATTERN 0xff
#define CHAR_TYPE 4
#define PATH_LENGTH_LIMIT (4096)


#define LIST_MEM_TEST
//#define SIMPLE_SEARCH_TREE_MEM_TEST
//#define AVL_TREE_MEM_TEST

typedef struct mem_item_info {
    simple_list_head_t item;
    void *addr;
    long ref;
    char file[PATH_LENGTH_LIMIT];
    long line;
    long size;
}mem_item_info_t;

#ifdef LIST_MEM_TEST


typedef struct mem_list{
    pthread_mutex_t mutex;
    simple_list_head_t mem_head;
    int item_count;
}mem_list_t;

void tools_dump_item_error_info(mem_item_info_t *ptr,const char *str);
void init_global_env();
void release_global_env();
int mem_item_compare_func(simple_list_head_t *list_item,void *find_item);
simple_list_head_t *find_mem_list_item(mem_list_t *mem_simple_list_head_ptr,simple_list_head_t *item);
void insert_mem_list_item(mem_list_t *mem_simple_list_head_ptr,simple_list_head_t *insert_item);
mem_item_info_t *get_mem_list_item();
void *tools_malloc(int size,const char *file_name,int line);
int tools_check_free_point(mem_item_info_t *mem_ptr);
void tools_dump_item_info();
void tools_dump_item_error_info(mem_item_info_t *ptr,const char *str);
void tools_free(void *ptr,const char *file,int line );
//void tools_free(void *ptr);
void tools_get_leak_mem();
char* tools_strdup( const char *str, const char*file_name, int line);
//////////////////////////////////////////////////////////////////////////////////////////////
//global list
mem_list_t  mem_simple_list_head;

void init_global_env(){
    mem_list_t* mem_head_ptr = &mem_simple_list_head;
    memset(mem_head_ptr,0,sizeof(mem_list_t));
    pthread_mutex_init(&mem_head_ptr->mutex,NULL);
    init_simple_list_head(&(mem_head_ptr->mem_head));
}

void release_global_env(){
    simple_list_head_t *tmp_head = &(mem_simple_list_head.mem_head);
    simple_list_head_t *tmp_item = tmp_head->next;

    mem_item_info_t *tmp_mem_info_item= NULL;
    printf("item count = %d  \n",mem_simple_list_head.item_count);
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
int mem_item_compare_func(simple_list_head_t *list_item,void *find_item){
    mem_item_info_t *mem_list_item = contain_of(list_item,mem_item_info_t,item);
    mem_item_info_t *mem_find_item = (mem_item_info_t*) find_item;
    if(mem_list_item->addr == mem_find_item->addr){
        return 0;
    }else{
        return 1;
    }
}

simple_list_head_t *find_mem_list_item(mem_list_t *mem_simple_list_head_ptr,simple_list_head_t *item){
    simple_list_head_t *result = NULL;
    result = find_list_item(&(mem_simple_list_head_ptr->mem_head),item,mem_item_compare_func);
    return result;
}


void insert_mem_list_item(mem_list_t *mem_simple_list_head_ptr,simple_list_head_t *insert_item){
    insert_list_item_behind(&(mem_simple_list_head_ptr->mem_head),insert_item);
    mem_simple_list_head_ptr->item_count ++;
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
    init_simple_list_head(&mem_item_ptr->item);
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
    //printf("######################################%s###################%p\n",__func__,mem_item_ptr->addr);
    mem_item_ptr->ref ++;
    memset(mem_item_ptr->addr,TOOLS_INIT_PATTERN,mem_size);

    mem_item_info_t *result_mem_item_ptr = NULL;
    simple_list_head_t *result_item_ptr = NULL;

    pthread_mutex_lock(&(mem_simple_list_head.mutex));
    result_item_ptr = find_mem_list_item(&mem_simple_list_head,&(mem_item_ptr->item));
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
        mem_simple_list_head.item_count --;
    }
    //insert to queue
    insert_mem_list_item(&mem_simple_list_head,&(mem_item_ptr->item));
    pthread_mutex_unlock(&(mem_simple_list_head.mutex));
    return  (void *)((unsigned char *)(mem_item_ptr->addr) + TOOLS_TEST_SPACE);
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
    unsigned char *tmp_tail = (unsigned char *)((unsigned char *)(mem_ptr->addr) + mem_ptr->size +TOOLS_TEST_SPACE);
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
    simple_list_head_t *tmp_head = &(mem_simple_list_head.mem_head);
    simple_list_head_t *tmp_item = tmp_head->next;

    mem_item_info_t *tmp_mem_info_item= NULL;
    printf("item count = %d  \n",mem_simple_list_head.item_count);
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

void tools_free(void *ptr,const char *file,int line ){
    int ret = 0;
    printf("%s %s %d \n",__func__,file,line); 
    mem_item_info_t tmp_mem_item = {0};
    //printf("###################%s ########################%p \n",__func__,ptr);
    tmp_mem_item.addr = ((unsigned char *)ptr - TOOLS_TEST_SPACE);
    //printf("######################################%s###################%p\n",__func__,tmp_mem_item.addr);
    mem_item_info_t *result_mem_item_ptr = NULL;
    simple_list_head_t *result_item_ptr = NULL;
    pthread_mutex_lock(&(mem_simple_list_head.mutex));
    result_item_ptr = find_mem_list_item(&mem_simple_list_head,&(tmp_mem_item.item));
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
        /*
        if(result_mem_item_ptr->ref == 0){
            //remove the item
            remove_list_item(&(result_mem_item_ptr->item));
            free(result_mem_item_ptr);
            mem_simple_list_head.item_count --;
        }
        */
    }else{
        //point from outside or error point
        printf("point from outside or error point %p\n",ptr);
        //try to free it
        //free(ptr);
    }
    pthread_mutex_unlock(&(mem_simple_list_head.mutex));
}



void tools_get_leak_mem(){
    simple_list_head_t *tmp_head = &(mem_simple_list_head.mem_head);
    simple_list_head_t *tmp_item = tmp_head->next;

    mem_item_info_t *tmp_mem_info_item= NULL;
    printf("item count = %d  \n",mem_simple_list_head.item_count);
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
    //printf("######################%s#################3\n",__func__);
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
#endif 



static mem_item_info_t* get_new_mem_item_info(){
    mem_item_info_t* tmp = (mem_item_info_t*)malloc(sizeof(mem_item_info_t));
    assert(tmp != NULL);
    memset(tmp,0,sizeof(mem_item_info_t));
    return tmp;
}

static int mem_compare(const void *data1,const void *data2){
    mem_item_info_t *tmp1 =(mem_item_info_t *)data1;
    mem_item_info_t *tmp2 =(mem_item_info_t *)data2;
    //printf(" %s tmp1->addr = %p tmp2->addr =%p \n",__func__,tmp1->addr,tmp2->addr); 
    //printf("##########%d \n",(tmp1->addr > tmp2->addr));
    if(tmp1->addr > tmp2->addr){
        return 1;
    }else if(tmp1->addr < tmp2->addr){
        return -1;
    }else{
        //printf("######%s %d ############\n",__func__,__LINE__);
        return 0;
    }
    
}

static void mem_destroy(void *data){
    mem_item_info_t *tmp =(mem_item_info_t *)data;
    free(tmp->addr);
    free(tmp);
}

static void dump_item_error_info(mem_item_info_t *ptr,const char *str){
    printf("%s error file %s line %ld ref = %ld \n",str,ptr->file,ptr->line,ptr->ref);
}

static void mem_dump_data(void *data){
    mem_item_info_t *tmp =(mem_item_info_t *)data;
    dump_item_error_info(tmp,"memory leak");
    printf("addr = %p ,ref = %ld ,file = %s ,line = %ld ",tmp->addr,tmp->ref,tmp->file,tmp->line);
    printf("\n");
}

static int mem_check_free_point(mem_item_info_t *mem_ptr){
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
    unsigned char *tmp_tail = (unsigned char *)((unsigned char *)(mem_ptr->addr) + mem_ptr->size +TOOLS_TEST_SPACE);
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


#ifdef SIMPLE_SEARCH_TREE_MEM_TEST

bin_tree_t mem_root = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


static mem_item_info_t* mem_find_item(void *data){
    tree_node_t *find_item = NULL;
    bin_tree_simple_search_fine(&mem_root,NULL,data,&find_item);
    if(find_item == NULL){
        return NULL;
    }else{
        return (mem_item_info_t*)((find_item)->data);
    }
}

static void mem_remove_item(void *data){
    bin_tree_simple_search_remove(&mem_root,NULL,NULL,data);
}

static void mem_insert_item(void *data){
    //printf("######################%d %s ################\n",__LINE__,__func__);
    bin_tree_simple_search_insert(&mem_root,NULL,data);
}





void init_global_env(){
    bin_tree_init(&mem_root,mem_compare,mem_destroy,mem_dump_data);
}

void* tools_malloc(int size,const char *file_name,int line){
    if(size == 0){
        printf("xxxx get a allocation memory size is zero");
        return NULL;
    }

    int mem_size = size + TOOLS_TEST_SPACE *2;

    mem_item_info_t *mem_item_ptr = get_new_mem_item_info();
    strncpy(mem_item_ptr->file,file_name,PATH_LENGTH_LIMIT);
    mem_item_ptr->line = line;
    mem_item_ptr->size = size;
    mem_item_ptr->addr = malloc(mem_size);
    printf("%s  mem_item_ptr->addr = %p \n",__func__,mem_item_ptr->addr); 
    mem_item_ptr->ref ++;
    memset(mem_item_ptr->addr,TOOLS_INIT_PATTERN,mem_size);

    pthread_mutex_lock(&mutex);
    mem_item_info_t *mem_item = mem_find_item((void *)mem_item_ptr);
    if(mem_item != NULL){
        printf("%s finde addr = %p \n",__func__,mem_item->addr);
        printf("error get item %s \n",__func__);
        dump_item_error_info(mem_item,"error item");
        mem_remove_item(mem_item_ptr);
    }
    mem_insert_item(mem_item_ptr);
    pthread_mutex_unlock(&mutex);
    return  (void *)((unsigned char *)(mem_item_ptr->addr) + TOOLS_TEST_SPACE);
}

void  tools_free(void *ptr,const char *file,int line ){
    mem_item_info_t tmp_mem_item = {0};
    tmp_mem_item.addr = ((unsigned char *)ptr - TOOLS_TEST_SPACE);

    pthread_mutex_lock(&mutex);
    printf("%s  tmp_mem_item->addr = %p \n",__func__,tmp_mem_item.addr); 
    mem_item_info_t *mem_item = mem_find_item(&tmp_mem_item);
    if(mem_item == NULL){
        printf("error free a false address %s  %p \n",__func__,tmp_mem_item.addr);
    }else{
        if(mem_item->ref <= 0){
            printf("error get item %s \n",__func__);
            dump_item_error_info(mem_item,"error item");
            mem_remove_item((void *)mem_item);
        }else{
            mem_item->ref--; 
            if(mem_item->ref == 0){
                if(mem_check_free_point(mem_item) < 0){
                    dump_item_error_info(mem_item,"overwrite");
                }
                mem_remove_item((void *)mem_item);
            }
        }
    }
    pthread_mutex_unlock(&mutex);

}

char* tools_strdup( const char *str, const char*file_name, int line){
    if(str == NULL){
        printf("tools_strdup get a null point\n");
    }
    int length = strlen(str);
    if(length > 1024 *8){
        printf("Atention get a very long string \n");
    }
    length += CHAR_TYPE;
    char *cpy_str = NULL;
    cpy_str = (char *)tools_malloc(length,file_name,line);
    assert(cpy_str != NULL);
    memset(cpy_str,0,length);
    strncpy(cpy_str,str,strlen(str));
    return cpy_str;
}

void release_global_env(){
    bin_tree_midorder_scan(&mem_root,bin_tree_root(&mem_root));
    bin_tree_destroy(&mem_root);
}
#endif





#ifdef AVL_TREE_MEM_TEST

bin_tree_t mem_root = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static mem_item_info_t* avl_mem_find_item(void *data){
    mem_item_info_t *find_item = NULL;
    avl_tree_find(&mem_root,NULL,(void *)data,(void **)(&find_item));
    return find_item;
}

static void avl_mem_remove_item(void *data){
    avl_tree_remove(&mem_root,NULL,data);
}

static void avl_mem_insert_item(void *data){
    //printf("######################%d %s ################\n",__LINE__,__func__);
    int balance =1 ;
    avl_tree_insert(&mem_root,NULL,data,&balance);
}

void init_global_env(){
    avl_tree_init(&mem_root,mem_compare,mem_destroy,mem_dump_data);
}

void* tools_malloc(int size,const char *file_name,int line){
    if(size == 0){
        printf("xxxx get a allocation memory size is zero");
        return NULL;
    }

    int mem_size = size + TOOLS_TEST_SPACE *2;

    mem_item_info_t *mem_item_ptr = get_new_mem_item_info();
    strncpy(mem_item_ptr->file,file_name,PATH_LENGTH_LIMIT);
    mem_item_ptr->line = line;
    mem_item_ptr->size = size;
    mem_item_ptr->addr = malloc(mem_size);
    //printf("%s  mem_item_ptr->addr = %p \n",__func__,mem_item_ptr->addr); 
    mem_item_ptr->ref ++;
    memset(mem_item_ptr->addr,TOOLS_INIT_PATTERN,mem_size);

    pthread_mutex_lock(&mutex);
    mem_item_info_t *mem_item = avl_mem_find_item((void *)mem_item_ptr);
    if(mem_item != NULL){
        printf("%s finde addr = %p \n",__func__,mem_item->addr);
        printf("error get item %s \n",__func__);
        dump_item_error_info(mem_item,"error item");
        avl_mem_remove_item(mem_item_ptr);
    }
    avl_mem_insert_item(mem_item_ptr);
    pthread_mutex_unlock(&mutex);
    return  (void *)((unsigned char *)(mem_item_ptr->addr) + TOOLS_TEST_SPACE);
}

void  tools_free(void *ptr,const char *file,int line ){
    mem_item_info_t tmp_mem_item = {0};
    tmp_mem_item.addr = ((unsigned char *)ptr - TOOLS_TEST_SPACE);

    pthread_mutex_lock(&mutex);
    //printf("%s  tmp_mem_item->addr = %p \n",__func__,tmp_mem_item.addr); 
    mem_item_info_t *mem_item = avl_mem_find_item(&tmp_mem_item);
    if(mem_item == NULL){
        printf("error free a false address %s  %p  %s %d \n",__func__,tmp_mem_item.addr,file,line);
    }else{
        if(mem_item->ref <= 0){
            printf("error get item %s \n",__func__);
            dump_item_error_info(mem_item,"error item");
            avl_mem_remove_item((void *)mem_item);
        }else{
            mem_item->ref--; 
            if(mem_item->ref == 0){
                if(mem_check_free_point(mem_item) < 0){
                    dump_item_error_info(mem_item,"overwrite");
                }
                avl_mem_remove_item((void *)mem_item);
            }
        }
    }
    pthread_mutex_unlock(&mutex);

}

char* tools_strdup( const char *str, const char*file_name, int line){
    if(str == NULL){
        printf("tools_strdup get a null point\n");
    }
    int length = strlen(str);
    if(length > 1024 *8){
        printf("Atention get a very long string \n");
    }
    length += CHAR_TYPE;
    char *cpy_str = NULL;
    cpy_str = (char *)tools_malloc(length,file_name,line);
    assert(cpy_str != NULL);
    memset(cpy_str,0,length);
    strncpy(cpy_str,str,strlen(str));
    return cpy_str;
}

void release_global_env(){
    avl_tree_preorder_scan(&mem_root);
    avl_tree_destroy(&mem_root);
}

#endif 
