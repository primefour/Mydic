#ifndef __STARDICT_H__
#define __STARDICT_H__
#include"sys/types.h"
#include"list.h"
#include"Dictionary.h"
#include "StardictIdx.h"
#include "StardictInfo.h"
#include "StardictDict.h"
#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


class StardictDictionary : public Dictionary{
    public:
        StardictDictionary(const char *dictionary_path);
        ~StardictDictionary();
        virtual int init();
        virtual int query_word(const char *word,meta_data_head *word_meta);
        virtual char* get_dictionary_name(char *buff,int len);
        virtual char* get_dictionary_version(char *buff,int len);
        virtual char* get_dictionary_author(char *buff,int len);
        virtual char* get_dictionary_date(char *buff,int len);
        virtual char* get_dictionary_description(char *buff,int len);
        virtual int get_dictionary_word_count();
    private:
        StardictInfo *si; 
        StardictIdx *sidx;
        StardictDict *sd;
        char *file_main_path;
};

#endif 
