#ifndef __GOLDEN_WORD_INDEX_ITEM_H__
#define __GOLDEN_WORD_INDEX_ITEM_H__
#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"
#include"String8.h"

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


class GoldenWordHashList:public Ref{
    public:
        GoldenWordHashList(int max_count);
        void DictHashInsert(SObject<WordIdxItem> &newItem);
        bool DictHashfind(const SObject<WordIdxItem> &item);
        const SObject<WordIdxItem>& DictHashGet(const SObject<WordIdxItem>&item);

    private:
        DictHashSet<SObject<WordIdxItem> > word_hash;
};
#endif
