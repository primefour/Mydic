#include"GoldenGraphic.h"
#include<string>
#include<string.h>
#include<map>
#include<stdio.h>


int main(int argc,char **argv){
    Graphic<string,int> graph(0);
    string tmp("Hello");
    graph.InsertVectex(tmp);
    string tmp1("world");
    int ten = 10;
    graph.InsertEdge(tmp,tmp1,ten);
    vector< Graphic<string,int>* > tt;

    printf("vectex is %d  \n",graph.GetVectexCount());
    graph.GetConnectComponount(tt);

    printf("vectex is %d  \n",graph.GetVectexCount());
    string you("You");

    string you1("You1");
    string you2("You2");
    string you3("You3");
    string you4("You4");
    string you5("You5");

    graph.InsertEdge(tmp,you,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());
    graph.InsertEdge(tmp,you1,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());
    graph.InsertEdge(you,you1,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());
    graph.InsertEdge(you1,you2,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());
    graph.InsertEdge(you2,you3,ten);

    printf("vectex is %d  \n",graph.GetVectexCount());
    printf("vectex is %d  \n",graph.GetVectexCount());
    printf("edge is %d  \n",graph.GetEdgesCount());


    return 0;
}
