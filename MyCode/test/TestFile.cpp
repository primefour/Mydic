#include "File.h"
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>


int main(int argc,char *argv[]){
    const char *file_name="./ReadMe";
    File readme(file_name);
    unsigned char buffer[2048]={0};
    readme.open(0);
    int ret = readme.read(buffer,2048);
    printf("read charecator count is ret = %d \n",ret);
    printf("%s",buffer);
    readme.lseek(SEEK_SET,0);

    ret = readme.read(buffer,2048);
    printf("read charecator count is ret = %d \n",ret);

    readme.lseek(SEEK_END,0);

    ret = readme.read(buffer,2048);
    printf("read charecator count is ret = %d \n",ret);

    readme.lseek(SEEK_SET,10);

    ret = readme.read(buffer,2048);
    printf("read charecator count is ret = %d \n",ret);
    printf("%s",buffer);

    ret = readme.write((const unsigned char *)"welcome to mydic",strlen("welcome to mydic"));

    ret = readme.read(buffer,2048);
    printf("read charecator count is ret = %d \n",ret);
    printf("%s",buffer);

    readme.lseek(SEEK_SET,0);

    ret = readme.read(buffer,2048);
    printf("read charecator count is ret = %d \n",ret);
    printf("%s\n",buffer);
    printf("############################\n");
    readme.lseek(SEEK_SET,0);
    while(readme.readline(buffer,2048)){
        printf("%s\n",buffer);
    }

    return 0;
}

