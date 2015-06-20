#include"DslParser.h"





DslTagNode *ParserLine(String8 *line){

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

    const char *tmp = line->string();
    status = PARSER_LINE_BEGIN;
    char buff[10240]={0};
    int i = 0;
    DslDesNode *tmpDesNode = NULL;
    vector<DslDesNode> store_node_stack ;
    vector<DslDesNode> node_stack;

    int match = 0;
    while(*tmp != NULL){
        if(status = PARSER_LINE_BEGIN){
            if(*tmp == '['){
                status = SINGLE_TAG_BEGIN;
                tmpDesNode = new DslDesNode;
                i = 0 ;
                memset(buff,0,sizeof(buff));
            }
            tmp ++;
        }else if(status == SINGLE_TAG_BEGIN){
            if(*tmp == ' '){
                //get attribute 
                tmpDesNode->mAttrName = buff ;
                memset(buff,0,sizeof(buff));
                i = 0;
                status == SINGLE_ATTR_BEGIN;

            }else if (*tmp == ']'){
                tmpDesNode->mAttrName = buff ;
                memset(buff,0,sizeof(buff));
                i = 0;
                if(match){
                    if(!DslDesNode.empty()){
                        DslDesNode_iterator &a = node_stack.back();
                        if (a == tmpDesNode){
                            store_node_stack.push_back(a);
                        }
                    }else{
                        printf("error for file \n");
                    }
                    match = 0;

                }else{
                    //complete one attribute node
                    status == VALUE_START;
                }
            }else if (*tmp == '/'){
                match = 1 ;
            }else{
                buff[i++] = *tmp ;
            }
            tmp ++;
        }else if(SINGLE_ATTR_BEGIN == status){
            if (*tmp == ']'){
                tmpDesNode->mAttrValue = buff ;
                memset(buff,0,sizeof(buff));
                i = 0;
                //complete one attribute node
                status == VALUE_START;
            }
            tmp++;
        }else if (VALUE_START == status){
            if(*tmp == '['){
                if(i != 0){
                    tmpDesNode->mDes = buff ;
                    memset(buff,0,sizeof(buff));
                    i = 0;
                }
                node_stack.push_back(tmpDesNode);

                status = SINGLE_TAG_BEGIN;
                tmpDesNode = new DslDesNode;

            }else{
                buff[i++] = *tmp;
            }
            tmp ++;
        }
    }
}
