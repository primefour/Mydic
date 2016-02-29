#include "AngelDict.h"
#include "AngelLog.h"
#include "String8.h"
#include <vector>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

const char *DictJsonObject[] = {
    "word","phonetic","meaning"
};


const char *DictPhoneticField[]={
    "value","url","type"
};

const char *DictMeaningField[]={
    "text","ex","pic"
};

const char *DictPictFeild[]={
    "url","res","comment"
};



AngelDictWord::AngelDictWord(const char *word):mWord(word){

}


void AngelDictWord::AddPict(const char *url,int w,int h,const char *comment){
    MeaningInst &it = mMeaning.back();
    PicInst pt;
    pt.url = url;
    pt.res = String8::format("%dx%d",w,h);
    pt.comment = comment;
    it.pic.push_back(pt);
}


void AngelDictWord::AddMeaning(const char *text,const char *ex){
    MeaningInst mt;
    mt.text = text;
    mt.ex.push_back(String8(ex));
    mMeaning.push_back(mt);
}



void AngelDictWord::AddPhonetic(const char *value,const char *url,int type){
    PhonetInst pt;
    pt.value = value;
    pt.url = url;
    pt.type = type;
    mPhonetic.push_back(pt);
}


int AngelDictWord::GetJsonString(char *buff,int len){
    StringBuffer s;
    Writer<StringBuffer> wt(s);
    wt.StartObject();
    //add word field
    wt.String(DictJsonObject[0]);
    wt.String(mWord.string());
    //add phonetic array
    vector<PhonetInst>::iterator pbit = mPhonetic.begin();
    vector<PhonetInst>::iterator peit = mPhonetic.end();
    wt.String(DictJsonObject[1]);

    wt.StartArray();
    for(;pbit < peit ;pbit ++){
        wt.StartObject();
        if(!pbit->value.isEmpty()){
            wt.String(DictPhoneticField[0]);
            wt.String(pbit->value.string());
        }else{
            wt.String(DictPhoneticField[0]);
            wt.String("");
        }

        wt.String(DictPhoneticField[1]);
        if(!pbit->url.isEmpty()){
            wt.String(pbit->url.string());
        }else{
            wt.String("");
        }

        wt.String(DictPhoneticField[2]);
        wt.Int(pbit->type);
        wt.EndObject();
    }
    wt.EndArray();


    //add meaning doc
    vector<MeaningInst>::iterator pmbit = mMeaning.begin();
    vector<MeaningInst>::iterator pmeit = mMeaning.end();
    wt.String(DictJsonObject[2]);

    wt.StartArray();
    for(;pmbit < pmeit ;pmbit ++){
        wt.StartObject();
        //add meaing text
        wt.String(DictMeaningField[0]);
        if(!pmbit->text.isEmpty()){
            wt.String(pmbit->text.string());
        }else{
            wt.String("");
        }


        //add example array 
        wt.String(DictMeaningField[1]);

        vector<String8>::iterator exbit = pmbit->ex.begin();
        vector<String8>::iterator exeit = pmbit->ex.end();
        wt.StartArray();
        while(exbit != exeit){
            if(!exbit->isEmpty()){
                wt.String(exbit->string());
            }else{
                wt.String("");
            }
            exbit ++;
        }
        wt.EndArray();


        //add picture array
        wt.String(DictMeaningField[2]);

        vector<PicInst>::iterator pxbit = pmbit->pic.begin();
        vector<PicInst>::iterator pxeit = pmbit->pic.end();

        wt.StartArray();

        while(pxbit != pxeit){
            wt.StartObject();
            wt.String(DictPictFeild[0]);
            if(!pxbit->url.isEmpty()){
                wt.String(pxbit->url.string());
            }else{
                wt.String("");
            }

            wt.String(DictPictFeild[1]);
            if(!pxbit->res.isEmpty()){
                wt.String(pxbit->res.string());
            }else{
                wt.String("");
            }

            wt.String(DictPictFeild[2]);
            if(!pxbit->comment.isEmpty()){
                wt.String(pxbit->comment.string());
            }else{
                wt.String("");
            }
            wt.EndObject();
            pxbit ++;
        }
        wt.EndArray();


        wt.EndObject();
    }
    wt.EndArray();
    wt.EndObject();

    angel_printfe(" json string : %s ",s.GetString());
    const char *psrc = s.GetString();
    char *pdes = buff;
    int i = 0;
    for(;i < len && *psrc != '\0';i++,psrc ++,pdes ++){
        *pdes = *psrc;
    }
    return i ;
}



