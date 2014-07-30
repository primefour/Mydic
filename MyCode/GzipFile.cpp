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
    position = 0;
    original_file_size = 0;
    init_access_point_list();
}

GzipFile::~GzipFile(){
    reset_access_point_list();
}


int GzipFile::check_file_type(unsigned char *buf,int *len){
    if(*len < 2){
        *len = 2;
        return 0;
    }
    unsigned char *ptr = (unsigned char *)buf;
    if (*ptr == ID1_VALUE && *(ptr+1)== ID2_VAlUE) {
        return 1;
    }else{
        return 0;
    }
}


int GzipFile::readline(unsigned char *buf,int len){
    printf("%s,%s\n",__FILE__,__func__);
    unsigned char rbuff[1024] = {0};
    int j = 0;
    int i = 0;
    int ret = 0;
    while(j < len){
        memset(rbuff,0,sizeof(rbuff));
        ret = read(rbuff,sizeof(rbuff));
        if(ret < 0){
            printf("read line error \n");
            return ret;
        }else if(ret == 0){
            printf("read end of file  \n");
            return ret;
        }
        i = 0;
        while(i < ret && j < len && rbuff[i] != '\0' && rbuff[i] != '\n'){
            buf[j] = rbuff[i];
            i++;
            j++;
        }
        if(i < ret ){
            position = position - ret + i + 1;
            //get line complete
            break;
        }
    }
    if(j >= len){
        return len;
    }else{
        return j + 1;
    }
}


int GzipFile::lseek(int whence,int offset){
    printf("%s,%s\n",__FILE__,__func__);
    if(whence == SEEK_SET){
        if(offset >  original_file_size){
            return -1;
        }
        position = offset;
    }else if(whence == SEEK_CUR){
        if(position + offset > original_file_size){
            return -1;
        }
        position += offset;
    }else{
        if(original_file_size + offset > original_file_size){
            return -1;
        }
        position = original_file_size + offset;
    }
    return position;
}


int GzipFile::write(const unsigned char *buf,int len){
    printf("%s,%s\n",__FILE__,__func__);
    return -1;
}


int GzipFile::read(unsigned char *buf,int len){
    printf("%s,%s\n",__FILE__,__func__);
    int ret = extract(position,buf,len);
    if(ret > 0){
        position += ret;
    }
    printf("gzipfile read ret = %d ####################\n",ret);
    return ret;
}


int GzipFile::open(int mode){
    if(is_open()){
        return 0;
    }
    int ret = File::open(O_RDWR);
    if(ret < 0){
        return -1;
    }
    position = 0;
    original_file_size = 0;
    ret = build_access_point();
    printf("build_access_point ret = %d \n",ret);
    return ret;
}





void GzipFile::set_access_point(access_point_t *ap,int bits, off_t in, off_t out,int chunk_size,
                                                unsigned left, unsigned char *window)
{
    printf("in = %ld,out =%ld \n",in,out);
    ap->original_end = out;
    //ap->chunk_size = chunk_size;
    ap->file_chunk_offset = in;
    ap->bits = bits;
    if (left){
        memcpy(ap->window, window + WINSIZE - left, left);
    }
    if (left < WINSIZE){
        memcpy(ap->window + left, window, WINSIZE - left);
    }
}


