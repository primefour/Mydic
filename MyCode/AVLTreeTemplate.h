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
