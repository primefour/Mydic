#include<stdio.h>
#include"AVLTreeTemplate.h"
#include"String8.h"
#include<unistd.h>



int main(){
    AVLTreeTemplate<int> avltree;
    int one = 1,two = 2,three = 3,four=4,five=5,six=6,seven = 7,eight =8,nine = 9,ten = 10;

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
    printf("avltree size = %d \n",avltree.GetSize());

    if(avltree.FindNode(five)){
        printf("fine OK\n");
    }else{
        printf("find fail \n");
    }

    if(avltree.FindNode(11)){
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

    String8 a("hello world!\n");
    printf("a = %s ",a.string());
    String8 b("you are right ");
    String8 c = a + b ;
    printf("c = %s \n",c.string());
    String8 d("hello = world ");
    printf("hello = %s \n",d.getStringValue('=').string());
    String8 value = c.getStringValue('=');
    if(value.isEmpty()){
        printf("value is empty \n");
    }else{
        printf("%s \n",value.string());
    }

    return 0;
}
