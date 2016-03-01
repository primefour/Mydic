#ifndef __STARDICT_IDX__
#define __STARDICT_IDX__
#include"String8.h"

class StardictIdx:public Ref{
    public:
        StardictIdx(const char *file_path,
                int word_count,
                int file_size,
                unsigned int dict_idx,
                int offsetbit = 32);
        ~StardictIdx();
    private:
        int init();

        unsigned int dict_idx;
        int  offsetbit;
        long word_count;
        long file_size;
        String8 file_path;
};
#endif