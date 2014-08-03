#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
#include"BinTree.h"

typedef enum{
    WEIGHT_LEFT_HEAVY =1,
    WEIGHT_BALANCE = 0,
    WEIGHT_RIGHT_HEAVY =-1
};



typedef struct avl_node_t {
    int weight;
    int hide;
    void *data;
}avl_node_t;

void avl_tree_insert
void avl_tree_find
void avl_tree_remove
void avl_tree_destroy
void avl_tree_init

#endif //__AVL_TREE_H__
