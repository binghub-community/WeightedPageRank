#include <stdio.h>

#include "readData.c"


// Creates a pointer to an array of strings
char **GenStrPtr (void);

// Read a collection of files and returns a pointer to array of strings w/ the file names
char **GetCollection (char *collectionFilename);

// Create a graph given the files and their corresponding outgoing links
Graph getGraph (char **URLList);

// Read from a file and returns a pointer to array of strings containing the outgoing links
char **OutLinks (char URL[MAX]);

// Read from a file and returns a pointer to array of strings containing the ingoing links
char **InLinks (char **URLList, char URL[MAX]);

// number of outgoing links
double numOutLinks(char URL[MAX]);

// number of ingoing links
double numInLinks(char **URLList, char URL[MAX]);

// number of items in the collection.txt file
int numCollection(char **collection);

// yes
char *Vertex_to_URL (char **URLList, Vertex v);

// yes
Vertex URL_to_Vertex (char **URLList, char *URL, int count);

