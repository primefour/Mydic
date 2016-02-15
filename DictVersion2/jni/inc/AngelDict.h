#ifndef __ANGEL_DICT_H__
#define __ANGEL_DICT_H__

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

class AngelDictWord{
    public:
        void AddPict(const char *url,int w,int h,const char *comment);
        void AddMeaning(const char *text,const char *ex);
        void AddPhonetic(const char *value,const char *url,int type);
    private:
        String8 mContent;
};


#endif //__ANGEL_DICT_H__
