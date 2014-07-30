#include"StardictSyn.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>


StardictSyn::StardictSyn(const char *file_path,long word_count):syn_file(file_path){
    syn_word_count = word_count;
}

StardictSyn::~StardictSyn(){
    int i = 0;
    synonym_word_t *tmp =array; 
    if(array != NULL){
        while(i < syn_word_count){
            if(tmp->synnonym_word != NULL){
                free(tmp->synnonym_word);
            }
            free(tmp);
            i++;
            tmp = (array+i);
        }
    }
}

int StardictSyn::init(){
    int ret = 0;
    ret = syn_file.open(0);
    if(ret < 0){
        return ret;
    }
    array = (synonym_word_t *)malloc(sizeof(synonym_word_t) *syn_word_count);

    unsigned char word_buff[1024]={0};
    int i = 0;
    unsigned char index_buff[4]={0};
    while(i < syn_word_count){
        memset(word_buff,0,sizeof(word_buff));
        ret = syn_file.read_terminating_by(word_buff,sizeof(word_buff),'\0');
        if(ret <= 0){
            break;
        }
        memset(index_buff,0,sizeof(index_buff));
        ret = syn_file.read(index_buff,sizeof(index_buff));
        if(ret <= 0){
            break;
        }
        (array + i)->synnonym_word = strdup((char *)word_buff);
        (array + i)->original_word_index= ::ntohl((*(long*)index_buff));
        if(i < 10){
            printf("synnoym word = %s index %d   \n",(array + i)->synnonym_word,(array + i)->original_word_index);
        }
        i++;
    }
    printf("file offset = %d \n",syn_file.lseek(SEEK_CUR,0));
}

//index
int StardictSyn::find_word(const char *str){
    int i = 0;
    while(i < syn_word_count){
        if(strcmp((array + i)->synnonym_word,str) == 0){
            break;
        }
        i++;
    }
    if(i == syn_word_count){
        return -1;
    }else{
        return (array + i)->original_word_index;
    }
}
