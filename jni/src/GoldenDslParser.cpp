#include"GoldenDslParser.h"
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
        node->mAttrName = String8(line,value-line);
        value ++;
        node->mAttrValue = String8(value,tag_end -value);

        //printf("node->mAttrName = %s ",node->mAttrName.string());
        //printf("node->mAttrValue = %s \n",node->mAttrValue.string());

        return tag_end + strlen(tag_pair[tag]);
    }else if(tag_end != NULL){
        node->mAttrName = String8(line,tag_end-line);
        //printf("node->mAttrName = %s \n",node->mAttrName.string());
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

    while(*tmp != '\n'){
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
                    if(strstr(buff,"&lt&lt")){
                        DslDesNode* node = store_stack->back();
                        node->mDes += String8(buff,strlen(buff)); 
                    }else{
                        DslDesNode* node = node_stack.back();
                        node->mDes = String8(buff,strlen(buff)); 
                    }
                    memset(buff,0,sizeof(buff));
                    desc_tmp = buff ;
                }
                if((*(tmp +1) == '/') ||(*(tmp +1) == '{' && *(tmp +2) == '/')) {
                    status = PARSER_TAG_END;
                }else{
                    status = PARSER_TAG_START;
                }
            }else{
                if(*tmp == '<'){
                    *(desc_tmp++) = '&';
                    *(desc_tmp++) = 'l';
                    *(desc_tmp++) = 't';
                    tmp++;
                }else if(*tmp == '>'){
                    *(desc_tmp++) = '&';
                    *(desc_tmp++) = 'g';
                    *(desc_tmp++) = 't';
                    tmp++;
                }else if(*tmp == '&'){
                    *(desc_tmp++) = '&';
                    *(desc_tmp++) = 'a';
                    *(desc_tmp++) = 'm';
                    *(desc_tmp++) = 'p';
                    tmp++;
                }else if(*tmp == '\"'){
                    *(desc_tmp++) = '&';
                    *(desc_tmp++) = 'q';
                    *(desc_tmp++) = 'u';
                    *(desc_tmp++) = 'o';
                    *(desc_tmp++) = 't';
                    tmp++;
                }else {
                    *(desc_tmp++) = *(tmp ++);
                }
                escape = 0;
            }
        }else if(status == PARSER_TAG_END){
            if(*tmp == '[' && *(tmp +1) == '/'){
                DslDesNode desNode ;
                tmp = ParserTag(tmp+2,"[/",&desNode);
                DslDesNode* node = node_stack.back();

                if(node->mAttrName == desNode.mAttrName){        
                    store_stack->push_back(node);
                    node_stack.pop_back();
                }else{
                    //printf("##########################################################################\n");
                    //printf("%s  %s not match \n",desNode.mAttrName.string(),node->mAttrName.string());
                    //printf("##########################################################################\n");
                    store_stack->push_back(node);
                }

            }else if(*tmp == '{' && *(tmp +1) == '{' && *(tmp+2) == '/'){
                DslDesNode desNode ;
                tmp = ParserTag(tmp+3,"{{/",&desNode);
                DslDesNode* node = node_stack.back();
                if(node->mAttrName == desNode.mAttrName){
                    store_stack->push_back(node);
                    node_stack.pop_back();
                }else{
                    //printf("##########################################################################\n");
                    //printf("%s  %s not match \n",desNode.mAttrName.string(),node->mAttrName.string());
                    //printf("##########################################################################\n");
                    store_stack->push_back(node);
                }
            }else{
                status = PARSER_DESC_START;
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
            *(tmp++) = data;
            break;
        }else{
            *(tmp++) = data;
        }
    }
    return tmp - buff;
}


void printDescription(vector<DslDesNode *> * des_vector){
    vector<DslDesNode *> *tmp = des_vector;
    vector<DslDesNode *>::iterator begin = tmp->begin();
    vector<DslDesNode *>::iterator end = tmp->end();
    for(;begin < end; begin ++){
        if((*begin)->mDes.string() != NULL){
            printf("%s ",(*begin)->mDes.string());
        }
    }
    printf("\n");
}




void printWord(DslWordNode *word){
    printf("word : %s \n",word->mWord->string());
    vector<vector<DslDesNode *> *> word_des = word->mDesNodeList;
    vector<vector<DslDesNode *> *>::iterator begin = word_des.begin();
    vector<vector<DslDesNode *> *>::iterator end = word_des.end();
    for(;begin < end;begin ++){
        printDescription(*begin);
    }
}

char* getDescrition(vector<DslDesNode *> * des_vector,char *buff,int n){
    vector<DslDesNode *> *tmp = des_vector;
    vector<DslDesNode *>::iterator begin = tmp->begin();
    vector<DslDesNode *>::iterator end = tmp->end();
    char *tmp_buff = buff;
    int len = 0;
    for(;begin < end; begin ++){
        if((*begin)->mDes.string() != NULL){
            snprintf(tmp_buff,n,"%s",(*begin)->mDes.string());
            len = strlen(tmp_buff);
            tmp_buff += len;
            n-=len;
            if(n < 0){
                printf("over write buffer,please enlarge the input buffer!!!!!\n");
                break;
            }
        }
    }
    return buff;
}

void generateHTML(DslWordNode *word,char *html,int n){
    char *tmp = html;
    vector<vector<DslDesNode *> *> word_des = word->mDesNodeList;
    vector<vector<DslDesNode *> *>::iterator begin = word_des.begin();
    vector<vector<DslDesNode *> *>::iterator end = word_des.end();

    const char *meta_data = "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n <hr/> \n";

    snprintf(tmp,n,"<HTML> \n<H4>%s</H4>\n<body>\n%s\n",word->mWord->string(),meta_data);
    int len = 0;
    len = strlen(tmp);
    tmp += len;
    n -= len;

    for(;begin < end;begin ++){
        snprintf(tmp,n,"%s","<p>");
        len = strlen(tmp);
        tmp += len; 
        n -= len;

        getDescrition(*begin,tmp,n + html - tmp);
        len = strlen(tmp);
        tmp += len; 
        n -= len;
        strncat(tmp,"</p>\n",n);
        len = strlen(tmp);
        tmp += len; 
        n -= len;
        if(n < 0){
            break;
        }
    }

    snprintf(tmp,n,"%s","</body> \n </HTML>");
    len = strlen(tmp);
    tmp += len;
    n -= len;
}


void writeHTMLFile(DslWordNode *word){
    char file_name[128]={0};
    char buff[4096]={0};
    snprintf(file_name,sizeof(file_name),"%s.html",word->mWord->string());
    int fileNo = open(file_name,O_CREAT|O_TRUNC|O_RDWR,0666);
    if(fileNo < 0){
        printf("Create file %s fail \n",file_name);
    }
    generateHTML(word,buff,sizeof(buff));
    write(fileNo,buff,strlen(buff));
    close(fileNo);
}




int main(){
    int fileNo = open("./gb2312.txt",O_RDONLY);
    if(fileNo < 0){
        printf("open file failed \n");
    }
    char buff[2048]={0};
    int count = 0;
    DslWordNode *word = NULL;
    while(readline(fileNo,buff)){
        if(buff[0] == '\t'){
            vector<DslDesNode *> *tmp = ParserLine(buff);
            if(word != NULL){
               word->mDesNodeList.push_back(tmp);
            }
        }else{
            if(word != NULL){
                //printWord(word);
                //printf("\n");
                writeHTMLFile(word);
            }
            word = new DslWordNode();
            word->mWord = new String8(buff);
        }
        memset(buff,0,sizeof(buff));
        if(count ++ > 50){
            break;
        }
    }
    return 0;
}
