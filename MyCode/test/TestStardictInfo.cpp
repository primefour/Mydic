#include "StardictInfo.h"


int main(){
    StardictInfo *si = new StardictInfo("langdao-ec-gb.ifo");
    si->init();
    si->dump();
    delete si;
    return 0;
}
