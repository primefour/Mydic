#ifndef __GOLDEN_HTML_HEADER__
#define __GOLDEN_HTML_HEADER__
#include"String8.h"

class GoldenHtmlHeader {
    public:
        GoldenHtmlHeader();
        void HTMLAddExpBegin();
        void HTMLAddExpEnd();
        void HTMLAddDictionaryName(String8 &DictName);
        void HTMLAddWord(String8 &word);
        void HtmlAddPhonetic(String8 &Phonetic,String8 &FileName);
        void HtmlAddOnlyMeaning(String8 &Meaning);
        void HtmlAddMeaningBegin();
        void HtmlAddImg(String8 &Name,String8 &Meaning);
        void HtmlAddMeaningEnd();
    private:
        String8 mHtml;
        int mPicPos ;
};


#endif //__GOLDEN_HTML_HEADER__
