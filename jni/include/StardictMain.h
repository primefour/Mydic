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
        virtual TextMetaData* DictQuery(const char *queryWord){
            return NULL;
        }
};

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

#define MAX_DICT_COUNT 10
class StardictMain{
    public :
        StardictMain();
        ~StardictMain();
        void InsertDict(const char *path);
        void DeleteDict(const char *path);
        const DictInterface *getDictIdx(int idx); 
    private:
        DictIntance* mDict[MAX_DICT_COUNT];
}

#endif
