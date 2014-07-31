#ifndef __STARDICT_IDX__
#define __STARDICT_IDX__
#include"File.h"
#include"list.h"
typedef struct word_item_t{
    char *word_str;
    union {
        int bit32;
        long long bit64;
    }word_data_offset;
    int word_data_size;
}word_item_t;


class StardictIdx{
    public:
        StardictIdx(const char *file_path,long word_count,long file_size,int offsetbit = 32);
        ~StardictIdx();
        int init();
        word_item_t* get_word(const char *str);
    private:
        word_item_t *array;
        File idx_file;
        int offsetbit;
        long word_count;
        long file_size;
};
#endif
