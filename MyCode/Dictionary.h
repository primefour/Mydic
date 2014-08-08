#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__
#include"sys/types.h"
#include"list.h"
#include"MetaDataHead.h"

class Dictionary{
    public:
        virtual ~Dictionary()
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
    char *name ;
    int status;
    Dictionary *dict;
}dict_ident_t;

class DictionarySet{
    public:
        DictionarySet();
        ~DictionarySet();
        Dictionary *get_dict(const char *name);
        int  scan_dir(const char *path);
        void remove_dict(const char *name);
    private:
        void add_dict(dict_ident_t *dict);
        HashList *dict_set;
}

#endif
