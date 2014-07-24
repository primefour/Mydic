#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<assert.h>


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


unsigned char test_data[768] ={
1,2,3,4,5,6,7,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16
};

void reverse_bmp_data(unsigned char *data,int stride,int height,int pixel_count){
    int i = 0;
    int j = 0;
    for(i = 0 ;i < height/2 ;i++){
        for(j = 0 ;j < stride ;j ++){
            if(pixel_count == 3){
                int offset = i *stride + j;
                int offset_exch = (height -i-1)*stride + j;
                unsigned char *tmp = (data + offset * pixel_count);
                unsigned char *tmp_exch = (data + offset_exch * pixel_count); 
                unsigned char data_tmp = *tmp ;
                *tmp = *tmp_exch;
                *tmp_exch = data_tmp;
                tmp ++;
                tmp_exch ++;
                data_tmp = *tmp ;
                *tmp = *tmp_exch;
                *tmp_exch = data_tmp;
                tmp ++;
                tmp_exch ++;
                data_tmp = *tmp ;
                *tmp = *tmp_exch;
                *tmp_exch = data_tmp;
            }else{
                int offset = i *stride + j;
                int offset_exch = (height -i-1)*stride + j;

                unsigned char *tmp = (data + offset * pixel_count);
                unsigned char *tmp_exch = (data + offset_exch * pixel_count); 
                unsigned char data_tmp = *tmp ;
                *tmp = *tmp_exch;
                *tmp_exch = data_tmp;
                tmp ++;
                tmp_exch ++;

                data_tmp = *tmp ;
                *tmp = *tmp_exch;
                *tmp_exch = data_tmp;
                tmp ++;
                tmp_exch ++;

                data_tmp = *tmp ;
                *tmp = *tmp_exch;
                *tmp_exch = data_tmp;

                tmp ++;
                tmp_exch ++;
                data_tmp = *tmp ;
                *tmp = *tmp_exch;
                *tmp_exch = data_tmp;
            }
        }
    }
}


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

typedef struct ycrcb_t{
    int width;
    int stride;
    int height;
    unsigned char *data;
}ycrcb_t;

typedef struct yuv_t{
    int width;
    int stride;
    int height;
    unsigned char *data;
}yuv_t;


typedef struct bmp_t{
    bmp_file_info_t bmp_file_info;
    bmp_info_t bmp_info;
    unsigned char *data;
}bmp_t;

//default 420
void read_ycrcb_flat(const char *file_name,ycrcb_t *pycrcb){
    memset(pycrcb,0,sizeof(ycrcb_t));
    int fd = open(file_name,O_RDONLY);
    if(fd < 0){
        perror("open error");
        return;
    }

    int width = atoi(file_name);
    char *pheight = strchr(file_name,'x');
    pheight++;
    if(pheight == NULL){
        printf("no resolution provider \n");
        assert(0);
    }
    int height = atoi(pheight);
    int stride = ((width + 3)>>2)<<2;
    printf("width x height = %d x %d  stride = %d \n",width,height,stride);

    int data_bytes = (stride * height * 3)>>1;
    printf("data bytes = %d \n",data_bytes);
    unsigned char *ptmp_data = (unsigned char *)malloc(data_bytes);
    int ret = read(fd,ptmp_data,data_bytes);
    if(ret != data_bytes ){
        printf("ERROR ################## READ YCRCB FILE FAILED\n");
        assert(0);
    }
    pycrcb->data = ptmp_data;
    pycrcb->stride = stride;
    pycrcb->width = width;
    pycrcb->height = height;
    close(fd);
    printf("%s complete \n",__func__);
}

void bmp_to_ycrcb(bmp_t *pbmp,ycrcb_t *pycrcb){

}

