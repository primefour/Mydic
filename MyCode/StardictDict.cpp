#include"StardictDict.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>

typedef struct meta_data_head{
    unsigned char *data;
    off_t original_offset;
    int data_size;
    list_head_t head;
}meta_data_head_t;

typedef struct meta_data_t{
    list_head_t list;
    char type;
    unsigned char *data;
}meta_data_t;


StardictDict::StardictDict(const char*file_name,const char *same_type_seq):dict_file(file_name){
    if(same_type_seq != NULL){
        same_seqence = strdup(same_type_seq);
    }else{
        same_seqence = NULL;
    }
    if(file_name != NULL){
        file_path = strdup(file_name);
    }else{
       file_path = NULL;
    }
    dict_file = NULL;
}


StardictDict::~StardictDict(){
    if(same_seqence != NULL){
        free(same_seqence);
    }
}
int StardictDict::init(){
    int type = (int)File::check_file_type(file_path);
    printf("type = %d \n",type);
    dict_file = File::MakeFileInstance((const void *)file_name,(DIC_FILE_TYPE)type);
    return dict_file->open(0);
}

void StardictDict::parse_meta_data(meta_data_t *meta){

}


int  StardictDict::read_word_data(meta_data_head_t *word_data){

}


//word's pure text meaing
//utf-8 string terminate with '\0'
int StardictDict::parse_m_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_STRING_TYPE;
    meta->data = data;
    return strlen(meta->data) +1;

}
//word's pure text meaning
//data is not a utf-8 string,but is instead a string in locale encoding,ending with '\0'
//sometimes using this type will save diskspace,but its use is discouraged
int StardictDict::parse_l_data(meta_data_t *meta,unsigned char *data){
    //fix me
    meta->type = DICT_STRING_TYPE;
    meta->data = data;
    return strlen(meta->data) +1;
}


//utf-8 string which is marked up with the Pango text markup language.
//for more information about this markup language,See the pango reference manual
//you might have it installed locally at 
//file:///usr/share/gtk-doc/html/pango/PangoMarkupFormat.html
int StardictDict::parse_g_data(meta_data_t *meta,unsigned char *data){
    //fix me
    meta->type = DICT_STRING_TYPE;
    meta->data = data;
    return strlen(meta->data) +1;
}

//Englist phonetic string
//the data should be a utf-8 string ending with '\0'
int StardictDict::parse_t_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_PHONETIC_TYPE;
    meta->data = data;
    return strlen(meta->data) +1;
}


// a utf-8 string which is marked up with the xdxf language
// see http://xdxf.sourceforge.net
// <rref> can have "type" attribute,it can be "image","sound","video" and "attach"
// <kref> can have "k" attribute
int StardictDict::parse_x_data(meta_data_t *meta,unsigned  char *data){
    meta->type = DICT_STRING_TYPE ;
    meta->data = data;
    return strlen(meta->data) +1;
}

//chinese YinBiao or japanese KANA
//the data should be a utf-8 string ending with '\0'
int StardictDict::parse_y_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_PINYIN_TYPE;
    meta->data = data;
    return strlen(meta->data) +1;
}
//Kingsoft PowerWord's data,the data is a utf-8 string ending with '\0'
//it is in xml format
int StardictDict::parse_k_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_STRING_TYPE ;
    meta->data = data;
    return strlen(meta->data) +1;
}
//MediaWiki markup lanaguage
//http://meta.wikimedia.org/wiki/Help:Editing#The_wiki_markup
int StardictDict::parse_w_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_WIKI_TYPE;
    meta->data = data;
    return strlen(meta->data) +1;
}
//html codecs
int StardictDict::parse_h_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_HTML_TYPE;
    meta->data = data;
    return strlen(meta->data) + 1;
}
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
int StardictDict::parse_r_data(meta_data_t *meta,unsigned char *data){
    if(strncmp(data,"img",3) == 0){
        meta->type = DICT_PIC_PATH_TYPE;
    }else if(strncmp(data,"snd",3) == 0){
        meta->type = DICT_SOUND_PATH_TYPE;
    }else if(strncmp(data,"vdo",3) == 0){
        meta->type = DICT_VIDEO_PATH_TYPE;
    }else if(strncmp(data,"att",3) == 0){
        meta->type = DICT_ATTACH_PATH_TYPE;
    }
    meta->data = data+4;
    return strlen(meta->data) + 1; 
}

//wave file 
//the data begins with a network byte-ordered int32 to identify the wav
//file's size,immediately followed by the file's content
int StardictDict::parse_W_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_SOUND_TYPE;
    int length = ntohl((unsigned int )data);
    meta->data = data +4;
    return length + 4;
}
//Picture file
//the data begins with a network byte-ordered int32 to identify the picture
//file's size,immediately followed by the file's content
int StardictDict::parse_P_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_PIC_TYPE;
    int length = ntohl((unsigned int )data);
    meta->data = data +4;
    return length + 4;
}
//this type identifier is reserved  for experimental extensions
int StardictDict::parse_X_data(meta_data_t *meta,unsigned char *data){
    //error
    printf("%s get a X type \n",__func__);
    return 0;
}