#define DATA_CACHE_SIZE 1024
int GzipFile::uncompress_file(File *outFile){
    int ret = 0;
    unsigned char input[DATA_CACHE_SIZE]; 
    unsigned char output[DATA_CACHE_SIZE];
    z_stream strm;
    /* initialize inflate */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm, 47);
    if (ret != Z_OK){
        return ret;
    }
    File::lseek(SEEK_SET,0);
    do {
        /* get some compressed data from input file */
        strm.avail_in = File::read(input,DATA_CACHE_SIZE);
        if (strm.avail_in < 0){
            printf("file read fail \n");
            ret = -1;
            break;
        }
        //should not get zero
        if (strm.avail_in == 0) {
            printf("file get end \n");
            ret = -1;
            break;
        }
        strm.next_in = input;
        /* process all of that, or until end of stream */
        do {
            strm.avail_out = DATA_CACHE_SIZE;
            strm.next_out = output;
            /* inflate until out of input, output, or at end of block --
               update the total input and output counters */
            ret = inflate(&strm, Z_BLOCK);      /* return at end of block */

            if (ret == Z_NEED_DICT){
                printf("ret == Z_NEED_DICT ####\n");
                ret = -1;
                break;
            }
            if (ret == Z_MEM_ERROR || ret == Z_DATA_ERROR){
                printf("get z mem error or z data error \n");
                ret = -1;
            }
            if (ret == Z_STREAM_END){
                ret = 0;
                break;
            }
            if(strm.avail_out != DATA_CACHE_SIZE){
                outFile->write(output,DATA_CACHE_SIZE - strm.avail_out);
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
    File::lseek(SEEK_SET,0);
    original_file_size = 0;
    do {
        /* get some compressed data from input file */
        strm.avail_in = File::read(input,CHUNK);
        if (strm.avail_in < 0){
            ret = Z_ERRNO;
            goto build_index_error;
        }
        if (strm.avail_in == 0) {
            printf("#######################################build index error\n");
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
            //printf("strm.data_type = %d,original_total_out = %ld ,file_total_in = %ld  \n",strm.data_type,original_total_out,file_total_in);

            if ((strm.data_type & 128) && !(strm.data_type & 64) &&
                    (original_total_out == 0 || original_total_out - original_last > SPAN)) {

                access_point_t *access_point = (access_point_t *)malloc(sizeof(access_point_t));
                if(access_point == NULL){
                    printf("allocate access point failed \n");
                    goto build_index_error;
                }
                memset(access_point,0,sizeof(access_point_t));
                init_list_head(&(access_point->list));
                //printf("original_total_out = %ld \n",original_total_out);
                set_access_point(access_point,strm.data_type & 7,
                                    file_total_in,original_total_out,original_total_out - original_last,
                                    strm.avail_out, window);
                insert_list_item_ahead(&access_point_list,&(access_point->list));
                original_last = original_total_out;

            }
        } while (strm.avail_in != 0);
    } while (ret != Z_STREAM_END);
    original_file_size = original_total_out;
    (void)inflateEnd(&strm);
    /* return error */
build_index_error:
    printf("###################%s %d \n",__func__,__LINE__);
    File::lseek(SEEK_SET,0);
    (void)inflateEnd(&strm);
    return ret;
}


int GzipFile::access_piont_compare(list_head_t *item1,void *data){
    access_point_t *list_item = contain_of(item1,access_point_t,list);
    off_t offset = *((off_t *)data);

    printf("list_item->original_end = %d ,offset = %ld \n",list_item->original_end,offset);
    if(list_item->original_end > offset){ 
        printf("OK in = %d ,out = %d \n",list_item->file_chunk_offset,list_item->original_end);
        return 0;
    }else{
        printf("in = %d ,out = %d \n",list_item->file_chunk_offset,list_item->original_end);
        return 1;
    }
}



int GzipFile::extract(off_t offset,unsigned char *buf, int len){
    int ret, skip;
    z_stream strm;
    unsigned char input[CHUNK];
    unsigned char discard[WINSIZE];

    /* proceed only if something reasonable to do */
    if (len < 0){
        return 0;
    }
    printf("offset = %ld \n",offset);

    list_head_t *find_item = find_list_item(&access_point_list,&offset,access_piont_compare);
    if(find_item == NULL){
        printf("can't find the offset in the list\n");
        return -1;
    }
    find_item = find_item->prev;
    access_point_t *first_item = contain_of(find_item,access_point_t,list);
    printf("first item in = %d ,out = %d \n",first_item->file_chunk_offset,first_item->original_end);
    /* initialize file and inflate state to start there */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm, -15);         /* raw inflate */
    if (ret != Z_OK){
        return ret;
    }
    ret = File::lseek(SEEK_SET,first_item->file_chunk_offset - (first_item->bits ? 1 : 0));
    if (ret == -1){
        goto extract_ret;
    }
    if (first_item->bits) {
        ret = File::read((unsigned char *)(&ret),1);
        if (ret == -1) {
            goto extract_ret;
        }
        (void)inflatePrime(&strm, first_item->bits, ret >> (8 - first_item->bits));
    }
    (void)inflateSetDictionary(&strm, first_item->window, WINSIZE);

    /* skip uncompressed bytes until offset reached, then satisfy request */
    offset -= first_item->original_end;
    strm.avail_in = 0;
    skip = 1;                               /* while skipping to offset */
    do {
        /* define where to put uncompressed data, and how much */
        if (offset == 0 && skip) {          /* at offset now */
            strm.avail_out = len;
            strm.next_out = buf;
            skip = 0;                       /* only do this once */
        }
        if (offset > WINSIZE) {             /* skip WINSIZE bytes */
            strm.avail_out = WINSIZE;
            strm.next_out = discard;
            offset -= WINSIZE;
        } else if (offset != 0) {             /* last skip */
            strm.avail_out = (unsigned)offset;
            strm.next_out = discard;
            offset = 0;
        }
        //printf("###################################%d ",__LINE__);
        /* uncompress until avail_out filled, or end of stream */
        do {
            if (strm.avail_in == 0) {
                strm.avail_in = File::read(input,CHUNK);
                if (strm.avail_in < 0 ) {
                    ret = Z_ERRNO;
                    goto extract_ret;
                }
                if (strm.avail_in == 0) {
                    ret = Z_DATA_ERROR;
                    goto extract_ret;
                }
                strm.next_in = input;
            }
            ret = inflate(&strm, Z_NO_FLUSH);       /* normal inflate */
            if (ret == Z_NEED_DICT)
                ret = Z_DATA_ERROR;
            if (ret == Z_MEM_ERROR || ret == Z_DATA_ERROR)
                goto extract_ret;
            if (ret == Z_STREAM_END)
                break;
        } while (strm.avail_out != 0);

        /* if reach end of stream, then don't keep trying to get more */
        if (ret == Z_STREAM_END)
            break;

        /* do until offset reached and requested data read, or stream ends */
    } while (skip);

    /* compute number of uncompressed bytes read after offset */
    ret = skip ? 0 : len - strm.avail_out;

    /* clean up and return bytes read or error */
  extract_ret:
    (void)inflateEnd(&strm);
    return ret;
}