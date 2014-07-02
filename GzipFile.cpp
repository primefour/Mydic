#include"GzipFile.h"
#include"log.h"
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>
extern "C"{
#include"zlib.h"
}


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
#define BUFFER_COMMPRESS 40960
int GzipFile::uncompress_file(File *outFile){
    int ret;
    z_stream strm;
    unsigned char input[BUFFER_COMMPRESS];
    unsigned char output[BUFFER_COMMPRESS];
    if(outFile == NULL){
        printf("output file invalidate\n");
        return -1;
    }

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if(ret != Z_OK){
        printf("%s init inflate failed \n",__func__);
        return -1;
    }
    File::lseek(SEEK_SET,head_length);
    do{
        strm.avail_in = File::read((char *)input,sizeof(input));
        if(strm.avail_in == 0){
            printf("read file eof ");
            inflateEnd(&strm);
            break;
        }else if(strm.avail_in < 0){
            printf("read file error !");
            inflateEnd(&strm);
            return -1;
        }
        strm.next_in = input;
        strm.avail_out = sizeof(output);
        strm.next_out = output;
        ret = inflate(&strm,Z_NO_FLUSH);
        if((ret == Z_NEED_DICT) || (Z_DATA_ERROR == ret) || (Z_MEM_ERROR ==ret)){
            inflateEnd(&strm);
            return -1;
        }
        outFile->write((char *)output,sizeof(output) - strm.avail_out);
    }while(1);
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
        ret = File::read((char *)extra_len,sizeof(extra_len));
        head_length += sizeof(extra_len);
        unsigned int extra_length=0;
        extra_length |= extra_len[0];
        extra_length |= extra_len[1]<<8;
        ALOGE("extra length = %d \n",extra_length);
        if(extra_info != NULL){
            free(extra_info);
            extra_info = NULL;
        }
        extra_info = (unsigned char *)malloc(extra_length);
        memset(extra_info,0,extra_length);
        ret = File::read((char *)extra_info,extra_length);
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

    }

    File::lseek(SEEK_END,-8);
    File::read((char*)crc32_info,sizeof(crc32_info));
    unsigned int size =0;
    size |= crc32_info[4];
    size |= crc32_info[5]<<8;
    size |= crc32_info[6]<<16;
    size |= crc32_info[7]<<24;
    printf("size = %d \n",size);

}

int GzipFile::open(char *path,int mode){
    int ret = File::open(NULL,O_RDWR);
    if(ret < 0){
        return -1;
    }
    ret += ParserHeader();
}
