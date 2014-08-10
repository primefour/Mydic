#include "StardictInfo.h"
#include"memory_test_tool.h"

int main(){
    init_global_env();
    StardictInfo *si = new StardictInfo("langdao-ec-gb.ifo");
    si->init();
    si->dump();
    delete si;
    release_global_env();
    return 0;
}
