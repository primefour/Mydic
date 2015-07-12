#include"GoldenWordIndexItem.h"
#include"GoldenHashSet.h"
#include"GoldenRef.h"


void GoldenWordHashList::DictHashInsert(SObject<WordIdxItem> &newItem){
    word_hash.DictHashInsert(newItem);
}


GoldenWordHashList::GoldenWordHashList(int max_count):word_hash(max_count){

}

