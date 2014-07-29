#ifndef __STARDICT_SYN_H__
#define __STARDICT_SYN_H__
#include"File.h"

typedef struct synonym_word_t{
    char *synnonym_word;
    unsigned int original_word_index;
}synonym_word_t;

class StardictSyn{
    public:
       StardictSyn(const char *file_path,long word_count);
       ~StardictSyn();
       int init();
       int find_word(const char *str);
    private:
        synonym_word_t *array;
        long syn_word_count;
        File syn_file;
};

#endif
