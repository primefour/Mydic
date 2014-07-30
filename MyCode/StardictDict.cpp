#include"StardictDict.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<fcntl.h>
#include"Stardict.h"


StardictDict::StardictDict(const char*file_name,const char *same_type_seq){
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

    if(dict_file != NULL){
        delete dict_file;
    }
}

int StardictDict::init(){
    int type = (int)File::check_file_type(file_path);
    printf("type = %d \n",type);
    dict_file = File::MakeFileInstance((const void *)file_path,(DIC_FILE_TYPE)type);
    return dict_file->open(0);
}

void StardictDict::parse_meta_data(meta_data_head_t *word_data){
    if(same_seqence != NULL){
        parse_meta_data_with_seq(word_data);
    }else{
        parse_meta_data_no_seq(word_data);
    }
}

void StardictDict::parse_meta_data_with_seq(meta_data_head_t *word_data){
    char *seq = same_seqence;
    unsigned char *pData = word_data->data;
    unsigned char *pData_end = word_data->data + word_data->data_size;
    init_list_head(&(word_data->head));
    meta_data_t * tmp = get_new_meta_item();
    while(*seq != '\0' && pData < pData_end ){
        pData += parse_common_flag(tmp,*seq,pData);
        if(tmp->data){
            insert_list_item_ahead(&(word_data->head),&(tmp->list));
            tmp = get_new_meta_item();
        }
        seq ++;
    }

    if(tmp->data == NULL){
        free(tmp);
    }
}


int StardictDict::parse_common_flag(meta_data_t *tmp,char flag,unsigned char *data){
    printf("%s flag = %c \n",__func__,flag);
    int length = 0;
    switch(flag){
        case 'm':
            length = parse_m_data(tmp,data);
            break;
        case 'l':
            length = parse_l_data(tmp,data);
            break;
        case 'g':
            length = parse_g_data(tmp,data);
            break;
        case 't':
            length = parse_t_data(tmp,data);
            break;
        case 'x':
            length = parse_x_data(tmp,data);
            break;
        case 'y':
            length = parse_y_data(tmp,data);
            break;
        case 'k':
            length = parse_k_data(tmp,data);
            break;
        case 'w':
            length = parse_w_data(tmp,data);
            break;
        case 'h':
            length = parse_h_data(tmp,data);
            break;
        case 'r':
            length = parse_r_data(tmp,data);
            break;
        case 'W':
            length = parse_W_data(tmp,data);
            break;
        case 'P':
            length = parse_P_data(tmp,data);
            break;
        case 'X':
            length = parse_X_data(tmp,data);
            break;
        default:
            printf("get a error format \n");
            break;
    }
}

void StardictDict::parse_meta_data_no_seq(meta_data_head_t *word_data){
    unsigned char *pData = word_data->data;
    unsigned char *pData_end = word_data->data + word_data->data_size;
    init_list_head(&(word_data->head));
    meta_data_t * tmp = get_new_meta_item();
    while(pData < pData_end){
        pData += parse_common_flag(tmp,*pData,++pData);
        if(tmp->data){
            insert_list_item_ahead(&(word_data->head),&(tmp->list));
            tmp = get_new_meta_item();
        }
    }
    if(tmp->data == NULL){
        free(tmp);
    }
}

int StardictDict::read_word_data(meta_data_head_t *word_data){
    dict_file->lseek(SEEK_CUR,word_data->original_offset);
    word_data->data = (unsigned char *)malloc(word_data->data_size);
    if(word_data->data == NULL){
        printf("word_data->data_size = %d  \n",word_data->data_size);
        assert(0);
    }
    int ret =  dict_file->read(word_data->data,word_data->data_size);
    if(ret != word_data->data_size){
        printf("%s ret = %d \n",__func__,ret); 
        assert(0);
    }else{
        parse_meta_data(word_data);
    }
    return ret;
}


//word's pure text meaing
//utf-8 string terminate with '\0'
int StardictDict::parse_m_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_STRING_TYPE;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;

}
//word's pure text meaning
//data is not a utf-8 string,but is instead a string in locale encoding,ending with '\0'
//sometimes using this type will save diskspace,but its use is discouraged
int StardictDict::parse_l_data(meta_data_t *meta,unsigned char *data){
    //fix me
    meta->type = DICT_STRING_TYPE;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}


//utf-8 string which is marked up with the Pango text markup language.
//for more information about this markup language,See the pango reference manual
//you might have it installed locally at 
//file:///usr/share/gtk-doc/html/pango/PangoMarkupFormat.html
int StardictDict::parse_g_data(meta_data_t *meta,unsigned char *data){
    //fix me
    meta->type = DICT_STRING_TYPE;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}

//Englist phonetic string
//the data should be a utf-8 string ending with '\0'
int StardictDict::parse_t_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_PHONETIC_TYPE;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}


// a utf-8 string which is marked up with the xdxf language
// see http://xdxf.sourceforge.net
// <rref> can have "type" attribute,it can be "image","sound","video" and "attach"
// <kref> can have "k" attribute
int StardictDict::parse_x_data(meta_data_t *meta,unsigned  char *data){
    meta->type = DICT_STRING_TYPE ;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}

//chinese YinBiao or japanese KANA
//the data should be a utf-8 string ending with '\0'
int StardictDict::parse_y_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_PINYIN_TYPE;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}
//Kingsoft PowerWord's data,the data is a utf-8 string ending with '\0'
//it is in xml format
int StardictDict::parse_k_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_STRING_TYPE ;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}
//MediaWiki markup lanaguage
//http://meta.wikimedia.org/wiki/Help:Editing#The_wiki_markup
int StardictDict::parse_w_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_WIKI_TYPE;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}
//html codecs
int StardictDict::parse_h_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_HTML_TYPE;
    meta->data = data;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
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
    if(strncmp((const char *)data,"img",3) == 0){
        meta->type = DICT_PIC_PATH_TYPE;
    }else if(strncmp((const char *)data,"snd",3) == 0){
        meta->type = DICT_SOUND_PATH_TYPE;
    }else if(strncmp((const char *)data,"vdo",3) == 0){
        meta->type = DICT_VIDEO_PATH_TYPE;
    }else if(strncmp((const char *)data,"att",3) == 0){
        meta->type = DICT_ATTACH_PATH_TYPE;
    }
    meta->data = data+4;
    meta->data_length = strlen((const char *)(meta->data)) +1;
    return meta->data_length;
}

//wave file 
//the data begins with a network byte-ordered int32 to identify the wav
//file's size,immediately followed by the file's content
int StardictDict::parse_W_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_SOUND_TYPE;
    int length = ntohl(*((unsigned int*)data));
    meta->data = data +4;
    meta->data_length =  length + 4;
    return meta->data_length; 
}
//Picture file
//the data begins with a network byte-ordered int32 to identify the picture
//file's size,immediately followed by the file's content
int StardictDict::parse_P_data(meta_data_t *meta,unsigned char *data){
    meta->type = DICT_PIC_TYPE;
    int length = ntohl(*((unsigned int *)data));
    meta->data = data +4;
    meta->data_length =  length + 4;;;;
    return meta->data_length; 
}
//this type identifier is reserved  for experimental extensions
int StardictDict::parse_X_data(meta_data_t *meta,unsigned char *data){
    //error
    printf("%s get a X type \n",__func__);
    return 0;
}

