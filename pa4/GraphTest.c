//Ethan Cox
//etecox
//pa4
//GraphTest.c
//Tests the GraphADT

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int n = 7;
   List L = newList();
   Graph G = NULL;

   G = newGraph(n);
   addEdge(G, 1, 2);
   addEdge(G, 2, 3);
   addEdge(G, 3, 4);
   addEdge(G, 2, 5);
   addEdge(G, 3, 5);
   addEdge(G, 4, 5);
   addEdge(G, 4, 6);
   addEdge(G, 4, 7);
   addEdge(G, 5, 7);
   printGraph(stdout, G);

   BFS(G, 1);
   printf("order = %d\n", getOrder(G));
   printf("size = %d\n", getSize(G));
   printf("parent = %d\n", getParent(G, 7));
   printf("distance = %d\n", getDist(G, 7));
   getPath(L, G, 7);
   printList(stdout, L);
   printf("\n");
}





