#ifndef __STARDICT_DICT__
#define __STARDICT_DICT__
#include<sys/types.h>
#include<string.h>
#include"GoldenDictLog.h"
#include"GoldenRef.h"
#include"String8.h"

class StardictDict;

class TextMetaData :public Ref{
    friend StardictDict;
    public:
        TextMetaData(); 
        TextMetaData(const TextMetaData & inst); 
        TextMetaData(const char *word):mWord(word){
            mWavDataLength = 0;
            mPicDataLength = 0;
            mWav = NULL;
            mPic = NULL;
        }
        void generateHTML(String8 &result);
        void setWord(const char *word){
            mWord.setTo(word);
        }
        void dumpInfo();
        ~TextMetaData();
    private:
        //text meaning
        String8 mWord;
        String8 mTextMeaning;//m l g
        String8 mTextPhonetic;
        String8 mImagePath;
        String8 mVideoPath;
        String8 mSoundPath;
        String8 mOther;
        int mWavDataLength;
        int mPicDataLength;
        unsigned char *mWav;
        unsigned char *mPic;
};


class StardictDict:public Ref{
    public:
        StardictDict(const char*file_name,const char *same_type_seq);
        ~StardictDict();
        void read_word_data(int offset,int length,TextMetaData* tmd);
    private:
        void parse_meta_data(TextMetaData *tmd, unsigned char *data,int length);
        int parse_common_flag(TextMetaData *tmp,char flag,unsigned char *data);

        //word's pure text meaing
        //utf-8 string terminate with '\0'
        int parse_m_data(TextMetaData *tmp,unsigned char *data);

        //word's pure text meaning
        //data is not a utf-8 string,but is instead a string in locale encoding,ending with '\0'
        //sometimes using this type will save diskspace,but its use is discouraged
        int parse_l_data(TextMetaData *tmp,unsigned char *data);

        //utf-8 string which is marked up with the Pango text markup language.
        //for more information about this markup language,See the pango reference manual
        //you might have it installed locally at 
        //file:///usr/share/gtk-doc/html/pango/PangoMarkupFormat.html
        int parse_g_data(TextMetaData *tmp,unsigned char *data);
        
        //Englist phonetic string
        //the data should be a utf-8 string ending with '\0'
        int parse_t_data(TextMetaData *tmp,unsigned char *data);

        // a utf-8 string which is marked up with the xdxf language
        // see http://xdxf.sourceforge.net
        // <rref> can have "type" attribute,it can be "image","sound","video" and "attach"
        // <kref> can have "k" attribute
        int parse_x_data(TextMetaData *tmp,unsigned  char *data);

        //chinese YinBiao or japanese KANA
        //the data should be a utf-8 string ending with '\0'
        int parse_y_data(TextMetaData *tmp,unsigned char *data);


        //Kingsoft PowerWord's data,the data is a utf-8 string ending with '\0'
        //it is in xml format
        int parse_k_data(TextMetaData *tmp,unsigned char *data);

        //MediaWiki markup lanaguage
        //http://meta.wikimedia.org/wiki/Help:Editing#The_wiki_markup
        int parse_w_data(TextMetaData *tmp,unsigned char *data);

        //html codecs
        int parse_h_data(TextMetaData *tmp,unsigned char *data);

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
        int parse_r_data(TextMetaData *tmp,unsigned char *data);

        //wave file 
        //the data begins with a network byte-ordered int32 to identify the wav
        //file's size,immediately followed by the file's content
        int parse_W_data(TextMetaData *tmp,unsigned char *data);

        //Picture file
        //the data begins with a network byte-ordered int32 to identify the picture
        //file's size,immediately followed by the file's content
        int parse_P_data(TextMetaData *tmp,unsigned char *data);

        //this type identifier is reserved  for experimental extensions
        int parse_X_data(TextMetaData *tmp ,unsigned char *data);

        String8 mSeq;
        String8 file_path;
};

#endif 
