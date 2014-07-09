#include"GzipFile.h"
#include"log.h"
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>
#include"list.h"
extern "C"{
#include"zlib.h"
}

void GzipFile::init_access_point_list(){

    init_list_head(&access_point_list);
}

void GzipFile::reset_access_point_list(){
    release_list(&access_point_list,NULL);
}


GzipFile::GzipFile(const char *file_path):File(file_path){
    init_access_point_list();
}

GzipFile::~GzipFile(){
    reset_access_point_list();
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


int GzipFile::open(int mode){
    int ret = File::open(O_RDWR);
    if(ret < 0){
        return -1;
    }
}





void GzipFile::set_access_point(access_point_t *ap,int bits, off_t in, off_t out, 
                                                unsigned left, unsigned char *window)
{
    ap->original_offset = out;
    ap->file_chunk_offset = in;
    ap->bits = bits;
    if (left){
        memcpy(ap->window, window + WINSIZE - left, left);
    }
    if (left < WINSIZE){
        memcpy(ap->window + left, window, WINSIZE - left);
    }
}

int GzipFile::uncompress_file(File *outFile){
    return 0;
}


int GzipFile::build_access_point(){
    int ret;
    off_t file_total_in, original_total_out; 
    off_t original_last;
    z_stream strm;
    unsigned char input[CHUNK];
    unsigned char window[WINSIZE];

    /* initialize inflate */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm, 47);      /* automatic zlib or gzip decoding */
    if (ret != Z_OK){
        return ret;
    }
    file_total_in = 0;
    original_total_out = 0;
    original_last = 0;
    strm.avail_out = 0;

    do {
        /* get some compressed data from input file */
        strm.avail_in = File::read((char *)input,CHUNK);
        if (strm.avail_in < 0){
            ret = Z_ERRNO;
            goto build_index_error;
        }
        if (strm.avail_in == 0) {
            ret = Z_DATA_ERROR;
            goto build_index_error;
        }

        strm.next_in = input;
        /* process all of that, or until end of stream */
        do {
            /* reset sliding window if necessary */
            if (strm.avail_out == 0) {
                strm.avail_out = WINSIZE;
                strm.next_out = window;
            }

            /* inflate until out of input, output, or at end of block --
               update the total input and output counters */
            file_total_in += strm.avail_in;
            original_total_out += strm.avail_out;
            ret = inflate(&strm, Z_BLOCK);      /* return at end of block */
            file_total_in -= strm.avail_in;
            original_total_out -= strm.avail_out;

            if (ret == Z_NEED_DICT){
                ret = Z_DATA_ERROR;
            }
            if (ret == Z_MEM_ERROR || ret == Z_DATA_ERROR){
                printf("get z mem error or z data error \n");
                goto build_index_error;
            }
            if (ret == Z_STREAM_END){
                break;
            }
            printf("strm.data_type = %d,original_total_out = %ld ,file_total_in = %ld  \n",strm.data_type,original_total_out,file_total_in);

            if ((strm.data_type & 128) && !(strm.data_type & 64) &&
                    (original_total_out == 0 || original_total_out - original_last > SPAN)) {

                access_point_t *access_point = (access_point_t *)malloc(sizeof(access_point_t));
                if(access_point == NULL){
                    printf("allocate access point failed \n");
                    goto build_index_error;
                }
                memset(access_point,0,sizeof(access_point_t));
                init_list_head(&(access_point->list));
                set_access_point(access_point, strm.data_type & 7, file_total_in,original_total_out, 
                        strm.avail_out, window);
                insert_list_item_behind(&access_point_list,&(access_point->list));
                original_last = original_total_out;

            }
        } while (strm.avail_in != 0);
    } while (ret != Z_STREAM_END);

    /* clean up and return index (release unused entries in list) */
    (void)inflateEnd(&strm);

    /* return error */
build_index_error:
    (void)inflateEnd(&strm);
    return ret;
}
