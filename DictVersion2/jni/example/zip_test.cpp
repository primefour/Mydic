#include<stdio.h>
#include"GoldenZipTool.h"


int main(){
    GoldenZipTool tmp("./hello.zip");
    tmp.ReleaseAllFiles();

    return 0;
}
