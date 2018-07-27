//Ethan Cox
//etecox
//GraphTest.c
//pa5
//Tests the GraphADT

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, n = 6;
   List S = newList();
   Graph G = newGraph(n);
   Graph T = NULL, C = NULL;

   for (i=1; i<= n; i++){
      append(S, i);
   }

   addArc(G, 1,2);
   addArc(G, 1,4);
   addArc(G, 2,5);
   addArc(G, 2,3);
   addArc(G, 2,6);
   addArc(G, 5,3);
   addArc(G, 5,4);
   addArc(G, 5,6);
   printGraph(stdout, G);

   DFS(G, S);
   printf("\n");
   printf("x: d f p\n");
   for (i = 1; i<n; i++){
      printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   printf("\n");
   printList(stdout, S);
   printf("\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

printf("List size = %d\n", length(S));
printf("Graph size = %d\n", getOrder(T)); 
   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}






