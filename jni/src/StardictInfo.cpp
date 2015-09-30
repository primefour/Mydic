#include"StardictInfo.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include"String8.h"
#include"GoldenDictLog.h"
#include"GoldenStandardIO.h"
#include"GoldenRef.h"
#include<stdexcept>
using namespace std;

const char *StardictInfo::infoFileList[]= {"version",
            "bookname",
            "wordcount",
            "synwordcount",
            "idxfilesize",
            "idxoffsetbits", 
            "author",
            "email",
            "website",
            "description",
            "date",
            "sametypesequence",
            NULL};

StardictInfo::StardictInfo(const char *file_path):file_name(file_path){
    SObject<SimpleFile> file_obj = NULL;
    try{
        file_obj = new SimpleFile(file_path,O_RDONLY);
    }catch (exception &e){
        golden_printfd("info file fail %s\n",e.what());
        throw exception();
    };
    golden_printfi("###################################\n");
    const int buff_len = 10240 ;
    char *buff= new char[buff_len];
    while(1){
        memset(buff,0,buff_len);
        int n = file_obj->ReadLine((unsigned char *)buff,buff_len);
        golden_printfi("n = %d buff = %s \n",n,buff);
        if(n <= 0){
            break;
        }
        buff[buff_len]='\0';
        int len = strlen(buff);
        if(len != 0 && buff[len-1] == '\n'){
            buff[len-1] = '0';
        }
        int i = 0;
        char *ret = NULL;
        while(infoFileList[i] != NULL){
            ret = strstr(buff,infoFileList[i]);
            if(ret == buff){

                mInfoString[i] = buff;
                break;
            }
            i++;
        }
    }
    delete[] buff;
}

void StardictInfo::dumpInfo(){
    int i = 0;
    while(i < INFO_MAX){
        golden_printfd("mInfoString = %s ",mInfoString[i].string());
        i++;
    }
    golden_printfd("\n");
}
