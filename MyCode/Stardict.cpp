#include"Stardict.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include "StardictIdx.h"
#include "StardictInfo.h"
#include "StardictDict.h"
#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include"utils.h"
#include"memory_test_tool.h"

StardictDirectory::StardictDirectory(const char *directory_path){
    int len = strlen(directory_path) + 1;
    file_main_path = (char *)malloc(len);
    memset(file_main_path,0,len);
    get_path_no_suffix(directory_path,file_main_path,len);
}

StardictDirectory::~StardictDirectory(){
    free(file_main_path);
    delete si;
    delete sidx;
    delete sd;
}

int StardictDirectory::init(){
    char info_file_name[1024]={0};
    char idx_file_name[1024]={0}; 
    char dict_file_name[1024]={0}; 
    strcpy(info_file_name,file_main_path);
    strcat(info_file_name,".ifo");
    int ret = access(info_file_name,F_OK|R_OK);
    if(ret < 0){
        printf("info file no exsit \n");
        return ret;
    }

    strcpy(idx_file_name,file_main_path);
    strcat(idx_file_name,".idx");
    ret = access(idx_file_name,F_OK|R_OK);
    if(ret < 0){
        printf("idx file no exsit \n");
        return ret;
    }

    strcpy(dict_file_name,file_main_path);
    strcat(dict_file_name,".dict.dz");
    ret = access(dict_file_name,F_OK|R_OK);
    if(ret < 0){
        printf("dict dz file no exsit check dict \n");
        memset(dict_file_name,0,sizeof(dict_file_name));
        strcpy(dict_file_name,file_main_path);
        strcat(dict_file_name,".dict");
        ret = access(dict_file_name,F_OK|R_OK);
        if(ret < 0){
            printf("dict file no exsit too \n");
            return ret;
        }
    }
    si = new StardictInfo(info_file_name);
    ret = si->init();
    if(ret < 0){
        return ret;
    }
    si->dump();
    sidx = new StardictIdx(idx_file_name,si->get_word_count(),si->get_idx_file_size());
    ret = sidx->init();
    if(ret < 0){
        return ret;
    }
    sd = new StardictDict(dict_file_name,si->get_same_types_sequence());
    ret = sd->init();
    if(ret < 0){
        return ret;
    }
    return 0;
}

int StardictDirectory::query_word(const char *word,meta_data_head *word_meta){
    word_item_t *tmp = NULL;
    printf("word = %s \n",word);
    if(sidx != NULL){
        tmp = sidx->get_word(word);
    }
    if(tmp == NULL){
        printf("%s get word return NULL \n",__func__);
    }
    if(tmp && sd != NULL){
        word_meta->original_offset = tmp->word_data_offset.bit32;
        word_meta->data_size = tmp->word_data_size;
        sd->read_word_data(word_meta);
        return 0;
    }else{
        return -1;
    }
}


char* StardictDirectory::get_directory_name(char *buff,int len){
    if(si != NULL && si->get_book_name()){
        strncpy(buff,si->get_book_name(),len);
        return buff;
    }else{
        return NULL;
    }
}
char* StardictDirectory::get_directory_version(char *buff,int len){
    if(si != NULL && si->get_version()){
        strncpy(buff,si->get_version(),len);
        return buff;
    }else{
        return NULL;
    }
}
char* StardictDirectory::get_directory_author(char *buff,int len){
    if(si != NULL && si->get_author()){
        strncpy(buff,si->get_author(),len);
        return buff;
    }else{
        return NULL;
    }
}
char* StardictDirectory::get_directory_date(char *buff,int len){
    if(si != NULL && si->get_date()){
        strncpy(buff,si->get_date(),len);
        return buff;
    }else{
        return NULL;
    }
}

char* StardictDirectory::get_directory_description(char *buff,int len){
    if(si != NULL && si->get_description()){
        strncpy(buff,si->get_description(),len);
        return buff;
    }else{
        return NULL;
    }
}

int StardictDirectory::get_directory_word_count(){
    if(si != NULL){
        return si->get_word_count();
    }else{
        return 0;
    }
}

