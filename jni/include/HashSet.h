#ifndef __HASH_SET_H__
#define __HASH_SET_H__
#include<vector>
#include<list>

using namespace std;

template <class HASH_ITEM_TYPE>
typedef int (*ptrGetHashValue)(HASH_ITEM_TYPE *item);


template <class HASH_ITEM_TYPE>
class DictHashSet{
    public:
        DictHashSet(int set_count,ptrGetHashValue pfn);
        DictHashSet(int set_count);
    private:
        int defaultHashCode(HASH_ITEM_TYPE *item);
        vector<list<HASH_ITEM_TYPE *>> mHashTable;
        ptrGetHashValue mPfn;
        int mMaxCapacity;
};



template<class HASH_ITEM_TYPE>
DictHashSet<HASH_ITEM_TYPE>::DictHashSet(int set_count,ptrGetHashValue pfn){
    mPfn = pfn;
    mHashTable.reserve(set_count);
}

template<class HASH_ITEM_TYPE>
DictHashSet<HASH_ITEM_TYPE>::DictHashSet(int set_count){
    mPfn = defaultHashCode;
    mHashTable.reserve(set_count);
}

template<class HASH_ITEM_TYPE>
int DictHashSet<HASH_ITEM_TYPE>::defaultHashCode(HASH_ITEM_TYPE *item){
    unsigned char *str_identity = item->string();
    const char *ptr;
    unsigned int val;
    val = 0;
    ptr = key;
    while (*ptr != '\0') {
        unsigned int tmp;
        val = (val << 4) + (*ptr);
        if (tmp = (val & 0xf0000000)) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
        ptr++;
    }
    return val % mMaxCapacity;
}

#endif //__HASH_SET_H__
