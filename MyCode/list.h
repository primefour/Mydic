#ifndef __GOLDEN_DICT_LIST__
#define __GOLDEN_DICT_LIST__


#define offset(type,item)   ((unsigned long)((unsigned char *)&(((type *)0)->item)))
#define contain_of(ptr,type,item) ((type *)(((unsigned char *)ptr) - offset(type,item)))

typedef int (*pfn_list_compare)(void *data1,void *data2);
typedef void (*pfn_list_destroy)(void *data);

typedef struct list_head{
    struct list_head *prev;
    struct list_head *next;
    void *data;
}list_head_t; 

class List{
    public:
        List(pfn_list_compare compare,pfn_list_destroy destroy);
        ~List();
        List(const List &list);
        void dump_list();
        void*find_list_item(void *data);
        void insert_list_tail(void *data);
        void insert_list_head(void *data);
        void*insert_list_local(void *prev_data,void *data);
        void remove_list_item(void *data);
        void*get_prev_item(void *data);
        void*get_next_item(void *data);
        void List::begin_iterate();
        void* List::iterate_item();

        static int default_list_compare(void *data1,void *data2);
        static void default_list_destroy(void *data);
    private:
        void init_list_item(list_head_t *item);
        void remove_list_item_(list_head_t *prev_item,list_head_t *next_item,list_head_t *remove_item);
        void add_list_item_(list_head_t * prev_item,list_head_t *next_item,list_head_t *insert_item);
        void init_list_head();
        void release_list();
        list_head_t* get_new_item();
        pfn_list_compare compare_func;
        pfn_list_destroy destroy_func;
        list_head_t head;
        list_head_t* cursor;
};

#endif //__GOLDEN_DICT_LIST__
