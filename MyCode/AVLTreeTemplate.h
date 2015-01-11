#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
#include"BinTreeTemplate.h"

enum{
    WEIGHT_LEFT_HEAVY =1,
    WEIGHT_BALANCE = 0,
    WEIGHT_RIGHT_HEAVY =-1
};

template <class T>
class AVLTreeNode{
    public:
    AVLTreeNode(){
        left = NULL;
        right = NULL;
        mData = NULL;
        weight = 0;
        hide = 0;
    }
    AVLTreeNode(T *data){
        mData = data;
        left = NULL;
        right = NULL;
        weight = 0;
        hide = 0;
    }
    AVLTreeNode(AVLTreeNode &node){
        mData = node.mData;
        left = NULL;
        right = NULL;
        weight = 0;
        hide = 0;
    }
    ~AVLTreeNode(){
        if(mData != NULL){
            delete mData;
        }
    }

    AVLTreeNode<T> *left;
    AVLTreeNode<T> *right;

    short weight ;
    short hide;
    T *mData;
};


template <type T>
class AVLTreeTemplate{
    public:
        AVLTreeTemplate(){
            mSize = 0 ;
            mRoot = NULL;
        }
        AVLTreeTemplate(const AVLTreeTemplate &tree){
            //simple copy
            mSize = tree.mSize;
            mRoot = tree.mRoot;
        }

        void PreorderScan(){
            avl_tree_preorder_scan(mRoot);
        }

        void MidorderScan(){
            avl_tree_midorder_scan(mRoot);
        }
        void PostorderScan(){
            avl_tree_postorder_scan(mRoot);
        }
        void LayerScan(){
            AVLTreeNode<T> *parent[2]={mRoot,NULL};
            avl_tree_layer_scan(parent);
        }

        int FindNode(T *data){
            AVLTreeNode<T> **ppNode = &mRoot;
            while(*ppNode != NULL){
                if(*((*ppNode)->mData) > *data){
                    ppNode = &((*ppNode)->left);
                }else if(*((*ppNode)->mData) < *data){
                    ppNode = &((*ppNode)->right);
                }else {
                    return ((*ppNode)->hide)?0:1;
                }
            }
            return 0;
        }

        int InsertNode(T *data){
        }

        void RemoveNode(T *data){
            //simple remove
            AVLTreeNode<T> **ppNode = &mRoot;
            while(*ppNode != NULL){
                if(*((*ppNode)->mData) > *data){
                    ppNode = &((*ppNode)->left);
                }else if(*((*ppNode)->mData) < *data){
                    ppNode = &((*ppNode)->right);
                }else {
                    (*ppNode)->hide = 1;
                }
            }
            return 0;
        }

        int GetSize(){
            return mSize;
        }
        int IsLeaf(AVLTreeNode<T> *node){
            return (node && (node->left == NULL && node->right == NULL));
        }
        
    private:

        void avl_tree_insert(AVLTreeNode<T> **ppNode,T *data,int *balance){
            AVLTreeNode<T> *insertNode = NULL;
            int cmp_val = 0;
            int ret_val = 0;
            if(ppNode == NULL){
                if(mRoot == NULL){
                    //handle empty tree
                    insertNode = new AVLTreeNode(data);
                    mRoot = insertNode;
                    mSize ++;
                    return ;
                }else{
                    ppNode = &mRoot; 
                }
            }

            if((*((*ppNode)->mData) > *data ){
                cmp_val = 1
            }else if((*((*ppNode)->mData) < *data)){
                cmp_val = -1;
            }else{
                cmp_val = 0;
            }

            if(cmp_val > 0){
                if((*ppNode)->left == NULL){
                    (*ppNode)->left = new AVLTreeNode(data);
                    *balance = 0;
                }else{
                    avl_tree_insert(&(*ppNode)->left,data,balance);
                }
                if(*balance == 0){
                    switch((*ppNode)->weight){
                        case WEIGHT_LEFT_HEAVY:
                            rotate_left(ppNode);
                            *balance = 1;
                            break;
                        case WEIGHT_BALANCE:
                            (*ppNode)->weight = WEIGHT_LEFT_HEAVY;
                            break;
                        case WEIGHT_RIGHT_HEAVY:
                            (*ppNode)->weight = WEIGHT_BALANCE;
                            *balance = 1;
                            break;
                    }
                }
            }else if(cmp_val < 0){
                if((*ppNode)->right == NULL){
                    (*ppNode)->right = new AVLTreeNode(data);
                    *balance = 0;
                }else{
                    avl_tree_insert(&(*ppNode)->right,data,balance);
                }
                if(*balance == 0){
                    switch((*ppNode)->weight){
                        case WEIGHT_LEFT_HEAVY:
                            (*ppNode)->weight = WEIGHT_BALANCE;
                            *balance = 1;
                            break;
                        case WEIGHT_BALANCE:
                            (*ppNode)->weight = WEIGHT_RIGHT_HEAVY;
                            break;
                        case WEIGHT_RIGHT_HEAVY:
                            rotate_right(ppNode);
                            *balance = 1;
                            break;
                    }
                }

            }else{
                if(!(*ppNode)->hide){
                    printf("############exist############\n");
                    return ;
                }else{
                    *ppNode = new AVLTreeNode(data);
                }
                *balance =1;
            }
        }

        void dump_data(T *data){
            //printf(" %d   ",*((int *)data));
        }

        void avl_tree_preorder_scan(AVLTreeNode<T> *node){
            if(node != NULL){
                if(!node->hide){
                    dump_data(node->mData);
                }
                avl_tree_preorder_scan(node->left);
                avl_tree_preorder_scan(node->right);
            }
        }

        void avl_tree_postorder_scan(AVLTreeNode<T> *node){
            if(node != NULL){
                avl_tree_postorder_scan(node->left);
                avl_tree_postorder_scan(node->right);
                if(!node->hide){
                    dump_data(node->mData);
                }
            }
        }

        void avl_tree_midorder_scan(AVLTreeNode<T> *node){
            if(node != NULL){
                avl_tree_midorder_scan(node->left);
                if(!node->hide){
                    dump_data(node->mData);
                }
                avl_tree_midorder_scan(node->right);
            }
        }

        void avl_tree_layer_scan(AVLTreeNode<T> **node_parent){
            int i = 0;
            int j = 0;
            AVLTreeNode<T> *parent[100]={0};
            while(node_parent[i] != NULL){
                if(node_parent[i]->left){
                    parent[j++] = node_parent[i]->left;
                }
                if(node_parent[i]->right){
                    parent[j++] = node_parent[i]->right;
                }
                if(!node_parent[i]->hide){
                    dump_data(node_parent[i]->mData);
                }
                i++;
            }
            if(node_parent[0] == NULL){
                return ;
            }
            printf("\n");
            bin_tree_layer_scan(parent);
        }

        int mSize;
        AVLTreeNode *mRoot;
};


#endif //__AVL_TREE_H__
