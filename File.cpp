#include"File.h"
#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>



File::File(char *path){
    memset(file_path,0,MAX_PATH_LENGTH);
    if(path != NULL){
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
}

File::File(){
    memset(file_path,0,MAX_PATH_LENGTH);
}

int File::check_file_type(){
    return -1;
}

int File::readline(char *buf,int len){
    unsigned char cache[1028]={0};
    int ret = -1;
    char *ptr = buf;
    memset(buf,len);
    int i = 0;
    while((ret = read(ptr,1) > 0) && (ptr != '\0') && ++i < len){ 
        ptr++;
    }

    if(ptr == '\0' && i != len){
        return i;
    }else{
        return -1;
    }
}


int File::lseek(int whence,int offset){
    if(fd >= 0){
        return lseek(fd,offset,whence);
    }else{
        return -1;
    }
}

int File::write(char *buf,int len){
    int ret = -1;
    if(fd > =){
        ret = write(fd,buf,len);
    }
    return ret;
}


int File::read(char *buf,int len){
    int ret = -1;
    memset(buf,0,len);
    if(fd >= 0){
       ret = read(fd,buf,len); 
    }
    return ret;
}



int File::open(char *path,int mode){
    if(path != NULL){
        strncpy(file_path,path,MAX_PATH_LENGTH);
    }
    fd=-1;
    fd = open(file_path,O_RDONLY);
    if(fd < 0){
        printf("open file error %s \n",file_path);
        perror();
        return -1;
    }
    return 0;
}





