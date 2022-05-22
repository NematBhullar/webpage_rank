// Interface to PageRank Implementation

#ifndef PAGERANK_H
#define PAGERANK_H

#include <stdbool.h>

#include "Graph.h"

// Given the number of URLs in the collections file, a graph is created with
// edges added for every page reference (ignoring self-loops and parallel edges)
Graph addURLs(int numURLs);


// Returns the degree (number) of inlinks of a vertex 
double inDegree(Graph g, int vertex);


// Returns the degree (number) of outlinks of a vertex    
double outDegree(Graph g, int vertex);


// Returns true if Vertex v has a page reference to Vertex w, false otherwise
bool inPageRef(Graph g, int v, int w);


// Returns the weight of a edge(v, w) as a ratio of inDegree of Vertex w and 
// inDegree of reference pages of Vertex v
double wIn(Graph g, int v, int w);      


// Returns the weight of a edge(v, w) as a ratio of outDegree of Vertex w and 
// outDegree of reference pages of Vertex v
double wOut(Graph g, int v, int w);     


// Given the original pagerank of a vertex v and the inlinks of v,
// it returns the product of the original pagerank, wIn and wOut
double sumInlinksPR(Graph g, int vertex);

void sortArray(Graph g);


void swapElements(int i, int j);


void printOutput(Graph g);


#endif


