// Implementation of the Directed Weighted Graph ADT
// Used an Adjacency Matrix

// Adapted for COMP2521 Assignment 2 Part 1 - pagerank

// Lecture and Lab Content
// From https://cgi.cse.unsw.edu.au/~cs2521/21T3/lab/8/questions

// Adapted by Nemat Bhullar 19/11/2021


#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

struct graph {
    int nV;             // #vertices
    int nE;             // #edges
    double **edges;     // adjacency matrix storing positive weights
                        // 0 if nodes not adjacent
};

static int  validVertex(Graph g, Vertex v);

////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV) {
    assert(nV > 0);

    // Creating a new graph 
    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // Initialise the properties of the graph
    g->nV = nV;
    g->nE = 0;

    // Assigning memory to store the edges in an adjacency matrix
    g->edges = malloc(nV * sizeof(double *));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->edges[i] = calloc(nV, sizeof(double));
        if (g->edges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    return g;
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

////////////////////////////////////////////////////////////////////////

int GraphNumVertices(Graph g) {
    return g->nV;
}

bool GraphInsertEdge(Graph g, Edge e) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    assert(e.v != e.w);
    assert(e.weight > 0.0);

    if (g->edges[e.v][e.w] == 0.0) {
        g->edges[e.v][e.w] = e.weight;              // directed edge    
        g->nE++;
        return true;
    } else {
        return false;
    }
}


bool GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (g->edges[v][w] != 0.0) {                    
        g->edges[v][w] = 0.0;
        g->nE--;
        return true;
    } else {
        return false;
    }
}


double GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));
    
    return g->edges[v][w];
}


void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int v = 0; v < g->nV; v++) {
        for (int w = 0; w < g->nV; w++) {
            if (g->edges[v][w] != 0.0 && v != w) {
                printf("Edge %d - %d: %lf\n", v, w, g->edges[v][w]);
            }
        }
    }
}


static int validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}




