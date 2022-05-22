// Interface to the List ADT
// Adapted for COMP2521 Assignment 2 Part 3 - scaledFootrule

// Written by John Shepherd, March 2013
// Lecture and Lab Content
// From https://cgi.cse.unsw.edu.au/~cs2521/21T3/lab/16/questions

// Adapted by Nemat Bhullar 19/11/2021
// Added the functions: checkInList, checkPosition


#ifndef LIST_H
#define LIST_H


typedef struct ListRep *List;


// Creates a new empty list
List  ListNew(void);

// Frees all memory associated with the given list
void  ListFree(List l);

// Displays a list as [1,2,3,...]
void  ListShow(List l);

// Adds an item to a list
void  ListInsert(List l, char *string, int position);

// Removes an item with the given key from a list
void  ListDelete(List l, char *string);

// Checks if the node is in the list
// Returns true if it is in the given list, false otherwise
int checkInList(List l, char *string);

// Return the number of elements currently in the list 
int ListLength(List l);

// Returns the url name given an integer position rank
char *checkPosition(List l, int pos);


#endif