void ycrcb_to_bmp(ycrcb_t *pycrcb,bmp_t *pbmp){
    int bmp_width = pycrcb->width;
    int bmp_height = pycrcb->height;
    int bmp_stride = pycrcb->stride;
    int bmp_data_bytes = (bmp_stride *bmp_height * 24)>>3;
    unsigned char *bmp_data = (unsigned char *)malloc(bmp_data_bytes);
    int i = 0;
    int j = 0;
    for(i = 0 ;i < bmp_height ;i += 2){
        for(j = 0;j < bmp_stride;j += 2){
            int bmp_offset00 = (i * bmp_stride + j ) * 3;//pixel count is 24
            int bmp_offset01 = bmp_offset00+3;
            int bmp_offset10 = bmp_offset00  + bmp_stride *3 ;
            int bmp_offset11 = bmp_offset10 + 3;

            int y_offset00 = i * pycrcb->stride + j;
            int y_offset01 = y_offset00 + 1;
            int y_offset10 = y_offset00 + pycrcb->stride;
            int y_offset11 = y_offset10 + 1;

            int cb_offset = pycrcb->stride * pycrcb->height + ((i * pycrcb->stride + j)>>2);
            int cr_offset = cr_offset + 1;//pycrcb->stride * pycrcb->height + ((pycrcb->stride * pycrcb->height)>>2)  + ((i * pycrcb->stride + j)>>2);

            int y = *(pycrcb->data + y_offset00);
            int cb = *(pycrcb->data + cb_offset);
            int cr =*(pycrcb->data + cr_offset);
#if 0//1
            *(bmp_data + bmp_offset00) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset00+1) = 1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset00+2) = 1.164*(y-16) + 2.017 * (cb - 128); 


            y = *(pycrcb->data + y_offset01);
            *(bmp_data + bmp_offset01) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset01+1) = 1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset01+2) = 1.164*(y-16) + 2.017 * (cb - 128); 

            y = *(pycrcb->data + y_offset10);
            *(bmp_data + bmp_offset10) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset10+1) = 1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset10+2) = 1.164*(y-16) + 2.017 * (cb - 128); 

            y = *(pycrcb->data + y_offset11);
            *(bmp_data + bmp_offset11) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset11+1) = 1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset11+2) = 1.164*(y-16) + 2.017 * (cb - 128); 
#else

            *(bmp_data + bmp_offset00) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset00+1) = *(bmp_data + bmp_offset00);//1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset00+2) = *(bmp_data + bmp_offset00) ;//1.164*(y-16) + 2.017 * (cb - 128); 


            y = *(pycrcb->data + y_offset01);
            *(bmp_data + bmp_offset01) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset01+1) = *(bmp_data + bmp_offset01);// 1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset01+2) = *(bmp_data + bmp_offset01);//1.164*(y-16) + 2.017 * (cb - 128); 

            y = *(pycrcb->data + y_offset10);
            *(bmp_data + bmp_offset10) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset10+1) = *(bmp_data + bmp_offset10);//1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset10+2) = *(bmp_data + bmp_offset10);//1.164*(y-16) + 2.017 * (cb - 128); 

            y = *(pycrcb->data + y_offset11);
            *(bmp_data + bmp_offset11) = 1.164 *(y-16) + 1.596 *(cr - 128);
            *(bmp_data + bmp_offset11+1) = *(bmp_data + bmp_offset11);//1.164 *(y-16) - 0.813 *(cr - 128) - 0.392 *(cb-128); 
            *(bmp_data + bmp_offset11+2) = *(bmp_data + bmp_offset11);//1.164*(y-16) + 2.017 * (cb - 128); 
#endif
        }
    }

    pbmp->bmp_info.info_size = 40;
    pbmp->bmp_info.width = bmp_width;
    pbmp->bmp_info.height =bmp_height;
    pbmp->bmp_info.planes = 1;
    pbmp->bmp_info.bit_count = 24;
    pbmp->bmp_info.compressed = 0;
    pbmp->bmp_info.image_size= (bmp_stride * bmp_height) * 3;
    pbmp->bmp_info.color_used = 0;
    pbmp->bmp_file_info.bf_size = 54 +  pbmp->bmp_info.image_size;
    pbmp->bmp_file_info.bf_image_data_offset = 54;
    pbmp->data = bmp_data;
    printf("width x height = %d x %d imagesize = %d bf_size = %d \n",bmp_width,bmp_height,pbmp->bmp_info.image_size,pbmp->bmp_file_info.bf_size);
}

void y_to_bmp(ycrcb_t *pycrcb,bmp_t *pbmp){

}

void crcb_to_bmp(ycrcb_t *pycrcb,bmp_t *pbmp){

}



void bmp_to_yuv(bmp_t *pbmp,yuv_t *pyuv){

}




