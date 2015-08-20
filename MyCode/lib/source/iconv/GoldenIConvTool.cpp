#include"GoldenIConvTool.h"

const char *utf8_type = "UTF-8";
const char *utf16_little_type = "UTF-16LE";
const char *utf16_big_type = "UTF-16BE";
const char *utf32_little_type = "UTF-32LE";
const char *utf32_big_type = "UTF-32BE";




static const char *GoldenIConvTool::GetFileEncoding(int fd){
    unsigned char buff[4] ={0};
    int ret = read(fd,buff,sizeof(buff));
    if(ret != sizeof(buff)){
        return NULL;
    }
    return GetFileEncoding(buff);
}

static const char *GoldenIConvTool::GetFileEncoding(unsigned char *buff){
    if(buff[0] == 0xEF && buff[1] == 0xBB && buff[2] == 0xBF){
        return utf8_type;
    }else if(buff[0] == 0xff && buff[1] == 0xfe &&  buff[2] == 0x00 && buff[3] == 0x00){
        return utf32_big_type;
    }else if(buff[3] == 0xff && buff[2] == 0xfe &&  buff[1] == 0x00 && buff[0] == 0x00){
        return utf32_little_type; 
    }else if(buff[0] == 0xFE && buff[1] == 0xFF){
        return utf16_big_type;
    }else if(buff[0] == 0xFF && buff[1] == 0xFE){
        return utf16_little_type;
    }else{
        return utf8_type;
    }
}

static int GoldenIConvTool::IConvString(const char *encode_type,const char *to_type,
                                char **input_buff,int ilength,char *output_buff,int olength){
    int ret = -1;
    iconv_t cd = iconv_open(to_type,encode_type);
    if (cd == (iconv_t)(-1)) {
        printf("iconv open fail \n");
        return ret;
    }

    size_t input_size = ilength;
    const int DEST_SIZE = 4096;
    char *dest_buff = (char *)malloc(DEST_SIZE);
    size_t output_size = DEST_SIZE;
    char *tmp_buff = dest_buff ;

    while(input_size > 0){
        ret = iconv(cd,input_buff,&input_size,&dest_buff,&output_size);
        printf("input_size = %d output_size = %d \n",input_size,output_size)
        if(ret == -1){
            if(errno == EINVAL){
                printf("EINVAL \n");
            }else{
                perror("iconv fail");
            }
            iconv_close(cd);
            return ret;
        }
    }

    ret = iconv(cd,NULL,NULL,&dest_buff,&output_size);
    printf("###input_size = %d output_size = %d \n",input_size,output_size)
    if (ret == (-1)) {
        if(errno == EINVAL){
            printf("EINVAL \n");
        }else{
            perror("iconv fail");
        }
        iconv_close(cd);
        return ret;
    }
    iconv_close(cd);

    memcpy(output_buff,tmp_buff,(DEST_SIZE - output_size));
    printf("iconv_string ret value = %d  %s \n",ret,output_buff);

    return 0;
}



static int GoldenIConvTool::ReadLine16(int fd,const char *encode_type,const char *to_type,
                                                                    char *buff,int length){
    return 0;
}

static int GoldenIConvTool::ReadLine32(int fd,const char *encode_type,const char *to_type,
                                                                    char *buff,int length){
    return 0;
}
