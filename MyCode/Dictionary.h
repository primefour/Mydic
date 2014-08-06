#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__
#include"sys/types.h"
#include"list.h"
#include"utils.h"

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
#endif
