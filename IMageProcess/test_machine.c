#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>


void print_type_capblity(){
    printf("sizeof int = %ld \n",sizeof(int));
    printf("char = %ld \n",sizeof(char));
    printf("long = %ld \n",sizeof(long));
    printf("long long = %ld \n",sizeof(long long));
    printf("Short = %ld \n",sizeof(short));
}


typedef struct bmp_file_info_t {
    unsigned int bf_size;
    unsigned int bf_image_data_offset;
}bmp_file_info_t;


void parse_bmp_header_info(unsigned char *phead_data,void *data){
    if(!data){
        return ;
    }
    bmp_file_info_t *bmp_file_info = (bmp_file_info_t *)data;
    bmp_file_info->bf_size = *((unsigned int *)(phead_data+2));
    bmp_file_info->bf_image_data_offset = *((unsigned int *)(phead_data + 10));
    printf("bf_size = %u ,data offset = %d \n",bmp_file_info->bf_size,bmp_file_info->bf_image_data_offset);
}

void create_bmp_header_info(bmp_file_info_t *pfile_info,unsigned char *data){
    *(data) = 'B';
    *(data+1)='M';
    *(unsigned int *)(data + 2) = pfile_info->bf_size;
    *(unsigned int *)(data + 10) = pfile_info->bf_image_data_offset;
}

typedef struct bmp_info_t {
    //offset 0
    unsigned int info_size; 
    //offset 4
    unsigned int width;
    //offset 8
    unsigned int height;
    //offset 12
    unsigned short planes; //always is 1
    //how many bits used to store one pixel
    //1,4,8,24:32
    //offset 14
    unsigned short bit_count;
    //whether or not compress image data
    //offset 16
    unsigned int compressed;
    //image data size==>bytes
    //offset 20
    unsigned int image_size;
    //offset 32
    unsigned int color_used;
}bmp_info_t;


void parse_bmp_data_info(unsigned char *data,void *pinfo_data){
    if(!data){
        return;
    }
    bmp_info_t *pdata_info_data = (bmp_info_t *)pinfo_data;
    pdata_info_data->info_size = *(unsigned int *)data;
    pdata_info_data->width = *(unsigned int *)(data + 4);
    pdata_info_data->height = *(unsigned int *)(data + 8);
    pdata_info_data->planes = 1;
    pdata_info_data->bit_count = *(unsigned short*)(data+14);
    pdata_info_data->compressed = *(unsigned int *)(data + 16);
    pdata_info_data->image_size =*(unsigned int *)(data +20);
    pdata_info_data->color_used = *(unsigned int *)(data + 32);
    printf("resolution %u x %u \n",pdata_info_data->width,pdata_info_data->height);
    printf("compressed = %d \n",pdata_info_data->compressed);
    printf("color_used = %d \n",pdata_info_data->color_used);
    printf("image size = %u \n",pdata_info_data->image_size);
}


void create_bmp_data_info(bmp_info_t *pinfo_data,unsigned char *data){
    if(!data){
        return;
    }
    bmp_info_t *pdata_info_data = (bmp_info_t *)pinfo_data;
    *(unsigned int *)data = pdata_info_data->info_size;
    *(unsigned int *)(data + 4) = pdata_info_data->width;
    *(unsigned int *)(data + 8) = pdata_info_data->height ;
    *(unsigned short*)(data + 12) = 1; 
    *(unsigned short*)(data+14) = pdata_info_data->bit_count;
    *(unsigned int *)(data + 16) = pdata_info_data->compressed;
    *(unsigned int *)(data +20) = pdata_info_data->image_size;
    *(unsigned int *)(data + 32) = pdata_info_data->color_used;
}


typedef struct bmp_t{
    bmp_file_info_t bmp_file_info;
    bmp_info_t bmp_info;
    unsigned char *data;
}bmp_t;


void read_bmp_file(bmp_t *pbmp,char *file_name){
    memset(pbmp,0,sizeof(bmp_t));
    int fd = open(file_name,O_RDONLY);
    if(fd < 0){
        perror("open error");
        return;
    }
    unsigned char tmp_buffer[1024]={0};
    int ret = read(fd,tmp_buffer,14);
    parse_bmp_header_info(tmp_buffer,&pbmp->bmp_file_info);
    memset(tmp_buffer,0,1024);
    ret = read(fd,tmp_buffer,1024);
    parse_bmp_data_info(tmp_buffer,&pbmp->bmp_info);
    int stride = ((pbmp->bmp_info.width+3)>>2)<<2;
    printf("stride = %d \n",stride);
    int height = pbmp->bmp_info.height;
    int pixel_depth = pbmp->bmp_info.bit_count;
    int data_bytes = (stride *height * pixel_depth)>>3;
    printf("data bytes = %d \n",data_bytes);
    unsigned char *ptmp_data = (unsigned char *)malloc(data_bytes);
    long int loc = lseek(fd,pbmp->bmp_file_info.bf_image_data_offset,SEEK_SET);
    ret = read(fd,ptmp_data,data_bytes);
    pbmp->data = ptmp_data;
    close(fd);
}



