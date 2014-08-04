#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
#include"BinTree.h"

enum{
    WEIGHT_LEFT_HEAVY =1,
    WEIGHT_BALANCE = 0,
    WEIGHT_RIGHT_HEAVY =-1
};



typedef struct avl_node_t {
    int weight;
    int hide;
    void *data;
}avl_node_t;


void avl_tree_remove(bin_tree_t *tree,tree_node_t *node,void *data);
void avl_tree_find(bin_tree_t *tree,tree_node_t *node,void *data,void **find_item);
void avl_tree_destroy(bin_tree_t *tree);
void avl_tree_insert(bin_tree_t *tree,tree_node_t **node,void *data,int *balance);
void avl_tree_init(bin_tree_t *tree,bin_compare_func compare,destroy_func destroy,dump_data_func dump_data);
void avl_tree_layer_scan(bin_tree_t *tree,tree_node_t **node_parent);

#endif //__AVL_TREE_H__
