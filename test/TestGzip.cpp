#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>


int main(int argc,char **argv){
    const char *file_name="./kkkk.gz";
    GzipFile gzip_file(file_name);
    gzip_file.open(NULL,0);
    File original_file("./raw.data");
    original_file.open(NULL,O_CREAT|O_RDWR);
    gzip_file.uncompress_file(&original_file);
    return 0;
}