void read_bmp_file(char *file_name,bmp_t *pbmp){
    memset(pbmp,0,sizeof(bmp_t));
    int fd = open(file_name,O_RDONLY);
    if(fd < 0){
        perror("open error");
        return;
    }
    unsigned char tmp_buffer[1024]={0};
    int ret = read(fd,tmp_buffer,14);
    parse_bmp_header_info(tmp_buffer,&pbmp->bmp_file_info);
    memset(tmp_buffer,0,sizeof(tmp_buffer));
    ret = read(fd,tmp_buffer,sizeof(tmp_buffer));
    parse_bmp_data_info(tmp_buffer,&pbmp->bmp_info);
    int stride = ((pbmp->bmp_info.width+3)>>2)<<2;
    printf("stride = %d \n",stride);
    int height = pbmp->bmp_info.height;
    int pixel_depth = pbmp->bmp_info.bit_count;
    int data_bytes = (stride *height * pixel_depth)>>3;
    //printf("data bytes = %d \n",data_bytes);
    unsigned char *ptmp_data = (unsigned char *)malloc(data_bytes);
    long int loc = lseek(fd,pbmp->bmp_file_info.bf_image_data_offset,SEEK_SET);
    ret = read(fd,ptmp_data,data_bytes);
    if(ret != data_bytes ){
        printf("ERROR ################## READ BMP FILE FAILED\n");
        assert(0);
    }
    pbmp->data = ptmp_data;
    reverse_bmp_data(ptmp_data,stride,height,pixel_depth>>3);
    close(fd);
}



void write_bmp_file(bmp_t *pbmp,const char *file_name){
    int fd = open(file_name,O_WRONLY|O_CREAT,0777);
    unsigned char *phead_info = (unsigned char *)malloc(pbmp->bmp_file_info.bf_image_data_offset);
    if(phead_info == NULL){
        printf("write bmp file failed no memory \n");
        return ;
    }
    memset(phead_info,0,pbmp->bmp_file_info.bf_image_data_offset);
    create_bmp_header_info(&(pbmp->bmp_file_info),phead_info);
    create_bmp_data_info(&(pbmp->bmp_info),phead_info+14);
    int ret = write(fd,phead_info,pbmp->bmp_file_info.bf_image_data_offset);
    printf("pbmp->bmp_info.image_size = %d \n",pbmp->bmp_info.image_size);
    //reverse_bmp_data(pbmp->data,pbmp->bmp_info.width,pbmp->bmp_info.height,pbmp->bmp_info.bit_count>>3);
    ret = write(fd,pbmp->data,pbmp->bmp_info.image_size);
    if(ret < 0){
        perror("write failed");
    }
    free(phead_info);
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
                if(y0 >= 0 && x0 >= 0 && y0 < pbmp->bmp_info.height && x0 < stride){
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

bmp_t* scaler_bmp(bmp_t *pbmp,int stride,int height,int scaler_width,int scaler_height){
    return NULL;
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
    read_bmp_file(argv[1],&bmp);
    char file_name[1024] = "copy";
    strncat(file_name,argv[1],1024);
    //test_bmp(&bmp);
    cpy_bmp = move_bmp(&bmp,10,10);
    write_bmp_file(cpy_bmp,file_name);
    int i = 0;
    int j = 0;
    for( i = 0;i < 16 ;i++){
        for( j = 0 ;j < 16 * 3; j ++){
            printf("%d ",*(test_data + i * 16 * 3 + j));
        }
        printf("\n");
    }
    reverse_bmp_data(test_data,16,16,3);
    printf("\n");
    for( i = 0;i < 16 ;i++){
        for( j = 0 ;j < 16 * 3; j ++){
            printf("%d ",*(test_data + i * 16 * 3 + j));
        }
        printf("\n");
    }
    ycrcb_t *pycrcb = (ycrcb_t *)malloc(sizeof(ycrcb_t));
    memset(pycrcb,0,sizeof(ycrcb_t));
    read_ycrcb_flat("960x544.yuv",pycrcb);
    bmp_t *new_bmp = (bmp_t *)malloc(sizeof(bmp_t));
    memset(new_bmp,0,sizeof(bmp_t));
    ycrcb_to_bmp(pycrcb,new_bmp);
    write_bmp_file(new_bmp,"960x544.bmp");

    return 0;
}









