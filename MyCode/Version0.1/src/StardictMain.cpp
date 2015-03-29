#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"GzipHeaderParser.h"


int dumpString(String8 a){
    if(!a.isEmpty()){
        printf("xxxxxx %s \n",a.string());
    }else{
        printf("xxxx is empty string \n");
    }
}
const char *ifo_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.ifo";
const char *idx_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.idx";
const char *dict_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.dict.dz";

const char *ce_ifo_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.ifo";
const char *ce_idx_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.idx";
const char *ce_dict_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.dict.dz";


int main(int argc,char **argv){
   /* 
    StardictInfo si(ifo_path);
    StardictIdx sidx(idx_path,si.getWordCount(),si.getIdxFileSize(),si.getOffsetBits());
    WordIdxItem wii = sidx.getIdxWord("hello");
    wii.dumpInfo(); 

    wii = sidx.getIdxWord("world");
    wii.dumpInfo(); 

    wii = sidx.getIdxWord("纵隔面");
    wii.dumpInfo(); 

    wii = sidx.getIdxWord("HelloWorld");
    printf("%s %d \n",__func__,__LINE__);
    wii.dumpInfo(); 

    
    StardictInfo ce_si(ce_ifo_path);
    StardictIdx ce_sidx(ce_idx_path,ce_si.getWordCount(),ce_si.getIdxFileSize(),ce_si.getOffsetBits());
    WordIdxItem ce_wii = ce_sidx.getIdxWord("纵隔面");
    ce_wii.dumpInfo(); 
    */
    GZipHeader tmpHeader(dict_path);
    GZipHeader cetmpHeader(ce_dict_path);
    return 0;
}
