#include"GoldenDictManager.h"
#include"StardictManager.h"
#include"GoldenHtmlHeader.h"
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdexcept>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<sys/stat.h>
#include<unistd.h>
#include<map>

using namespace std;

#ifdef ANDROID_PLATFORM
const char *GOLDEN_TMP_PHONETIC_PATH = "/sdcard/MiGuoDict/Phonetic/";
const char *GOLDEN_TMP_IMG_PATH = "/sdcard/MiGuoDict/Img/";
const char *GOLDEN_IDX_DICT_PATH = "/sdcard/MiGuoDict/DictIdx.dat";
const char *GOLDEN_CACHE_DICT_PATH = "/sdcard/MiGuoDict/Cache/";
const char *GOLDEN_ROOT_PATH= "/sdcard/";

#else
const char *GOLDEN_TMP_PHONETIC_PATH = "./Phonetic/";
const char *GOLDEN_TMP_IMG_PATH = "./Img/";
const char *GOLDEN_IDX_DICT_PATH = "./DictIdx.dat";
const char *GOLDEN_CACHE_DICT_PATH = "./Cache/";
const char *GOLDEN_ROOT_PATH= "./";
#endif


TextMetaData:: TextMetaData(){
    golden_printfd("TextMetaData copy construct function \n");
    mWavDataLength = 0;
    mPicDataLength = 0;
    mWav = NULL;
    mPic = NULL;
}

TextMetaData::TextMetaData(const TextMetaData &tmp){
    golden_printfd("TextMetaData copy construct function \n");
    mWavDataLength = tmp.mWavDataLength;
    if(mWavDataLength != 0){
        mWav = new unsigned char[mWavDataLength];
        memcpy(mPic,tmp.mPic,mWavDataLength);
    }

    if(mPicDataLength != 0){
        mPic = new unsigned char[mPicDataLength];
        memcpy(mPic,tmp.mPic,mPicDataLength);

    }
    mTextMeaning = tmp.mTextMeaning;
    mTextPhonetic = tmp.mTextPhonetic;
    mImagePath = tmp.mImagePath;
    mVideoPath = tmp.mVideoPath;
    mSoundPath = tmp.mSoundPath;
    mOther = tmp.mOther;
}


void TextMetaData::dumpInfo(){
    golden_printfd("Text Mean: %s \n",mTextMeaning.string());
    golden_printfd("Text Phonetic: %s \n",mTextPhonetic.string());
    golden_printfd("Image Path : %s \n",mImagePath.string());
    golden_printfd("Video path : %s \n",mVideoPath.string());
    golden_printfd("Sound Path: %s \n",mSoundPath.string());
    golden_printfd("Other : %s \n",mOther.string());
    if(mWav != NULL){
        golden_printfd("there is wav data \n");
    }
    if(mPic != NULL){
        golden_printfd("there is pic data \n");
    }
}

TextMetaData::~TextMetaData(){
    if(mWav != NULL){
        delete mWav;
    }
    mWav = NULL;
    if(mPic != NULL){
        delete mPic;
    }
    mPic = NULL;
}

/*********************************************************************************
 *GoldenDictManager
 *********************************************************************************/

void GoldenDictManager::doWithFiles(const char *file){
    //golden_printfe("file = %s \n",file);
    String8 tmp_path(file);
    //golden_printfd("getFullExtension %s \n",tmp_path.getFullExtension().string());
    if(tmp_path.getPathExtension().string() == NULL){
        return ;
    }
    String8 Ext(tmp_path.getPathExtension());
    //golden_printfd("##%s \n",Ext.string());
    Ext.toLower();
    //golden_printfd("%s \n",Ext.string());
    int type = mDictionaryType[Ext];
    //golden_printfe("type %d  \n",type);
    if(type == 0){
        return ;
    }

    if(type == STAR_DICT_TYPE){
        try{
            //get the type of dictionary by the extend of file
            GoldenDictInterface *tmp =  new StardictInstance(tmp_path.getBasePath());
            golden_printfe("dictionary name = %s \n",tmp->GetDictonaryName().string());
            SObject<GoldenDictInterface> obj = mDictionaryMap[tmp->GetDictonaryName()];
            if(obj.GetPoint() != NULL ){
                golden_printfd("mDictionaryMap is not NULL \n");
                delete tmp;
                tmp = NULL;
                golden_printfd("end mDictionaryMap is not NULL \n");
                return ;
            }else{
                golden_printfd("mDictionaryMap is NULL \n");
            }
            golden_printfd("mDictionaryMap tmp_path.getBasePath() %s \n",tmp_path.getBasePath().string());
            mDictionaryMap[tmp->GetDictonaryName()] = tmp;
            mDictionaryPath[tmp->GetDictonaryName()] = tmp_path;
        }catch(exception &ex){
            golden_printfe("add dict fail %s %s  \n",tmp_path.string(),ex.what());
        }
    }else if(type == DSL_DICT_TYPE){

    }

}

