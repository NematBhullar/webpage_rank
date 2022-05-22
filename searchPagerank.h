// Interface to SearchPageRank Implementation

#ifndef SEARCHPR_H
#define SEARCHPR_H

#include <stdbool.h>

#include "ListSearch.h"


// Given the number of search terms, it reads in every line from the 
// invertedIndex.txt file if that line contains a search term. 
void readLines(int numTerms);


// Given the number of search terms and a list of urls, it splits the line 
// read in from invertedIndex.txt and stores the urls in a list 
void readURLs(List urlList, int numTerms);


// Given a url name, it returns the weighted pagerank, read from the 
// pagerankList.txt file
double readRanks(char *URL);


// Given a url name, the function checks whether it is a valid search term.
// Returns 1 if valid, 0 otherwise. The search term is ignored if 0.
int checkURL(char *string);

#endif
