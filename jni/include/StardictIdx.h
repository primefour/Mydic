#ifndef __STARDICT_IDX__
#define __STARDICT_IDX__
#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"
#include"String8.h"

class StardictIdx:public Ref{
    public:
        StardictIdx(GoldenWordOffsetInfoHMap *map,
                const char *file_path,
                int word_count,
                int file_size,
                unsigned int dict_idx,
                int offsetbit = 32);

        ~StardictIdx();
        int init();

    private:
        unsigned int dict_idx;
        int  offsetbit;
        long word_count;
        long file_size;
        String8 file_path;
        SObject<GoldenWordOffsetInfoHMap> Hmap;
};
#endif
