#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<wchar.h>
#include "iconv_string.h"


const char *utf8_type = "UTF-8";
const char *utf16_little_type = "UTF-16-little-end";
const char *utf16_big_type = "UTF-16-big-end";
const char *utf32_little_type = "UTF-32-little-end";
const char *utf32_big_type = "UTF-32-big-end";


const char *GetFileEncoding(unsigned char *buff){
    if(buff[0] == 0xEF && buff[1] == 0xBB && buff[2] == 0xBF){
        return utf8_type;
    }else if(buff[0] == 0xFE && buff[1] == 0xFF){
        return utf16_little_type;
    }else if(buff[0] == 0xFF && buff[1] == 0xFE){
        return utf16_big_type;
    }else if(buff[0] == 0xff && buff[1] == 0xfe &&  buff[2] == 0x00 && buff[3] == 0x00){
        return utf32_little_type;
    }else if(buff[3] == 0xff && buff[2] == 0xfe &&  buff[1] == 0x00 && buff[0] == 0x00){
        return utf32_big_type; 
    }else{
        return utf8_type;
    }
}

const char *file_path = "/home/crazyhorse/MyProject/Advanced_Learners_Dictionary.dsl";
int main(int argc,char **argv){
    int fd = open(file_path,O_RDONLY);
    if(fd < 0){
        printf("open file fail %s \n",file_path);
        return 0;
    }

    unsigned char buff[4];

    int ret = read(fd,buff,sizeof(buff));
    if(ret != sizeof(buff)){
        close(fd);
        return 0;
    }

    const char *encode_type = GetFileEncoding(buff);

    printf("encode-type = %s \n",encode_type);
    unsigned short read_buff[1024]={0};
    unsigned short new_line = L'\n';
    unsigned short *tmp = read_buff;
    printf("new line char value sizeof = %ld 0x%04x \n",sizeof(new_line),new_line);
    while(read(fd,tmp,sizeof(unsigned short)) && (*tmp != new_line)){
        printf("0x%04x \n",*tmp);
        tmp ++;
    }
    //printf("read_buff = %s \n",read_buff);

    char utf8_buff[1024]={0};

    //extern int iconv_string (const char* tocode, const char* fromcode, 
    //const char* start, const char* end, char** resultp, size_t* lengthp);
    size_t length = sizeof(utf8_buff);
    extern int printfk(int a);
    printfk(2);

    ret = iconv_string(utf8_type,encode_type, 
                            (const char *)read_buff,
                            (const char *)tmp, 
                            (char **)&utf8_buff,
                            &length);

    printf("iconv_string ret value = %d  %s ",ret,utf8_buff);
    
    return 0;
}
