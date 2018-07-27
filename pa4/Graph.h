//Ethan Cox
//etecox
//pa4
//Graph.h
//Header file for the GraphADT

#ifndef _GRAPH_H_INCLUDE
#define _GRAPH_H_INCLUDE

#include"List.h"

// Exported type------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors-------------------------------------------------
//newGraph(int n)
//returns a new Graph
Graph newGraph(int n);

//freeGraph(Graph *pG)
//Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph *pG);

//Access functions---------------------------------------------------------
//int getOrder(Graph G)
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

//Manipulation Procedures--------------------------------------------------
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

//Other operations--------------------------------------------------------
void printGraph(FILE* out, Graph G);


#endif
