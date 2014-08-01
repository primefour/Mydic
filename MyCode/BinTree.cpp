#include"BinTree.h"
#include<stdio.h>

void bin_tree_init(bin_tree_t *tree,compare_func compare,destroy_func destory){
    if(tree == NULL){
        return ;
    }
    tree->fpn_compare = compare;
    tree->fpn_destory = destory;
    tree->size = 0;
    tree->root = NULL;
}



void bin_tree_destroy(bin_tree_t *tree){
    bin_tree_remove(tree,NULL);
}

/*
 * remove the left branch of node
 */
void bin_tree_remove_left(bin_tree_t *tree,tree_node_t *node){
    tree_node_t **remove_item = NULL;
    if(node == NULL){
        *remove_item = &(tree->root);
    }else{
        *remove_item = &(node->left);
    }

    if(*remove_item != NULL){
        bin_tree_remove_left(tree,*remove_item);
        bin_tree_remove_right(tree,*remove_item);
        if(tree->fpn_destory != NULL){
            tree->fpn_destory((*remove_item)->data);
        }
        free(*remove_item);
        *remove_item = NULL;
        tree->size --;
    }
}

/*
 * remove the right branch of node
 */
void bin_tree_remove_right(bin_tree_t *tree,tree_node_t *node){
    tree_node_t **remove_item = NULL;
    if(node == NULL){
        *remove_item = &(tree->root);
    }else{
        *remove_item = &(node->right);
    }

    if(*remove_item != NULL){
        bin_tree_remove_left(tree,*remove_item);
        bin_tree_remove_right(tree,*remove_item);
        if(tree->fpn_destory != NULL){
            tree->fpn_destory((*remove_item)->data);
        }
        free(*remove_item);
        *remove_item = NULL;
        tree->size --;
    }
}

/*
 * merge the both tree as a new tree's left and rigth branch,data as root
 * node's value
 */
int bin_tree_merge(bin_tree_t *merge,bin_tree_t *left,bin_tree_t *right,const void *data){
    if(bin_tree_ins_left(merge,NULL,data) < 0){
        bin_tree_destroy(merge);
        return -1;
    }
    bin_tree_root(merge)->left = bin_tree_root(left);
    bin_tree_root(merge)->right = bin_tree_root(right);
    merge->size = left->size + right->size + 1;
    memset(left,0,sizeof(bin_tree_t));
    memset(right,0,sizeof(bin_tree_t));
    return 0;
}

/*
 * create a new node with the value of data and insert to the node's left
 * if node's left is not NULL will return -1
 */
int bin_tree_ins_left(bin_tree_t *tree,tree_node_t *node,const void *data){
    bin_tree_t **insert_position = NULL;
    if(node == NULL){
        *insert_position = &(tree->root);
    }else{
        *insert_position = &(node->left);
    }
    if(*insert_position == NULL){
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        assert(new_node != NULL);
        new_node->data = data;
        *insert_position = new_node; 
        tree->size ++;
        return 0;
    }else{
        return -1;
    }
}

/*
 * create a new node with the value of data and insert to the node's right 
 * if node's right is not NULL will return -1
 */
int bin_tree_ins_right(bin_tree_t *tree,tree_node_t *node,const void *data){
    bin_tree_t **insert_position = NULL;
    if(node == NULL){
        *insert_position = &(tree->root);
    }else{
        *insert_position = &(node->right);
    }
    if(*insert_position == NULL){
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        assert(new_node != NULL);
        new_node->data = data;
        *insert_position = new_node; 
        tree->size ++;
        return 0;
    }else{
        return -1;
    }
}


/*
 * create a new node with value of data and insert to the 
 * left branch of the node 
 */
void bin_tree_insert_left(bin_tree_t *tree,tree_node_t *node,const void *data){
    bin_tree_t **insert_position = NULL;
    if(node == NULL){
        *insert_position = &(tree->root);
    }else{
        *insert_position = &(node->left);
    }
    if(*insert_position == NULL){
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        assert(new_node != NULL);
        new_node->data = data;
        *insert_position = new_node; 
        tree->size ++;
    }else{
        bin_tree_insert_left(tree,*insert_position,data);
    }
}

void bin_tree_insert_right(bin_tree_t *tree,tree_node_t *node,const void *data){
    bin_tree_t **insert_position = NULL;
    if(node == NULL){
        *insert_position = &(tree->root);
    }else{
        *insert_position = &(node->right);
    }
    if(*insert_position == NULL){
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        assert(new_node != NULL);
        new_node->data = data;
        *insert_position = new_node; 
        tree->size ++;
    }else{
        bin_tree_insert_right(tree,*insert_position,data);
    }

}



int bin_tree_size(const bin_tree_t *tree){
    if(tree != NULL){
        return tree->size;
    }
    return 0;
}


int bin_tree_isleaf(const tree_node_t *node){
    return node->left == NULL && node->right == NULL;
}

tree_node_t* bin_tree_root(const  bin_tree_t *tree){
    return tree->root;
}


