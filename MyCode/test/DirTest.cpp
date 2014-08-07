#include<stdio.h>
#include<stdlib.h>
#include"DirectoryUtils.h"
int main(){
    DirectoryScanner *ds = new DirectoryScanner();
    ds->processDirectory("/home/crazyhorse/test/golden_dic/MyDict/MyCode/test");
    ds->DumpFileList();
    return 0;
}
