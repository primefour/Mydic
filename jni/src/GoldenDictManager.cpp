#include"GoldenDictManager.h"
#include"StardictManager.h"
#include"GoldenHtmlHeader.h"
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdexcept>
#include<map>

using namespace std;

const char *PhoneticPath = "/sdcard/GoldenDict/Phonetic/";
const char *ImgPath = "/sdcard/GoldenDict/Img/";


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
    golden_printfe("file = %s \n",file);
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
                return ;
            }else{
                golden_printfd("mDictionaryMap is NULL \n");
            }
            golden_printfd("mDictionaryMap tmp_path.getBasePath() %s \n",tmp_path.getBasePath().string());
            mDictionaryMap[tmp->GetDictonaryName()] = tmp;
        }catch(exception &ex){
            golden_printfe("add dict fail %s %s  \n",tmp_path.string(),ex.what());
        }
    }else if(type == DSL_DICT_TYPE){

    }

}

const char* GoldenDictInterface::getPhoneticPath(){
    return PhoneticPath;
}

const char* GoldenDictInterface::getImgPath(){
    return ImgPath;
}

GoldenDictManager::GoldenDictManager():mIgnoreFileExtend(10),mIgnorePath(10){
    //mDictionaryType[String8("ifo")]=STAR_DICT_TYPE;
    mDictionaryType[String8(".idx")]=STAR_DICT_TYPE;
    //mDictionaryType[String8("dict.dz")]=STAR_DICT_TYPE;
    mDictionaryType[String8(".dsl")]=DSL_DICT_TYPE;
    //mDictionaryType[String8("files.zip")]=DSL_DICT_TYPE;
}

void GoldenDictManager::GoldenDictAdd(const char *path){
    GoldenPathScanner *scanner = new GoldenPathScanner(path,this);
    scanner->GoldenStartScan();
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

    GoldenHtmlHeader *html = new GoldenHtmlHeader();
    html->HTMLAddExpBegin();
    char *tmpBuff = buff;
    TextMetaData Meta;
    while(begin != end){
        if(begin->second->IsEnable()){
            if(begin->second->GoldenDictQuery(word,&Meta) == 0){
                html->HTMLAddDictionaryName(begin->second->GetDictonaryName());
                if(!Meta.mOther.isEmpty()){
                    golden_printfe("getSameTypeSeq is html \n");
                    strcpy(tmpBuff,Meta.mOther.string());
                    tmpBuff += strlen(tmpBuff);
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
    html->HTMLAddExpEnd();

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
