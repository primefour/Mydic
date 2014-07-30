#include "StardictIdx.h"
#include "StardictInfo.h"
#include "StardictDict.h"


int main(){
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

    return 0;
}
