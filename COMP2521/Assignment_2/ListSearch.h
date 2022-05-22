// Interface to the List Search ADT
// Adapted for COMP2521 Assignment 2 Part 2 - searchPageRank

// Written by John Shepherd, March 2013
// Lecture and Lab Content
// From https://cgi.cse.unsw.edu.au/~cs2521/21T3/lab/16/questions

// Adapted by Nemat Bhullar 19/11/2021
// Added the functions: ListAddFreq, ListSelectionSort, checkInList


#ifndef LISTSEARCH_H
#define LISTSEARCH_H


typedef struct ListRep *List;


// Creates a new empty list
List ListSearchNew(void);

// Frees all memory associated with the given list
void ListSearchFree(List l);

// Displays a list as [1,2,3,...]
void ListSearchShow(List l);

// Adds an item to a list
void ListSearchInsert(List l, char *string, int freq, double rank);

// Removes an item with the given key from a list
void ListSearchDelete(List l, char *string);

// Adds the frequencies to the nodes in the list
void ListSearchAddFreq(List l);

// Sorts the given list in descending order of frequencies
List ListSearchSelectionSort(List l);

// Checks if the node is in the list
// Returns true if it is in the given list, false otherwise
int ListSearchCheckInList(List l, char *string);


#endif


