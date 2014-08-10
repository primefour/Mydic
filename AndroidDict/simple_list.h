#ifndef __GOLDEN_DICT_SIMPLE_LIST__
#define __GOLDEN_DICT_SIMPLE_LIST__

typedef struct simple_list_head{
    struct simple_list_head *prev;
    struct simple_list_head *next;
}simple_list_head_t; 

#define offset(type,item)   ((unsigned long)((unsigned char *)&(((type *)0)->item)))
#define contain_of(ptr,type,item) ((type *)(((unsigned char *)ptr) - offset(type,item)))


typedef int (*compare_func)(simple_list_head_t *item1,void *data);
typedef void (*release_func)(void *);

#define for_each_item(head,ptr_fun) do{ \
    simple_list_head_t *tmp_head = head.next; \
    while(tmp_head != &head){ \
        ptr_fun(tmp_head); \
        tmp_head = tmp_head->next; \
    } \
}while(0)

void init_simple_list_head(simple_list_head_t *simple_list_head_ptr);
void release_list(simple_list_head_t *simple_list_head_ptr,release_func);
simple_list_head_t* find_list_item(simple_list_head_t *simple_list_head_ptr,void *data,compare_func func);
void insert_list_item_behind(simple_list_head_t *item,simple_list_head_t *insert_item);
void insert_list_item_ahead(simple_list_head_t *item,simple_list_head_t *insert_item);
simple_list_head_t *remove_list_item(simple_list_head_t *remove_item);



#endif //__GOLDEN_DICT_SIMPLE_LIST__
