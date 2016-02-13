#ifndef GOLDEN_HASH_MAP_2_H__
#define GOLDEN_HASH_MAP_2_H__
#include<vector>
#include<list>
#include<map>
#include<algorithm>
using namespace std;

/*
template <class KeyType>
class HashFunction{
    public :
        typedef int (*fpn_hash)(KeyType);
        fpn_hash mFpn ;
};
*/
template<class TypeKey,class TypeItem,class hash_fpn,int Tcount = 1999>
class HashMapExt{
    public:
        HashMapExt(const hash_fpn fpn = hash_fpn() ,int count = Tcount):mHashTable(count,NULL),mInvalidList(),mFpn(fpn){
            mSize = count;
        }

        class iterator{
            public:
                iterator(){

                }
                iterator(const typename list<TypeItem>::iterator &it){
                    mIt = it;
                }
                const TypeItem& operator*() const {
                    return *mIt;
                }

                const TypeItem* operator->() const {
                    return &(*mIt);
                }
            private:
                const typename list<TypeItem>::iterator mIt;

        };

        TypeItem* insert(TypeKey &key,TypeItem &item){
            int offset = mFpn(key);
            offset %= mSize ;
            if(mHashTable[offset] == NULL){
                mHashTable[offset] = new map<TypeKey,list<TypeItem>* >();
            }

            map<TypeKey,list<TypeItem>* > *tmp_map = mHashTable[offset];
            typename map<TypeKey,list<TypeItem>* >::iterator map_end = tmp_map->end(); 
            typename map<TypeKey,list<TypeItem>* >::iterator tmp_pair = tmp_map->find(key);
            if(tmp_pair != map_end){
                tmp_pair->second->push_back(item);
                return &(tmp_pair->second->back());
            }else{
                list<TypeItem> *item_list = new list<TypeItem>();
                pair<TypeKey,list<TypeItem>* > data = pair<TypeKey,list<TypeItem>* >(key,item_list);
                typename map<TypeKey,list<TypeItem>* >::iterator pair_it= (tmp_map->insert(data)).first;
                pair_it->second->push_back(item);
                return &( pair_it->second->back());
            }
        }

        list<TypeItem>& find(TypeKey &key){
            int offset = mFpn(key);
            offset %= mSize ;
            if(mHashTable[offset] != NULL){
                map<TypeKey,list<TypeItem>* > *tmp_map = mHashTable[offset];
                typename map<TypeKey,list<TypeItem>* >::iterator map_end = tmp_map->end(); 
                typename map<TypeKey,list<TypeItem>* >::iterator tmp_pair = tmp_map->find(key);
                if(tmp_pair == map_end){
                    return mInvalidList;
                }else{
                    return *(tmp_pair->second) ;
                }
            }else{
                return mInvalidList;
            }
        }
        
    private:
        list<TypeItem> mInvalidList;
        vector<map<TypeKey,list<TypeItem>* >* > mHashTable;
        hash_fpn mFpn ;
        int mSize;
};

#endif //GOLDEN_HASH_MAP_2_H__
