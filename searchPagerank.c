// COMP2521 Assignment 2

// Written by: Nemat Bhullar (z5360388)
// Date: 15/11/2021

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRINGS 100
#define MAXCHAR 50
#define MAXPAGES 50

#include "ListSearch.h"
#include "searchPagerank.h"

// Global Arrays
char searchTerms[MAXSTRINGS][MAXCHAR];
char storeLines[MAXSTRINGS][MAXCHAR];


////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {
    assert(argc == 4);
    // Reading and storing the search terms 
    // The index of the search term is their position in input
    int numTerms = 0;
    for (int arg = 1; arg < argc; arg++) {
        // Ignore terms that are not in the invertedIndex.txt file
        if (checkURL(argv[arg]) == 1) {
            strcpy(searchTerms[numTerms], argv[arg]);
            numTerms++;
        }
    }
    
    // Read in the lines from invertedIndex.txt that contain the search terms
    readLines(numTerms);
    
    // Create a new list to store the URLs
    List urlList = ListSearchNew();
    readURLs(urlList, numTerms);
    
    // Adding the frequencies of each node
    ListSearchAddFreq(urlList);
    
    // Create and print a sorted list
    List orderedList = ListSearchSelectionSort(urlList);
    ListSearchShow(orderedList);
    ListSearchFree(orderedList);
    ListSearchFree(urlList);
    return 0;
}


void readLines(int numTerms) {
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    
    char bufferLine[MAXSTRINGS];
    // Scan the .txt file
    while (fscanf(invertedIndex, "%s", bufferLine) == 1) {
        // Scan the array
        for (int i = 0; i < numTerms; i++) {
            if (strcmp(searchTerms[i], bufferLine) == 0) {
                fgets(storeLines[i], MAXSTRINGS, invertedIndex);
            }
        }
    }
    fclose(invertedIndex);
}   



void readURLs(List urlList, int numTerms) {
    int numRefs = 0;
    for (int i = 0; i < numTerms; i++) {
        // Split and store the urls from the line containing the search term
        char *URL = strtok(storeLines[i], " ");
        while (strcmp(URL, "\n") != 0) {
            double rank = readRanks(URL);
            ListSearchInsert(urlList, URL, 0, rank);
            URL = strtok(NULL, " ");
            numRefs++;
        }
    }
}



double readRanks(char *URL) {
    FILE *pagerankList = fopen("pagerankList.txt", "r");
    
    char bufferURL[MAXSTRINGS];
    char outDegree[MAXCHAR];
    char temp[MAXCHAR];
    double value = 0.0;
    
    int loop = 1;
    while (fscanf(pagerankList, "%s", bufferURL) == 1 && loop) {
        // Remove the comma after the url name
        int len = strlen(bufferURL);
        if (bufferURL[len - 1] == ',') {
            bufferURL[len - 1] = '\0';
        }
        
        // Scan the rest of the line if the url is found
        if (strcmp(URL, bufferURL) == 0) {
            fscanf(pagerankList, "%s", outDegree);      // outDegree
            fscanf(pagerankList, "%s", temp);           // weighted pagerank
            value = strtod(temp, NULL);
            loop = 0;
        }
    }
    
    fclose(pagerankList);
    return value;
}   


int checkURL(char *string) {
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    
    char bufferLine[MAXSTRINGS];
    // Scan the .txt file
    while (fscanf(invertedIndex, "%s", bufferLine) == 1) {
        if (strcmp(string, bufferLine) == 0) {
            fclose(invertedIndex);
            return 1;
        }
    }
    fclose(invertedIndex);
    return 0;
}   










