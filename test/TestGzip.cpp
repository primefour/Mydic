#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>


int main(int argc,char **argv){

    //init
    File::add_check_func(GzipFile::check_file_type,GZIP_FILE_TYPE);
    const char *file_name="./langdao-ec-gb.dict.dz";
    int type = (int)File::check_file_type(file_name);
    printf("type = %d \n",type);
    File *inst = File::MakeFileInstance((const void *)file_name,(DIC_FILE_TYPE)type);
    inst->open(0);
    File original_file("./raw.data");

    original_file.open(O_CREAT|O_RDWR);

    inst->build_access_point();

    unsigned char buff[1024]={0};
    inst->extract(0,buff,sizeof(buff));
    printf("%s ",buff);
    inst->uncompress_file(&original_file);
    return 0;
}




