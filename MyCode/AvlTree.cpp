#include"AvlTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BinTree.h"
//#include"memory_test_tool.h"
#define avl_weight_data(node)  ((avl_node_t*)((node)->data))

static void rotate_left(tree_node_t **node){
    tree_node_t *left = NULL;
    tree_node_t *grand_child = NULL;
    left = (*node)->left;
    if(avl_weight_data(*node)->weight == WEIGHT_LEFT_HEAVY){
        (*node)->left = left->right;
        left->right = (*node);
        avl_weight_data(*node)->weight = WEIGHT_BALANCE;
        avl_weight_data(left)->weight = WEIGHT_BALANCE;
        *node = left;
    }else{
        grand_child = left->right;
        left->right = grand_child->left;
        grand_child->left = left;
        (*node)->left = grand_child->right;
        grand_child->right = *node;
        switch(avl_weight_data(grand_child)->weight){
            case WEIGHT_LEFT_HEAVY:
                avl_weight_data(*node)->weight = WEIGHT_RIGHT_HEAVY;
                avl_weight_data(left)->weight = WEIGHT_BALANCE;
            break;
            case WEIGHT_BALANCE:
                avl_weight_data(*node)->weight = WEIGHT_BALANCE;
                avl_weight_data(left)->weight = WEIGHT_BALANCE;
            break;
            case WEIGHT_RIGHT_HEAVY:
                avl_weight_data(*node)->weight = WEIGHT_BALANCE;
                avl_weight_data(left)->weight = WEIGHT_LEFT_HEAVY;
            break;
        }
        avl_weight_data(grand_child)->weight = WEIGHT_BALANCE;
        *node = grand_child;
    }
    return;
}


static void rotate_right(tree_node_t **node){
    tree_node_t *right = NULL;
    tree_node_t *grand_child = NULL;
    right = (*node)->right;
    if(avl_weight_data(right)->weight == WEIGHT_RIGHT_HEAVY){
        (*node)->right = right->left;
        right->left = (*node);
        avl_weight_data(*node)->weight = WEIGHT_BALANCE;
        avl_weight_data(right)->weight = WEIGHT_BALANCE;
        *node = right;
    }else{
        grand_child = right->left;
        right->left = grand_child->right;
        grand_child->right = right;
        (*node)->right = grand_child->left;
        grand_child->left = *node;
        switch(avl_weight_data(grand_child)->weight){
            case WEIGHT_LEFT_HEAVY:
            avl_weight_data((*node))->weight = WEIGHT_BALANCE;
            avl_weight_data(right)->weight = WEIGHT_RIGHT_HEAVY;
            break;
            case WEIGHT_BALANCE:
            avl_weight_data((*node))->weight = WEIGHT_BALANCE;
            avl_weight_data(right)->weight = WEIGHT_BALANCE;
            break;
            case WEIGHT_RIGHT_HEAVY:
            avl_weight_data((*node))->weight = WEIGHT_LEFT_HEAVY;
            avl_weight_data(right)->weight = WEIGHT_BALANCE;
            break;
        }
        avl_weight_data(grand_child)->weight = WEIGHT_BALANCE;
        *node = grand_child;
    }
    return;
}

static void destroy_right(bin_tree_t *tree,tree_node_t *node);

static void destroy_left(bin_tree_t *tree,tree_node_t *node){
    tree_node_t **position;
    if(node == NULL){
        position = &(tree->root);
    }else{
        position = &(node->left);
    }
    if(*position){
        destroy_left(tree,*position);
        destroy_right(tree,*position);
        if(tree->fpn_destory != NULL){
            tree->fpn_destory(avl_weight_data(*position)->data);
        }
        free((*position)->data);
        free((*position));
        *position = NULL;
        tree->size--;
    }
    return ;
}

static void destroy_right(bin_tree_t *tree,tree_node_t *node){
    tree_node_t **position;
    if(node == NULL){
        position = &(tree->root);
    }else{
        position = &(node->right);
    }

    if(*position != NULL){
        destroy_left(tree,*position);
        destroy_right(tree,*position);

        if(tree->fpn_destory != NULL){
            tree->fpn_destory(avl_weight_data(*position)->data);
        }
        free((*position)->data);
        free((*position));
        *position = NULL;
        tree->size--;
    }
    return ;
}



void avl_tree_init(bin_tree_t *tree,bin_compare_func compare,
        destroy_func destroy,dump_data_func dump_data){
    bin_tree_init(tree,compare,destroy,dump_data);
}

