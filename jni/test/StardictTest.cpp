#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
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
    goldenDict.GoldenScanDisk("./bin");//"/home/crazyhorse/test/golden_dic/MyDict/jni/bin/CollinsCOBUILD-BL");//"./bin");
    /*
    const char **dictList = (const char **)malloc(sizeof(const char *) * 20);
    memset(dictList,0,sizeof(const char *) * 20);

    goldenDict.GoldenDictGetDicts(dictList);
    const char **tmp = dictList ;
    while(*tmp != NULL){
        golden_printfe(" ###### %s  \n",*tmp );
        tmp ++;
    }

    tmp = dictList;
    while(*tmp != NULL){
        golden_printfe("begin remove dict %s  \n",*tmp);
        goldenDict.GoldenDictRemoveDict(*tmp);
        golden_printfe("end remove dict %s  \n",*tmp);
        tmp ++;
    }

    tmp = dictList;
    while(*tmp != NULL){
        golden_printfe("begin add dict %s  \n",*tmp);
        goldenDict.GoldenDictAddDict(*tmp);
        golden_printfe("end add dict %s  \n",*tmp);
        tmp ++;
    }
    
    golden_printfe("GoldenDictPersist\n");
    goldenDict.GoldenDictPersist();
    golden_printfe("end GoldenDictPersist\n");
    goldenDict.GoldenDictReload();
    golden_printfe("end GoldenDictReloa\n");

    char buff[1024]={0};
    char queryResult[409600]={0};
    while(1){
        scanf("%s",buff);
        golden_printfd("####query word is %s \n",buff);
        memset(queryResult,0,sizeof(queryResult));
        goldenDict.GoldenDictQuery(buff,queryResult);
        golden_printfd("####%s \n",queryResult);
    }
    */
    sleep(50);
    return 0;
}
