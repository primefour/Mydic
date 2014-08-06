#include "StardictIdx.h"
#include "StardictInfo.h"
#include "StardictDict.h"
#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include"Stardict.h"
#include"memory_test_tool.h"



int main(){
    init_global_env();
    File::Init_check_list();
    File::add_check_func(GzipFile::check_file_type,GZIP_FILE_TYPE);
    StardictDictionary *sd = new StardictDictionary("./langdao-ec-gb.dict.dz");
    int ret = sd->init();
    printf("main ret = %d \n",ret);
    if(ret < 0){
        return -1 ;
    }
    char buff[1024]={0};
    while(1){
        MetaDataHeader *tmp_head = new MetaDataHeader();
        memset(buff,0,sizeof(buff));
        printf("Please input words:");
        scanf("%s",buff);
        printf("%s",buff);
        if(strcmp(buff,"quitOK") == 0){
            break;
        }
        ret = sd->query_word(buff,tmp_head);
        printf("ret = %d kkkkk\n",ret);
        //tmp_head->dump_meta_data_head();
        //delete tmp_head;
        printf("#####################ret = %d kkkkk\n",ret);
    }
    File::release_check_list();
    delete sd;
    release_global_env();
    return 0;
}