void avl_tree_insert(bin_tree_t *tree,tree_node_t **node,void *data,int *balance){
    avl_node_t *avl_data = NULL;
    int cmp_val = 0;
    int ret_val = 0;
    if(node == NULL){
        if(tree->root == NULL){
            //hendle empty tree
            avl_data = (avl_node_t *)malloc(sizeof(avl_node_t));
            memset(avl_data,0,sizeof(avl_node_t));
            avl_data->weight = WEIGHT_BALANCE;
            avl_data->data = (void *)data;
            printf("%ld insert to as root  \n",(long)data);
            bin_tree_ins_left(tree,NULL,avl_data);
            return ;
        }else{
            //printf("####%ld  will be inserted \n",(long)data);
            node = &(tree->root);
        }
    }

    cmp_val = tree->fpn_compare(avl_weight_data(*node)->data,data);
    //printf("%s    %d  --> %ld  %ld\n",__func__,__LINE__,(long)(avl_weight_data(*node)->data),(long)data);
    if(cmp_val > 0){
        if((*node)->left == NULL){
            avl_data = (avl_node_t *)malloc(sizeof(avl_node_t));
            memset(avl_data,0,sizeof(avl_node_t));
            avl_data->weight = WEIGHT_BALANCE;
            avl_data->data = (void *)data;
            //printf("%ld insert to %ld left \n",(long)data,(long)(avl_weight_data(*node)->data));
            bin_tree_ins_left(tree,*node,avl_data);
            *balance = 0;
        }else{
            avl_tree_insert(tree,&(*node)->left,data,balance);
        }
        if(*balance == 0){
            switch(avl_weight_data((*node))->weight){
                case WEIGHT_LEFT_HEAVY:
                    rotate_left(node);
                    *balance = 1;
                    break;
                case WEIGHT_BALANCE:
                    avl_weight_data((*node))->weight = WEIGHT_LEFT_HEAVY;
                    break;
                case WEIGHT_RIGHT_HEAVY:
                    avl_weight_data((*node))->weight = WEIGHT_BALANCE;
                    *balance = 1;
                    break;
            }
        }
    }else if(cmp_val < 0){
        if((*node)->right == NULL){
            avl_data = (avl_node_t *)malloc(sizeof(avl_node_t));
            memset(avl_data,0,sizeof(avl_node_t));
            avl_data->weight = WEIGHT_BALANCE;
            avl_data->data = (void *)data;
            //printf("%ld insert to %ld right \n",(long)data,(long)(avl_weight_data(*node)->data));
            bin_tree_ins_right(tree,*node,avl_data);
            *balance = 0;
        }else{
            avl_tree_insert(tree,&(*node)->right,data,balance);
        }
        if(*balance == 0){
            switch(avl_weight_data((*node))->weight){
                case WEIGHT_LEFT_HEAVY:
                    avl_weight_data((*node))->weight = WEIGHT_BALANCE;
                    *balance = 1;
                    break;
                case WEIGHT_BALANCE:
                    avl_weight_data((*node))->weight = WEIGHT_RIGHT_HEAVY;
                    break;
                case WEIGHT_RIGHT_HEAVY:
                    rotate_right(node);
                    *balance = 1;
                    break;
            }
        }

    }else{
        if(!avl_weight_data((*node))->hide){
            printf("############exist############\n");
            return ;
        }else{
            if(tree->fpn_destory != NULL){
                tree->fpn_destory(avl_weight_data((*node))->data);
            }
            avl_weight_data((*node))->data = data;
            avl_weight_data((*node))->hide = 0;
        }
        *balance =1;
    }
}

void avl_tree_remove(bin_tree_t *tree,tree_node_t *node,void *data){
    int cmp_val = 0;
    if(node == NULL){
        if(tree->root != NULL){
            node = tree->root;
        }else{
            printf("this is an empty tree \n");
            return ;
        }
    }
    cmp_val = tree->fpn_compare(avl_weight_data(node)->data,data);
    if(cmp_val < 0){
        if(node->right != NULL){
            avl_tree_remove(tree,node->right,data);
        }else{
            //printf("%s can't find the item \n",__func__);
        }
    }else if(cmp_val > 0){
        if(node->left != NULL){
            avl_tree_remove(tree,node->left,data);
        }else{
            //printf("%s can't find the item \n",__func__);
        }
    }else{
        if(!avl_weight_data(node)->hide){
            avl_weight_data(node)->hide =1;
        }else{
            //printf("%s this has already been hide \n",__func__);
        }
    }
}

void avl_tree_find(bin_tree_t *tree,tree_node_t *node,void *data,void **find_item){
    int cmp_val = 0;
    if(node == NULL){
        if(tree->root != NULL){
            node = tree->root;
        }else{
            printf("this is an empty tree \n");
            return ;
        }
    }
    cmp_val = tree->fpn_compare(avl_weight_data(node)->data,data);
    if(cmp_val < 0){
        if(node->right != NULL){
            avl_tree_find(tree,node->right,data,find_item);
        }else{
            //printf("%s not find the item \n",__func__);
        }
    }else if(cmp_val > 0){
        if(node->left != NULL){
            avl_tree_find(tree,node->left,data,find_item);
        }else{
            //printf("%s not find the item \n",__func__);
        }
    }else{
        if(!avl_weight_data(node)->hide){
            *find_item = avl_weight_data(node)->data;
        }else{
            //printf("%s this is hided item \n",__func__);
        }
    }
}

void avl_tree_destroy(bin_tree_t *tree){
    destroy_left(tree,NULL);
}


static void avl_tree_preorder_scan_(bin_tree_t *tree,tree_node_t *node){
    if(node != NULL){
        if(tree->fpn_dump_data){
            avl_node_t *data = (avl_node_t *)(node->data);
            if(! data->hide){
                tree->fpn_dump_data(data->data);
            }
        }
        avl_tree_preorder_scan_(tree,node->left);
        avl_tree_preorder_scan_(tree,node->right);
    }
}

void avl_tree_preorder_scan(bin_tree_t *tree){
    avl_tree_preorder_scan_(tree,bin_tree_root(tree));
}



void avl_tree_layer_scan(bin_tree_t *tree,tree_node_t **node_parent){
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
            avl_node_t *data = (avl_node_t *)(node_parent[i]->data);
            if(! data->hide){
                tree->fpn_dump_data(data->data);
            }
        }
        i++;
    }
    if(node_parent[0] == NULL){
        return ;
    }
    printf("\n");
    avl_tree_layer_scan(tree,parent);
}

