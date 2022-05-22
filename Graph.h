// Implementation of the Directed Weighted Graph ADT
// Used an Adjacency Matrix

// Adapted for COMP2521 Assignment 2 Part 1 - pagerank

// Lecture and Lab Content
// From https://cgi.cse.unsw.edu.au/~cs2521/21T3/lab/8/questions

// Adapted by Nemat Bhullar 19/11/2021


#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;

typedef int Vertex;

// Edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
    double weight;
} Edge;


// Creates a new graph
Graph GraphNew(int nV);


// Frees all memory associated with the given graph
void GraphFree(Graph g);


// Returns the number of vertices in the given graph
int GraphNumVertices(Graph g);


// Inserts  an  edge into a graph. Does nothing if there is already an
// edge between `e.v` and `e.w`. Returns true if successful, and false
// if there was already an edge.
bool GraphInsertEdge(Graph g, Edge e);


// Removes an edge from a graph. Returns true if successful, and false
// if the edge did not exist.
bool GraphRemoveEdge(Graph g, Vertex v, Vertex w);


// Returns the weight of the edge between `v` and `w` if it exists, or
// 0.0 otherwise
double GraphIsAdjacent(Graph g, Vertex v, Vertex w);


// Displays information about the graph
void GraphShow(Graph g);


#endif



