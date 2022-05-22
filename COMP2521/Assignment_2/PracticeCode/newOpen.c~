#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

#define MAXCHAR 50
#define MAXURL 100

// An array to store the URLs of max 50 characters
// Each index of the URL (out of max 100 URLs) is its graph vertex
char collectURL[MAXURL][MAXCHAR] = {0};

// An array that stores the original page rank to calculate diff
double originalPR[MAXURL];

// Storing new pageranks
double newPR[MAXURL];


int main(int argc, char *argv[]) {
    // Creating a new file, "r" for reading
    FILE *newFile = fopen(argv[1], "r");
    
    int numURLs = 0;
    while (fscanf(newFile, " %s", collectURL[numURLs]) == 1) { // One character less for end string
        numURLs++;
    }
    
    Graph g = GraphNew(numURLs);
    
    for (int v = 0; v < numURLs; v++) {
        char urlFile[MAXCHAR];
        strcpy(urlFile, collectURL[v]);
        FILE *file = fopen(strcat(urlFile, ".txt"), "r");
        
        char buffer[MAXCHAR];
        while (fscanf(file, "%49s", buffer) == 1) {
            for (int w = 0; w < numURLs; w++) {
                if (strcmp(collectURL[w], buffer) == 0 && v != w) {
                    GraphInsertEdge(g, (Edge){v, w, 1});
                    printf("%s - %s\n", collectURL[v], collectURL[w]);
                }
            }
        }
        fclose(file);
        
        // Add a initialising weight to the pageranks
        originalPR[v] = 1/numURLs;
        newPR[v] = 1/numURLs;
    }
 
    // Close the file
    fclose(newFile);
    
    GraphShow(g);
    
    return 0;
}



