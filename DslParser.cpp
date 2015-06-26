#include"DslParser.h"
#include<list>
#include<map>
#include<string>
#include"String8.h"
#include<set>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

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
        {"[/","]"},
        {"{{","}}"},
        {"{{/","}}"},
    };
    const char *tag_end = strstr(line,tag_pair[tag]);
    const char * value = strstr(line," ");
    if (value != NULL && value < tag_end ){
        //have attribute value 
        node->mAttrName = String8(line,tag_end-line);
        value ++;
        node->mAttrValue = String8(value,tag_end -value);
        return tag_end + strlen(tag_pair[tag]);
    }else if(tag_end != NULL){
        node->mAttrName = String8(line,tag_end-line);
        return tag_end + strlen(tag_pair[tag]);
    }else{
        return line;
    }
}

vector<DslDesNode *> *ParserLine(const char *line){
    const char *tmp = line;
    int status = PARSER_LINE_BEGIN;
    char buff[10240]={0};
    int i = 0;
    DslDesNode *tmpDesNode = NULL;
    vector<DslDesNode*> node_stack;
    int match = 0;
    int escape = 0;
    const char *ret = NULL;
    char *desc_tmp = buff ;
    vector<DslDesNode *> *store_stack = new vector<DslDesNode *>();

    while(*tmp != '\0'){
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
                    tmp = ParserTag(tmp+2,"{{",tmpDesNode);
                }else{
                    tmp = ParserTag(tmp+1,"[",tmpDesNode);
                }

                if(!strstr(tmpDesNode->mAttrName.string(),"id")){
                    node_stack.push_back(tmpDesNode);
                }else{
                    delete tmpDesNode;
                }
            }else{
                status = PARSER_DESC_START;
            }
        }else if (status == PARSER_DESC_START){
            if(*tmp == '\\' && !escape){
                escape = 1;
                tmp ++;
            }else if((*tmp == '[' || *tmp == '{') && !escape){
                if(desc_tmp != buff){
                    DslDesNode* node = node_stack.back();
                    node->mDes = String8(buff,strlen(buff)); 
                    memset(buff,0,sizeof(buff));
                    desc_tmp = buff ;
                }
                status = PARSER_TAG_END;
            }else{
                *(desc_tmp++) = *(tmp ++);
                escape = 0;
            }
        }else if(status == PARSER_TAG_END){
            if(*tmp == '[' && *(tmp +1) == '/'){
                DslDesNode desNode ;
                tmp = ParserTag(tmp+2,"[/",&desNode);
                DslDesNode* node = node_stack.back();
                if(node->mAttrName == desNode.mAttrName){        
                    store_stack->push_back(node);
                }else{
                    printf("%s  %s not match \n",desNode.mAttrName.string(),node->mAttrName.string());
                }

            }else if(*tmp == '{' && *(tmp +1) == '{' && *(tmp+2) == '/'){
                DslDesNode desNode ;
                tmp = ParserTag(tmp+3,"{{/",&desNode);
                DslDesNode* node = node_stack.back();
                if(node->mAttrName == desNode.mAttrName){
                    store_stack->push_back(node);
                }else{
                    printf("%s  %s not match \n",desNode.mAttrName.string(),node->mAttrName.string());
                }
            }else{
                status = PARSER_LINE_BEGIN;
            }
        }

    }
    return store_stack ;
}


int readline(int fd,char *buff){
    char data;
    int ret = -1;
    char *tmp = buff;
    int count  = 0;
    while((ret = read(fd,&data,1))){
        if(data == '\n'){
            break;
        }else{
            *(tmp++) = data;
        }
    }
    return tmp - buff;
}

int main(){
    int fileNo = open("./gb2312.txt",O_RDONLY);
    if(fileNo < 0){
        printf("open file failed \n");
    }
    char buff[2048]={0};
    int count = 0;
    while(readline(fileNo,buff)){
        if(buff[0] != ' '){
            vector<DslDesNode *> *tmp = ParserLine(buff);
        }else{
            printf("%s \n",buff);
        }
        if(count ++ > 20){
            break;
        }
    }
    return 0;
}
