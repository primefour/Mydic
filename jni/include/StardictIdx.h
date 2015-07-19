#ifndef __STARDICT_IDX__
#define __STARDICT_IDX__
#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"
#include"String8.h"

class StardictIdx:public Ref{
    public:
        StardictIdx(GoldenWordHashList *idx_list,
                            const char* path,int word_count,
                            int file_size,
                            int offsetbit = 32);
        ~StardictIdx();
        int init();

    private:
        int  offsetbit;
        long word_count;
        long file_size;
        String8 file_path;
        SObject<GoldenWordHashList> word_list;
};
#endif
