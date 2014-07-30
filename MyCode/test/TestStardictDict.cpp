#include "StardictIdx.h"
#include "StardictInfo.h"
#include "StardictDict.h"
#include"GzipFile.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>



int main(){
    File::add_check_func(GzipFile::check_file_type,GZIP_FILE_TYPE);
    StardictInfo *si = new StardictInfo("langdao-ec-gb.ifo");
    si->init();
    si->dump();
    StardictIdx *sidx = new StardictIdx("langdao-ec-gb.idx",si->get_word_count(),si->get_idx_file_size());
    int ret = sidx->init();
    printf("##########################ret = %d    \n",ret);
    word_item_t *tmp = sidx->get_word("hello");
    if(tmp != NULL){
        printf("word = %s offset %d ,length %d  \n",tmp->word_str,tmp->word_data_offset.bit32,tmp->word_data_size);
    }else{
        printf("can't find the word \n");
    }
    StardictDict *sd = new StardictDict("langdao-ec-gb.dict.dz",si->get_same_types_sequence());
    ret = sd->init();
    printf("ret = %d \n",ret);
    meta_data_head *tmp_head = get_new_meta_head();
    tmp_head->original_offset = tmp->word_data_offset.bit32;
    tmp_head->data_size = tmp->word_data_size;
    sd->read_word_data(tmp_head);
    dump_meta_head(tmp_head);

    return 0;
}
