#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__
#include"sys/types.h"
#include"list.h"
#include"Directory.h"
#include"utils.h"

class Directory{
    public:
        virtual int init()=0;
        virtual int query_word(const char *word,meta_data_head *word_meta)=0;
        virtual char* get_directory_name(char *buff,int len) = 0;
        virtual char* get_directory_version(char *buff,int len)=0;
        virtual char* get_directory_author(char *buff,int len)=0;
        virtual char* get_directory_date(char *buff,int len)=0;
        virtual char* get_directory_description(char *buff,int len)=0;
        virtual int get_directory_word_count()=0;

};
#endif
