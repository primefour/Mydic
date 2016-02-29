#ifndef __STARDICT_MAIN_H__
#define __STARDICT_MAIN_H__
#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"StardictDict.h"
#include"GoldenDictManager.h"

class StardictInstance:public GoldenDictInterface{
    public:
        //StardictInstance(String8 path,int dict_idx);
        StardictInstance(String8 path,int dict_idx,GoldenWordHashMap &map);
        virtual const String8& GetDictonaryName();
        virtual const String8& GetIdentifyPath();
        virtual const String8& GetResourcePath();
        virtual int GoldenDictReadData(WordOffsetInfo &woi,TextMetaData *ptrMeta);
        virtual ~StardictInstance();
    private:
        SObject<StardictInfo> mStarInfo;
        SObject<StardictIdx>  mStarIdx;
        SObject<StardictDict> mDict;
        String8 mStarDictName;
        String8 mIdentifyPath;
        String8 mResourceDir;
#ifdef OLD_IDX
        SObject<GoldenWordIdxInteface> mWordList;
#endif
};

#endif
