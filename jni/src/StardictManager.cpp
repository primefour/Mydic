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

const String8& StardictInstance::GetResourcePath(){
    return mResourceDir ;
}




StardictInstance::StardictInstance(String8 path,int dict_idx,GoldenWordHashMap &map):mStarInfo(NULL),mStarIdx(NULL),mDict(NULL){
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
    //mWordList = new GoldenWordHashList(mStarInfo->getWordCount());
    //mWordList = new GoldenWordTriTree();
    try{
        mStarIdx = new StardictIdx(&map,path+".idx",mStarInfo->getWordCount(),mStarInfo->getIdxFileSize(),dict_idx,mStarInfo->getOffsetBits());
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
    mResourceDir = mIdentifyPath.getPathDir() + String8("res/");
    if(access(mResourceDir.string(),F_OK) != 0){
        mResourceDir = String8::empty();
    }
}

int StardictInstance::GoldenDictReadData(WordOffsetInfo &woi,TextMetaData *ptrMeta){
    if(woi.size != 0 && ptrMeta != NULL){
        mDict->read_word_data(woi.offset,woi.size,ptrMeta);
        return 0;
    }else{
        return -1;
    }
}
