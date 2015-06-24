#ifndef __DSL_PARSER_H__
#define __DSL_PARSER_H__
#include"String8.h"
#include<list>
#include<map>
#include<vector>
using namespace std;


typedef struct DslDesNode{
    String8 mDes;
    String8 mAttrName;
    String8 mAttrValue; 
    DslDesNode *mNext;
}DslDesNode;

typedef struct DslWordNode{
        String8 mWord;
        vector<DslDesNode> mDesNode;
}DslTagNode;


enum PARSER_STATUE{
    PARSER_LINE_BEGIN,
    PARSER_TAG_START,
    PARSER_TAG_END,
    PARSER_DESC_START,
    PARSER_LINE_END
};

#endif
