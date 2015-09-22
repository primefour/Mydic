#ifndef __GOLDEN_HTML_HEADER__
#define __GOLDEN_HTML_HEADER__
#include<map>
#include"String8.h"
using namespace std;

class GoldenHtmlHeader {
    public:
        GoldenHtmlHeader();
        void HTMLAddExpBegin();
        void HTMLAddExpEnd();
        void HTMLAddDictionaryName(const String8 &DictName);
        void HTMLAddWord(String8 &word);
        void HtmlAddPhonetic(String8 &Phonetic,String8 &FileName);
        void HtmlAddOnlyMeaning(String8 &Meaning);
        void HtmlAddMeaningBegin();
        void HtmlAddImg(String8 &Name,String8 &Meaning);
        void HtmlAddMeaningEnd();
        void AddHtmlPiece(const char *htmlCode);
        String8& EncodeString(String8 &str);
        const char *getResult(){
            return mHtml.string();
        }
    private:
        map<char,String8> mHtmlSpecialChar ;
        String8 mHtml;
        int mPicPos ;
};


#endif //__GOLDEN_HTML_HEADER__
