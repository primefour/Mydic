#ifndef __BIT_TREE_H__ 
#define __BIT_TREE_H__
typedef int (*compare_func)(const void *data1,const void *data2);
typedef void (*destory_func)(void *data);

typedef struct bin_tree_t{
    int size ;
    compare_func fpn_compare;
    destory_func fpn_destory;
    tree_node_t *root;
}bin_tree_t;


typedef struct tree_node_t{
    struct tree_node_t *left;
    struct tree_node_t *right;
    void *data;
}tree_node_t;

void bin_tree_init(bin_tree_t *tree,compare_func compare,destroy_func destory);
void bin_tree_destroy(bin_tree_t *tree);
void bin_tree_remove_left(bin_tree_t *tree,tree_node_t *node);
void bin_tree_remove_right(bin_tree_t *tree,tree_node_t *node);
int bin_tree_merge(bin_tree_t *merge,bin_tree_t *left,bin_tree_t *right,const void *data);
int bin_tree_insert_left(bin_tree_t *tree,tree_node_t *node,const void *data);
int bin_tree_insert_right(bin_tree_t *tree,tree_node_t *node,const void *data);
int bin_tree_size(const bin_tree_t *tree);
int bin_tree_isleaf(const tree_node_t *node);
tree_node_t* bin_tree_root(const  bin_tree_t *tree);
int bin_tree_ins_left(bin_tree_t *tree,tree_node_t *node,const void *data);
/*
 * create a new node with the value of data and insert to the node's right 
 * if node's right is not NULL will return -1
 */
int bin_tree_ins_right(bin_tree_t *tree,tree_node_t *node,const void *data);

#endif 

