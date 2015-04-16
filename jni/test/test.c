#include"StandardIO.h"
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>


int main(int argc,char **argv){
    MemFile file("./bin/trademarks.txt",O_CREAT|O_RDWR);
    unsigned char buff[1024]={0};
    int ret = 0;
    while((ret = file.ReadLine(buff,sizeof(buff))) != 0){
        printf("%s  %d \n",buff,ret);
        file.Seek(SEEK_SET,10);
        memset(buff,0,sizeof(buff));
    }
    printf("ret = %d  \n",ret);
    
    return 0;
}
