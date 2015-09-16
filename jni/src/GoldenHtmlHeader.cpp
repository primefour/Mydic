#include"GoldenHtmlHeader.h"
#include<map>
#include"String8.h"
#include"GoldenDictManager.h"
#include"GoldenDictLog.h"

using namespace std;


const char *HtmlHeader= "<html>\n <head> \n <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=0, minimum-scale=1.0,maximum-scale=1.0\"> \n \
    <title>Mi Guo Dictionary</title> \n </head> \n <style type=\"text/css\"> \n body { \n background-position: center top; \n color: #665544; \n background-color: #d4d0c6; \n \
    } \n p { \n background-image: url(\"img2.jpg\");} \n .title { \n font-family:Helvetica, Arial, sans-serif; \n background-image: url(\"img3.jpg\"); \n font-size:100%; \n color: #055550; \n \
    margin: 10px 0px 5px 0px; \n padding: 0px; \n } \n .title1 { \n font-family:Helvetica, Arial, sans-serif; \n font-size:130%; \n color: #077770; \n margin: 10px 0px 5px 0px; \n padding: 0px;\n\
    }\n .meaning{ \n font-family:Helvetica, Arial, sans-serif; \n font-size:100%; \n color: #332211; \n margin: 10px 0px 5px 0px; \n padding: 0px; \n } \n img.large { \n width: 500px; \n \
	 height: 500px;}\n img.medium { \n width: 250px;\n height: 250px;}\n img.small {\n width: 100px;\n height: 100px;}\n img.align-left { \n float: left; \n margin-right: 10px;} \n \
     img.align-center { \n display: block;\n margin: 0px auto;} \n img.align-right	{ \n float: right;\n margin-left: 10px;}\n </style> \n <body> \n" ;


void GoldenHtmlHeader::HTMLAddExpBegin(){
    //mHtml += GoldenHtmlHeader;
}

void GoldenHtmlHeader::HTMLAddExpEnd(){
    mHtml += "</body>\n </html>\n";
}

void GoldenHtmlHeader::HTMLAddDictionaryName(String8 &DictName){
    mHtml += "<h5 class=title>";
    mHtml += DictName ;
    mHtml += "</h5>\n<hr/>\n";
}


void GoldenHtmlHeader::HTMLAddWord(String8 &word){
    mHtml +="<p class=\"title1\">";
    mHtml += word ;
    mHtml += "</p>\n<hr/>\n"; 
}

void GoldenHtmlHeader::HtmlAddPhonetic(String8 &Phonetic,String8 &FileName){
    if(!FileName.isEmpty()){
        mHtml += "<a href=\"";
        mHtml += GoldenDictInterface::getPhoneticPath();
        mHtml += FileName;
        mHtml += "\">";
        mHtml += Phonetic;
        mHtml += "</a>\n" ;
    }
}

String8& GoldenHtmlHeader::EncodeString(String8 &str){
    const char *data = str.string();
    const int BUFF_SIZE = 40960;
    char *buff  = new char[BUFF_SIZE];
    memset(buff,0,BUFF_SIZE);
    golden_printfe("%s  %d ",__FILE__,__LINE__);
    while(*data != '\0'){
        if(mHtmlSpecialChar[*data]){
            strcat(buff,mHtmlSpecialChar[*data]);
            buff += strlen(mHtmlSpecialChar[*data]);
        }else{
            *(buff++) = *(data++);
        }
    }
    golden_printfe("%s  %d ",__FILE__,__LINE__);
    str.setTo(buff);
    return str;
}




void GoldenHtmlHeader::HtmlAddOnlyMeaning(String8 &Meaning){
    mHtml += "<hr/>\n<p class=\"meaning\">";
    mHtml +=Meaning ;
    mHtml +="<p>\n";
}

void GoldenHtmlHeader::HtmlAddMeaningBegin(){
    mHtml +="<div class = meaning> \n" ;
}

void GoldenHtmlHeader::HtmlAddMeaningEnd(){
    mHtml += "</div> \n";
}

void GoldenHtmlHeader::HtmlAddImg(String8 &Name,String8 &Meaning){
    mHtml += "<p><img src=\"";
    mHtml += GoldenDictInterface::getImgPath();
    mHtml += Name;
    mHtml += "\" class=\"";
    if(mPicPos == 0){
        mHtml  += "align-left small\" />";
    }else if(mPicPos == 1){
        mHtml  += "align-right small\" />";
    }else {
        mHtml  += "align-center small\" />";
    }
    mHtml += Meaning;
    mHtml += "</p>\n";
}

GoldenHtmlHeader::GoldenHtmlHeader():mHtml(HtmlHeader){
    mPicPos = 0;
    mHtmlSpecialChar[' '] = "nbsp";
    mHtmlSpecialChar['<'] = "lt";
    mHtmlSpecialChar['>'] = "gt";
    mHtmlSpecialChar['&'] = "amp";
    mHtmlSpecialChar['\"'] = "quot";
    mHtmlSpecialChar[(char)149] = "bull";
    mHtmlSpecialChar[(char)129] = "trade";
}
