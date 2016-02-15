#include "AngelDict.h"
#include "AngelLog.h"
#include "String8.h"
#include <vector>
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

}