void write_bmp_file(bmp_t *pbmp,char *file_name){
    int fd = open(file_name,O_WRONLY|O_CREAT,0777);
    unsigned char *phead_info = (unsigned char *)malloc(pbmp->bmp_file_info.bf_image_data_offset);
    if(phead_info == NULL){
        return ;
    }
    memset(phead_info,0,pbmp->bmp_file_info.bf_image_data_offset);
    create_bmp_header_info(&(pbmp->bmp_file_info),phead_info);
    create_bmp_data_info(&(pbmp->bmp_info),phead_info+14);
    int ret = write(fd,phead_info,pbmp->bmp_file_info.bf_image_data_offset);
    printf("pbmp->bmp_info.image_size = %d \n",pbmp->bmp_info.image_size);
    ret = write(fd,pbmp->data,pbmp->bmp_info.image_size);
    if(ret < 0){
        perror("write failed");
    }
}


bmp_t *move_bmp(bmp_t *pbmp,int x,int y){
    int pixel_byte = pbmp->bmp_info.bit_count >>3;
    int stride = ((pbmp->bmp_info.width+3) >>2)<<2;
    int i=0;
    int j=0;
    unsigned char *pdata = pbmp->data;
    int data_offset = 0;
    bmp_t *cpy_bmp = (bmp_t *)malloc(sizeof(bmp_t));
    memset(cpy_bmp,0,sizeof(bmp_t));
    memcpy(cpy_bmp,pbmp,sizeof(bmp_t));

    cpy_bmp->data = (unsigned char *)malloc(pbmp->bmp_info.image_size);
    memset(cpy_bmp->data,0,pbmp->bmp_info.image_size);

    printf("pixel byte = %d \n",pixel_byte);
    int x0,y0;
    unsigned int pixel_value;
    if(pixel_byte != 0){
        for(j=0;j<pbmp->bmp_info.height;j++){
            for(i=0;i<stride;i++){
                pixel_value = 0xffffffff;
                data_offset = j*stride + i;
                data_offset *= pixel_byte;
                y0 = j - y;
                x0 = i - x;
                //printf("y0 = %d,x0 = %d,j=%d,i=%d,y=%d,x=%d\n",y0,x0,j,i,y,x);
                if(y0 >= 0 && x0 >= 0){
                    pixel_value = *(unsigned int *)(pdata + ((y0 * stride + x0)*pixel_byte));
                }
                if(pixel_byte == 3){
                    *(unsigned int *)(cpy_bmp->data + data_offset) = pixel_value;
                }else if(pixel_byte == 4){
                    *(unsigned int *)(cpy_bmp->data + data_offset) = pixel_value;
                }
            }
        }
    }else{
        //pixel_byte is 1/2
    }
    return cpy_bmp;

}

void test_bmp(bmp_t *pbmp){
    int pixel_byte = pbmp->bmp_info.bit_count >>3;
    int stride = ((pbmp->bmp_info.width+3) >>2)<<2;
    int i=0;
    int j=0;
    unsigned char *pdata = pbmp->data;
    int data_offset = 0;
    printf("pixel byte = %d \n",pixel_byte);
    if(pixel_byte != 0){
        for(j=0; j < 300 && j<pbmp->bmp_info.height;j++){
            for(i=0;i<stride;i++){
                data_offset = j*stride + i;
                if(pixel_byte == 3){
                    *(unsigned int *)(pdata + data_offset) = 0xffff;
                }else if(pixel_byte == 4){
                    *(unsigned int *)(pdata + data_offset) = 0xffff;
                }
            }
        }
    }else{
        //pixel_byte is 1/2
    }
}


int main(int argc,char **argv){
    if(argc < 2){
        printf("please input file name! \n");
        return -1;
    }
    bmp_t bmp, *cpy_bmp;
    memset(&bmp,0,sizeof(bmp));
    read_bmp_file(&bmp,argv[1]);
    char file_name[1024] = "copy";
    strncat(file_name,argv[1],1024);
    //test_bmp(&bmp);
    cpy_bmp = move_bmp(&bmp,0,0);
    write_bmp_file(cpy_bmp,file_name);
    free(bmp.data);
    return 0;
}









