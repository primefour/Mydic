#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"


void GoldenWordHashList::DictHashInsert(SObject<WordIdxItem> &newItem){
    word_hash.DictHashInsert(newItem);
}

bool GoldenWordHashList::DictHashfind(const SObject<WordIdxItem> &item){
    word_hash.DictHashfind(item);
}

const SObject<WordIdxItem>& GoldenWordHashList::DictHashGet(const SObject<WordIdxItem>&item){
    return word_hash.DictHashGet(item);
}


GoldenWordHashList::GoldenWordHashList(int max_count):word_hash(max_count){

}

