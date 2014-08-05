#ifndef __HASH_LIST__
#define __HASH_LIST__
#include"list.h" 

typedef unsigned long (*pfn_hash)(void *data) ;
//typedef int  (*pfn_hash_compare)(void *data,void *data2);
//typedef void (*pfn_hash_destroy)(void *data);
#define DEFAULT_ARRAY_LENGTH (1024*1024)

class HashList{
    public:
        HashList();
        HashList(pfn_hash func,pfn_list_compare compare,pfn_list_destroy destroy,long array_length);
        ~HashList();

        void hash_insert(void *data);
        void*hash_find(void *data);
        void hash_remove(void *data);
        void set_pfn(pfn_hash func,pfn_list_compare compare,pfn_list_destroy destroy);

        static unsigned long default_hash(void *data);
        static void default_hash_destroy(void *data);
        static int default_hash_compare(void *data,void *data2);
    private:
        pfn_hash hash_func;
        pfn_list_compare compare_func;
        pfn_list_destroy destroy_func;
        List **array;
        long array_size; 
};

#endif 