const char* GoldenDictManager::GoldenGetTmpPhoneticPath(){
    return GOLDEN_TMP_PHONETIC_PATH;
}

const char* GoldenDictManager::GoldenGetTmpImgPath(){
    return GOLDEN_TMP_IMG_PATH;
}

const char *GoldenDictManager::GoldenGetCachePath(){
    return GOLDEN_CACHE_DICT_PATH ;
}

GoldenDictManager::GoldenDictManager():mIgnoreFileExtend(10),mIgnorePath(10){
    //mDictionaryType[String8("ifo")]=STAR_DICT_TYPE;
    mDictionaryType[String8(".idx")]=STAR_DICT_TYPE;
    //mDictionaryType[String8("dict.dz")]=STAR_DICT_TYPE;
    mDictionaryType[String8(".dsl")]=DSL_DICT_TYPE;
    //mDictionaryType[String8("files.zip")]=DSL_DICT_TYPE;
}

void GoldenDictManager::GoldenScanDisk(const char *path){
    GoldenPathScanner *scanner = NULL;
    if(path == NULL){
         scanner = new GoldenPathScanner(GOLDEN_ROOT_PATH,this);
         //update list file
         unlink(GOLDEN_IDX_DICT_PATH);
    }else{
         scanner = new GoldenPathScanner(path,this);
    }
    scanner->GoldenStartScan();
    GoldenDictPersist();
    delete scanner;
}

//save idx files path and dictionaries' name in DictIdx file
void GoldenDictManager::GoldenDictPersist(){
    typename map<String8,SObject<GoldenDictInterface> >::iterator begin,end;
    begin = mDictionaryMap.begin();
    end = mDictionaryMap.end();
    SObject<SimpleFile> fileObj = new SimpleFile(GOLDEN_IDX_DICT_PATH,O_APPEND|O_CREAT|O_RDWR,0666);
    char buff[4096]={0};
    while(begin != end){
        memset(buff,0,sizeof(buff));
        snprintf(buff,sizeof(buff),"%s==>%s\n", begin->first.string(),begin->second->GetIdentifyPath().string());
        fileObj->Write((unsigned char *)buff,strlen(buff));
        golden_printfe("%s \n",buff);
        begin ++;
    }
}

//read DictIdx and restore dictionaries
char *GoldenDictManager::GoldenDictGetPersistData(const char *dictName,char *rbuff,int length){
    SObject<SimpleFile> fileObj = new SimpleFile(GOLDEN_IDX_DICT_PATH,0);
    char buff[4096]={0};
    int ret = fileObj->ReadLine((unsigned char *)buff,sizeof(buff));
    char name[1024]={0};
    char path[PATH_MAX]={0};
    int rflag = 0;
    while(ret != 0){
        char *flag = strstr(buff,"==>");
        memcpy(name,buff,flag - buff);
        flag += strlen("==>");
        strcpy(path,flag);
        path[strlen(path) -1] ='\0';
        golden_printfe("buff = %s name %s  path = %s \n",buff,name,path);
        if(strcmp(name,dictName) == 0 ){
            strncpy(rbuff,path,length);
            rflag  = 1;
        }
        memset(buff,0,sizeof(buff));
        memset(name,0,sizeof(name));
        memset(path,0,sizeof(path));
        ret = fileObj->ReadLine((unsigned char *)buff,sizeof(buff));
        golden_printfe("end ret = %d buff = %s \n",ret,buff);
    }
    if(rflag){
        return rbuff;
    }else{
        return NULL;
    }

}

//read DictIdx and restore dictionaries
void GoldenDictManager::GoldenDictReload(){
    SObject<SimpleFile> fileObj = new SimpleFile(GOLDEN_IDX_DICT_PATH,0);
    char buff[4096]={0};
    int ret = fileObj->ReadLine((unsigned char *)buff,sizeof(buff));
    char name[1024]={0};
    char path[PATH_MAX]={0};
    while(ret != 0){
        char *flag = strstr(buff,"==>");
        memcpy(name,buff,flag - buff);
        flag += strlen("==>");
        strcpy(path,flag);
        path[strlen(path) -1] ='\0';
        golden_printfe("buff = %s name %s  path = %s \n",buff,name,path);
        doWithFiles(path);
        //mDictionaryPath[String8(name)] = String8(path);
        memset(buff,0,sizeof(buff));
        memset(name,0,sizeof(name));
        memset(path,0,sizeof(path));
        ret = fileObj->ReadLine((unsigned char *)buff,sizeof(buff));
        golden_printfe("end ret = %d buff = %s \n",ret,buff);
    }
}

