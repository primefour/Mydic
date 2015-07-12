#ifndef __STARDICT_IDX__
#define __STARDICT_IDX__
#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"
#include"String.h"

class StardictIdx:public Ref{
    public:
        StardictIdx(const char* path,int word_count,
                            int file_size,int offsetbit = 32,);
        ~StardictIdx();
        void setWordList(GoldenWordHashList *word_list){
            this->word_list = word_list;
        }
        int init();

    private:
        int  offsetbit;
        long word_count;
        long file_size;
        String8 file_path;
        SObject<GoldenWordHashList> word_list;
};
#endif
