#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>


int main(int argc,char **argv){
    const char *file_name="/home/crazyhorse/MyProject/GoldenDict/GitDict/test/langdao-ec-gb.dict.dz";
    GzipFile gzip_file(file_name);
    gzip_file.open(NULL,0);
    return 0;
}

