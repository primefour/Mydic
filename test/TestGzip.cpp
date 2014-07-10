#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>


int main(int argc,char **argv){
    const char *file_name="./langdao-ec-gb.dict.dz";
    GzipFile gzip_file(file_name);
    gzip_file.open(0);
    File original_file("./raw.data");
    original_file.open(O_CREAT|O_RDWR);
    gzip_file.build_access_point();
    unsigned char buff[1024*1024]={0};
    gzip_file.extract(0,buff,sizeof(buff));
    printf("%s ",buff);
    return 0;
}




