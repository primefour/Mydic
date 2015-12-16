#include"GoldenGraphic.h"
#include<string>
#include<string.h>
#include<map>


int main(int argc,char **argv){
    Graphic<string,int> graph(0);
    string tmp("Hello");
    graph.InsertVectex(tmp);
    string tmp1("world");
    int ten = 10;
    graph.InsertEdge(tmp,tmp1,ten);
    vector< Graphic<string,int>* > tt;
    graph.GetCircleAndConnectivity(tt);


    /*
    graph.InsertEdge("Hello","You",10);
    graph.InsertEdge("Hello","Me",10);
    graph.InsertEdge("Hello","He",10);
    graph.InsertEdge("He","is",10);
    graph.InsertEdge("is","Wonderful",10);
    */
    return 0;
}
