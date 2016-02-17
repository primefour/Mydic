#include "AngelDict.h"
#include "AngelLog.h"
#include "String8.h"
#include <vector>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

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
    if(pbit != peit ){
        wt.String(DictJsonObject[1])
        wt.StartArray();
        for(;pbit < peit ;pbit ++){
            wt.StartObject();
            if(!pbit->value.isEmpty()){
                wt.String(DictPhoneticField[0]);
                wt.String(pbit->value.string());
            }

            if(!pbit->url.isEmpty()){
                wt.String(DictPhoneticField[1]);
                wt.String(pbit->url.string());
            }
            wt.String(DictPhoneticField[2]);
            wt.Int(type);
            wt.EndObject();
        }
        wt.EndArray();
    }



    wt.EndObject();

}



