#ifndef __HASH_LIST__
#define __HASH_LIST__
#include"list.h" 

typedef unsigned long (*pfn_hash)(void *key) ;
typedef int  (*pfn_hash_compare)(void *data,void *data2);
typedef void (*pfn_hash_destroy)(void *key,void *data);
#define DEFAULT_ARRAY_LENGTH (1024*1024)

typedef struct hash_item_t {
    void *key;
    void *data;
    struct hash_item_t *next;
}hash_item_t;


typedef struct hash_head_t {
    struct hash_item_t *next;
}hash_head_t;


class HashList{
    public:
        HashList(pfn_hash func,pfn_hash_compare compare,pfn_hash_destroy destroy,long array_length);
        ~HashList();
        void hash_insert(void *key,void *data);
        void*hash_find(void *key,void *data);
        void hash_remove(void *key,void *data);
        int get_size();
    private:
        pfn_hash hash_func;
        pfn_hash_compare compare_func;
        pfn_hash_destroy destroy_func;
        hash_head_t *head_array;
        long array_size; 
        long item_count;
};

#endif 
