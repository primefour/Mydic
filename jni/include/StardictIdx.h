#ifndef __STARDICT_IDX__
#define __STARDICT_IDX__
#include"String8.h"
#include"AVLTreeTemplate.h"

#ifdef ANDROID_PLATFORM
#include <android/log.h>
#define  LOG_TAG    "DICT2"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define printf LOGE
#endif

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
        void dumpInfo(){
            printf("word = %s offset = %d size = %d \n",idx_word.string(),data_offset,data_size);
        }

        String8 idx_word;
        int data_offset;
        int data_size;
};


class StardictIdx:public Ref{
    public:
        StardictIdx(const char* path,int word_count,int file_size,int offsetbit = 32);
        ~StardictIdx();
        WordIdxItem getIdxWord(const char *word);
        int init();
    private:
        AVLTreeTemplate<WordIdxItem> word_tree;
        int  offsetbit;
        long word_count;
        long file_size;
        String8 file_path;
};
#endif
