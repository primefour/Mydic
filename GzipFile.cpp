#include"GzipFile.h"
#include"log.h"
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>


GzipFile::GzipFile(const char *file_path):File(file_path){

}

GzipFile::GzipFile(){

}

GzipFile::~GzipFile(){

}


int GzipFile::check_file_type(char *buf,int len){
    if(len < 2){
        return 0;
    }
    unsigned char *ptr = (unsigned char *)buf;
    if (*ptr == ID1_VALUE && *(ptr+1)== ID2_VAlUE) {
        return 1;
    }else{
        return 0;
    }
}

int GzipFile::readline(char *buf,int len){
    printf("%s,%s\n",__FILE__,__func__);
    return 0;
}


int GzipFile::lseek(int whence,int offset){

    printf("%s,%s\n",__FILE__,__func__);
    return 0;
}

int GzipFile::write(const char *buf,int len){

    printf("%s,%s\n",__FILE__,__func__);
    return 0;
}


int GzipFile::read(char *buf,int len){
    printf("%s,%s\n",__FILE__,__func__);
    return 0;
}


int GzipFile::ParserHeader(){
    printf("%s \n",__func__);
    int ret = File::read((char*)fixed_head,sizeof(fixed_head));

    if(!check_file_type((char*)fixed_head,8)){
        printf("not a Gzip file \n");
        return -1;
    }

    head_length += sizeof(fixed_head);
    if(fixed_head[FLG] & FLAG_EXTRA_VALUE ){
        ALOGE("%s\n","has extra value");
        ret = File::read((char *)extra_info_header,sizeof(extra_info_header));
        head_length += sizeof(extra_info_header);
        unsigned int extra_length=0;
        extra_length |= extra_info_header[0];
        extra_length |= extra_info_header[1]<<8;
        ALOGE("extra length = %d \n",extra_length);
        File::lseek(SEEK_CUR,extra_length);
        head_length += extra_length;
    }

    if(fixed_head[FLG] & FLAG_NAME_VALUE){
        ALOGE("%s\n","FLAG_NAME_VALUE");
        //string
        ALOGE("%x \n",File::lseek(SEEK_CUR,0));
        File::readline(zip_name,sizeof(zip_name));
        ALOGE("%s \n",zip_name);
        head_length += strlen(zip_name) + 1;
    }

    if(fixed_head[FLG]&FLAG_COMMENT_VALUE){

        ALOGE("%s\n","FLAG_COMMENT_VALUE");
        //string
        File::readline(comment,sizeof(comment));
        ALOGE("%s \n",comment);
        head_length += strlen(comment) + 1;
    }

    if(fixed_head[FLG]&FLAG_HCRC_VALUE){
        ALOGE("%s\n","FLAG_HCRC_VALUE");
        File::read((char *)crc16_head,sizeof(crc16_head));
        head_length += sizeof(crc16_head);

        File::lseek(SEEK_END,-8);
        File::read((char*)crc32_info,sizeof(crc32_info));
    }
}

int GzipFile::open(char *path,int mode){
    int ret = File::open(NULL,O_RDWR);
    if(ret < 0){
        return -1;
    }
    ret += ParserHeader();
}
