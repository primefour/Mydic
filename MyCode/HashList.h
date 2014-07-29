#ifndef __HASH_LIST__
#define __HASH_LIST__
#include"list.h" 

typedef unsigned long (*pfn_hash)(void *data) ;
#define DEFAULT_ARRAY_LENGTH (1024*1024)

class HashList{
    public:
        HashList();
        HashList(pfn_hash func,long array_length);
        ~HashList();
        static unsigned long default_hash_func(void *data);
    private:
        pfn_hash hash_func;
        list_head_t *array;
        long array_size; 
};
#endif 
