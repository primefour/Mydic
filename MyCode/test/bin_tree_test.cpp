#include"bin_tree.h"
#include<stdio.h>



void dump_test_data(void *data){
    int tmp = (int)data;
    printf(" %d ",tmp);
}



int main(){
    bin_tree_t test_tree;
    bin_tree_init(&test_tree,NULL,NULL,dump_test_data);
    bin_tree_ins_left(&test_tree,NULL,0);
    return 0;
}
