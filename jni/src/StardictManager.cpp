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
        mDict = new StardictDict(path + ".dict.dz",mStarInfo->getSameTypeSeq());
    }catch(exception &e){
        golden_printfe("star dict file check fail xxxx \n");
        throw exception();//"dict file error");
    }
    mStarDictName = mStarInfo->getBookName();
}


int StardictInstance::GoldenDictQuery(const char *word,char *buff){
    SObject<WordIdxItem> tmp = new WordIdxItem(word,0,0);
    if(word && buff && mWordList->DictHashfind(tmp)){
        TextMetaData targetHTML(word);
        const SObject<WordIdxItem>&target = mWordList->DictHashGet(tmp);
        mDict->read_word_data(target->data_offset,target->data_size,&targetHTML);
        String8 HTML;
        targetHTML.generateHTML(HTML);
        strcpy(buff,HTML.string());
        return 0;
    }else{
        return -1;
    }
}


