#include"GoldenGraphic.h"
#include<string>
#include<string.h>
#include<map>
#include<stdio.h>


int main(int argc,char **argv){
    Graphic<string,int> graph(0);
    string tmp("Hello");
    graph.InsertVectex(tmp);

    printf("####vectex is %d  \n",graph.GetVectexCount());
    string tmp1("world");
    int ten = 10;
    graph.InsertEdge(tmp,tmp1,ten);
    vector< Graphic<string,int>* > tt;
    printf("####vectex is %d  \n",graph.GetVectexCount());
    printf("kkkkk edge is %d  \n",graph.GetEdgesCount());
    graph.GetConnectComponount(tt);
    string you("You");
    string you1("You1");
    string you2("You2");
    string you3("You3");
    string you4("You4");
    string you5("You5");

    graph.InsertEdge(tmp,you,ten);
  
    printf("xxxvectex is %d  \n",graph.GetVectexCount());
    printf("edge is %d  \n",graph.GetEdgesCount());
    graph.InsertEdge(tmp,you1,ten);

    printf("xxxvectex is %d  \n",graph.GetVectexCount());

    printf("edge is %d  \n",graph.GetEdgesCount());
    graph.InsertEdge(you,you1,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());

    printf("edge is %d  \n",graph.GetEdgesCount());
    graph.InsertEdge(you1,you2,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());

    printf("edge is %d  \n",graph.GetEdgesCount());
    graph.InsertEdge(you2,you3,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());
    printf("edge is %d  \n",graph.GetEdgesCount());

    Graphic<string,int> yy(1) ;
    Graphic<string,int> xx(1) ;


    string he("he");
    string is("is");
    string world("world");
    string des("des");
    string five("five");
    string six("six");
    string seven("seven");
    int one = 1;
    int four = 4;
    int eight = 9 ;
    int two = 2;
    int three = 3;

    yy.InsertEdge(he,is,one);
    yy.InsertEdge(he,five,four);
    yy.InsertEdge(is,world,eight);
    yy.InsertEdge(five,six,two);
    yy.InsertEdge(six,des,ten);
    yy.InsertEdge(world,des,three);
    yy.InsertEdge(five,seven,three);

    printf("vectex is %d  \n",yy.GetVectexCount());
    printf("###edge is %d  \n",yy.GetEdgesCount());

    yy.GetShortPath(&xx,he,des,0);
    return 0;
}
