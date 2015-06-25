#include"DslParser.h"
#include<list>
#include<map>
#include<string>
#include"String8.h"
#include<set>

using namespace std;


class TagCompare{
    public:
    bool operator()(const char *str1,const char *str2){
        return strcmp(str1,str2);
    }
};


const char *ParserTag(const char* line,const char* tag,DslDesNode *node){
    map<const char *,const char *> tag_pair ={
        {"[","]"},
        {"{{","}}"},
    };
    const char *tag_end = strstr(line,tag_pair[tag]);
    if(tag_end != NULL){
        node->mAttrName = String8(line,tag_end-line);
        return tag_end + strlen(tag_pair[tag]);
    }else{
        return line;
    }
}


DslTagNode *ParserLine(String8 *line){
    const char *tmp = line->string();
    int status = PARSER_LINE_BEGIN;
    char buff[10240]={0};
    int i = 0;
    DslDesNode *tmpDesNode = NULL;
    vector<DslDesNode*> store_node_stack ;
    vector<DslDesNode*> node_stack;
    int match = 0;
    int escape = 0;
    const char *ret = NULL;
    char *desc_tmp = buff ;

    while(*tmp != NULL){
        if(status == PARSER_LINE_BEGIN){
            if(*tmp == '['){
                status = PARSER_TAG_START;
            }else{
                tmp ++;
            }
        }else if (status == PARSER_TAG_START){
            if(*tmp == '[' || *tmp == '{'){
                tmpDesNode = new DslDesNode;
                i = 0 ;
                memset(buff,0,sizeof(buff));
                if(*(tmp+1) == '{'){
                    tmp = parsertag(tmp+2,tmp,tmpdesnode);
                }else{
                    tmp = parsertag(tmp++,tmp,tmpdesnode);
                }
                node_stack.push_back(tmpdesnode);
            }else{
                status = PARSER_DESC_START;
            }
        }else if (status == PARSER_DESC_START){
            if(*tmp == '\\' && !escape){
                escape = 1;
                tmp ++;
            }else if((*tmp == '[' || *tmp == '{') && !escape){
                if(desc_tmp != buff){
                    vector<DslDesNode*>::iterator node = node_stack.back();
                    (*node)->mDes = String8(buff,strlen(buff)); 
                }
                status == PARSER_TAG_START;
            }else{
                *(desc_tmp++) = *(tmp ++);
                escape = 0;
            }
        }

    }

    return NULL;
}
/*
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
            //get tag
            strstr(tmp,buff);



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
        }else if (MUTIL_LTAG_BEGIN == status){
            if(*tmp == '{'}{
                status = SINGLE_TAG_BEGIN;
                tmpDesNode = new DslDesNode;
                i = 0 ;
                memset(buff,0,sizeof(buff));
            }
        }
    }
}
*/


int main(){
    return 0;
}
