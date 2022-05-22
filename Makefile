CC = gcc
CFLAGS = -Wall -Werror -g

SUPPORTING_FILES = Graph.c Graph.h ListSearch.c ListSearch.h 

.PHONY: all
all: pagerank searchPagerank scaledFootrule

pagerank: pagerank.c pagerank.h $(SUPPORTING_FILES)
	$(CC) $(CFLAGS) -o pagerank pagerank.c pagerank.h $(SUPPORTING_FILES) -lm
	cp pagerank ex1
	cp pagerank ex2
	cp pagerank ex3

searchPagerank: searchPagerank.c searchPagerank.h $(SUPPORTING_FILES)
	$(CC) $(CFLAGS) -o searchPagerank searchPagerank.c searchPagerank.h $(SUPPORTING_FILES) -lm
	cp searchPagerank ex1
	cp searchPagerank ex2
	cp searchPagerank ex3

.PHONY: clean
clean:
	rm -f pagerank searchPagerank 
	rm -f ex?/pagerank ex?/searchPagerank 







