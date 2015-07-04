#include"StardictIdx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>
#include"String8.h"
#include"StandardIO.h"
#include"AVLTreeTemplate.h"
#include"HashSet.h"
#include"GoldenDictLog.h"

/*
uint32_t htonl(uint32_t hostlong);

uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);

uint16_t ntohs(uint16_t netshort);
*/

StardictIdx:: StardictIdx(const char *file_path,int word_count,int file_size,int offsetbit):file_path(file_path),word_hash(word_count){
    this->word_count = word_count;
    this->offsetbit = offsetbit;
    this->file_size = file_size;
    golden_printfi("word_count  = %d file_size = %d  offsetbit=%d \n",word_count,file_size,offsetbit);
    init();
}

StardictIdx::~StardictIdx(){
}

int StardictIdx::init(){
    unsigned char word_buff[1024]={0};
    MemFile file_obj(file_path,O_RDONLY);
    int offset_read_size = 8;
    if(offsetbit == 64){
        offset_read_size = 12;
    }

    int i = 0;
    unsigned char offset_buff[12]={0};
    while(i < word_count){
        memset(word_buff,0,sizeof(word_buff));
        int ret = file_obj.ReadTerminating(word_buff,sizeof(word_buff),'\0');
        if(ret <= 0){
            break;
        }
        memset(offset_buff,0,sizeof(offset_buff));
        ret = file_obj.Read(offset_buff,offset_read_size);
        if(ret <= 0){
            break;
        }
#if 0
        if(i%5000 == 0){
            golden_printfi("word = %s %d\n",word_buff,::ntohl(*((long*)offset_buff)));
        }
#endif

        WordIdxItem newItem((const char *)word_buff,ntohl(*(unsigned int *)offset_buff),ntohl(*(unsigned int *)(offset_buff+4))); 
        //word_tree.InsertNode(newItem);
        word_hash.DictHashInsert(newItem);
        i++;
    }
    return 0;
}


WordIdxItem StardictIdx::getIdxWord(const char *str){
    WordIdxItem tmp(str,0,0);
    //WordIdxItem c = word_tree.FindNode(tmp);
    const WordIdxItem c = word_hash.DictHashGet(tmp);
    return c;
}



       
