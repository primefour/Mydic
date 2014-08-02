#include<string.h>
#include<stdlib.h>
#include"memory_test_tool.h"

int main(){
    init_global_env();
    char *tmp = (char *)malloc(10);
    free(tmp);
    tmp = (char *)malloc(10);
    free(tmp);
    tmp = (char *)malloc(10);
    free(tmp);
    const char *hello_world = "hello world";
    tmp = strdup(hello_world);
    free(tmp);
    release_global_env();
    return 0;
}
