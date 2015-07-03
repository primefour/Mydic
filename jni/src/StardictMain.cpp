#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"GzipHeaderParser.h"
#include"GzipDeflate.h"
#include"StardictDict.h"
#include"Ref.h"
#include"StardictMain.h"

#ifdef ANDROID_PLATFORM
#include <android/log.h>
#define  LOG_TAG    "DICT2"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define printf LOGE
#else

#define LOGE printf
#define LOGI printf

#endif




StardictIntance::~StardictIntance(){
    if(si != NULL){
        delete si;
    }
    if(sidx != NULL){
        delete sidx;
    }
    if(dict != NULL){
        delete dict;
    }
}

void StardictIntance::DictQuery(const char *queryWord,TextMetaData*tmd){
    WordIdxItem wii = sidx->getIdxWord(queryWord);
    wii.dumpInfo(); 
    dict->read_word_data(wii.data_offset,wii.data_size,tmd);
}

StardictIntance::StardictIntance(String8 path){
    si = NULL;
    sidx = NULL;
    dict = NULL;
    si = new StardictInfo(path + ".ifo");
    //check si
    if(si&&si->getWordCount() < 0){
        printf("check fail \n");
        return ;
    }
    sidx = new StardictIdx(path+".idx",si->getWordCount(),si->getIdxFileSize(),si->getOffsetBits());
    if(!sidx){
        printf("check fail xx \n");
        return ;
    }
    dict = new StardictDict(path + ".dict.dz",si->getSameTypeSeq());
    if(dict == NULL){
        printf("check fail xxxx \n");
    }
}


//static state
StardictMain::~StardictMain(){
    int i = 0;
    while(i < MAX_DICT_COUNT){
        if(mDict[i] != NULL){
            delete mDict[i] ;
            mDict[i] = NULL;
        }
        i++;
    }
}

void StardictMain::InsertDict(const char *path){
    printf("%s %d %s ",__func__,__LINE__,path);
    //check the path
    String8 tmp_path(path);
    //just stardict now
    printf("tmp_path.getBasePath() = %s ",tmp_path.getBasePath().string());
    DictInterface *tmp =  new StardictIntance(tmp_path.getBasePath());
    int i = 0;
    while(i < MAX_DICT_COUNT){
        if(mDict[i] == NULL){
            break;
        }
        i++;
    }
    mDict[i] = tmp;
}

DictInterface *StardictMain::getDictIdx(int idx){
    if(idx < MAX_DICT_COUNT && mDict[idx] != NULL){
        return mDict[idx];
    }
    return NULL;
}

void StardictMain::DeleteDict(const char *path){
    printf("%s %d ",__func__,__LINE__);
}

StardictMain::StardictMain(){
    int i = 0;
    while(i < MAX_DICT_COUNT){
        mDict[i] = NULL;
        i++;
    }

}
