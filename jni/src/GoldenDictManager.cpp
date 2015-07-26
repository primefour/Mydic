#include"GoldenDictManager.h"
#include"StardictManager.h"
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdexcept>
#include<map>


using namespace std;

GoldenDictManager::GoldenDictManager(){
    mDictionaryType[String8("ifo")]=STAR_DICT_TYPE;
    mDictionaryType[String8("idx")]=STAR_DICT_TYPE;
    mDictionaryType[String8("dict.dz")]=STAR_DICT_TYPE;
    mDictionaryType[String8("dsl")]=DSL_DICT_TYPE;
    mDictionaryType[String8("files.zip")]=DSL_DICT_TYPE;
}

void GoldenDictManager::GoldenDictAdd(const char *path){
    //check the path
    String8 tmp_path(path);
    //just stardict now
    golden_printfd("tmp_path.getBasePath() = %s \n",tmp_path.getBasePath().string());
    golden_printfd("tmp_path.getFullExtension() = %s \n",tmp_path.getFullExtension().string());

    String8 Ext(tmp_path.getFullExtension());
    Ext.toLower();
    golden_printfd("%s \n",Ext.string());
    int type = mDictionaryType[Ext];
    golden_printfd("type  = %d \n", type);
    if(type == STAR_DICT_TYPE){
        try{
            //get the type of dictionary by the extend of file
            GoldenDictInterface *tmp =  new StardictInstance(tmp_path.getBasePath());
            mDictionaryMap[String8(tmp_path.getBasePath())] = tmp;  
        }catch(exception &ex){
            golden_printfe("add dict fail %s %s  \n",path,ex.what());
        }
    }else if(type == DSL_DICT_TYPE){

    }
}


void GoldenDictManager::GoldenDictDelete(const char *path){
    mDictionaryMap[String8(path).getBasePath()] = NULL;  
}

#define WRITE_FILE_FOR_DEBUG

int GoldenDictManager::GoldenDictQuery(const char *word,char *buff){
    typename map<String8,SObject<GoldenDictInterface> >::iterator begin,end;
    begin = mDictionaryMap.begin();
    end = mDictionaryMap.end();
#ifdef WRITE_FILE_FOR_DEBUG
    String8 fileName(word);
#endif
    while(begin != end){
        if(begin->second->IsEnable()){
            begin->second->GoldenDictQuery(word,buff);
#ifdef WRITE_FILE_FOR_DEBUG
            fileName += begin->second->GetDictonaryName();
            fileName +=".html";
            int fd = open(fileName.string(),O_CREAT|O_TRUNC|O_WRONLY,0664);
            if(fd < 0){
                golden_printfe("create file fail %s \n",fileName.string());
            }else{
                write(fd,buff,strlen(buff));
                close(fd);
                fd = -1;
            }
#endif

        }
        begin ++;
    }
    return 0;
}
