#ifndef __BIT_TREE_H__ 
#define __BIT_TREE_H__

typedef int (*bin_compare_func)(const void *data1,const void *data2);
typedef void (*destroy_func)(void *data);
typedef void (*dump_data_func)(void *data);

typedef struct tree_node_t{
    struct tree_node_t *left;
    struct tree_node_t *right;
    int weight;
    void *data;
}tree_node_t;

typedef struct bin_tree_t{
    int size ;
    bin_compare_func fpn_compare;
    destroy_func fpn_destory;
    dump_data_func fpn_dump_data;
    tree_node_t *root;
}bin_tree_t;


void bin_tree_init(bin_tree_t *tree,bin_compare_func compare,destroy_func destory,dump_data_func dump_data);
void bin_tree_destroy(bin_tree_t *tree);
void bin_tree_remove_left(bin_tree_t *tree,tree_node_t *node);
void bin_tree_remove_right(bin_tree_t *tree,tree_node_t *node);
void bin_tree_insert_left(bin_tree_t *tree,tree_node_t *node,void *data);
void bin_tree_insert_right(bin_tree_t *tree,tree_node_t *node,void *data);

int bin_tree_merge(bin_tree_t *merge,bin_tree_t *left,bin_tree_t *right,void *data);
int bin_tree_size(const bin_tree_t *tree);
int bin_tree_isleaf(const tree_node_t *node);
//#define bin_tree_root(tree) (tree->root)
tree_node_t* bin_tree_root(const  bin_tree_t *tree);
int bin_tree_ins_left(bin_tree_t *tree,tree_node_t *node,void *data);
/*
 * create a new node with the value of data and insert to the node's right 
 * if node's right is not NULL will return -1
 */
int bin_tree_ins_right(bin_tree_t *tree,tree_node_t *node,void *data);

void bin_tree_preorder_scan(bin_tree_t *tree,tree_node_t *node);
void bin_tree_midorder_scan(bin_tree_t *tree,tree_node_t *node);
void bin_tree_postorder_scan(bin_tree_t *tree,tree_node_t *node);
void bin_tree_layer_scan(bin_tree_t *tree,tree_node_t **node_parent);
void bin_tree_find_node(bin_tree_t *tree,tree_node_t *node,void *data,tree_node_t **find_item);

void bin_tree_simple_search_insert(bin_tree_t *tree,tree_node_t *node,void *data);
void bin_tree_simple_search_fine(bin_tree_t *tree,tree_node_t *node,void *data,tree_node_t **find_item);
void bin_tree_simple_search_remove(bin_tree_t *tree,tree_node_t *parent_node,tree_node_t *node,void *data);

#endif 

