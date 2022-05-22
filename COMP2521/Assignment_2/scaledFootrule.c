// COMP2521 Assignment 2

// Written by: Nemat Bhullar (z5360388)
// Date: 19/11/2021

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRINGS 1000
#define MAXCHAR 50
#define MAXPAGES 50

#include "List.h"
#include "scaledFootrule.h"

// Global arrays to store data
char listFiles[MAXSTRINGS][MAXCHAR];
int listPositions[MAXSTRINGS];
int listPerms[MAXSTRINGS*MAXSTRINGS][MAXCHAR];
double rank[MAXSTRINGS*MAXSTRINGS];

// Global variable
int numPerms = 0;


////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {

    // Scanning in all the files
    for (int arg = 1; arg < argc; arg++) {  
        strcpy(listFiles[arg - 1], argv[arg]);
    }
    
    // Number of files
    int numFiles = argc - 1;
    
    // A list of all the URLs
    List collection = readURLs(numFiles);
    
    // Cardinality of c
    int length = ListLength(collection);
    
    // Positions available
    for (int i = 0; i < length; i++) listPositions[i] = i + 1;
    
    // Get all permutations for n number of elements
    permutations(0, length);
    
    for (int i = 0; i < numPerms; i++) {
        rank[i] = scaledDist(length, numFiles, i);
    }
    
    int min = 0;
    double minRank = rank[min];
    for (int i = 0; i < numPerms; i++) {
        if (rank[i] < minRank) {
            minRank = rank[i];
            min = i;
        }
    }
    
    printf("%lf\n", minRank); 
    for (int j = 0; j < length; j++) {
        if (checkPosition(collection, listPerms[min][j]) != 0) {
            printf("%s\n", checkPosition(collection, listPerms[min][j]));
        }
    }
    return 0;

}


////////////////////////////////////////////////////////////////////////////////


List readURLs(int numFiles) {
    List C = ListNew();
    for (int i = 0; i < numFiles; i++) {
        FILE *file = fopen(listFiles[i], "r");
        
        // Scan in URLs
        int pos = 0;
        char bufferURL[MAXSTRINGS];
        while (fscanf(file, "%s", bufferURL) == 1) {  
            // Remove Duplicates 
            if (checkInList(C, bufferURL) == 0) {
                pos++;
                ListInsert(C, bufferURL, pos);
            }
        }
        fclose(file);
    }
    return C;
}


// Pos is the position of the pointer
// Length is the number of elements in the permutation
void permutations(int pos, int length) {
    int i;
    
    if (pos == length) {
        for (int j = 0; j < length; j++) {
            listPerms[numPerms][j] = listPositions[j];
        }
        numPerms++;
                
    } else {
        for (i = pos; i < length; i++) {
            swap(pos, i);
            permutations(pos + 1, length);
            swap(pos, i);
        }
    }
}


void swap(int x, int y) {
    int temp = listPositions[x];
    listPositions[x] = listPositions[y];
    listPositions[y] = temp;   
}


double scaledDist(int numURLs, int numFiles, int perm) {
    double sum = 0.0;
    
    for (int i = 0; i < numFiles; i++) {
        FILE *file = fopen(listFiles[i], "r");

        double pos = 0.0;
        char bufferURL[MAXSTRINGS];
        while (fscanf(file, "%s", bufferURL) == 1) {  
            pos += 1;
        }
        fclose(file);
        
        for (int j = 0; j < pos; j++) {
            // For each url,
            // subtract the position in file and the positons in permutation,
            // then obtain the absolute value and add to sum
            sum += fabs(((j/pos) - (listPerms[perm][j]/numURLs)));
        }
    }
    return sum;
}
