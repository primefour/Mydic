#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"GzipHeaderParser.h"
#include"GzipDeflate.h"


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
    
    StardictInfo si(ifo_path);
    StardictIdx sidx(idx_path,si.getWordCount(),si.getIdxFileSize(),si.getOffsetBits());
    WordIdxItem wii = sidx.getIdxWord("hello");
    wii.dumpInfo(); 

    wii = sidx.getIdxWord("a");
    wii.dumpInfo(); 
/*
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
    //GZipHeader cetmpHeader(ce_dict_path);
    int chnum,chlen,version;
    tmpHeader.getExtraInfo(chnum,chlen,version);
    printf("chnum = %d chlen = %d version = %d \n",chnum,chlen,version);
    int offset = wii.data_offset;
    int len = wii.data_size;

    unsigned char *gbuff = new unsigned char[len];
    memset(gbuff,0,len);
    GzipDeflate tmpInflate(dict_path);
    tmpInflate.Seek(SEEK_SET,offset);
    tmpInflate.Read(gbuff,len);
    int fd = open("./tmp.file",O_CREAT|O_RDWR,0666);
    if(fd < 0){
        perror("hello world ");
        printf("open failed \n");
    }
    write(fd,gbuff,len);
    /*
    dictData *dd = dict_data_open(dict_path,0); 
    char *ddstr = dict_data_read_ (dd,offset,len,NULL,NULL);
    printf("ddstr = %s \n",ddstr);
    */

    return 0;
}
