#ifndef __STARDICT_DICT__
#define __STARDICT_DICT__
#include"list.h"
#include"File.h"
#include"sys/types.h"


typedef enum DICT_META_TYPE_T{
    DICT_ATTACH_PATH_TYPE, 
    DICT_SOUND_PATH_TYPE, 
    DICT_PIC_PATH_TYPE, 
    DICT_VIDEO_PATH_TYPE,
    DICT_HTML_TYPE,
    DICT_WIKI_TYPE,
    DICT_ATTACH_TYPE,
    DICT_PIC_TYPE,
    DICT_SOUND_TYPE,
    DICT_PHONETIC_TYPE,
    DICT_STRING_TYPE,
    DICT_PINYIN_TYPE,
}DICT_META_TYPE_T;

typedef struct meta_data_head{
    unsigned char *data;
    off_t original_offset;
    int data_size;
    list_head_t head;
}meta_data_head_t;

typedef struct meta_data_t{
    list_head_t list;
    int type;
    unsigned char *data;
}meta_data_t;


class StardictDict{
    public:
        StardictDict(const char*file_name,const char *same_type_seq);
        ~StardictDict();
        int init(); 
        void parse_meta_data(meta_data_head_t *word_data);
        int  read_word_data(meta_data_head_t *word_data);
    private:
        meta_data_t *get_new_meta_item();
        //word's pure text meaing
        //utf-8 string terminate with '\0'
        int parse_m_data(meta_data_t *meta,unsigned char *data);
        //word's pure text meaning
        //data is not a utf-8 string,but is instead a string in locale encoding,ending with '\0'
        //sometimes using this type will save diskspace,but its use is discouraged
        int parse_l_data(meta_data_t *meta,unsigned char *data);
        //utf-8 string which is marked up with the Pango text markup language.
        //for more information about this markup language,See the pango reference manual
        //you might have it installed locally at 
        //file:///usr/share/gtk-doc/html/pango/PangoMarkupFormat.html
        int parse_g_data(meta_data_t *meta,unsigned char *data);
        //Englist phonetic string
        //the data should be a utf-8 string ending with '\0'
        int parse_t_data(meta_data_t *meta,unsigned char *data);
        // a utf-8 string which is marked up with the xdxf language
        // see http://xdxf.sourceforge.net
        // <rref> can have "type" attribute,it can be "image","sound","video" and "attach"
        // <kref> can have "k" attribute
        int parse_x_data(meta_data_t *meta,unsigned char *data);
        //chinese YinBiao or japanese KANA
        //the data should be a utf-8 string ending with '\0'
        int parse_y_data(meta_data_t *meta,unsigned char *data);
        //Kingsoft PowerWord's data,the data is a utf-8 string ending with '\0'
        //it is in xml format
        int parse_k_data(meta_data_t *meta,unsigned char *data);
        //MediaWiki markup lanaguage
        //http://meta.wikimedia.org/wiki/Help:Editing#The_wiki_markup
        int parse_w_data(meta_data_t *meta,unsigned char *data);
        //html codecs
        int parse_h_data(meta_data_t *meta,unsigned char *data);
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
        int parse_r_data(meta_data_t *meta,unsigned char *data);
        //wave file 
        //the data begins with a network byte-ordered int32 to identify the wav
        //file's size,immediately followed by the file's content
        int parse_W_data(meta_data_t *meta,unsigned char *data);
        //Picture file
        //the data begins with a network byte-ordered int32 to identify the picture
        //file's size,immediately followed by the file's content
        int parse_P_data(meta_data_t *meta,unsigned char *data);
        //this type identifier is reserved  for experimental extensions
        int parse_X_data(meta_data_t *meta,unsigned char *data);
        //file
        File *dict_file;
        char *same_seqence;
        char *file_path;
};

#endif 
