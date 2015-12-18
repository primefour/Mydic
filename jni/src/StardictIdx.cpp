#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdexcept>
#include"GoldenStandardIO.h"
#include"GoldenHashSet.h"
#include"GoldenDictLog.h"
#include"GoldenWordIndexItem.h"
#include"StardictIdx.h"
#include"String8.h"
using namespace std;


StardictIdx:: StardictIdx(GoldenWordIdxInteface *idx_list,const char *file_path,
                    int word_count,int file_size,int offsetbit):word_list(idx_list),file_path(file_path){
    this->word_count = word_count;
    this->offsetbit = offsetbit;
    this->file_size = file_size;
    golden_printfi("word_count  = %d file_size = %d  offsetbit=%d \n",word_count,file_size,offsetbit);
}

StardictIdx::~StardictIdx(){

}

int StardictIdx::init(){
    unsigned char word_buff[1024]={0};
    SObject<MemFile> file_obj = NULL;
    try{
        file_obj = new MemFile(file_path,O_RDONLY);
    }catch (exception &e){
        golden_printfe("index file open fail %s ",e.what());
        throw exception();//"index file open fail");
    }
    
    int offset_read_size = 8;
    if(offsetbit == 64){
        offset_read_size = 12;
    }

    int i = 0;
    unsigned char offset_buff[12]={0};
    while(i < word_count){
        memset(word_buff,0,sizeof(word_buff));
        int ret = file_obj->ReadTerminating(word_buff,sizeof(word_buff),'\0');
        if(ret <= 0){
            break;
        }
        memset(offset_buff,0,sizeof(offset_buff));
        ret = file_obj->Read(offset_buff,offset_read_size);
        if(ret < 0){
            break;
        }
#if 0
        if(i%5000 == 0){
            golden_printfi("word = %s %d\n",word_buff,::ntohl(*((long*)offset_buff)));
        }
#endif
        i++;
        SObject<WordIdxItem> newItem(new WordIdxItem((const char *)word_buff,
                                                ntohl(*(unsigned int *)offset_buff),
                                                ntohl(*(unsigned int *)(offset_buff+4))));
        word_list->WordInsert(newItem);
    }
    return 0;
}
