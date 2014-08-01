#include"BinTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void bin_tree_init(bin_tree_t *tree,compare_func compare,destroy_func destory,dump_data_func dump_data){
    if(tree == NULL){
        return ;
    }
    memset(tree,0,sizeof(bin_tree_t));
    tree->fpn_compare = compare;
    tree->fpn_destory = destory;
    tree->fpn_dump_data = dump_data;
}



void bin_tree_destroy(bin_tree_t *tree){
    bin_tree_remove_left(tree,NULL);
}

/*
 * remove the left branch of node
 */
void bin_tree_remove_left(bin_tree_t *tree,tree_node_t *node){
    tree_node_t **remove_item = NULL;
    if(node == NULL){
        remove_item = &(tree->root);
    }else{
        remove_item = &(node->left);
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
        remove_item = &(tree->root);
    }else{
        remove_item = &(node->right);
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
int bin_tree_merge(bin_tree_t *merge,bin_tree_t *left,bin_tree_t *right,void *data){
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
int bin_tree_ins_left(bin_tree_t *tree,tree_node_t *node,void *data){
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->left);
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
int bin_tree_ins_right(bin_tree_t *tree,tree_node_t *node,void *data){
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->right);
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
void bin_tree_insert_left(bin_tree_t *tree,tree_node_t *node,void *data){
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->left);
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

void bin_tree_insert_right(bin_tree_t *tree,tree_node_t *node,void *data){
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->right);
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


void bin_tree_preorder_scan(bin_tree_t *tree,tree_node_t *node){
    if(node != NULL){
        if(tree->fpn_dump_data){
            tree->fpn_dump_data(node->data);
        }
        bin_tree_preorder_scan(tree,node->left);
        bin_tree_preorder_scan(tree,node->right);
    }
}


void bin_tree_midorder_scan(bin_tree_t *tree,tree_node_t *node){
    if(node != NULL){
        bin_tree_midorder_scan(tree,node->left);
        if(tree->fpn_dump_data){
            tree->fpn_dump_data(node->data);
        }
        bin_tree_midorder_scan(tree,node->right);
    }
}

void bin_tree_postorder_scan(bin_tree_t *tree,tree_node_t *node){
    if(node != NULL){
        bin_tree_postorder_scan(tree,node->left);
        bin_tree_postorder_scan(tree,node->right);
        if(tree->fpn_dump_data){
            tree->fpn_dump_data(node->data);
        }
    }
}

void bin_tree_layer_scan(bin_tree_t *tree,tree_node_t **node_parent){
    int i = 0;
    int j = 0;
    tree_node_t *parent[1024]={0};
    while(*(node_parent +i)){
        if((*(node_parent +i))->left){
            parent[j++] = (*(node_parent +i))->left;
        }
        if((*(node_parent +i))->right){
            parent[j++] = (*(node_parent +i))->right;
        }
        if(tree->fpn_dump_data){
            tree->fpn_dump_data((*(node_parent +i))->data);
        }
        i++;
    }
    printf("\n");
    bin_tree_layer_scan(tree,parent);
}

void bin_tree_find_node(bin_tree_t *tree,tree_node_t *node,void *data,tree_node_t **find_item){
    if(tree == NULL || data == NULL || find_item != NULL){
        return ;
    }
    if(node != NULL){
        if(tree->fpn_compare){
            if(tree->fpn_compare(node->data,data) == 0){
                *find_item = node ;
            }else{
                bin_tree_find_node(tree,node->left,data,find_item);
                bin_tree_find_node(tree,node->right,data,find_item);
            }
        }
    }
}


