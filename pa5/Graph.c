//Ethan Cox
//etecox
//pa5
//Graph.c
//Implementation of the GraphADT for DFS

//Macros and .h files-----------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define INF -1
#define NIL 0

//structs-----------------------------------------------------------------
//private Graph Object
typedef struct GraphObj{
   List *list;
   int *color;
   int *parent;
   int *discover;
   int *finish;
   int order;
   int size;
} GraphObj;

//Constructors/Destructors-------------------------------------------------
//Graph newGraph(int n)
//creates a new Graph by initializing all the fields in the struct
//each field will contain n elements
Graph newGraph(int n){
   Graph G;
   G = malloc(sizeof(GraphObj));
   assert(G != NULL);
   G->list = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1, sizeof(int));
   for (int i = 1; i <= n; i++){
      G->list[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = 0;
      G->finish[i] = 0;
   }
   G->order = n;
   G->size = 0;
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
   free(G->parent);
   free(G->discover);
   free(G->finish);
   free(*pG);
   *pG = NULL;
}

//Access functions---------------------------------------------------------
//int getOrder()
//returns the Order(#of vertices) of the Graph
int getOrder(Graph G){
   if (G == NULL){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(1);
   }
   return G->order;
}

//int getSize()
//returns the size(#of edges) of the Graph
int getSize(Graph G){
   if (G == NULL){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(1);
   }
   return G->size;
}

//int getParent()
//returns the parent of u
//pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(1);
   }
   if (u > getOrder(G) || u < 1){
      printf("calling getParent() with vertex out of bounds\n");
      exit(1);
   }
   //if u has no parent
   return G->parent[u];
}

//int getDiscover()
//returns the discovery time of u
//pre: 1<=u<=getOrder(G)
int getDiscover(Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(1);
   }
   if (u > getOrder(G) || u < 1){
      printf("calling getParent() with vertex out of bounds\n");
      exit(1);
   }
   return G->discover[u];
}

//int getFinish()
//returns the finish time of u
//pre: 1<=u<=getOrder(G)
int getFinish(Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(1);
   }
   if (u > getOrder(G) || u < 1){
      printf("Graph Error: calling getFinish() with vertex out of bounds\n");
      exit(1);
   }
   return G->finish[u];
}

//Manipulations procedures--------------------------------------------------
//void addArc(Graph G, int u, int v);
//adds v to the adjacency list of u
//pre: 1<=u<=getOrder(G), 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v){
   if (G == NULL){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(1);
   }
   if ((u > getOrder(G) || u < 1) || (v > getOrder(G) || v < 1)){
      printf("Graph Error: calling addArc() with vertex out of bounds\n");
      exit(1);
   }
   //find the place in u's adjacency list where v belongs
   List L = G->list[u];
   for (moveFront(L); index(L) >= 0; moveNext(L)){
      if (v < get(L)){
         insertBefore(L, v);
         break;
      }
   }
   //if v belongs at the end of u's adjacency list
   if (index(L) == -1){
      append(L, v);
   }
   G->size++;
}

//void addEdge(Graph G, int u, int v)
//inserts new edge joining u to v
//adds v to adjacency list of u and u to adjacency list of v
void addEdge(Graph G, int u, int v){
   if (G == NULL){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(1);
   }
    //check that u and v are valid vertices
    if ((u > getOrder(G) || u < 1) || (v > getOrder(G) || v < 1)){
       printf("Graph Error: calling addEdge with vertex out of bounds\n");
       exit(1);
    }
    //add u to v's adjacency list and v to u's adjacency list
    addArc(G, u, v);
    addArc(G, v, u);
   //addArc was called twice so G->size was increased twice, but we only want
   //to add one edge so we must subtract one from size now
   G->size--;
}

//void Visit()
//private helper function for DFS
void Visit(List S, Graph G, int u, int *time){
   if (G == NULL){
      printf("Graph Error: calling Visit() on NULL Graph reference\n");
      exit(1);
   }
   //set u's discovery time
   *time += 1;
   G->discover[u] = *time;
   G->color[u] = GRAY;
   int v;
   //iterate through u's adjacency list
   for (moveFront(G->list[u]); index(G->list[u]) >= 0; moveNext(G->list[u])){
      v = get(G->list[u]);
      //if u and v are an edge in the forest establish the connection
      if (G->color[v] == WHITE){
         G->parent[v] = u;
         Visit(S, G, v, time);
      }
   }
   //turn u black and set its finish time
   G->color[u] = BLACK;
   *time += 1;
   G->finish[u] = *time;
   prepend(S, u);
}

//void DFS(Graph G, List S)
//runs DFS on vertices in the order of List S
//Pre: length(S) == getOrder(G)
void DFS(Graph G, List S){
   if (G == NULL){
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(1);
   }
   if (length(S) != getOrder(G)){
      printf("called DFS without matching List and Graph sizes\n");
      exit(1);
   }
   //set u's components to their original states
   for (int i = 1; i <= getOrder(G); i++){
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = 0;
      G->finish[i] = 0;
   }
   int time = 0;
   int u = 0;
   //iterate through the vertices in List S and add all conection from list u
   //to the DFS forest
   for (moveFront(S); index(S) >= 0; moveNext(S)){
      u = get(S);
      if (G->color[u] == WHITE){
	 Visit(S, G, u, &time);
      }
   }

   //remove the indeces that were in the List to start with
   int s;
   for (s = length(S)/2; s > 0; s--){
      deleteBack(S);
   }
}

//Other Functions--------------------------------------------------------------

//Graph transpose()
//returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
   if (G == NULL){
      printf("Graph Error: calling transpose() on NULL Graph reference\n");
      exit(1);
   }
   int n = getOrder(G);
   Graph H = newGraph(n);
   int u;
   for (int i = 1; i <= getOrder(G); i++){
      for (moveFront(G->list[i]); index(G->list[i]) >= 0; moveNext(G->list[i])){
	 u = get(G->list[i]);
	 addArc(H, u, i);
	 G->size++;
      }
   }
   return H;
}

//Graph copyGraph()
//returns a reference to a graph that is a copy of G
Graph copyGraph(Graph G){
   if (G == NULL){
      printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(1);
   }
   int n = getOrder(G);
   Graph H = newGraph(n);
   int u;
   for (int i = 1; i <= getOrder(G); i++){
       for (moveFront(G->list[i]); index(G->list[i]) >= 0; moveNext(G->list[i])){
         u = get(G->list[i]);
         addArc(H, i, u);
	 G->size++;
      }
   }
   return H;
}

//void printGraph(FILE* out, Graph G)
//prints out the adjacency list representation of G to the out file
void printGraph(FILE* out, Graph G){
   if (G == NULL){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++){
      fprintf(out, "%d: ", i);
      printList(out, G->list[i]);
      fprintf(out, "\n");
   }
}








