#ifndef __GOLDEN_DICT_LIST__
#define __GOLDEN_DICT_LIST__
typedef struct list_head{
    struct list_head *prev;
    struct list_head *next;
}list_head_t; 

#define for_each_item(head,ptr_fun) do{ \
    list_head_t *tmp_head = &head; \
    while(tmp_head->next != &head){ \
        ptr_fun(tmp_head); \
        tmp_head = tmp_head->next; \
    } \
}while(0)


#endif //__GOLDEN_DICT_LIST__
