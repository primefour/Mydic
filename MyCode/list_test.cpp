#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"memory_test_tool.h"
#include"BinTreeTemplate.h"

int main(){
    List<int> a;

    int *ten = new int(10);
    int *one = new int(1);
    int *two = new int(2);
    int *three = new int(3);
    int *four = new int(4);
    int *five = new int(5); 
    int *six = new int(6);
    int *seven = new int(7) ;
    int *eight = new int(8);
    int *nine = new int(9);

    a.InsertTail(ten);
    a.InsertHead(one);
    a.InsertTail(two);
    a.InsertTail(three);
    a.InsertTail(four);
    a.InsertTail(five);
    a.InsertTail(six);

    a.DumpList();

    int tmp_int = 10;
    int *tmp = a.FindItem(&tmp_int);
    printf("tmp = %d \n",*tmp);
    tmp_int = 13 ;
    tmp = a.FindItem(&tmp_int);
    if(tmp == NULL){
        printf("find test OK\n");
    }else{
        printf("get a error for the template\n");
    }


    //a.RemoveItem(&tmp_int);
    tmp_int = 10;
    //a.RemoveItem(&tmp_int);
    a.DumpList();

    int *hello = new int(30);
    
    tmp = a.InsertLocal(&tmp_int,hello);

    a.DumpList();
    printf("ehlll kkkkkkkkkkkkkkkkkkkk\n");
    tmp_int = 2;
    tmp = a.InsertLocal(&tmp_int,hello);

    a.DumpList();

    tmp = a.GetNextItem(hello);
    printf("hello world ############\n");
    printf("tmp = %d \n",*tmp);

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

    if(tree.FindNode(new int(11))){
        printf("fine OK\n");
    }else{
        printf("find fail \n");
    }

    tree.MidorderScan();
    printf("\n");

    tree.RemoveNode(five);
    tree.MidorderScan();
    printf("\n");
    tree.RemoveNode(one);
    tree.MidorderScan();
    printf("\n");

    return 0;
}
