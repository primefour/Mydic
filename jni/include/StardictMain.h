#ifndef __STARDICT_MAIN_H__
#define __STARDICT_MAIN_H__
#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"GzipHeaderParser.h"
#include"GzipDeflate.h"
#include"StardictDict.h"

class DictInterface{
    public:
        virtual void DictQuery(const char *queryWord,TextMetaData*tmd){
            return ;
        }
};

class StardictIntance:public DictInterface{
    public:
        StardictIntance(String8 path);
        virtual ~StardictIntance();
        virtual void DictQuery(const char *queryWord,TextMetaData*tmd);
    private:
        StardictInfo *si;
        StardictIdx  *sidx;
        StardictDict *dict;
};

#define MAX_DICT_COUNT 10
class StardictMain{
    public :
        StardictMain();
        ~StardictMain();
        void InsertDict(const char *path);
        void DeleteDict(const char *path);
        DictInterface *getDictIdx(int idx); 
    private:
      DictInterface* mDict[MAX_DICT_COUNT];
};

#endif
