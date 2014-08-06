#ifndef __DIRECTORY_UTILS_H__
#define __DIRECTORY_UTILS_H__
#include"sys/types.h"
#include"list.h"
#include<stdio.h>

//don't change the items order
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
    DICT_MAX_TYPE
}DICT_META_TYPE_T;

typedef struct meta_data_t{
    int type;
    int data_length;
    unsigned char *data;
}meta_data_t;

typedef struct meta_data_head{
    unsigned char *data;
    off_t original_offset;
    int data_size;
    meta_data_t meta_data[DICT_MAX_TYPE];
}meta_data_head_t;


class MetaDataHeader{
    public:
        MetaDataHeader();
        MetaDataHeader(off_t original_offset,int data_size);
        ~MetaDataHeader();
        void dump_meta_data_head();
        void update_meta_item(int type,unsigned char *data,int data_len);
        void update_meta_data_head(off_t offset,int data_len);
        off_t get_original_offset();
        unsigned char *get_data_ptr();       
        int get_data_length();
    private:
        void dump_meta_item(meta_data_t *meta_item,int i);
        meta_data_head_t meta_data_head;
};




int split_path_no_suffix(const char *file_path,char *file_main_path,int path_len ,char *file_name,int len);
char *get_path_no_suffix(const char *file_path,char *file_name,int len);
char *get_path_suffix(const char *file_path,char *suffix,int len);

#endif
