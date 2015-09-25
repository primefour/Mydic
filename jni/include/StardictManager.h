#ifndef __STARDICT_MAIN_H__
#define __STARDICT_MAIN_H__
#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"StardictDict.h"
#include"GoldenDictManager.h"

class StardictInstance:public GoldenDictInterface{
    public:
        StardictInstance(String8 path);
        virtual const String8& GetDictonaryName();
        virtual const String8& GetIdentifyPath();
        virtual int GoldenDictQuery(const char *word,TextMetaData *ptrMeta);
        virtual ~StardictInstance();
    private:
        SObject<StardictInfo> mStarInfo;
        SObject<StardictIdx>  mStarIdx;
        SObject<StardictDict> mDict;
        String8 mStarDictName;
        String8 mIdentifyPath;
        SObject<GoldenWordHashList> mWordList;
};

#endif
