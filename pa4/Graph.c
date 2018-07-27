//Ethan Cox
//etecox
//pa4
//Graph.c
//Implements the GraphADT

//Macros and .h files-------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
//#include"List.h"
#include"Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define INF -1
#define NIL -2

//structs-------------------------------------------------------------------

//private Graph Object
typedef struct GraphObj{
   List *list;
   int *color;
   int *parent;
   int *distance;
   int order;
   int size;
   int source;
} GraphObj;

//Constructors/Destructors--------------------------------------------------

//Graph newGraph(int n);
//creates a new Graph by initializing all the fields in the struct
//each field will contain n elements
Graph newGraph(int n){
   Graph G;
   G = malloc(sizeof(GraphObj));
   assert(G != NULL);
   G->list = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   for (int i = 1; i <= n; i++){
      G->list[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->distance[i] = INF;
   }
   G->order = n;
   G->size = 0;
   G->source = NIL;
   return(G);
}

//void freeGraph(Graph* pG)
//Frees heap memory pointed to by *pG and sets *pG to NULL
void freeGraph(Graph* pG){
   Graph G = *pG;
   for (int i = 0; i < (G->order+1); i++){
      freeList(&(G->list[i]));
   }
   free(G->list);
   free(G->color);
   free(G->distance);
   free(G->parent);
   free(*pG);
   *pG = NULL;
}

//Access functions-----------------------------------------------------------
//int getOrder(Graph G);
//returns the Order (#of vertices) of the Graph
int getOrder(Graph G){
   return G->order;
}

//int getSize(Graph G)
//returns the size (# of edges) of the Graph
int getSize(Graph G){
   return G->size;
}

//int getSource(Graph G)
//returns the returns the source vertex most recently used in BFS
int getSource(Graph G){
   return G->source;
}

//int getParent(Graph G, int u)
//returns the parent of vertex u if not NIL
int getParent(Graph G, int u){
   if (u > getOrder(G) || u < 1){
      printf("Calling getParent with vertex out of bounds\n");
      exit(1);
   }
   if (u != NIL){
      return G->parent[u];
   }
   else{
      return NIL;
   }
}

//int getDist(Graph G, int u)
//return the Distance from the source to vertex u
int getDist(Graph G, int u){
   if (u > getOrder(G) || u < 1){
      printf("Calling getDist with vertex out of bounds\n");
      exit(1);
   }
   if (u != INF){
      return G->distance[u];
   }
   else{
      return NIL;
   }
}

//void getPath(List L, Graph G, int u)
//append the vertices of the shotest path to u to List L or NIL if none exits
void getPath(List L, Graph G, int u){
   if (getSource(G) == NIL){
      printf("Calling getPath() with NULL source\n");
   }
   if (u > getOrder(G) || u < 1){
      printf("Calling getPath() with vertex out of bounds\n");
      exit(1);
   }
   int source = G->source;
   if (u == source){
      prepend(L, u);
   }
   else{
      int dist = getDist(G, u);
      for (int i = 0; i <= dist; i++){
	 prepend(L, u);
	 u = G->parent[u];
      }
   }
}

//Manipulation functions----------------------------------------------------
//void makeNull(Graph G)
//returns G to its original state
void makeNull(Graph G){
   for (int i = 1; i <= G->order; i++){
      clear(G->list[i]);
      G->color[i] = WHITE;
      G->distance[i] = INF;
      G->parent[i] = NIL;
   }
   G->size = 0;
   G->source = NIL;
}

//void addEdge(Graph G, int u, int v)
//inserts new edge joining u to v
//adds v to adjacency list of u and u to adjacency list of v
void addEdge(Graph G, int u, int v){
  //check that u and v are valid vertices
   if ((u > getOrder(G) || u < 1) || (v > getOrder(G) || v < 1)){
      printf("Calling addEdge with vertex out of bounds\n");
      exit(1);
   }
   addArc(G, u, v);
   addArc(G, v, u);
   //addArc was called twice so G->size was increased twice, but we only want
   //to add one edge so we must subtract one from size now
   G->size--;
}

//void addArc(Graph G, int u, int v)
//adds v to the adjacency list of u
void addArc(Graph G, int u, int v){
   if ((u > getOrder(G) || u < 1) || (v > getOrder(G) || v < 1)){
      printf("Calling addEdge with vertex out of bounds\n");
      exit(1);
   }
   List L = G->list[u];
   for (moveFront(L); index(L) >= 0; moveNext(L)){
      if (v < get(L)){
	 insertBefore(L, v);
	 break;
      }
   }
   if (index(L) == -1){
      append(L, v);
   }
   G->size++;
}

//void BFS(Graph G, int s)
//runs BFS on G starting from vertex s
void BFS(Graph G, int s){
   for (int i = 1; i <= (G->order); i++){
      G->color[i] = WHITE;
      G->distance[i] = INF;
      G->parent[i] = NIL;
   }

   //initialize components of s
   G->source = s;
   G->color[s] = GRAY;
   G->distance[s] = 0;
   G->parent[s] = NIL;

   //create and initialize new list to be used as FIFO Queue for remainder of BFS
   List L = newList();
   prepend(L, s);
   int u;
   while (length(L) > 0){
      u = back(L);
      deleteBack(L);
      //get adjugate list of u
      List adj = G->list[u];
      for (moveFront(adj); index(adj) >= 0; moveNext(adj)){
         int a = get(adj);
         if (G->color[a] == WHITE){
	    G->color[a] = GRAY;
	    G->distance[a] = G->distance[u]+1;
	    G->parent[a] = u;
	    prepend(L, a);
	 }
      } 
   }
   freeList(&L);
}

//Other functions--------------------------------------------------------------
//void printGraph(FILE* out, Graph G)
//Prints out the Graph
void printGraph(FILE* out, Graph G){
   if (out == NULL || G == NULL){
      printf("Calling printGraph() on a null reference\n");
      exit(1);
   }
   for (int i = 1; i <= getOrder(G); i++){
       fprintf(out, "%d: ", i);
       printList(out, G->list[i]);
       fprintf(out, "\n");
   }
}







