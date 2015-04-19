#ifndef __GOLDEN_DICT_LIST__
#define __GOLDEN_DICT_LIST__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define offset(type,item)   ((unsigned long)((unsigned char *)&(((type *)0)->item)))
#define contain_of(ptr,type,item) ((type *)(((unsigned char *)ptr) - offset(type,item)))

template<class T>
class ListItem{
    public:
        ListItem<T> *prev;
        ListItem<T> *next;
        T mData;

        ListItem(){
            prev = this;
            next = this;
        }

        ListItem(T &data){
            mData = data;
            prev = this;
            next = this;
        }

        ListItem(const ListItem &item){
            mData = item.mData;
        }

        ~ListItem(){
        }
}; 


template<class T>
class List{
    public:
        List();
        ~List();
        List(const List &list);
        void DumpList();
        void InsertTail(T &data);
        void InsertHead(T &data);
        void RemoveItem(T &data);
        void InsertLocal(T &prev_data,T &data);

        T* FindItem(const T &data);
        T* GetPrevItem(const T &data);
        T* GetNextItem(const T &data);
    private:
        void remove_list_item_(ListItem<T> *prev_item,ListItem<T> *next_item,ListItem<T> *remove_item);
        void add_list_item_(ListItem<T>* prev_item,ListItem<T> *next_item,ListItem<T> *insert_item);
        ListItem<T> mHead;
};

template <class T >
List<T>::List(){
    mHead.prev = &mHead;
    mHead.next = &mHead;
}

template <class T >
List<T>::List(const List &list){
    mHead = list.mHead;
}


template <class T >
List<T>::~List(){
    ListItem<T> *TmpItem = mHead.next; 
    while(TmpItem != &mHead){ 
        remove_list_item_(TmpItem->prev,TmpItem->next,TmpItem);
        delete TmpItem;
        TmpItem = mHead.next;
    } 
}

template <class T >
void List<T>::remove_list_item_(ListItem<T> *prev_item,ListItem<T> *next_item,ListItem<T> *remove_item){
    prev_item->next = next_item;
    next_item->prev = prev_item;
    remove_item->next = remove_item;
    remove_item->prev = remove_item;
}


template <class T >
void List<T>::DumpList(){
    ListItem<T> *tmp_head = mHead.next; 
    while(tmp_head != &mHead){ 
        printf("dump list %d \n",(tmp_head->mData));
        tmp_head = tmp_head->next;
    } 
}


template <class T >
T* List<T>::FindItem(const T &data){
    ListItem<T> *TmpItem = mHead.next; 
    while(TmpItem != &mHead){ 
        if((data) == (TmpItem->mData)){
            return & TmpItem->mData;
        }
        TmpItem = TmpItem->next;
    } 
    return NULL;
}


template <class T >
void List<T>::add_list_item_(ListItem<T>* prev_item,ListItem<T> *next_item,ListItem<T> *insert_item){
    prev_item->next = insert_item;
    insert_item->prev = prev_item;
    insert_item->next = next_item;
    next_item->prev = insert_item;
}

template <class T >
void List<T>::InsertTail(T &data){
    ListItem<T> *newItem= new ListItem<T>(data);
    add_list_item_(mHead.prev,&mHead,newItem);
}

template <class T >
void List<T>::InsertHead(T &data){
    ListItem<T> *newItem= new ListItem<T>(data);
    add_list_item_(&mHead,mHead.next,newItem);
}

template <class T >
T* List<T>::GetPrevItem(const T &data){
    ListItem<T> *TmpItem = mHead.next; 
    while(TmpItem != &mHead){ 
        if(data == (TmpItem->mData)){
            break;
        }
        TmpItem = TmpItem->next;
    } 

    if(TmpItem == &mHead){
        return NULL;
    }
    return &TmpItem->prev->mData;
}

template <class T >
T* List<T>::GetNextItem(const T &data){
    ListItem<T> *TmpItem = mHead.next; 
    while(TmpItem != &mHead){ 
        if(data == (TmpItem->mData)){
            break;
        }
        TmpItem = TmpItem->next;
    } 

    if(TmpItem == &mHead){
        return NULL;
    }
    return &TmpItem->next->mData;
}


template <class T >
void List<T>::InsertLocal(T&prev_data,T &data){
    ListItem<T> *TmpItem = mHead.next; 
    while(TmpItem != &mHead){ 
        if(prev_data == (TmpItem->mData)){
            break;
        }
        TmpItem = TmpItem->next;
    } 
    if(TmpItem == &mHead || TmpItem->next == &mHead){
        InsertTail(data);
    }else{
        ListItem<T> *newItem= new ListItem<T>(data);
        add_list_item_(TmpItem,TmpItem->next,newItem);
    }
}

template <class T >
void List<T>::RemoveItem(T& data){
    ListItem<T> *TmpItem = mHead.next; 
    while(TmpItem != &mHead){ 
        if(data == (TmpItem->mData)){
            break;
        }
        TmpItem = TmpItem->next;
    } 
    if(TmpItem != &mHead){
        remove_list_item_(TmpItem->prev,TmpItem->next,TmpItem);
    }else{
        return ;
    }
    delete TmpItem ;
}

#endif //__GOLDEN_DICT_LIST__
