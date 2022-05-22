// Implementation of the List Search ADT 
// Adapted for COMP2521 Assignment 2 Part 2 - searchPageRank

// Written by John Shepherd, March 2013
// Lecture and Lab Content
// From https://cgi.cse.unsw.edu.au/~cs2521/21T3/lab/16/questions

// Adapted by Nemat Bhullar 19/11/2021
// Edited the ListNode struct
// Added the functions: swapNode, ListAddFreq, ListSelectionSort, checkInList


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListSearch.h"

#define MAXSTRINGS 1000
#define MAXCHAR 50
#define MAXPAGES 30

typedef struct ListNode {
	char *name;
	int frequency;
	double weightedrank;
	struct ListNode *next;
} ListNode;

typedef struct ListRep {
	ListNode *first;  // ptr to first node
	ListNode *last;   // ptr to last node
} ListRep;

static void swapNode(ListNode *x, ListNode *y);

////////////////////////////////////////////////////////////////////////////////

List ListSearchNew(void) {
	List l = malloc(sizeof(ListRep));
	assert (l != NULL);
	l->first = NULL;
	l->last = NULL;
	return l;
}

void ListSearchFree(List l) {
	ListNode *curr, *next;
	curr = l->first;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(l);
}

////////////////////////////////////////////////////////////////////////////////


void ListSearchShow(List l) {
    int i = 0;
	ListNode *curr = l->first;
	while (curr != NULL) {
		printf("%s\n", curr->name);
		curr = curr->next;
		i++;
		if (i == MAXPAGES) break; 
	}
}


void ListSearchInsert(List l, char *string, int freq, double rank) {
	ListNode *new = malloc(sizeof(ListNode));
	assert (new != NULL);
	new->name = strdup(string);
	new->frequency = freq;
	new->weightedrank = rank;
	new->next = NULL;

	if (l->first == NULL) {
		l->first = new;
	} else {
		l->last->next = new;
	}
	l->last = new;
}


void ListSearchDelete(List l, char *string) {
	ListNode *prev, *curr;
	prev = NULL; curr = l->first;
	while (curr != NULL) {
		if (strcmp(string, curr->name) == 0) {
			break;
		}
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL) {
		if (prev == NULL) {
			l->first = curr->next;
		} else {
			prev->next = curr->next;
		}
		free(curr);
		if (l->first == NULL) {
			l->last = NULL;
		}
	}
}


void ListSearchAddFreq(List l) {
    ListNode *curr = l->first;
    while (curr != NULL) {
        ListNode *comp = l->first;
        while (comp != NULL) {
            if (strcmp(curr->name, comp->name) == 0) {
                curr->frequency = curr->frequency + 1;
            }
            comp = comp->next;
        }
        curr = curr->next;
    }
}


List ListSearchSelectionSort(List l) {
    ListNode *curr = l->first;

    while(curr != NULL) {
        ListNode *temp = curr->next;
        while(temp != NULL) {
            // Sort by frequency
            if(curr->frequency < temp->frequency) {
                swapNode(curr, temp);
            }
            
            // Sort by weightedrank
            if (curr->frequency == temp->frequency) {
                if (curr->weightedrank < temp->weightedrank) {
                    swapNode(curr, temp);
                }
            }
            /* Sort by name
            if (curr->frequency == temp->frequency) {
                if (curr->weightedrank == temp->weightedrank) {
                    if (strcmp(curr->name, temp->name) > 0) {
                        swapNode(curr, temp);
                    }
                }
            }*/
            temp = temp->next;
        }
        curr = curr->next;
    }
    
    // Create a new ordered list to remove duplicates
    List newOrdered = ListSearchNew();
    curr = l->first;
    while (curr != NULL) {
        if (ListSearchCheckInList(newOrdered, curr->name) == 0) {
            ListSearchInsert(newOrdered, curr->name, curr->frequency, curr->weightedrank);
            curr = l->first;
        }  
        curr = curr->next;
    }
    return newOrdered;
}


int ListSearchCheckInList(List l, char *string) {
    ListNode *curr = l->first;
	while (curr != NULL) {
		if (strcmp(string, curr->name) == 0) {
			return 1;
		}
		curr = curr->next;
	}
    return 0;
}   
    

////////////////////////////////////////////////////////////////////////////////    
    

// A void function that takes two ListNodes and swaps all their data
static void swapNode(ListNode *x, ListNode *y) {
    char *tempName = x->name;
    int tempFreq = x->frequency;
    double tempRank = x->weightedrank;
    
    x->name = strdup(y->name);
    x->frequency = y->frequency;
    x->weightedrank = y->weightedrank;
    
    y->name = strdup(tempName);
    y->frequency = tempFreq;
    y->weightedrank = tempRank;
}


       






