#ifndef __STARDICT_IDX__
#define __STARDICT_IDX__
#include"File.h"
#include"list.h"

class WordIdxItem:public Ref{
    public:
        WordIdxItem(){
            word_str = NULL;
            bit32 = 0;
            word_data_size = 0;
        }
        char*word_str;
        int bit32;
        int word_data_size;
};


class StardictIdx:public Ref{
    public:
        StardictIdx(String* path,long word_count,long file_size,int offsetbit = 32);
        ~StardictIdx();
        WordIdxItem* GetIdxWord(String8 *word);
    private:
        int Init();
        AVLTreeTemplate<WordIdxItem> word_tree;
        SimpleFile FileIO;
        int  offsetbit;
        long word_count;
        long file_size;
};
#endif
