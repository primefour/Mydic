#include"BinTree.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"memory_test_tool.h"
#include"AvlTree.h"


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
    /*
    init_global_env();
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
    */
    
    /*
     *                                    10
     *                                 0      15
     *                              -1      13    17
     *                            -3      11  14     18 
     *                                      12          19
     */

/*
    bin_tree_t simple_test_tree;
    bin_tree_init(&simple_test_tree,compare_test,NULL,dump_test_data);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)10);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)10);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)0);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)-1);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)-3);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)15);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)13);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)11);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)12);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)14);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)17);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)18);
    bin_tree_simple_search_insert(&simple_test_tree,NULL,(void *)19);

    memset(parent,0,sizeof(parent));
    parent[0] = bin_tree_root(&simple_test_tree);
    bin_tree_layer_scan(&simple_test_tree,parent);
    printf("tree size = %d \n",bin_tree_size(&simple_test_tree));
    find_item = NULL;
    bin_tree_simple_search_fine(&simple_test_tree,NULL,(void*)-1,&find_item);
    if(find_item != NULL){
        printf(" **%ld** \n",(long)(find_item->data));
    }
    bin_tree_simple_search_remove(&simple_test_tree,NULL,NULL,(void*)15);
    //bin_tree_simple_search_fine(&simple_test_tree,NULL,(void*)19,&find_item);
    if(find_item != NULL){
        printf(" **%ld** \n",(long)(find_item->data));
    }

    parent[0] = bin_tree_root(&simple_test_tree);
    bin_tree_layer_scan(&simple_test_tree,parent);
    printf("tree size = %d \n",bin_tree_size(&simple_test_tree));
*/
    bin_tree_t avl_test_tree;
    int balance = 1;
    avl_tree_init(&avl_test_tree,compare_test,NULL,dump_test_data);
    printf("%s   %d \n",__func__,__LINE__);
    //avl_tree_insert(bin_tree_t *tree,tree_node_t **node,const void *data,int *balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)10,&balance);
    printf("%s   %d \n",__func__,__LINE__);
    avl_tree_insert(&avl_test_tree,NULL,(void *)10,&balance);
    printf("%s   %d \n",__func__,__LINE__);
    avl_tree_insert(&avl_test_tree,NULL,(void *)0,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)-1,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)-3,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)15,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)13,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)11,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)12,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)14,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)17,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)18,&balance);
    avl_tree_insert(&avl_test_tree,NULL,(void *)19,&balance);
    printf("%s   %d \n",__func__,__LINE__);
    tree_node_t *parent[2]={0};
    parent[0] = bin_tree_root(&avl_test_tree);
    avl_tree_layer_scan(&avl_test_tree,parent);
   /* 
    bin_tree_destroy(&test_tree);
    bin_tree_destroy(&simple_test_tree);
    release_global_env();
    */
    return 0;
}
