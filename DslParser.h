#ifndef __DSL_PARSER_H__
#define __DSL_PARSER_H__
#include"String8.h"
#include<list>
#include<map>
#include<vector>


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
    SINGE_TAG_BEGIN,
    SINGE_ATTR_BEGIN,
    VALUE_START,
    MUTIL_LTAG_BEGIN,
    MUTIL_LTAG_CONTINUE,
    MUTIL_LTAG_END,
    MUTIL_RTAG_BEGIN,
    MUTIL_RTAG_CONTINUE,
    MUTIL_RTAG_END,
    PARSER_LINE_END
}


class DslLineParser{
    public :
}

#endif
