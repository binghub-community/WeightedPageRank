#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX 1000

#include "Graph.h"

char **GenStrPtr (void);
char **GetCollection (char *collectionFilename);
Graph getGraph (char **URLList);
char **OutLinks (char URL[MAX]);
char **InLinks (char **URLList, char URL[MAX]);
double numOutLinks(char URL[MAX]);
double numInLinks(char **URLList, char URL[MAX]);
int numCollection(char **collection);
char *Vertex_to_URL (char **URLList, Vertex v);
Vertex URL_to_Vertex (char **URLList, char *URL, int count);


// Creates a pointer to an array of strings
char **GenStrPtr (void){

    char **list = malloc(MAX * sizeof(char*));
    for (int i = 0; i < MAX; i++){
        list[i] = malloc(MAX * sizeof(char));
        *list[i] = 0;       //this didn't end up working for me so i had to stick to strncmp('text', url, 2)
    }

    return list;
}

// Read a collection of files and returns a pointer to array of strings w/ the file names
char **GetCollection (char *collectionFilename){

    char **list = GenStrPtr();

    char buffer[MAX];
    int i = 0;
    FILE *fp = fopen(collectionFilename, "r");
    while (fscanf(fp, "%s", buffer) != EOF){
        strcpy(list[i], buffer);
        i++;
    }

    fclose(fp);

    return list;
}

// Create a graph given the files and their corresponding outgoing links
Graph getGraph (char **URLList){

    int count = numCollection(URLList);
    // printf("%d\n", count);       // check count
    
    Graph g = newGraph(count);

    // for every URL i want to create a node in the graph and create an edge from each node to its outgoing links(nodes)
    for (int b = 0; strncmp(URLList[b], "url", 2) == 0 && b < count; b++){     //for every url...
        char **outlinks = OutLinks(URLList[b]);     //array of URLs that go out from previous URL of collection
        for (int c = 0; strncmp(outlinks[c], "url", 2) == 0; c++){
            // printf("%d\n", URL_to_Vertex(URLList, outlinks[c], count));      //check if correct vertexes are being assigned
            int source = URL_to_Vertex(URLList, URLList[b], count);
            int dest = URL_to_Vertex(URLList, outlinks[c], count);
            // Edge new = mkEdge(g, source, dest);
            insertEdge(g, source, dest, 1);
        }
        // printf("BREAK\n");
    }

    return g;
        
}

// Read from a file and returns a pointer to array of strings containing the outgoing links
char **OutLinks (char URL[MAX]){

    char **links = GenStrPtr();

    char buffer[MAX];
    char URL_txt[MAX] = "its 4/20 haha";       //copy 
    char suffix[] = ".txt";
    strcpy(URL_txt, URL);
    strncat(URL_txt, suffix, 4);
    // printf("%s\n", URL_txt);        //check if url is now a txt file name



    int i = 0;
    FILE *fp = fopen(URL_txt, "r");
    while (fscanf(fp, "%s", buffer) != EOF){
        if (strncmp(buffer, "url", 2) == 0){
            if (strncmp(buffer, URL_txt, 4) == 0)       //ignore self
                continue;
            else {
                strcpy(links[i], buffer);
                // printf("%s\n", links[i]);        //check if URLs are getting copied
                i++;
            }
        }
    }
    fclose(fp);

    //check if pointer to array contains all the URLs
    // for (int b = 0; strncmp(links[b], "url", 2) == 0; b++){
    //     printf("%s\n", links[b]); 
    // }

    return links;
}

// Read from a file and returns a pointer to array of strings containing the ingoing links
char **InLinks (char **URLList, char URL[MAX]){

    char **links = GenStrPtr();


    char URL_txt[MAX] = "blaze it";       //copy 
    char suffix[] = ".txt";
    char buffer[MAX];
    int i = 0;

    for (int a = 0; strncmp(URLList[a], "url", 2) == 0; a++){       //for every URL
        if (strcmp(URLList[a], URL) == 0){     //do not open same file
            continue;
        } else {
            strcpy(URL_txt, URLList[a]);
            strncat(URL_txt, suffix, 4);
            FILE *fp = fopen(URL_txt, "r");     //open the URL
            while (fscanf(fp, "%s", buffer) != EOF){
                if (strcmp(buffer, URL) == 0){
                    strcpy(links[i], URLList[a]);
                    i++;
                }
            }
        }
        
    }

    return links;
}

// number of outgoing links
double numOutLinks(char URL[MAX]){

    char buffer[MAX];
    char URL_txt[MAX] = "its 4/20 haha";       //copy 
    char suffix[] = ".txt";
    strcpy(URL_txt, URL);
    strncat(URL_txt, suffix, 4);

    double i = 0;
    FILE *fp = fopen(URL_txt, "r");
    while (fscanf(fp, "%s", buffer) != EOF){
        if (strncmp(buffer, "url", 2) == 0){
            if (strncmp(buffer, URL_txt, 4) == 0)       //ignore selfs
                continue;
            else
                i++;
        }
    }
    fclose(fp);

    if (i == 0){
        i = 0.5;
    }

    return i;
}

// number of ingoing links
double numInLinks(char **URLList, char URL[MAX]){

    double i = 0;

    char URL_txt[MAX] = "blaze it";       //copy 
    char suffix[] = ".txt";
    char buffer[MAX];

    for (int a = 0; strncmp(URLList[a], "url", 2) == 0; a++){
        strcpy(URL_txt, URLList[a]);
        strncat(URL_txt, suffix, 4);
        FILE *fp = fopen(URL_txt, "r");
        while (fscanf(fp, "%s", buffer) != EOF){
            if (strcmp(buffer, URL) == 0){
                i++;
            }
        }
        fclose(fp);
    }

    if (i == 0){
        i = 0.5;
    }

    return i;
}

// number of items in the collection.txt file
int numCollection(char **collection){
    int count = 0;
    for (int a = 0; strncmp(collection[a], "url", 2) == 0; a++)
        count++;
    
    return count;
}

// yes
char *Vertex_to_URL (char **URLList, Vertex v){
    return URLList[v];
}


// yes
Vertex URL_to_Vertex (char **URLList, char *URL, int count){
    for (int i = 0; i < count; i++){
        if (strcmp(URL, URLList[i]) == 0){
            return i;
        }
    }

    return -1;
}



// int main(void){
//     char **files = GetCollection("collection.txt");
//     // char **outs = OutLinks(files[0]);
//     // printf("%s\n", outs[2]);

//     // char **ins = InLinks(files, "url11");
//     // printf("%s\n", ins[2]);
    
//     // printf("%s\n", Vertex_to_URL(files, 3));
//     // printf("%d\n", URL_to_Vertex(files, "url23", 7));

//     Graph g = getGraph(files);

//     showGraph(g, files);
//     // int a = numOutLinks(files[6]);
//     // printf("%d\n", a);

//     // printf("%d\n", numInLinks(files, "url11"));
//     return 0;
// }

