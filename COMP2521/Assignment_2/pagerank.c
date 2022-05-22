// COMP2521 Assignment 2

// Written by: Nemat Bhullar (z5360388)
// Date: 9/11/2021

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "pagerank.h"

// Defining Constants
#define MAXCHAR 100
#define MAXURL 1000

// An array to store the URLs of max 50 characters
// Each index of the URL (out of max 1000 URLs) is its graph vertex
char collectURL[MAXURL][MAXCHAR] = {0};

// An array that stores the original page rank to calculate diff
double originalPR[MAXURL];

// Storing new pageranks
double newPR[MAXURL];

// Storing vertex indices
int vertexIndex[MAXURL];


////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 0;
    }
    double d = atof(argv[1]);               // damping factor
    double diffPR = atof(argv[2]);          // sum of PageRank differences
    int maxIterations = atoi(argv[3]);      // maximum number of iterations

    // Read in every URL and return the number of URLs  
    // The index is the position of the url        
    FILE *collections = fopen("collection.txt", "r");
    
    int numURLs = 0;
    while (fscanf(collections, "%s", collectURL[numURLs]) == 1) { 
        vertexIndex[numURLs] = numURLs;
        numURLs++;
    }

    // Close the collections file
    fclose(collections);
        
    // Create a new graph for the URLs and initialise the PR arrays
    Graph g = addURLs(numURLs);
    
    // Initialising input for algorithm
    int iteration = 0;
    double diff = diffPR;
    double constant = (1-d)/numURLs;
    
    while (iteration < maxIterations && diff >= diffPR) {
        
        // PageRank algorithm
        for (int v = 0; v < numURLs; v++) {
            originalPR[v] = newPR[v];
            newPR[v] = constant + d*(sumInlinksPR(g, v));

        }    
        
        // Calculating diff
        double diffSum = 0.0;
        for (int v = 0; v < numURLs; v++) {
            diffSum += fabs(newPR[v] - originalPR[v]);
        }

        diff = diffSum;
        iteration++;
    }
    
    sortArray(g);
    
    // Print the output to be in order
    printOutput(g);
    GraphFree(g);
    return 0;
}


////////////////////////////////////////////////////////////////////////////////


Graph addURLs(int numURLs) {
    Graph g = GraphNew(numURLs);
    
    // Open each url and add an edge to every other URL present
    for (int v = 0; v < numURLs; v++) {
        // Holds the file name with the appendation ".txt"
        char currURL[MAXCHAR];
        strcpy(currURL, collectURL[v]);
        FILE *currFile = fopen(strcat(currURL, ".txt"), "r");
        
        // For every URL in the current URL page reference, add an edge
        char buffer[MAXCHAR];
        while (fscanf(currFile, "%s", buffer) == 1 && !feof(currFile)) {
            for (int w = 0; w < numURLs; w++) {
                if (strcmp(collectURL[w], buffer) == 0 && v != w) {
                    GraphInsertEdge(g, (Edge){v, w, 1});
                }
            }
        }
        fclose(currFile);
        
        // Add an initialising weight to the pageranks
        originalPR[v] = 1.0/numURLs;
        newPR[v] = 1.0/numURLs;
    }
    
    return g;
}


double inDegree(Graph g, int vertex) {             
    double numIn = 0;
    // Checking g[i][vertex]
    for (int i = 0; i < GraphNumVertices(g); i++) { 
        if (GraphIsAdjacent(g, i, vertex) != 0 && vertex != i) {   
            numIn++;
        }
    }    
    return numIn;
}
    

double outDegree(Graph g, int vertex) {            
    double numOut = 0;
    // Checking g[vertex][i]
    for (int i = 0; i < GraphNumVertices(g); i++) { 
        if (GraphIsAdjacent(g, vertex, i) != 0 && vertex != i) {
            numOut++;
        }
    }
    if (numOut == 0) return 0.5;
    return numOut;
}


bool inPageRef(Graph g, int v, int w) {        
    if (GraphIsAdjacent(g, v, w) != 0 && v != w) return true;
    else return false;                
}    


double wIn(Graph g, int v, int w) {                      
    double numerator = inDegree(g, w);
    double denominator = 0.0;
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (inPageRef(g, v, i) && v != i) {
            denominator += inDegree(g, i); // i should have at least 1 inlink v
        }
    }
    return numerator/denominator;
}


double wOut(Graph g, int v, int w) {                 
    double numerator = outDegree(g, w);
    double denominator = 0.0;
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (inPageRef(g, v, i) && v != i) { 
            denominator += outDegree(g, i);
        }
    }
    return numerator/denominator;
}


double sumInlinksPR(Graph g, int vertex) {
    double sum = 0.0;
    for (int i = 0; i < GraphNumVertices(g); i++) {
        // For every inlink of a vertex
        if (inPageRef(g, i, vertex) && vertex != i) {
            sum += originalPR[i] * wIn(g, i, vertex) * wOut(g, i, vertex);
        }
    }
    return sum;
}
    

void sortArray(Graph g) {
    int i = 0;
    for (i = 0; i < GraphNumVertices(g); i++) {
        int j = i + 1;
        for (j = i + 1; j < GraphNumVertices(g); j++) {
            if (newPR[j] > newPR[i]) {
                swapElements(i, j);
            } 
            if (newPR[j] == newPR[i]) {
                if (strcmp(collectURL[i], collectURL[j]) > 0) {
                    swapElements(i, j);
                }
            }
        }
    }
}


void swapElements(int i, int j) {
    double tempO = newPR[i];
    double tempN = originalPR[i];
    char *tempName = strdup(collectURL[i]);
    int tempIndex = vertexIndex[i];
    
    newPR[i] = newPR[j];
    originalPR[i] = originalPR[j];
    strcpy(collectURL[i], collectURL[j]);
    vertexIndex[i] = vertexIndex[j];

    newPR[j] = tempO;
    originalPR[j] = tempN;
    strcpy(collectURL[j], tempName);
    vertexIndex[j] = tempIndex;
}


void printOutput(Graph g) {         
    for (int i = 0; i < GraphNumVertices(g); i++) {
        char *name = collectURL[i];
        int deg = outDegree(g, vertexIndex[i]);
        double rank = newPR[i];
        printf("%s, %d, %.7lf\n", name, deg, rank);
    }
}    







