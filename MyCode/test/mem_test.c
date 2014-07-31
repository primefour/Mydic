#include"memory_test_tool.h"

int main(){
    init_global_env();
    char *tmp = (char *)tools_malloc(10,__FILE__,__LINE__);
    tools_free(tmp);
    tmp = (char *)tools_malloc(10,__FILE__,__LINE__);
    tools_free(tmp);
    tmp = (char *)tools_malloc(10,__FILE__,__LINE__);
    tools_free(tmp);
    const char *hello_world = "hello world";
    tmp = tools_strdup(hello_world,__FILE__,__LINE__);
    tools_free(tmp);
    release_global_env();
    return 0;
}
