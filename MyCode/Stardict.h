#ifndef __STARDICT_H__
#define __STARDICT_H__
#include"sys/types.h"
#include"list.h"
typedef enum DICT_META_TYPE_T{
    DICT_ATTACH_PATH_TYPE, 
    DICT_SOUND_PATH_TYPE, 
    DICT_PIC_PATH_TYPE, 
    DICT_VIDEO_PATH_TYPE,
    DICT_HTML_TYPE,
    DICT_WIKI_TYPE,
    DICT_ATTACH_TYPE,
    DICT_PIC_TYPE,
    DICT_SOUND_TYPE,
    DICT_PHONETIC_TYPE,
    DICT_STRING_TYPE,
    DICT_PINYIN_TYPE,
}DICT_META_TYPE_T;

typedef struct meta_data_head{
    unsigned char *data;
    off_t original_offset;
    int data_size;
    list_head_t head;
}meta_data_head_t;

typedef struct meta_data_t{
    list_head_t list;
    int type;
    int data_length;
    unsigned char *data;
}meta_data_t;


meta_data_t *get_new_meta_item();
void dump_meta_item(meta_data_t *meta_item);
meta_data_head *get_new_meta_head();
void head_release_func(void *data);
void release_meta_head(meta_data_head *phead);
void dump_meta_head(meta_data_head *phead);
#endif 
