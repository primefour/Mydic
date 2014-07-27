#ifndef __GOLDEN_DICT_LIST__
#define __GOLDEN_DICT_LIST__

typedef struct list_head{
    struct list_head *prev;
    struct list_head *next;
}list_head_t; 

#define offset(type,item)   ((unsigned long)((unsigned char *)&(((type *)0)->item)))
#define contain_of(ptr,type,item) ((type *)(((unsigned char *)ptr) - offset(type,item)))


typedef int (*compare_func)(list_head_t *item1,void *data);
typedef void (*release_func)(void *);

#define for_each_item(head,ptr_fun) do{ \
    list_head_t *tmp_head = head.next; \
    while(tmp_head != &head){ \
        ptr_fun(tmp_head); \
        tmp_head = tmp_head->next; \
    } \
}while(0)

void init_list_head(list_head_t *list_head_ptr);
void release_list(list_head_t *list_head_ptr,release_func);
list_head_t* find_list_item(list_head_t *list_head_ptr,void *data,compare_func func);
void insert_list_item_behind(list_head_t *item,list_head_t *insert_item);
void insert_list_item_ahead(list_head_t *item,list_head_t *insert_item);
list_head_t *remove_list_item(list_head_t *remove_item);



#endif //__GOLDEN_DICT_LIST__
