#ifndef __HASH_SET_H__
#define __HASH_SET_H__
#include<stdio.h>
#include<string.h>
#include<vector>
#include<list>
#include"GoldenDictLog.h"
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
        void DictHashAnalysis();
    private:
        int defaultHashCode(const HASH_ITEM_TYPE *item);
        vector< list<HASH_ITEM_TYPE> > mHashTable;
        HASH_ITEM_TYPE *mLatestItem;
        int (*mPfn)(const HASH_ITEM_TYPE *item);
        int mMaxCapacity;
};



template<class HASH_ITEM_TYPE>
DictHashSet<HASH_ITEM_TYPE>::DictHashSet(int set_count,int (*pfn)(const HASH_ITEM_TYPE *item)):mHashTable(set_count,list<HASH_ITEM_TYPE>()){
    mLatestItem  = NULL;
    mMaxCapacity = set_count;
    mPfn = pfn;
}


template<class HASH_ITEM_TYPE>
DictHashSet<HASH_ITEM_TYPE>::DictHashSet(int set_count):mHashTable(set_count,list<HASH_ITEM_TYPE>()){
    mLatestItem  = NULL;
    mMaxCapacity = set_count;
}


template<class HASH_ITEM_TYPE>
int DictHashSet<HASH_ITEM_TYPE>::defaultHashCode(const HASH_ITEM_TYPE *item){
    unsigned int val;
    val = 0;
    const char *ptr = item->string();
    golden_printfi("%s \n",ptr);
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

    if(mLatestItem != NULL && *mLatestItem == item){
        return *mLatestItem ;
    }

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
            mLatestItem = begin;
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
            if(*mLatestItem == item){
                mLatestItem = NULL;
            }
            mHashTable[idx].remove(begin);
        }
        begin ++;
    }
}


template<class HASH_ITEM_TYPE>
void DictHashSet<HASH_ITEM_TYPE>::DictHashAnalysis(){
    typename vector<list<HASH_ITEM_TYPE> >::iterator begin = mHashTable.begin();
    typename vector<list<HASH_ITEM_TYPE> >::iterator end = mHashTable.end();
    int count = 0;
    while(begin < end){
        golden_printfd(" %d ",begin->size());
        count ++ ;
        if(count % 100 == 0){
            golden_printfd("\n");
        }
        begin ++;
    }
}



#endif //__HASH_SET_H__
