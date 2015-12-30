#ifndef __GOLDEN_WORD_INDEX_ITEM_H__
#define __GOLDEN_WORD_INDEX_ITEM_H__
#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"
#include"String8.h"
#include"GoldenTriTree.h"
#include<list>
#include"GoldenHashMapExt.h"
using namespace std;

class WordIdxItem:public Ref{
    public:
        WordIdxItem(){
            data_offset = 0; 
            data_size = 0;
        }

        WordIdxItem(const char *word,int offset,int size):idx_word(word),data_offset(offset),data_size(size){
        }

        WordIdxItem(const WordIdxItem &IdxItem){
            idx_word = IdxItem.idx_word;
            data_offset = IdxItem.data_offset;
            data_size = IdxItem.data_size;
        }

        WordIdxItem& operator=(const WordIdxItem &IdxItem){
            idx_word = IdxItem.idx_word;
            data_offset = IdxItem.data_offset;
            data_size = IdxItem.data_size;
            return *this;
        }

        bool operator<(const WordIdxItem & other) const{
            return idx_word < other.idx_word; 
        }
        bool operator<=(const WordIdxItem & other) const{
            return idx_word <= other.idx_word; 
        }
        bool operator==(const WordIdxItem & other) const{
            return idx_word == other.idx_word; 
        }
        bool operator!=(const WordIdxItem & other) const{
            return idx_word != other.idx_word; 
        }
        bool operator>=(const WordIdxItem & other) const{
            return idx_word >= other.idx_word; 
        }
        bool operator>(const WordIdxItem & other) const{
            return idx_word > other.idx_word; 
        }

        bool operator<(const String8 &other) const{
            return idx_word < other ; 
        }
        bool operator<=(const String8 &other) const{
            return idx_word <= other; 
        }
        bool operator==(const String8 &other) const{
            return idx_word == other; 
        }
        bool operator!=(const String8 &other) const{
            return idx_word != other; 
        }
        bool operator>=(const String8 &other) const{
            return idx_word >= other; 
        }
        bool operator>(const String8 &other) const{
            return idx_word > other; 
        }

        void dumpInfo(){
            golden_printfd("####word = %s offset = %d size = %d \n",idx_word.string(),data_offset,data_size);
        }

        const char *string()const {
            return idx_word.string();
        }

        String8 idx_word;
        int data_offset;
        int data_size;
};


struct WordOffsetInfo{
    WordOffsetInfo(){
        type = 0;
        size = 0;
        offset = 0 ;
    }
    WordOffsetInfo(unsigned int t,unsigned int s,int ds){
        type = t;
        offset= s;
        size = ds;
    }
    unsigned int type:10;
    unsigned int size:22;
    unsigned int offset;
};


class GoldenWordIdxInteface :public Ref{
    public:
        GoldenWordIdxInteface(){};
        virtual void WordInsert(SObject<WordIdxItem> &newItem){ return; };
        virtual bool WordFind(const SObject<WordIdxItem> &item){return false;};
        virtual const SObject<WordIdxItem>& WordGet(SObject<WordIdxItem>&item) {return item;};
};


class GoldenWordOffsetInfoHMap:public Ref{
    public:
        GoldenWordOffsetInfoHMap():minValidate(){};
        virtual void insert(String8 &key,WordOffsetInfo woi){ return; };
        virtual list<WordOffsetInfo>& find(String8 key) { return minValidate;};
        list<WordOffsetInfo>  minValidate;
};

class defaultHashCode {
    public :
        int operator()(const String8 &key){
            unsigned int val;
            val = 0;
            const char *ptr = key.string();
            while (*ptr != '\0') {
                unsigned int tmp;
                val = (val << 4) + (*ptr);
                if (tmp = (val & 0xf0000000)) {
                    val = val ^ (tmp >> 24);
                    val = val ^ tmp;
                }
                ptr++;
            }
            return val ;
        }
};


class GoldenWordHashMap:public GoldenWordOffsetInfoHMap{

    virtual void insert(String8 &key,WordOffsetInfo &woi){
        mHMap.insert(key,woi); 
    };

    virtual list<WordOffsetInfo> & find(String8 key) {
        return mHMap.find(key);
    }
    private:
        HashMapExt<String8,WordOffsetInfo,defaultHashCode,199999> mHMap ;

};



class GoldenWordHashList:public GoldenWordIdxInteface {
    public:
        GoldenWordHashList(int max_count);
        virtual void WordInsert(SObject<WordIdxItem> &newItem);
        virtual bool WordFind(const SObject<WordIdxItem> &item);
        virtual const SObject<WordIdxItem>& WordGet(SObject<WordIdxItem>&item);

    private:
        DictHashSet<SObject<WordIdxItem> > word_hash;
};

class TriString8 {
    public:
        class iterator {
            public:
                iterator(char *data){
                    ptr = data;
                }
                iterator& operator++(){
                    ptr ++;
                    return *this;
                }
                iterator operator++(int){
                    iterator tmp(*this);
                    ptr ++;
                    return tmp;
                }
                bool operator==(const iterator &t){
                    return t.ptr == ptr;
                }
                bool operator!=(const iterator &t){
                    return ptr != t.ptr;
                }

                char& operator*(){
                    return *ptr;
                }

            private:
               char *ptr; 
        };

        TriString8(const char *data):mdata(strdup(data)),mBegin(mdata),mEnd(mdata+strlen(mdata)){
        }

        TriString8::iterator& begin(){
            return mBegin;
        }

        TriString8::iterator& end(){
            return mEnd;
        }
    private :
        char *mdata;
        TriString8::iterator mBegin;
        TriString8::iterator mEnd;
};

struct TriLeaves{
        TriLeaves(int offset,int size){
            this->offset = offset;
            this->size= size;
        }
        bool operator==(const TriLeaves &dd) const {
            return dd.offset == offset && dd.size == size;
        }
        int offset ;
        int size;
};


class GoldenWordTriTree:public GoldenWordIdxInteface {
    public:
        GoldenWordTriTree();
        virtual void WordInsert(SObject<WordIdxItem> &newItem);
        virtual bool WordFind(const SObject<WordIdxItem> &item);
        virtual const SObject<WordIdxItem>& WordGet(SObject<WordIdxItem>&item);
    private:
        TriTree<TriString8,char,TriLeaves> Root;
};

#endif
