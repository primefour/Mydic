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
    access_point = NULL;
}

GzipFile::~GzipFile(){
    reset_access_point();
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

int GzipFile::reset_access_point(){
    access_point_t *tmp;
    while(access_point != NULL){
        tmp = access_point->next;
        free(access_point);
        access_point = tmp;
    }
    access_point = NULL;
}

void GzipFile::set_access_point(access_point_t *ap,int bits, off_t in, off_t out, 
                                                unsigned left, unsigned char *window)
{

    ap->original_offset = out;
    ap->file_chunk_offset = in;
    ap->bits = bits;

    if (left)
        memcpy(next->window, window + WINSIZE - left, left);
    if (left < WINSIZE)
        memcpy(next->window + left, window, WINSIZE - left);
    index->have++;

    /* return list, possibly reallocated */
    return index;
}


int GzipFile::build_access_point(){


    reset_access_point();
    access_point = (access_point_t *)malloc(sizeof(access_point_t));
    if(access_point == NULL){
        return -1;
    }

    memset(access_point,0,sizeof(access_point_t));

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
        strm.avail_in = File::read(input,CHUNK);
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
                goto build_index_error;
            }
            if (ret == Z_STREAM_END){
                break;
            }

            if ((strm.data_type & 128) && !(strm.data_type & 64) &&
                (original_total_out == 0 || original_total_out - original_last > SPAN)) {

                index = addpoint(index, strm.data_type & 7, totin,
                                 totout, strm.avail_out, window);

                last = original_total_out;
            }
        } while (strm.avail_in != 0);
    } while (ret != Z_STREAM_END);

    /* clean up and return index (release unused entries in list) */
    (void)inflateEnd(&strm);
    index->list = realloc(index->list, sizeof(struct point) * index->have);
    index->size = index->have;
    *built = index;
    return index->size;

    /* return error */
  build_index_error:
    (void)inflateEnd(&strm);
    if (index != NULL)
        free_index(index);
    return ret;


}
