#include<stdio.h>
#include"StardictMain.h"
#include"GoldenDictLog.h"

#if 0
const char *ifo_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.ifo";
const char *idx_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.idx";
const char *dict_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ec-gb.dict.dz";

const char *ce_ifo_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.ifo";
const char *ce_idx_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.idx";
const char *ce_dict_path = "/home/crazyhorse/MyProject/GoldenDict/GitDict/MyCode/Version0.1/bin/langdao-ce-gb.dict.dz";
#else
const char *ifo_path = "./bin/langdao-ec-gb.ifo";
const char *idx_path = "./bin/langdao-ec-gb.idx";
const char *dict_path = "./bin/langdao-ec-gb.dict.dz";

const char *ce_ifo_path = "./bin/langdao-ce-gb.ifo";
const char *ce_idx_path = "./bin/langdao-ce-gb.idx";
const char *ce_dict_path = "./bin/langdao-ce-gb.dict.dz";
#endif


int main(){
    static StardictMain* pDictMain = NULL ;
    pDictMain = new StardictMain();
    pDictMain->InsertDict(ifo_path);
    char buff[1024]={0};
    TextMetaData tmd;

    while(1){
        scanf("%s",buff);
        golden_printfd("####query word is %s \n",buff);
        pDictMain->getDictIdx(0)->DictQuery(buff,&tmd);

        golden_printfd("####begin\n");
        tmd.dumpInfo();
        golden_printfd("####end\n");

    }
    return 0;
}
