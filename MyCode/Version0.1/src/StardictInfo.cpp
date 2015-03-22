#include"StardictInfo.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"memory_test_tool.h"

const char *ind_ver="version";
const char *ind_name="bookname";
const char *ind_count="wordcount";
const char *ind_syn="synwordcount";
const char *ind_size="idxfilesize";
const char *ind_offset="idxoffsetbits";
const char *ind_author="author";
const char *ind_email="email";
const char *ind_website="website";
const char *ind_descrip="description";
const char *ind_date="date";
const char *ind_sts="sametypesequence";


char *StardictInfo::get_string_value(char *str_line){
    //printf("%s   %d \n",__func__,__LINE__);
    char *value = NULL;
    value = strchr(str_line,'=');
    value ++;
    return strdup(value);
}

int StardictInfo::get_integer_value(char *str_line){
    //printf("%s   %d \n",__func__,__LINE__);
    char *value = NULL;
    value = strchr(str_line,'=');
    value ++;
    return atoi(value);
}

void StardictInfo::dump(){
    //printf("%s   %d \n",__func__,__LINE__);
    if(version != NULL){
        printf("version = %s \n",version);
    }
    if(book_name != NULL){
        printf("book_name = %s \n",book_name);
    }
    if(author != NULL){
        printf("author = %s \n",author);
    }
    if(email != NULL){
        printf("email = %s \n",email);
    }
    if(description != NULL){
        printf("description = %s \n",description);
    }
    if(date != NULL){
        printf("date = %s \n",date);
    }
    printf("word_count = %ld syn_word_count = %ld idx_file_size = %ld offset bits = %d ,sts = %s \n",word_count,
        syn_word_count,idx_file_size,offset_is_64bit,same_types_sequence); 
}

void StardictInfo::parse_line(char *str_line){
    //printf("%s   %d \n",__func__,__LINE__);
    if(*str_line == 'a'){
        //author
        //printf("%s   %d \n",__func__,__LINE__);
        author = get_string_value(str_line);
    }else if(*str_line == 'b'){
        //printf("%s   %d \n",__func__,__LINE__);
        book_name = get_string_value(str_line);
    }else if(*str_line == 'd'){
        //printf("%s   %d \n",__func__,__LINE__);
        if(strstr(str_line,ind_date)){
            //date
            date = get_string_value(str_line);
        }else{
            //description
            description = get_string_value(str_line);
        }
    }else if(*str_line == 'i'){
        //printf("%s   %d \n",__func__,__LINE__);
        if(strstr(str_line,ind_size)){
            //idx file size
            idx_file_size = get_integer_value(str_line);
        }else if(strstr(str_line,ind_offset)){
            offset_is_64bit = get_integer_value(str_line);
        }
    }else if(*str_line == 's'){
        //printf("%s   %d \n",__func__,__LINE__);
        //synwordcount
        if(strstr(str_line,ind_syn)){
            syn_word_count = get_integer_value(str_line);
        }else if (strstr(str_line,ind_sts)){
            same_types_sequence =  get_string_value(str_line);
        }
    }else if(*str_line == 'v'){
        //printf("%s   %d \n",__func__,__LINE__);
        version = get_string_value(str_line);
    }else if(*str_line == 'w'){
        //printf("%s   %d \n",__func__,__LINE__);
        if(strstr(str_line,ind_count)){
            word_count = get_integer_value(str_line);
        }else{
            website = get_string_value(str_line);
        }
    }
}

int StardictInfo::init(){
    //printf("%s   %d \n",__func__,__LINE__);
    int ret = info_file.open(0);
    char buff[10240]={0};
    while(1){
        memset(buff,0,sizeof(buff));
        ret = info_file.readline((unsigned char *)buff,sizeof(buff));
        buff[10239]='\0';
        printf("%s ret = %d :str = %s \n",__func__,ret,buff);
        if(ret <= 0){
            break;
        }
        parse_line(buff);
    }
    return ret ;
}

