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
#include"Dictionary.h"



int main(){
    init_global_env();
    File::Init_check_list();
    File::add_check_func(GzipFile::check_file_type,GZIP_FILE_TYPE);

    DictionarySet *ds = new DictionarySet();
    ds->scan_dir("./");
    const char *dicts_name[20] ={0};
    ds->get_dicts_name(dicts_name,1024);
    int i = 0;
    while(i < 20){
        if(dicts_name[i] != NULL){
            printf("dict %d  %s \n",i,dicts_name[i]);
        }
        i++;
    }
/*
    char buff[1024]={0};
    MetaDataHeader *tmp_head = new MetaDataHeader();
    while(1){
        memset(buff,0,sizeof(buff));
        printf("Please input words:");
        scanf("%s",buff);
        printf("%s",buff);
        if(strcmp(buff,"quitOK") == 0){
            break;
        }
        ret = sd->query_word(buff,tmp_head);
        printf("ret = %d kkkkk\n",ret);
        tmp_head->dump_meta_data_head();
        printf("#####################ret = %d kkkkk\n",ret);
    }
    delete tmp_head;

    */
    File::release_check_list();
    delete ds;
    release_global_env();
    return 0;
}
