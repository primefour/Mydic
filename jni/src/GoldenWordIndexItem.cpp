#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"


void GoldenWordHashList::WordInsert(SObject<WordIdxItem> &newItem){
    word_hash.DictHashInsert(newItem);
}

bool GoldenWordHashList::WordFind(const SObject<WordIdxItem> &item){
    word_hash.DictHashfind(item);
}

const SObject<WordIdxItem>& GoldenWordHashList::WordGet(SObject<WordIdxItem>&item){
    return word_hash.DictHashGet(item);
}


GoldenWordHashList::GoldenWordHashList(int max_count):word_hash(max_count){

}




void GoldenWordTriTree::WordInsert(SObject<WordIdxItem> &newItem){
    TriString8 tmp = TriString8(newItem->idx_word.string());
    TriNode<char,TriLeaves>* tmp_node = Root.InsertData(tmp);
    TriLeaves tl(newItem->data_offset,newItem->data_size);
    tmp_node->InsertLeaves(tl);
}

bool GoldenWordTriTree::WordFind(const SObject<WordIdxItem> &item){
    TriString8 tmp = TriString8(item->idx_word.string());
    TriNode<char,TriLeaves> *kk = Root.FindData(tmp);
    if(kk != NULL){
        vector<TriLeaves> tt = kk->GetLeaves();
        if(tt.size() != 0){
            return true;
        }
    }
    return false;
}

const SObject<WordIdxItem>& GoldenWordTriTree::WordGet(SObject<WordIdxItem>&item){
    TriString8 tmp = TriString8(item->idx_word.string());
    TriNode<char,TriLeaves> *kk = Root.FindData(tmp);
    vector<TriLeaves> tt = kk->GetLeaves();
    if(tt.size() != 0){
        item->data_offset = tt[0].offset;
        item->data_size = tt[0].size;
    }
    return item;
}

GoldenWordTriTree::GoldenWordTriTree(){

}

