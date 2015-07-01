#ifndef __HASH_SET_H__
#define __HASH_SET_H__
#include<stdio.h>
#include<string.h>
#include<vector>
#include<list>

using namespace std;

template <class HASH_ITEM_TYPE>
class DictHashSet{
    public:
        DictHashSet(int set_count,int (*pfn)(const HASH_ITEM_TYPE *item));
        DictHashSet(int set_count);
        void DictHashInsert(const HASH_ITEM_TYPE &item);
        void DictHashRemove(const HASH_ITEM_TYPE &item);
        bool DictHashfind(const HASH_ITEM_TYPE &item);
        const HASH_ITEM_TYPE& DictHashGet(const HASH_ITEM_TYPE &item);
    private:
        int defaultHashCode(const HASH_ITEM_TYPE *item);
        vector< list<HASH_ITEM_TYPE> > mHashTable;
        int (*mPfn)(const HASH_ITEM_TYPE *item);
        int mMaxCapacity;
};



template<class HASH_ITEM_TYPE>
DictHashSet<HASH_ITEM_TYPE>::DictHashSet(int set_count,int (*pfn)(const HASH_ITEM_TYPE *item)){
    mPfn = pfn;
    mHashTable.reserve(set_count);
}


template<class HASH_ITEM_TYPE>
DictHashSet<HASH_ITEM_TYPE>::DictHashSet(int set_count){
    mHashTable.reserve(set_count);
}


template<class HASH_ITEM_TYPE>
int DictHashSet<HASH_ITEM_TYPE>::defaultHashCode(const HASH_ITEM_TYPE *item){
    unsigned int val;
    val = 0;
    const char *ptr = NULL ;//item->string();
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


template<class HASH_ITEM_TYPE>
void DictHashSet<HASH_ITEM_TYPE>::DictHashInsert(const HASH_ITEM_TYPE &item){
    int idx = 0;
    if(mPfn){
        idx = mPfn(&item);
    }else{
        idx = defaultHashCode(&item);
    }

    typename list<HASH_ITEM_TYPE>::iterator begin = mHashTable[idx].begin();
    typename list<HASH_ITEM_TYPE>::iterator end = mHashTable[idx].end();

    while(begin != end){
        if(*begin == item){
            return ;
        }
        begin ++;
    }
    mHashTable[idx].push_back(item);
}

template<class HASH_ITEM_TYPE>
const HASH_ITEM_TYPE& DictHashSet<HASH_ITEM_TYPE>::DictHashGet(const HASH_ITEM_TYPE &item){
    int idx = 0;
    if(mPfn){
        idx = mPfn(&item);
    }else{
        idx = defaultHashCode(&item);
    }
    typename list<HASH_ITEM_TYPE>::iterator begin = mHashTable[idx].begin();
    typename list<HASH_ITEM_TYPE>::iterator end = mHashTable[idx].end();
    while(begin != end){
        if(*begin == item){
            return *begin;
        }
        begin++ ;
    }
    return item;
}


template<class HASH_ITEM_TYPE>
bool DictHashSet<HASH_ITEM_TYPE>::DictHashfind(const HASH_ITEM_TYPE &item){
    int idx = 0;
    if(mPfn){
        idx = mPfn(&item);
    }else{
        idx = defaultHashCode(&item);
    }
    typename list<HASH_ITEM_TYPE>::iterator begin = mHashTable[idx].begin();
    typename list<HASH_ITEM_TYPE>::iterator end = mHashTable[idx].end();
    while(begin != end){
        if(*begin == item){
            return true;
        }
        begin++ ;
    }
    return false;
}

template<class HASH_ITEM_TYPE>
void DictHashSet<HASH_ITEM_TYPE>::DictHashRemove(const HASH_ITEM_TYPE &item){
    int idx = 0;
    if(mPfn){
        idx = mPfn(&item);
    }else{
        idx = defaultHashCode(&item);
    }

    typename list<HASH_ITEM_TYPE>::iterator begin = mHashTable[idx].begin();
    typename list<HASH_ITEM_TYPE>::iterator end = mHashTable[idx].end();
    while(begin != end){
        if(*begin == item){
            mHashTable[idx].remove(begin);
        }
        begin ++;
    }
}



#endif //__HASH_SET_H__