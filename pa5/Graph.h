//Ethan Cox
//etecox
//pa5
//Graph.h
//Header file for the GraphADT

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include"List.h"

//Exported type-------------------------------------------------------------
typedef struct GraphObj* Graph;

//Constructors-Destructors--------------------------------------------------
Graph newGraph(int n);

void freeGraph(Graph* pG);

//Access functions----------------------------------------------------------
int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

//Manipulations procedures--------------------------------------------------
void addArc(Graph G, int u, int v);

void addEdge(Graph G, int u, int v);

void DFS(Graph G, List S);

//Other functions-----------------------------------------------------------
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif





