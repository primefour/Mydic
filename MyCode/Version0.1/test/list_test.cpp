#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
//#include"memory_test_tool.h"
#include"BinTreeTemplate.h"
#include"AVLTreeTemplate.h"

int main(){
    List<int> a;

    int one = 1,two = 2,three = 3,four=4,five=5,six=6,seven = 7,eight =8,nine = 9,ten = 10;
    a.InsertTail(ten);
    a.InsertHead(one);
    a.InsertTail(two);
    a.InsertTail(three);
    a.InsertTail(four);
    a.InsertTail(five);
    a.InsertTail(six);

    a.DumpList();

    int tmp_int = 10;
    int tmp = 0;
    int *ptmp = a.FindItem(tmp_int);
    printf("tmp = %d \n",*ptmp);
    tmp_int = 13 ;
    ptmp= a.FindItem(tmp_int);
    if(ptmp == NULL){
        printf("find test OK\n");
    }else{
        printf("get a error for the template\n");
    }


    //a.RemoveItem(&tmp_int);
    tmp_int = 10;
    //a.RemoveItem(&tmp_int);
    a.DumpList();

    int hello = 30;
    
    a.InsertLocal(tmp_int,hello);

    a.DumpList();
    printf("ehlll kkkkkkkkkkkkkkkkkkkk\n");
    tmp_int = 2;
    a.InsertLocal(tmp_int,hello);

    a.DumpList();

    ptmp = a.GetNextItem(hello);
    printf("hello world ############\n");
    printf("tmp = %d \n",*ptmp);

    BinTree<int> tree;

    tree.InsertNode(one);
    tree.InsertNode(two);
    tree.InsertNode(one);
    printf("tree size = %d ",tree.GetSize());

    tree.InsertNode(five);
    tree.InsertNode(four);
    tree.InsertNode(ten);
    tree.InsertNode(seven);
    tree.InsertNode(six);
    tree.InsertNode(eight);
    tree.InsertNode(nine);
    tree.InsertNode(three);
    printf("tree size = %d ",tree.GetSize());
    if(tree.FindNode(five)){
        printf("fine OK\n");
    }else{
        printf("find fail \n");
    }

    if(tree.FindNode(11)){
        printf("fine OK\n");
    }else{
        printf("find fail \n");
    }

    tree.PreorderScan();

    printf("\n");
    tree.MidorderScan();

    printf("\n");
    tree.PostorderScan();

    printf("\n");
    tree.LayerScan();
    printf("\n");

    tree.RemoveNode(five);
    tree.PreorderScan();

    printf("\n");
    tree.MidorderScan();

    printf("\n");
    tree.PostorderScan();

    printf("\n");
    tree.LayerScan();

    printf("\n");
    tree.RemoveNode(one);
    tree.PreorderScan();
    printf("\n");
    tree.MidorderScan();
    printf("\n");
    tree.PostorderScan();
    printf("\n");
    tree.LayerScan();
    printf("\n");
/*
    AVLTreeTemplate<int> avltree;

    avltree.InsertNode(one);
    avltree.InsertNode(two);
    avltree.InsertNode(one);
    printf("avltree size = %d ",avltree.GetSize());

    avltree.InsertNode(five);
    avltree.InsertNode(four);
    avltree.InsertNode(ten);
    avltree.InsertNode(seven);
    avltree.InsertNode(six);
    avltree.InsertNode(eight);
    avltree.InsertNode(nine);
    avltree.InsertNode(three);
    printf("avltree size = %d ",avltree.GetSize());
    if(avltree.FindNode(five)){
        printf("fine OK\n");
    }else{
        printf("find fail \n");
    }

    if(avltree.FindNode(new int(11))){
        printf("fine OK\n");
    }else{
        printf("find fail \n");
    }

    avltree.PreorderScan();

    printf("\n");
    avltree.MidorderScan();

    printf("\n");
    avltree.PostorderScan();

    printf("\n");
    avltree.LayerScan();
    printf("\n");

    printf(" avltree.RemoveNode(five); \n");
    avltree.RemoveNode(five);
    avltree.PreorderScan();

    printf("\n");
    avltree.MidorderScan();

    printf("\n");
    avltree.PostorderScan();

    printf("\n");
    avltree.LayerScan();

    printf("\n");
    avltree.RemoveNode(one);
    avltree.PreorderScan();
    printf("\n");
    avltree.MidorderScan();
    printf("\n");
    avltree.PostorderScan();
    printf("\n");
    avltree.LayerScan();
    printf("\n");
    */


    return 0;
}
