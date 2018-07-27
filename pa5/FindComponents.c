//Ethan Cox
//etecox
//pa5
//FindComponenets.c
//Handles the input/output for pa5 and finds the scc's for the graphs provided

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Graph.h"

#define MAX_LEN 160
#define INF  -1
#define NIL  0

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

   //read in the first line of input file to get size of graph
   fgets(line, MAX_LEN, in);
   int size = 0;
   sscanf(line, "%d", &size);

   //read in all edge lines of input file and addArcs to graph
   int x = 0;
   int y = 0;
   Graph G = newGraph(size);
   while( fgets(line, MAX_LEN, in) != NULL){
      sscanf(line, "%d %d", &x, &y);
      //if x = 0 anx y = 0 no more arcs to be added to graph
      if (x == 0 && y == 0){
         break;
      }
      else{
	 //add edge from x to y to Graph
	 addArc(G, x, y);
      }
   }
   fprintf(out, "Adjacency list representation of G: \n");
   printGraph(out, G);

   //create List of vertices to be used during DFS
   List L = newList();
   for (int i = 1; i <= size; i++){
      append(L, i);
   }
   //get transpose of G
   Graph T = transpose(G);
   
   //run DFS on G in increasing vertice order
   DFS(G, L);
   //run DFS on T in order of decreasing finish times
   DFS(T, L);

   //get the number of strongly connected components
   int components = 0;
   for (moveFront(L); index(L) >= 0; moveNext(L)){
      //if the parent of get(S) is NIL we have a strongly connected component
      if(getParent(T, get(L)) == NIL){
	 components++;
      }
   }

   //create an array of lists to hold all of the strongly connected components
   List numComponents[components];
   for (int i = 0; i < components; i++){
      numComponents[i] = newList();
   }

   int m = 0;
   int n;
   //iterate through list backwards since it is in reverse order of finish time
   for (moveBack(L); index(L) >= 0; movePrev(L)){
      n = get(L);
      if (m == components){
         break;
      }
      prepend(numComponents[m], n);
      if (getParent(T, n) == NIL){
	 m++;
      }
   }

   //print out the adjacency list of G
   fprintf(out, "\nG contains %d strongly connected components: \n", components);
   for (int j = 0; j < components; j++){
      fprintf(out, "Component %d: ", j+1);
      printList(out, numComponents[j]);
      fprintf(out, "\n");
      //free memory associated with list
      freeList(&(numComponents[j]));
   }

   //free memory associated with both Graphs and the List
   freeGraph(&G);
   freeGraph(&T);
   freeList(&L);

   //close files and return from main
   fclose(in);
   fclose(out);
   return(0);
}








