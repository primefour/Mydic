#ifndef __STARDICT_H__
#define __STARDICT_H__
#include"sys/types.h"
#include"list.h"
#include"Directory.h"
#include "StardictIdx.h"
#include "StardictInfo.h"
#include "StardictDict.h"
#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


class StardictDirectory : public Directory {
    public:
        StardictDirectory(const char *directory_path);
        ~StardictDirectory();
        virtual int init();
        virtual int query_word(const char *word,meta_data_head *word_meta);
        virtual char* get_directory_name(char *buff,int len);
        virtual char* get_directory_version(char *buff,int len);
        virtual char* get_directory_author(char *buff,int len);
        virtual char* get_directory_date(char *buff,int len);
        virtual char* get_directory_description(char *buff,int len);
        virtual int get_directory_word_count();
    private:
        StardictInfo *si; 
        StardictIdx *sidx;
        StardictDict *sd;
        char *file_main_path;
};

#endif 
