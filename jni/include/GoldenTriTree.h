#ifndef GOLDEN_TRI_TREE_H__
#define GOLDEN_TRI_TREE_H__
#include<vector>
#include<algorithm>
#include<assert.h>

using namespace std;

template <class ItemType,class LeavesType>
struct TriNode{
    TriNode(){
    }
    TriNode(ItemType data){
        this->data = data;
    }

    TriNode<ItemType,LeavesType>* InsertChildren(ItemType &data){
        TriNode<ItemType,LeavesType> *node = FindInChildren(data);
        if(node == NULL){
            children.push_back(TriNode<ItemType,LeavesType>(data));
            return &(children.back());
        }else{
            return node;
        }
    }

    TriNode<ItemType,LeavesType>* InsertLeaves(LeavesType &data){
        typename vector<LeavesType>::iterator tmp = find(leaves.begin(),leaves.end(),data);
        if(tmp == leaves.end()){
            leaves.push_back(data);
        }
        return this;
    }

    TriNode<ItemType,LeavesType>* FindInChildren(ItemType &data){
        typename vector<TriNode<ItemType,LeavesType> >::iterator begin = children.begin(); 
        typename vector<TriNode<ItemType,LeavesType> >::iterator end = children.end();
        while(begin != end){
            if(begin->data == data){
                break;
            }
            begin ++;
        }
        if(begin == end){
            return NULL;
        }else{
            return &(*begin);
        }
    }

    const vector<LeavesType>& GetLeaves() const {
        return leaves;
    }

    bool isChildrenEmpty(){
        return children.empty();
    }

    bool isLeavesEmpty(){
        return leaves.empty();
    }

    ItemType data; 
    vector<TriNode<ItemType,LeavesType> > children;
    vector<LeavesType> leaves;
};


template <class DataType,class ItemType,class LeavesType>
class TriTree{
    public:
        TriTree(){
            mRoot = new TriNode<ItemType,LeavesType>();
            assert(mRoot != NULL);
        }

        TriNode<ItemType,LeavesType>* InsertData(DataType &data){
            typename DataType::iterator begin = data.begin();
            typename DataType::iterator end = data.end();
            TriNode<ItemType,LeavesType> *tmp = mRoot;
            TriNode<ItemType,LeavesType> *next = tmp;
            while(begin != end){
                tmp = next;
                next = tmp->InsertChildren(*begin);
                begin ++;
            }
            return tmp;
        }

        TriNode<ItemType,LeavesType>* FindData(DataType &data){
            typename DataType::iterator begin = data.begin();
            typename DataType::iterator end = data.end();
            TriNode<ItemType,LeavesType> *tmp = mRoot;
            TriNode<ItemType,LeavesType> *next = tmp;

            while(begin != end && next != NULL){
                tmp = next;
                next = tmp->FindInChildren(*begin);
                begin ++;
            }
            if(begin == end && tmp != NULL){
                return tmp;
            }else{
                return NULL;
            }
        }

    private:
        TriNode<ItemType,LeavesType> *mRoot;

};

#endif

