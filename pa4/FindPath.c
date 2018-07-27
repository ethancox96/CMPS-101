//Ethan Cox
//etecox
//pa4
//FindPath.c
//Uses the GraphADT to preform calculations

//include .h files and define macros
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Graph.h"

#define MAX_LEN 160
#define INF  -1
#define NIL  -2

int main(int argc, char* argv[]){
   FILE *in, *out;
   char line[MAX_LEN];
   
   //check args length
   if (argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   //open in and out files
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if (in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if (out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   //read in first line of input file to get size of graph
   fgets(line, MAX_LEN, in);
   int size = 0;
   sscanf(line, "%d", &size);

   //read in all edge lines of input file and addEdges to graph
   int x = 0;
   int y = 0;
   Graph G = newGraph(size);
   while( fgets(line, MAX_LEN, in) != NULL){
      sscanf(line, "%d %d", &x, &y);
      //if x = 0 and y = 0 no more edges to be added to graph
      if (x == 0 && y == 0){
	 break;
      }
      else{
	 //add edge from x to y to Graph
	 addEdge(G, x, y);
      }
   }

   printGraph(out, G);

   //read in to all pairs of vertices to check for path between them
   int dist;
   List L;
   while (fgets(line, MAX_LEN, in) != NULL){
      sscanf(line, "%d %d", &x, &y);
      //No more vertices to be read in, exit while loop
      if (x == 0 && y == 0){
	 break;
      }
      else{
	 //run BFS to create BFS tree
	 BFS(G, x);
	 fprintf(out, "\n");
	 //get distance between vertices
	 dist = getDist(G, y);
	 //if no path exits
	 if (dist == INF){
	    fprintf(out, "The distance from %d to %d is infinity\n", x, y);
	    fprintf(out, "No %d-%d path exists\n", x, y);
	 }
	 //if a path exists
	 else{
	    fprintf(out, "The distance from %d to %d is %d\n", x, y, dist);
	    L = newList();
	    //get and print out path
	    getPath(L, G, y);
	    fprintf(out, "A shortest %d-%d path is: ", x, y);
	    printList(out, L);
	    fprintf(out, "\n");
	 }
	 freeList(&L);
      }
   }

   freeGraph(&G);
   fclose(in);
   fclose(out);
   return 0;
}