//add a single file
void GoldenDictManager::GoldenDictAddDict(const char *name){
    String8 tmp(name);
    char buff[1024] = {0};
    if(mDictionaryPath.count(tmp) == 0){
        if(GoldenDictGetPersistData(name,buff,sizeof(buff)) != NULL){
            mDictionaryPath[tmp] = String8(buff);
        }else{
            return ;
        }
    }
    doWithFiles(mDictionaryPath[String8(name)].string());
}

void GoldenDictManager::GoldenDictRemoveDict(const char *name){
    mDictionaryMap[String8(name)] = NULL;
}

void GoldenDictManager::GoldenDictEnableDict(const char *name ,bool enable){
    mDictionaryMap[String8(name)]->SetEnable(enable);
}

void GoldenDictManager::GoldenDictGetDicts(const char **list){
    if(list == NULL){
        return ;
    }
    typename map<String8,String8>::iterator begin,end;
    begin = mDictionaryPath.begin();
    end = mDictionaryPath.end();
    const char **tmp = list;
    while(begin != end){
        *tmp = begin->first.string();
        begin ++;
        tmp ++;
    }
}

void GoldenDictManager::GoldenDictSetOrder(const char **list){
    if(list == NULL){
        return ;
    }
    const char **tmp = list;
    int count = 0;
    mOrderList.clear();
    golden_printfe("###count is %d size of list is %d \n",count,mOrderList.size());

    while(*tmp != NULL){
        mOrderList.push_back(String8(*tmp));
        tmp++;
        count ++;
    }
    golden_printfe("count is %d size of list is %d \n",count,mOrderList.size());

    return ;
}

#define WRITE_FILE_FOR_DEBUG

int GoldenDictManager::GoldenDictQuery(const char *word,char *buff){
    typename map<String8,SObject<GoldenDictInterface> >::iterator begin,end;
    begin = mDictionaryMap.begin();
    end = mDictionaryMap.end();
#ifdef WRITE_FILE_FOR_DEBUG
    String8 fileName(word);
#endif

    GoldenHtmlHeader *html = new GoldenHtmlHeader();
    html->HTMLAddExpBegin();
    if(mOrderList.size() == 0){ 
        while(begin != end){
            TextMetaData Meta;
            if(begin->second.GetPoint() != NULL && begin->second->IsEnable()){
                if(begin->second->GoldenDictQuery(word,&Meta) == 0){
                    html->HTMLAddDictionaryName(begin->second->GetDictonaryName());
                    if(!Meta.mOther.isEmpty()){
                        golden_printfe("getSameTypeSeq is html \n");
                        html->AddHtmlPiece(Meta.mOther.string());
                    }else{
                        html->HTMLAddWord(html->EncodeString(Meta.mWord));
                        if(!Meta.mTextPhonetic.isEmpty()){
                            html->HtmlAddPhonetic(html->EncodeString(Meta.mTextPhonetic),Meta.mSoundPath);
                        }
                        if(!Meta.mTextMeaning.isEmpty()){
                            html->HtmlAddOnlyMeaning(html->EncodeString(Meta.mTextMeaning));
                        }
                    }
                }
            }
            begin ++;
        }
    }else{
        golden_printfe("use order list to query word \n");
        vector<String8>::iterator list_begin = mOrderList.begin();
        vector<String8>::iterator list_end = mOrderList.end();
        while(list_begin != list_end){
            TextMetaData Meta;
            golden_printfe("KKKK %s === %d  %d \n",list_begin->string(),mDictionaryMap.count(*list_begin),mOrderList.size());
            if(mDictionaryMap.count(*list_begin)){
                if(mDictionaryMap[*list_begin]->GoldenDictQuery(word,&Meta) == 0){
                    html->HTMLAddDictionaryName(mDictionaryMap[*list_begin]->GetDictonaryName());
                    if(!Meta.mOther.isEmpty()){
                        golden_printfe("getSameTypeSeq is html \n");
                        html->AddHtmlPiece(Meta.mOther.string());
                    }else{
                        html->HTMLAddWord(html->EncodeString(Meta.mWord));
                        if(!Meta.mTextPhonetic.isEmpty()){
                            html->HtmlAddPhonetic(html->EncodeString(Meta.mTextPhonetic),Meta.mSoundPath);
                        }
                        if(!Meta.mTextMeaning.isEmpty()){
                            html->HtmlAddOnlyMeaning(html->EncodeString(Meta.mTextMeaning));
                        }
                    }
                }
            }
            list_begin ++;
        }
    }
    html->HTMLAddExpEnd();
    strcpy(buff,html->getResult());
#ifdef WRITE_FILE_FOR_DEBUG
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
    delete html;
    return 0;
}
