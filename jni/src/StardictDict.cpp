#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdexcept>
#include"GoldenStandardIO.h"
#include"GoldenGzipHeaderParser.h"
#include"GoldenGzipInflate.h"
#include"GoldenDictLog.h"
#include"StardictDict.h"
#include"String8.h"
using namespace std;

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

void TextMetaData::generateHTML(String8 &result){
    const int buff_len = 10240;
    char *buff = new char[buff_len] ;
    memset(buff,0,buff_len);
    char *tmp = buff;
    int n = buff_len;
    int len = 0;
    const char *meta_data = "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n <hr/> \n";
    snprintf(tmp,n,"<HTML> \n<H4>%s</H4>\n<body>\n%s\n",mWord.string(),meta_data);
    len = strlen(tmp);
    tmp += len;
    n -= len;

    if(!mTextPhonetic.isEmpty()){
        snprintf(tmp,n,"%s <p>",mTextPhonetic.string());
        len = strlen(tmp);
        tmp += len;
        n -= len;
    }

    const char *ptr_m = mTextMeaning.string();
    const char * html_p = " <p>\n";
    const int html_p_len = strlen(html_p);
    while(*ptr_m){
        if(*ptr_m == '\n'){
            strcat(tmp," <p>\n");
            tmp += html_p_len;
        }else{
            *tmp = *ptr_m;
            tmp ++;
        }
        ptr_m ++;
    }
    n = buff_len - strlen(buff);

    const char *audio = "<p> </p> \n<a href hello.wav > audio </a> <p></p> " ;

    snprintf(tmp,n,"%s",audio);
    len = strlen(tmp);
    tmp += len;
    n -= len;

    snprintf(tmp,n,"%s","</body> \n </HTML>");
    len = strlen(tmp);
    tmp += len;
    n -= len;

    result.setTo(buff);
    delete[] buff;
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


/********************************************stardict dictionary**********************************************/

StardictDict::StardictDict(const char*file_name,const char *same_type_seq):mSeq(same_type_seq),file_path(file_name){
    SObject<GzipInflate> file_obj = NULL;
    try{
        file_obj = new GzipInflate(file_path,O_RDONLY);
    }catch(exception &e){
        throw exception();//"Gzip file error %s ",e.what());
    }
}

StardictDict::~StardictDict(){

}


void StardictDict::read_word_data(int offset,int length,TextMetaData* tmd){
    golden_printfi("%s offset = %d length = %d \n",__func__,offset,length);
    SObject<GzipInflate> file_obj = NULL;
    try{
        file_obj = new GzipInflate(file_path,O_RDONLY);
    }catch(exception &e){
        golden_printfe("gzip file error %s ",e.what()); 
        throw exception();//"get word fail");
    }
    file_obj->Seek(SEEK_SET,offset);
    unsigned char *buff = new unsigned char [length + 4] ;
    memset(buff,0,length +4);
    int ret = file_obj->Read(buff,length);
    if(ret != length){
        golden_printfe("%s ret error xxxxxxxx",__func__);
        throw exception();//"get word fail");
    }
    parse_meta_data(tmd,buff,length);
    delete[] buff;
}


void StardictDict::parse_meta_data(TextMetaData *tmd, unsigned char *data,int length){
    const char *seq = mSeq.string();
    unsigned char *pData = data;
    unsigned char *pData_end = pData + length;

    if(!mSeq.isEmpty()){
        while(*seq != '\0' && pData < pData_end ){
            pData += parse_common_flag(tmd,*seq,pData);
            seq ++;
        }
    }else{
        while(pData < pData_end ){
            pData += parse_common_flag(tmd,*(++pData),pData);
        }

    }
}


int StardictDict::parse_common_flag(TextMetaData *tmp,char flag,unsigned char *data){
    golden_printfi("%s flag = %c \n",__func__,flag);
    int length = 0;
    switch(flag){
        case 'm':
            length = parse_m_data(tmp,data);
            break;
        case 'l':
            length = parse_l_data(tmp,data);
            break;
        case 'g':
            length = parse_g_data(tmp,data);
            break;
        case 't':
            length = parse_t_data(tmp,data);
            break;
        case 'x':
            length = parse_x_data(tmp,data);
            break;
        case 'y':
            length = parse_y_data(tmp,data);
            break;
        case 'k':
            length = parse_k_data(tmp,data);
            break;
        case 'w':
            length = parse_w_data(tmp,data);
            break;
        case 'h':
            length = parse_h_data(tmp,data);
            break;
        case 'r':
            length = parse_r_data(tmp,data);
            break;
        case 'W':
            length = parse_W_data(tmp,data);
            break;
        case 'P':
            length = parse_P_data(tmp,data);
            break;
        case 'X':
            length = parse_X_data(tmp,data);
            break;
        default:
            golden_printfe("get a error format \n");
            break;
    }
    return length;
}


//word's pure text meaing
//utf-8 string terminate with '\0'
int StardictDict::parse_m_data(TextMetaData *tmp,unsigned char *data){
    int length = strlen((const char *)data) +1;
    tmp->mTextMeaning.append((char *)data);
    tmp->mTextMeaning.append("\n");
    return length; 

}
//word's pure text meaning
//data is not a utf-8 string,but is instead a string in locale encoding,ending with '\0'
//sometimes using this type will save diskspace,but its use is discouraged
int StardictDict::parse_l_data(TextMetaData *tmp,unsigned char *data){
    //fix me
    int length = strlen((const char *)data) +1;
    tmp->mTextMeaning.append((char *)data);
    tmp->mTextMeaning.append("\n");
    return length; 
}


//utf-8 string which is marked up with the Pango text markup language.
//for more information about this markup language,See the pango reference manual
//you might have it installed locally at 
//file:///usr/share/gtk-doc/html/pango/PangoMarkupFormat.html
int StardictDict::parse_g_data(TextMetaData *tmp,unsigned char *data){
    //fix me
    int length = strlen((const char *)data) +1;
    tmp->mTextMeaning.append((char *)data);
    tmp->mTextMeaning.append("\n");
    return length; 
}

//Englist phonetic string
//the data should be a utf-8 string ending with '\0'
int StardictDict::parse_t_data(TextMetaData *tmp,unsigned char *data){
    int length = strlen((const char *)data) +1;
    tmp->mTextPhonetic.append((char *)data);
    tmp->mTextPhonetic.append("\n");
    return length; 
}


// a utf-8 string which is marked up with the xdxf language
// see http://xdxf.sourceforge.net
// <rref> can have "type" attribute,it can be "image","sound","video" and "attach"
// <kref> can have "k" attribute
int StardictDict::parse_x_data(TextMetaData *tmp,unsigned  char *data){
    int length = strlen((const char *)data) +1;
    tmp->mOther.append((char *)data);
    tmp->mOther.append("\n");
    return length; 
}

//chinese YinBiao or japanese KANA
//the data should be a utf-8 string ending with '\0'
int StardictDict::parse_y_data(TextMetaData *tmp,unsigned char *data){
    int length = strlen((const char *)data) +1;
    tmp->mTextPhonetic.append((char *)data);
    tmp->mTextPhonetic.append("\n");
    return length; 
}
//Kingsoft PowerWord's data,the data is a utf-8 string ending with '\0'
//it is in xml format
int StardictDict::parse_k_data(TextMetaData *tmp,unsigned char *data){
    int length = strlen((const char *)data) +1;
    tmp->mOther.append((char *)data);
    tmp->mOther.append("\n");
    return length; 
}
//MediaWiki markup lanaguage
//http://meta.wikimedia.org/wiki/Help:Editing#The_wiki_markup
int StardictDict::parse_w_data(TextMetaData *tmp,unsigned char *data){
    int length = strlen((const char *)data) +1;
    tmp->mOther.append((char *)data);
    tmp->mOther.append("\n");
    return length; 
}

//html codecs
int StardictDict::parse_h_data(TextMetaData *tmp,unsigned char *data){
    int length = strlen((const char *)data) +1;
    tmp->mOther.append((char *)data);
    tmp->mOther.append("\n");
    return length; 
}

//Resouce file list:
//the content can be:
//img:image file
//snd:sound file
//vdo:video file
//att:attachment file
//More the one line is supported as a list of available files
//You should fine the files in the resource storage
//ihte image will be shown,the sound file will have a play button
//you can save as the attachment file and so on
//note:resouce storage
//1.direct directory or res sub-directory
//2.the res.rifo, res.ridx and res.rdic database
//Direct files may have file name encoding problem,as linux use utf-8
//and windows use local encoding,so you'b better just use ASCII file name
//or use database to store utf8 file name
int StardictDict::parse_r_data(TextMetaData *tmp,unsigned char *data){
    if(strncmp((const char *)data,"img",3) == 0){
        data += 4;
        tmp->mImagePath.append((char *)data); 
        tmp->mImagePath.append("\n"); 
    }else if(strncmp((const char *)data,"snd",3) == 0){
        data += 4;
        tmp->mSoundPath.append((char *)data); 
        tmp->mSoundPath.append("\n"); 
    }else if(strncmp((const char *)data,"vdo",3) == 0){
        data += 4;
        tmp->mVideoPath.append((char *)data); 
        tmp->mVideoPath.append("\n"); 
    }else if(strncmp((const char *)data,"att",3) == 0){
        data += 4;
        tmp->mOther.append((char *)data);
        tmp->mOther.append("\n");
    }
    int length = strlen((const char *)data) + 5; 
    return length;
}

//wave file 
//the data begins with a network byte-ordered int32 to identify the wav
//file's size,immediately followed by the file's content
int StardictDict::parse_W_data(TextMetaData *tmp,unsigned char *data){
    int len = ntohl(*((unsigned int*)data));
    tmp->mWavDataLength = len;
    tmp->mWav = new unsigned char[len];
    memcpy(tmp->mWav,data+4,len);
    return len + 4; 
}

//Picture file
//the data begins with a network byte-ordered int32 to identify the picture
//file's size,immediately followed by the file's content
int StardictDict::parse_P_data(TextMetaData *tmp,unsigned char *data){
    int len = ntohl(*((unsigned int*)data));
    tmp->mPic = new unsigned char[len];
    tmp->mPicDataLength = len;
    memcpy(tmp->mPic,data+4,len);
    return len + 4;
}

//this type identifier is reserved  for experimental extensions
int StardictDict::parse_X_data(TextMetaData *tmp ,unsigned char *data){
    //error
    golden_printfe("%s get a X type \n",__func__);
    return 0;
}

