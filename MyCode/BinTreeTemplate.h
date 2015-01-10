#ifndef __BIT_TREE_TEMPLATE_H__ 
#define __BIT_TREE_TEMPLATE_H__ 
template <class T>
class TreeNode{
    public:
    TreeNode(){
        left = NULL;
        right = NULL;
        mData = NULL;
        weight = 0;
    }
    TreeNode(T *data){
        mData = data;
        left = NULL;
        right = NULL;
        weight = 0;
    }
    TreeNode(TreeNode &node){
        mData = node.mData;
        left = NULL;
        right = NULL;
        weight = 0;
    }
    ~TreeNode(){
        if(mData != NULL){
            //delete mData;
        }
    }

    TreeNode<T> *left;
    TreeNode<T> *right;
    int weight;
    T *mData;
};


template <class T>
class BinTree{
    public:
        //void PreorderScan();

        void MidorderScan(){
            bin_tree_midorder_scan(mRoot);
        }

        //void PostorderScan();
        //void LayerScan();

        int FindNode(T *data){
            TreeNode<T> **ppNode = &mRoot;
            while(*ppNode != NULL){
                if(*((*ppNode)->mData) > *data){
                    ppNode = &((*ppNode)->left);
                }else if(*((*ppNode)->mData) < *data){
                    ppNode = &((*ppNode)->right);
                }else {
                    return 1;
                }
            }
            return 0;
        }

        int InsertNode(T *data){
            TreeNode<T> **ppNode = &mRoot;
            while(*ppNode != NULL){
                if(*((*ppNode)->mData) > *data){
                    ppNode = &((*ppNode)->left);
                }else if(*((*ppNode)->mData) < *data){
                    ppNode = &((*ppNode)->right);
                }else {
                    //have the same item
                    return -1;
                }
            }
            *ppNode = new TreeNode<T>(data);
            mSize ++;
            return 0;
        }

        void RemoveNode(T *data){
            TreeNode<T> **ppNode = &mRoot;
            while(*ppNode != NULL){
                if(*((*ppNode)->mData) > *data){
                    ppNode = &((*ppNode)->left);
                }else if(*((*ppNode)->mData) < *data){
                    ppNode = &((*ppNode)->right);
                }else {
                    //find the item;
                    break;
                }
            }
            //remove the Item
            if(*ppNode != NULL){
                TreeNode<T> *findNode = *ppNode;
                if((*ppNode)->left != NULL && (*ppNode)->right != NULL) {
                    TreeNode<T> **ppminNode = &((*ppNode)->right);
                    TreeNode<T> *minNode = NULL;
                    while((*ppminNode)->left != NULL){
                        ppminNode = &((*ppminNode)->left);
                    }
                    minNode = *ppminNode;
                    *ppminNode = (*ppminNode)->right;
                    minNode->left = findNode->left;
                    minNode->right = findNode->right;
                    *ppNode = minNode;
                    delete findNode;
                }else if((*ppNode)->left != NULL){
                    *ppNode = (*ppNode)->left;
                    delete findNode;
                }else if((*ppNode)->right != NULL){
                    *ppNode = (*ppNode)->right;
                    delete findNode;
                }else{
                    delete *ppNode;
                    *ppNode = NULL;
                }
                mSize--;
            }
        }

        int GetSize(){
            return mSize;
        }
        int IsLeaf(TreeNode<T> *node){
            return (node && (node->left == NULL && node->right == NULL));
        }

        BinTree(){
            mSize = 0;
            mRoot = NULL;
        }
        BinTree(BinTree & tree){
            mSize = tree.mSize;
            mRoot = tree.mRoot;
        }
        ~BinTree(){
            bin_tree_destroy();
        }
        
    private:
        void dump_data(T *data){
            printf(" %d   ",*((int *)data));
        }
        void bin_tree_midorder_scan(TreeNode<T> *node){
            if(node != NULL){
                bin_tree_midorder_scan(node->left);
                dump_data(node->mData);
                bin_tree_midorder_scan(node->right);
            }
        }
        void bin_tree_destroy(){
            if(mRoot != NULL){
                bin_tree_remove_left(&mRoot);
            }
            mSize = 0;
        }
        void bin_tree_remove_left(TreeNode<T> **ppnode){
            if(*ppnode != NULL){
                if((*ppnode)->left != NULL){
                    bin_tree_remove_left(&((*ppnode)->left));
                }
                if((*ppnode)->right != NULL){
                    bin_tree_remove_right(&((*ppnode)->right));
                }
                delete *ppnode;
                *ppnode = NULL;
                mSize --;
            }
        }

        void bin_tree_remove_right(TreeNode<T> **ppnode){
            if(*ppnode != NULL){
                if((*ppnode)->left != NULL){
                    bin_tree_remove_left(&((*ppnode)->left));
                }

                if((*ppnode)->right != NULL){
                    bin_tree_remove_right(&((*ppnode)->right));
                }
                delete *ppnode;
                *ppnode = NULL;
                mSize --;
            }
        }

        int bin_tree_ins_left(TreeNode<T> *node,T *data){
            if(node != NULL){
                if(node->left == NULL){
                    node->left = new TreeNode<T>(data);
                }else{
                    return -1;
                }
            }else{
                if(mRoot == NULL){
                    mRoot = new TreeNode<T>(data);
                }else{
                    return -1;
                }
            }
            return 0;
        }
        /*
         * create a new node with the value of data and insert to the node's right 
         * if node's right is not NULL will return -1
         */
        int bin_tree_ins_right(TreeNode<T> *node,T *data){
            if(node != NULL){
                if(node->right == NULL){
                    node->right = new TreeNode<T>(data);
                }else{
                    return -1;
                }
            }else{
                if(mRoot == NULL){
                    mRoot = new TreeNode<T>(data);
                }else{
                    return -1;
                }
            }
            return 0;
        }
        int mSize ;
        TreeNode<T> *mRoot;
};
#endif 

