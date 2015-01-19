#ifndef __AVL_TREE_TEMPLATE_H__
#define __AVL_TREE_TEMPLATE_H__
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
        left = node.left;
        right = node.right;
        weight = node.weight;
        mData = node.mData;
        hide = 0;
    }
    void operator=(const  AVLTreeNode<T> &node){
        left = node.left;
        right = node.right;
        weight = node.weight;
        hide = 0;
        mData = node.mData;
    }
    ~AVLTreeNode(){
        if(mData != NULL){
            //delete mData;
        }
    }

    AVLTreeNode<T> *left;
    AVLTreeNode<T> *right;

    short weight ;
    short hide;
    T *mData;
};


template <class T>
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

        ~AVLTreeTemplate(){
            avl_tree_destroy();
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
            int balance = 1;
            avl_tree_insert(NULL,data,&balance);
            return 1;
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
                    return ;
                }
            }
        }

        int GetSize(){
            return mSize;
        }
        int IsLeaf(AVLTreeNode<T> *node){
            return (node && (node->left == NULL && node->right == NULL));
        }
        
    private:

        static void rotate_left(AVLTreeNode<T> **node){
            AVLTreeNode<T> *left = NULL;
            AVLTreeNode<T> *grand_child = NULL;
            left = (*node)->left;
            if((*node)->weight == WEIGHT_LEFT_HEAVY){
                (*node)->left = left->right;
                left->right = (*node);
                (*node)->weight = WEIGHT_BALANCE;
                left->weight = WEIGHT_BALANCE;
                *node = left;
            }else{
                grand_child = left->right;
                left->right = grand_child->left;
                grand_child->left = left;
                (*node)->left = grand_child->right;
                grand_child->right = *node;
                switch(grand_child->weight){
                    case WEIGHT_LEFT_HEAVY:
                        (*node)->weight = WEIGHT_RIGHT_HEAVY;
                        left->weight = WEIGHT_BALANCE;
                        break;
                    case WEIGHT_BALANCE:
                        (*node)->weight = WEIGHT_BALANCE;
                        left->weight = WEIGHT_BALANCE;
                        break;
                    case WEIGHT_RIGHT_HEAVY:
                        (*node)->weight = WEIGHT_BALANCE;
                        left->weight = WEIGHT_LEFT_HEAVY;
                        break;
                }
                grand_child->weight = WEIGHT_BALANCE;
                *node = grand_child;
            }
            return;
        }


        static void rotate_right(AVLTreeNode<T> **node){
            AVLTreeNode<T> *right = NULL;
            AVLTreeNode<T> *grand_child = NULL;
            right = (*node)->right;
            if(right->weight == WEIGHT_RIGHT_HEAVY){
                (*node)->right = right->left;
                right->left = (*node);
                (*node)->weight = WEIGHT_BALANCE;
                (right)->weight = WEIGHT_BALANCE;
                *node = right;
            }else{
                grand_child = right->left;
                right->left = grand_child->right;
                grand_child->right = right;
                (*node)->right = grand_child->left;
                grand_child->left = *node;
                switch((grand_child)->weight){
                    case WEIGHT_LEFT_HEAVY:
                        ((*node))->weight = WEIGHT_BALANCE;
                        (right)->weight = WEIGHT_RIGHT_HEAVY;
                        break;
                    case WEIGHT_BALANCE:
                        ((*node))->weight = WEIGHT_BALANCE;
                        (right)->weight = WEIGHT_BALANCE;
                        break;
                    case WEIGHT_RIGHT_HEAVY:
                        ((*node))->weight = WEIGHT_LEFT_HEAVY;
                        (right)->weight = WEIGHT_BALANCE;
                        break;
                }
                (grand_child)->weight = WEIGHT_BALANCE;
                *node = grand_child;
            }
            return;
        }


        void avl_tree_insert(AVLTreeNode<T> **ppNode,T *data,int *balance){
            AVLTreeNode<T> *insertNode = NULL;
            int cmp_val = 0;
            int ret_val = 0;
            if(ppNode == NULL){
                if(mRoot == NULL){
                    //handle empty tree
                    insertNode = new AVLTreeNode<T>(data);
                    mRoot = insertNode;
                    mSize ++;
                    return ;
                }else{
                    ppNode = &mRoot; 
                }
            }

            if(*((*ppNode)->mData) > *data ){
                cmp_val = 1;
            }else if((*((*ppNode)->mData) < *data)){
                cmp_val = -1;
            }else{
                cmp_val = 0;
            }

            if(cmp_val > 0){
                if((*ppNode)->left == NULL){
                    (*ppNode)->left = new AVLTreeNode<T>(data);
                    *balance = 0;
                    mSize ++;
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
                    (*ppNode)->right = new AVLTreeNode<T>(data);
                    *balance = 0;
                    mSize ++;
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
                    if((*ppNode)->mData != data) {
                        printf("replace data value \n");
                        delete (*ppNode)->mData;
                        (*ppNode)->mData = data;
                    }
                    return ;
                }else{
                    delete (*ppNode)->mData;
                    (*ppNode)->mData = data; 
                    (*ppNode)->hide = 0;
                    return ;
                }
                *balance =1;
            }
        }

        void dump_data(T *data){
            printf(" %d   ",*((int *)data));
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
            avl_tree_layer_scan(parent);
        }

        void avl_tree_destroy(){
            if(mRoot != NULL){
                avl_tree_remove_left(&mRoot);
            }
            mSize = 0;
        }
        void avl_tree_remove_left(AVLTreeNode<T> **ppnode){
            if(*ppnode != NULL){
                if((*ppnode)->left != NULL){
                    avl_tree_remove_left(&((*ppnode)->left));
                }
                if((*ppnode)->right != NULL){
                    avl_tree_remove_right(&((*ppnode)->right));
                }
                delete *ppnode;
                *ppnode = NULL;
                mSize --;
            }
        }

        void avl_tree_remove_right(AVLTreeNode<T> **ppnode){
            if(*ppnode != NULL){
                if((*ppnode)->left != NULL){
                    avl_tree_remove_left(&((*ppnode)->left));
                }

                if((*ppnode)->right != NULL){
                    avl_tree_remove_right(&((*ppnode)->right));
                }
                delete *ppnode;
                *ppnode = NULL;
                mSize --;
            }
        }


        int mSize;
        AVLTreeNode<T> *mRoot;
};

#endif 
