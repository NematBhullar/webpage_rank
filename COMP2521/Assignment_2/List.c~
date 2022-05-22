// Implementation of the List ADT 
// Adapted for COMP2521 Assignment 2 Part 3 - scaledFootrule

// Written by John Shepherd, March 2013
// Lecture and Lab Content
// From https://cgi.cse.unsw.edu.au/~cs2521/21T3/lab/16/questions

// Adapted by Nemat Bhullar 19/11/2021
// Edited the ListNode struct
// Added the functions: checkInList, checkPosition


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAXSTRINGS 1000
#define MAXCHAR 50
#define MAXPAGES 30

typedef struct ListNode {
	char *name;
	int position;
	struct ListNode *next;
} ListNode;

typedef struct ListRep {
	ListNode *first;  // ptr to first node
	ListNode *last;   // ptr to last node
} ListRep;


////////////////////////////////////////////////////////////////////////

List ListNew(void) {
	List l = malloc(sizeof(ListRep));
	assert (l != NULL);
	l->first = NULL;
	l->last = NULL;
	return l;
}

void ListFree(List l) {
	ListNode *curr, *next;
	curr = l->first;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(l);
}

////////////////////////////////////////////////////////////////////////


void ListShow(List l) {
    int i = 0;
	ListNode *curr = l->first;
	while (curr != NULL) {
		printf("%s", curr->name);
		curr = curr->next;
		i++;
	}
}


void ListInsert(List l, char *string, int position) {
	ListNode *new = malloc(sizeof(ListNode));
	assert (new != NULL);
	new->name = strdup(string);
	new->position = position;
	new->next = NULL;

	if (l->first == NULL) {
		l->first = new;
	} else {
		l->last->next = new;
	}
	l->last = new;
}


void ListDelete(List l, char *string) {
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


int checkInList(List l, char *string) {
    ListNode *curr = l->first;
	while (curr != NULL) {
		if (strcmp(string, curr->name) == 0) {
			return 1;
		}
		curr = curr->next;
	}
    return 0;
}


char *checkPosition(List l, int pos) {
    ListNode *curr = l->first;
	while (curr != NULL) {
		if (curr->position == pos) {
			return curr->name;
		}
		curr = curr->next;
	}
    return 0;
}


int ListLength(List l) {
	int n = 0;
	ListNode *curr = l->first; 
	while (curr != NULL) {
		n++;
		curr = curr->next;
	}
	return n;
}




