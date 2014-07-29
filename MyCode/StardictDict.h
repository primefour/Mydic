#ifndef __STARDICT_DICT__
#define __STARDICT_DICT__

typedef struct meta_data_head{
    unsigned char *data;
    off_t original_offset;
    int data_size;
    list_head_t head;
}meta_data_head_t;

typedef struct meta_data_t{
    list_head_t list;
    char type;
    unsigned char *data;
}meta_data_t;


class StardictDict{
    public:
        StardictDict(const char*file_name,char *same_type_seq);
        ~StardictDict();
        int init(); 
        void get_lowercase_meta_data(unsigned char *data,meta_data_t *meta);
        void get_uppercase_meta_data(unsigned char *data,meta_data_t *meta);
        void parse_meta_data(meta_data_t *meta);
        int  read_word_data(meta_data_head_t *word_data);
    private:
        File *dict_file;
};

#endif 
