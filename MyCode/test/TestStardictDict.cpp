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
    File::add_check_func(GzipFile::check_file_type,GZIP_FILE_TYPE);
    StardictDictionary *sd = new StardictDictionary("./langdao-ec-gb.dict.dz");
    int ret = sd->init();
    printf("main ret = %d \n",ret);
    if(ret < 0){
        return -1 ;
    }
    char buff[1024]={0};
    meta_data_head tmp_head = {0}; 
    while(1){
        memset(buff,0,sizeof(buff));
        printf("Please input words:");
        scanf("%s",buff);
        printf("%s",buff);
        init_meta_item_head(&tmp_head);
        ret = sd->query_word(buff,&tmp_head);
        printf("ret = %d kkkkk\n",ret);
        dump_meta_head(&tmp_head);
        release_meta_head(&tmp_head);
    }
    delete sd;
    release_global_env();
    return 0;
}
