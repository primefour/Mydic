#include<stdio.h>
#include"GoldenDictManager.h"
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
    static GoldenDictManager goldenDict;
    goldenDict.GoldenDictAdd(ifo_path);

    char buff[1024]={0};
    char queryResult[4096]={0};
    while(1){
        scanf("%s",buff);
        golden_printfd("####query word is %s \n",buff);
        memset(queryResult,0,sizeof(queryResult));
        goldenDict.GoldenDictQuery(buff,queryResult);
        golden_printfd("####%s \n",queryResult);
    }
    return 0;
}
