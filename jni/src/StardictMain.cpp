#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"GzipHeaderParser.h"
#include"GzipDeflate.h"
#include"StardictDict.h"

#if 0
const char *ifo_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.ifo";
const char *idx_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.idx";
const char *dict_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.dict.dz";

const char *ce_ifo_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.ifo";
const char *ce_idx_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.idx";
const char *ce_dict_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.dict.dz";
#else
const char *ifo_path = "./bin/langdao-ec-gb.ifo";
const char *idx_path = "./bin/langdao-ec-gb.idx";
const char *dict_path = "./bin/langdao-ec-gb.dict.dz";

const char *ce_ifo_path = "./bin/langdao-ce-gb.ifo";
const char *ce_idx_path = "./bin/langdao-ce-gb.idx";
const char *ce_dict_path = "./bin/langdao-ce-gb.dict.dz";
#endif

class StardictIntance:public Ref,DictInterface{
    public:
        StardictIntance(const char *path);
        virtual ~StardictIntance();
        virtual TextMetaData* DictQuery(const char *queryWord);
    private:
        StardictInfo *si;
        StardictIdx  *sidx;
        StardictDict *dict;
};

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

TextMetaData* StardictIntance::DictQuery(const char *queryWord){
    WordIdxItem wii = sidx->getIdxWord(queryWord);
    wii.dumpInfo(); 
    return dict->read_word_data(wii.data_offset,wii.data_size);
}


StardictIntance::StardictIntance(String8 *path){
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
    dict = new dict(path + ".dict.dz",si->getSameTypeSeq());
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
    }
}

void StardictMain::InsertDict(const char *path){
    //check the path
    String8 tmp_path(path);
    //just stardict now
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

const DictInterface *StardictMain::getDictIdx(int idx){
    if(idx < MAX_DICT_COUNT && mDict[idx] != NULL){
        return mDict[idx];
    }
    return NULL;
}

void StardictMain::DeleteDict(const char *path){

}

StardictMain::StardictMain(){
    int i = 0;
    while(i < MAX_DICT_COUNT){
        mDict[i] = NULL;
    }

}
