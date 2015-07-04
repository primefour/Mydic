#include"StardictInfo.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"StandardIO.h"
#include<unistd.h>
#include<fcntl.h>
#include"String8.h"
#include"GoldenDictLog.h"

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
    SimpleFile file_obj(file_path,O_RDONLY);
    char buff[10240]={0};
    while(1){
        memset(buff,0,sizeof(buff));
        int n = file_obj.ReadLine((unsigned char *)buff,sizeof(buff));
        if(n <= 0){
            break;
        }
        buff[10239]='\0';
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
}

void StardictInfo::dumpInfo(){
    int i = 0;
    while(i < INFO_MAX){
        golden_printfd("mInfoString = %s ",mInfoString[i].string());
        i++;
    }
    golden_printfd("\n");
}
