#include"BinTree.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int compare_test(const void *data1,const void *data2){
    long value1 = (long)data1;
    long value2 = (long)data2;
    if(value1 == value2){
        return 0;
    }else if(value1 > value2){
        return 1;
    }else{
        return -1;
    }
}

void dump_test_data(void *data){
    long tmp = (long)data;
    printf(" ##%ld## ",tmp);
}
/*                                   1
 *                        3                      2
 *                 5            4          6            7 
 *                                     8                    9
 */


int main(){
    bin_tree_t test_tree;
    bin_tree_init(&test_tree,compare_test,NULL,dump_test_data);
    int ret = bin_tree_ins_left(&test_tree,NULL,(void *)1);
    printf("line %d ret = %d \n",__LINE__,ret);
    ret = bin_tree_ins_left(&test_tree,bin_tree_root((&test_tree)),(void *)3);
    printf("line %d ret = %d \n",__LINE__,ret);
    ret = bin_tree_ins_right(&test_tree,bin_tree_root((&test_tree)),(void *)2);
    printf("line %d ret = %d \n",__LINE__,ret);
    tree_node_t *find_item = NULL;
    bin_tree_find_node(&test_tree,bin_tree_root((&test_tree)),(void*)3,&find_item);
    if(find_item){
        ret = bin_tree_ins_right(&test_tree,find_item,(void *)4);
        printf("line %d ret = %d \n",__LINE__,ret);
    }else{
        printf("can't find the item \n");
    }

    find_item = NULL;
    bin_tree_find_node(&test_tree,bin_tree_root((&test_tree)),(void*)3,&find_item);
    if(find_item){
        ret = bin_tree_ins_left(&test_tree,find_item,(void *)5);
        printf("line %d ret = %d \n",__LINE__,ret);
    }else{
        printf("can't find the item \n");
    }

    find_item = NULL;
    bin_tree_find_node(&test_tree,bin_tree_root((&test_tree)),(void*)2,&find_item);
    if(find_item){
        ret = bin_tree_ins_left(&test_tree,find_item,(void *)6);
        printf("line %d ret = %d \n",__LINE__,ret);
    }else{
        printf("can't find the item \n");
    }

    find_item = NULL;
    bin_tree_find_node(&test_tree,bin_tree_root((&test_tree)),(void*)2,&find_item);
    if(find_item){
        ret = bin_tree_ins_right(&test_tree,find_item,(void *)7);
        printf("line %d ret = %d \n",__LINE__,ret);
    }else{
        printf("can't find the item \n");
    }


    find_item = NULL;
    bin_tree_find_node(&test_tree,bin_tree_root((&test_tree)),(void*)6,&find_item);
    if(find_item){
        ret = bin_tree_ins_left(&test_tree,find_item,(void *)8);
        printf("line %d ret = %d \n",__LINE__,ret);
    }else{
        printf("can't find the item \n");
    }


    find_item = NULL;
    bin_tree_find_node(&test_tree,bin_tree_root((&test_tree)),(void*)7,&find_item);
    if(find_item){
        ret = bin_tree_ins_right(&test_tree,find_item,(void *)9);
        printf("line %d ret = %d \n",__LINE__,ret);
    }else{
        printf("can't find the item \n");
    }

    bin_tree_midorder_scan(&test_tree,bin_tree_root((&test_tree)));
    printf("\n");
    bin_tree_preorder_scan(&test_tree,bin_tree_root((&test_tree)));
    printf("\n");
    bin_tree_postorder_scan(&test_tree,bin_tree_root((&test_tree)));
    printf("\n");
    tree_node_t *parent[2]={0};
    parent[0] = bin_tree_root(&test_tree);
    bin_tree_layer_scan(&test_tree,parent);
    /*
     *                                    10
     *                                 0      15
     *                              -1      13    17
     *                            -3      11  12     18 
     */

    bin_tree_t simple_test_tree;
    bin_tree_init(&simple_test_tree,compare_test,NULL,dump_test_data);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)10);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)10);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)0);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)-1);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)-3);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)15);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)13);

    memset(parent,0,sizeof(parent));
    parent[0] = bin_tree_root(&simple_test_tree);
    bin_tree_layer_scan(&simple_test_tree,parent);
    printf("tree size = %d \n",bin_tree_size(&simple_test_tree));
    find_item = NULL;
    bin_tree_simple_search_fine(&simple_test_tree,NULL,(void*)-1,&find_item);
    if(find_item != NULL){
        printf(" **%ld** \n",(long)(find_item->data));
    }



    return 0;

}
