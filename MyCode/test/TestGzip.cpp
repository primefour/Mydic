#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include"memory_test_tool.h"


int main(int argc,char **argv){
    init_global_env();
    //init
    File::add_check_func(GzipFile::check_file_type,GZIP_FILE_TYPE);
    const char *file_name="./langdao-ec-gb.dict.dz";
    int type = (int)File::check_file_type(file_name);
    printf("type = %d \n",type);
    File *inst = File::MakeFileInstance((const void *)file_name,(DIC_FILE_TYPE)type);
    inst->open(0);
    /*
    File original_file("./raw.data");
    original_file.open(O_CREAT|O_RDWR);
    */
    unsigned char buff[10240]={0};
/*
    inst->lseek(SEEK_SET,500000);
    inst->read(buff,sizeof(buff));
    printf("%s \n",buff);
    */

    memset(buff,0,sizeof(buff));
    int ret = 0 ;
    int i = 0;
    while((ret = inst->readline(buff,sizeof(buff)) ) && i++ < 5){
        printf("ret = %d \n",ret);
        printf("%s\n",buff);
    }
    printf("ret = %d \n",ret);
    printf("%s\n",buff);
    delete inst;
    File::release_check_func();
    release_global_env();
    return 0;
}




