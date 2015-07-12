#ifndef __DSL_PARSER_H__
#define __DSL_PARSER_H__
#include"String8.h"
#include<list>
#include<map>
#include<vector>
#include"StardictMain.h"
#include"StardictDict.h"

using namespace std;

enum PARSER_STATUE{
    PARSER_LINE_BEGIN,
    PARSER_TAG_START,
    PARSER_TAG_END,
    PARSER_DESC_START,
    PARSER_LINE_END
};

typedef struct DslDesNode{
    String8 mDes;
    String8 mAttrName;
    String8 mAttrValue; 
    DslDesNode *mNext;
}DslDesNode;

typedef struct DslWordNode{
        String8 *mWord;
        vector<vector<DslDesNode *> *> mDesNodeList;
}DslTagNode;

class DslDocumentParser{
    public:
        DslDocumentParser(const char *path);

    private:
        void BuildIdx4Dict();
        String8 GetDocEncoding();
        String8 mTextEncoding;
        String8 mFilePath;
        vector<WordIdxItem> mWordVector;
};


class DslDictionary:public DictInterface{
    public:
        DslDictionary(String8 path);
        virtual ~DslDictionary();
        virtual void DictQuery(const char *queryWord,TextMetaData*tmd);
    private:
        DslDocumentParser mParser;
};


#endif
