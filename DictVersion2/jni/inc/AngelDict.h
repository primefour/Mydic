#ifndef __ANGEL_DICT_H__
#define __ANGEL_DICT_H__
#include<vector>
#include"String8.h"
using namespace std;
/*
 * {
 *  word:Hello,
 *  phonetic:[
 *   { 
 *   value:"[hello]",url:"file:///sdcard//voice/hello.wav",type:1}
 *  ]
 *  meaning:[
 *  {
 *  text:"ni hao",ex:"Hello,My dear!",pic:[{
 *  url:"file:///scard/pic/hello.jpg",res:176x432,comment:"meeting"
 *  }
 *  ]
 *  ]
 */


/*
 *  {
 *      word:"hello",
 *      phonetic:[{
 *      value:"[helou]",url:"file:///sdcard/voice/hello.mp3",type:1,
 *      }]
 *      meaning:[{text:"ni hao",ex:"Hello,My dear",pic:[
 *      url:"file:///scard/pic/hello.jpg",res:176x324,comment:meeting
 *      ]
 *      }
 *      ]
 *  }
 *
 */

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


struct PicInst{
    String8 url;
    String8 res;
    String8 comment;
};

struct MeaningInst{
    String8 text;
    vector<String8> ex;
    vector<PicInst> pic;
};

struct PhonetInst{
    String8 value;
    String8 url;
    int type;
};



class AngelDictWord{
    public:
        AngelDictWord(const char *word);
        void AddPict(const char *url,int w,int h,const char *comment);
        void AddMeaning(const char *text,const char *ex);
        void AddPhonetic(const char *value,const char *url,int type);
        int GetJsonString(char *buff,int len);
    private:
        String8 mWord;
        vector<PhonetInst> mPhonetic;
        vector<MeaningInst> mMeaning;
};

#endif //__ANGEL_DICT_H__
