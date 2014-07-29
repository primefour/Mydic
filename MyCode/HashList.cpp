#include"HashList.h"


unsigned long HashList::default_hash_func(void *data){
    long locate = (long)data;
    return locate % DEFAULT_ARRAY_LENGTH ;
}


HashList::HashList(){
    array_size = DEFAULT_ARRAY_LENGTH ;
    hash_func = default_hash_func;
}

HashList::HashList(pfn_hash func,long array_length){
    hash_func = func;
    array_size = array_length;
}

HashList::~HashList(){
}
