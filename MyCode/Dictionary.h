#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__
#include"sys/types.h"
#include"list.h"
#include"HashList.h"
#include"MetaDataHead.h"

class Dictionary{
    public:
        virtual int init()=0;
        virtual int query_word(const char *word,MetaDataHeader *word_meta)=0;
        virtual char* get_dictionary_name(char *buff,int len) = 0;
        virtual char* get_dictionary_version(char *buff,int len)=0;
        virtual char* get_dictionary_author(char *buff,int len)=0;
        virtual char* get_dictionary_date(char *buff,int len)=0;
        virtual char* get_dictionary_description(char *buff,int len)=0;
        virtual int get_dictionary_word_count()=0;

};


//status using to checkt whether is enabled
typedef struct dict_ident_t{
    char *name;
    int status;
    Dictionary *dict;
}dict_ident_t;

#define MAX_DICT_SUPPORT 20
class DictionarySet{
    public:
        DictionarySet();
        ~DictionarySet();
        int  scan_dir(const char *path);
        void remove_dict(char *name);
        int add_dict(const char *name,Dictionary *dict);
        void get_dicts_name(const char **dict_array,int strlen);
        Dictionary* get_dict(const char *dict_name);
    private:
        HashList *dict_set;
        const char *dict_name_list[MAX_DICT_SUPPORT];
};

#endif
