#include"BinTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
//#include"memory_test_tool.h"

void bin_tree_init(bin_tree_t *tree,bin_compare_func compare,destroy_func destory,dump_data_func dump_data){
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
        printf("free %s   %d \n",__func__,__LINE__);
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
        printf("free %s   %d \n",__func__,__LINE__);
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
    //printf("%s   %d \n",__func__,__LINE__);
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->left);
    }
    if(*insert_position == NULL){
        printf("############malloc #############\n");
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        memset(new_node,0,sizeof(tree_node_t));
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
    //printf("%s   %d \n",__func__,__LINE__);
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->right);
    }
    if(*insert_position == NULL){
        printf("%s   %d \n",__func__,__LINE__);
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        memset(new_node,0,sizeof(tree_node_t));
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
    //printf("%s   %d \n",__func__,__LINE__);
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->left);
    }
    if(*insert_position == NULL){
        printf("%s   %d \n",__func__,__LINE__);
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        memset(new_node,0,sizeof(tree_node_t));
        assert(new_node != NULL);
        new_node->data = data;
        *insert_position = new_node; 
        tree->size ++;
    }else{
        bin_tree_insert_left(tree,*insert_position,data);
    }
}

void bin_tree_insert_right(bin_tree_t *tree,tree_node_t *node,void *data){
    //printf("%s   %d \n",__func__,__LINE__);
    tree_node_t **insert_position = NULL;
    if(node == NULL){
        insert_position = &(tree->root);
    }else{
        insert_position = &(node->right);
    }
    if(*insert_position == NULL){
        printf("%s   %d \n",__func__,__LINE__);
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        memset(new_node,0,sizeof(tree_node_t));
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
    tree_node_t *parent[100]={0};
    while(node_parent[i] != NULL){
        if(node_parent[i]->left){
            parent[j++] = node_parent[i]->left;
        }
        if(node_parent[i]->right){
            parent[j++] = node_parent[i]->right;
        }
        if(tree->fpn_dump_data){
            tree->fpn_dump_data(node_parent[i]->data);
        }
        i++;
    }
    if(node_parent[0] == NULL){
        return ;
    }
    printf("\n");
    bin_tree_layer_scan(tree,parent);
}

void bin_tree_find_node(bin_tree_t *tree,tree_node_t *node,void *data,tree_node_t **find_item){
    if(tree == NULL ||  find_item == NULL){
        return ;
    }
    if(node != NULL){
        if(tree->fpn_compare){
            if(tree->fpn_compare(node->data,data) == 0){
                //printf("####%ld %s \n",(long)(node->data),__func__);
                *find_item = node ;
            }else{
                bin_tree_find_node(tree,node->left,data,find_item);
                bin_tree_find_node(tree,node->right,data,find_item);
            }
        }
    }
}



void bin_tree_simple_search_insert(bin_tree_t *tree,tree_node_t *node,void *data){
    //printf("######################%d %s ################\n",__LINE__,__func__);
    tree_node_t **compare_item = NULL;
    if(tree->fpn_compare== NULL){
        printf("please assign a compare function to the tree\n");
        return ;
    }
    if(node != NULL){
        compare_item = &node;
    }else{
        compare_item = &(tree->root);
    }
    if(*compare_item){
        int ret = tree->fpn_compare((*compare_item)->data,data);
        if(ret > 0){
            if((*compare_item)->left != NULL){
                //printf("######################%d %s ################\n",__LINE__,__func__);
                bin_tree_simple_search_insert(tree,(*compare_item)->left,data);
            }else{
                printf("%ld insert to %ld left \n",(long)data,(long)(*compare_item)->data); 
                bin_tree_ins_left(tree,*compare_item,data);
            }
        }else if(ret < 0){
            if((*compare_item)->right != NULL){
                //printf("######################%d %s ################\n",__LINE__,__func__);
                bin_tree_simple_search_insert(tree,(*compare_item)->right ,data);
            }else{
                printf("%ld insert to %ld right \n",(long)data,(long)(*compare_item)->data); 
                bin_tree_ins_right(tree,*compare_item,data);
            }
        }else{
            printf("the item have been in the tree %ld \n",(long)data);
        }
    }else{
        if(bin_tree_size(tree)){
            printf("tree is not empty and insert the data as a root error\n");
            assert(0);
            return ;
        }
        printf("tree is empty and insert the data as a root \n");
        bin_tree_ins_left(tree,NULL,data);
    }
}


void bin_tree_simple_search_fine(bin_tree_t *tree,tree_node_t *node,void *data,tree_node_t **find_item){
    tree_node_t **compare_item = NULL;
    if(tree->fpn_compare== NULL){
        printf("please assign a compare function to the tree\n");
        return ;
    }
    if(node != NULL){
        compare_item = &node;
    }else{
        compare_item = &(tree->root);
    }
    if(*compare_item){
        int ret = tree->fpn_compare((*compare_item)->data,data);
        if(ret > 0){
            //printf("##############%s ####################left %p #\n",__func__,(*compare_item)->left);
            if((*compare_item)->left != NULL){
                bin_tree_simple_search_fine(tree,(*compare_item)->left,data,find_item);
            }else{
                printf("can't find the item %ld \n",(long)data);
                return;
            }
        }else if(ret < 0){
            //printf("##############%s ####################right %p #\n",__func__,(*compare_item)->right);
            if((*compare_item)->right != NULL){
                bin_tree_simple_search_fine(tree,(*compare_item)->right,data,find_item);
            }else{
                printf("can't find the item %ld \n",(long)data);
                return;
            }
        }else{
            //printf("##############%s ####################%p #\n",__func__,(*(compare_item)));
            *find_item = *(compare_item);
            return ;
        }
    }

}
/*
 *                                    10
 *                                 0      15
 *                              -1      13    17
 *                            -3      11  12     18 
 */
void bin_tree_simple_search_remove(bin_tree_t *tree,tree_node_t *parent_node,tree_node_t *node,void *data){
    tree_node_t *compare_item = NULL;
    if(tree->fpn_compare== NULL){
        printf("please assign a compare function to the tree\n");
        return ;
    }
    if(node != NULL && parent_node != NULL){
        compare_item = node;
    }else{
        compare_item = (tree->root);
    }
    if(compare_item){
        int ret = tree->fpn_compare((compare_item)->data,data);
        if(ret > 0){
            if((compare_item)->left != NULL){
                bin_tree_simple_search_remove(tree,compare_item,(compare_item)->left,data);
            }else{
                printf("can't find the item %ld \n",(long)data);
                return;
            }
        }else if(ret < 0){
            if((compare_item)->right != NULL){
                bin_tree_simple_search_remove(tree,compare_item,(compare_item)->right,data);
            }else{
                printf("can't find the item %ld \n",(long)data);
                return;
            }
        }else{
            //find the item and remove the item from the tree
            if((compare_item)->left == NULL && (compare_item)->right == NULL){
                //no child just remove
                if(parent_node != NULL){
                    if(parent_node->left == compare_item){
                        parent_node->left = NULL;
                    }else if (parent_node->right == compare_item){
                        parent_node->right = NULL;
                    }
                }else{
                    //get a empty tree
                    printf("become an empty tree \n");
                    tree->root= NULL;
                }

            }else if ((compare_item)->left != NULL && (compare_item)->right != NULL){
                //has two child we should find a item to replace the removed item
                //we select the smallest of right branch as the root of left and right branch
                tree_node_t *right_branch = (compare_item)->right;
                tree_node_t *right_branch_parent = right_branch ; 
                while(right_branch->left != NULL){
                    right_branch_parent = right_branch;
                    right_branch = right_branch->left;
                }
                if(right_branch_parent == right_branch){
                    right_branch->left = (compare_item)->left;
                }else{
                    right_branch_parent->left = right_branch->right;
                    right_branch->left = (compare_item)->left;
                    right_branch->right = (compare_item)->right;
                }
                if(parent_node != NULL){
                    if(parent_node->left == compare_item){
                        parent_node->left = right_branch;
                    }else if (parent_node->right == compare_item){
                        parent_node->right = right_branch;
                    }
                }else{
                    tree->root= right_branch;
                }

            }else{
                if((compare_item)->left != NULL){
                    if(parent_node != NULL){
                        //no right child just remove
                        if(parent_node->left == compare_item){
                            parent_node->left = (compare_item)->left;
                        }else if (parent_node->right == compare_item){
                            parent_node->right = (compare_item)->left;
                        }
                    }else{
                        tree->root= (compare_item)->left;
                    }
                }else{
                    //no left child just remove
                    if(parent_node != NULL){
                        if(parent_node->left == compare_item){
                            parent_node->left = (compare_item)->right;
                        }else if (parent_node->right == compare_item){
                            parent_node->right = (compare_item)->right;
                        }
                    }else{
                        tree->root= (compare_item)->right;
                    }
                }
            }

            if(tree->fpn_destory != NULL){
                tree->fpn_destory((compare_item)->data);
            }

    printf("free %s   %d \n",__func__,__LINE__);
            free(compare_item);
            tree->size --;
            return ;
        }
    }
}






