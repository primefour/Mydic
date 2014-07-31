#include"StardictIdx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>

/*
uint32_t htonl(uint32_t hostlong);

uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);

uint16_t ntohs(uint16_t netshort);
*/

StardictIdx:: StardictIdx(const char *file_path,long word_count,long file_size,int offsetbit):idx_file(file_path){
    this->word_count = word_count;
    this->offsetbit = offsetbit;
    this->file_size = file_size;
    array= NULL;
}

StardictIdx::~StardictIdx(){
    int i = 0 ;
    word_item_t *temp = array;
    while(i < word_count){
        free(temp->word_str);
        free(temp);
        i++;
        temp = array + i;
    }
}

int StardictIdx::init(){
    int ret = 0;
    ret = idx_file.open(0);
    if(ret < 0){
        printf("open file failed \n");
        return ret;
    }

    array = (word_item_t *)malloc(word_count *sizeof(word_item_t));
    if(array == NULL){
        printf("%s allocate memory failed \n",__func__);
        assert(0);
    }
    memset(array,0,word_count *sizeof(word_item_t));
    unsigned char word_buff[1024]={0};
    int offset_read_size = 8;
    if(offsetbit == 64){
        offset_read_size = 12;
    }
    int i = 0;
    unsigned char offset_buff[12]={0};
    while(i < word_count){
        memset(word_buff,0,sizeof(word_buff));
        ret = idx_file.read_terminating_by(word_buff,sizeof(word_buff),'\0');
        if(ret <= 0){
            break;
        }
        memset(offset_buff,0,sizeof(offset_buff));
        ret = idx_file.read(offset_buff,offset_read_size);
        if(ret <= 0){
            break;
        }
        (array + i)->word_str = strdup((char *)word_buff);
        if(offsetbit == 64){
            printf("###################64 bit wait a short while \n");
        }else{
            (array + i)->word_data_offset.bit32 = ::ntohl(*((long*)offset_buff));
            (array + i)->word_data_size = ::ntohl(*((long*)(offset_buff+4)));
        }

        if(i < 10){
            printf("word = %s offset %d ,length %d  \n",(array + i)->word_str,(array + i)->word_data_offset.bit32,(array + i)->word_data_size);
        }
        i++;
    }
    printf("file offset = %d \n",idx_file.lseek(SEEK_CUR,0));
    return ret;
}

word_item_t* StardictIdx::get_word(const char *str){
    int i = 0;
    //printf("str = %s \n",str);
    while(i < word_count){
        //printf("(array + i)->word_str = %s \n",(array + i)->word_str);
        if(strcmp((array + i)->word_str,str) == 0){
            break;
        }
        i++;
    }
    if(i == word_count){
        return NULL;
    }else{
        return(array + i); 
    }
}


       
