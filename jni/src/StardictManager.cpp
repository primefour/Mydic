#include<stdio.h>
#include<stdexcept>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"StardictDict.h"
#include"StardictManager.h"
#include"GoldenGzipHeaderParser.h"
#include"GoldenGzipInflate.h"
#include"GoldenRef.h"
#include"GoldenDictLog.h"

using namespace std;

StardictInstance::~StardictInstance() {

}

const String8& StardictInstance::GetDictonaryName(){
    return mStarDictName;
}

const String8& StardictInstance::GetIdentifyPath(){
    return mIdentifyPath;
}

const String8 StardictInstance::GetResourcePath(){
    if(mIdentifyPath.getPathDir().isEmpty()){
        return String8("/sdcard/"); 
    }
    golden_printfe("mIdentifyPath.getPathDir() = %s \n",mIdentifyPath.getPathDir().string());
    return mIdentifyPath.getPathDir() + String8("res/");
}




StardictInstance::StardictInstance(String8 path):mStarInfo(NULL),mStarIdx(NULL),mDict(NULL),mWordList(NULL){
    try{
        mStarInfo = new StardictInfo(path + ".ifo");
    }catch (exception &e){
        golden_printfd("star info fail %s \n",e.what());
        throw exception();//"star info fail");
    }

    if(mStarInfo->getWordCount() < 0){
        golden_printfe("get word count check fail \n");
        throw exception();//"info get word count fail");
    }

    golden_printfd("mStarInfo->getWordCount() = %d \n",mStarInfo->getWordCount());
    mStarInfo->dumpInfo();
    mWordList = new GoldenWordHashList(mStarInfo->getWordCount());

    try{
        mStarIdx = new StardictIdx(mWordList.GetPoint(),path+".idx",mStarInfo->getWordCount(),mStarInfo->getIdxFileSize(),mStarInfo->getOffsetBits());
        mStarIdx->init();
    }catch (exception &e){
        golden_printfe("check fail xx \n");
        throw exception();//"idx file error");
    }

    try{
        String8 dict_path = path + ".dict.dz";
        if (access(dict_path, F_OK) != 0) {
            dict_path = path + ".dict";
            if (access(dict_path , F_OK) != 0) {
                golden_printfe("no dict file \n");
                throw exception();
            }
        }
        mDict = new StardictDict(dict_path,mStarInfo->getSameTypeSeq());

    }catch(exception &e){
        golden_printfe("star dict file check fail xxxx \n");
        throw exception();//"dict file error");
    }
    mStarDictName = mStarInfo->getBookName();
    mIdentifyPath = path + ".idx";
}


int StardictInstance::GoldenDictQuery(const char *word,TextMetaData *ptrMeta){
    if(word != NULL && strlen(word) != 0){
        SObject<WordIdxItem> tmp = new WordIdxItem(word,-1,-1);
        if(mWordList->WordFind(tmp)){
            ptrMeta->setWord(word);
            const SObject<WordIdxItem>&target = mWordList->WordGet(tmp);
            if(target->data_offset == -1){
                golden_printfe("Don't find this word \n");
                return -1;
            }
            mDict->read_word_data(target->data_offset,target->data_size,ptrMeta);
            return 0;
        }else{
            return -1;
        }
    }
    return -1;
}


