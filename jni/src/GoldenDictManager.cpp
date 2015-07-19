#include"GoldenDictManager.h"
#include"StardictManager.h"
#include<stdexcept>
using namespace std;

GoldenDictManager::GoldenDictManager(){

}

void GoldenDictManager::GoldenDictAdd(const char *path){
    //check the path
    String8 tmp_path(path);
    //just stardict now
    golden_printfd("tmp_path.getBasePath() = %s ",tmp_path.getBasePath().string());
    try{
        //get the type of dictionary by the extend of file
        GoldenDictInterface *tmp =  new StardictInstance(tmp_path.getBasePath());
        mDictionaryMap[String8(tmp_path.getBasePath())] = tmp;  
    }catch(exception &ex){
        golden_printfe("add dict fail %s %s  \n",path,ex.what());
    }
}


void GoldenDictManager::GoldenDictDelete(const char *path){
    mDictionaryMap[String8(path).getBasePath()] = NULL;  
}

int GoldenDictManager::GoldenDictQuery(const char *word,char *buff){
    mDictionaryMap[String8("./bin/langdao-ec-gb")]->GoldenDictQuery(word,buff);
    return 0;
}
