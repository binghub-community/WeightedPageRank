#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "readData.h"



char **findMatchedURLs (char *file, char **querylist){

    char **matchedurls = GenStrPtr();

    char *token;
    char buffer[MAX];

    FILE *fp = fopen(file, "r");

    while (fgets(buffer, MAX, fp)){
        printf("%s", buffer);
        token = strtok(buffer, " ");
        break;
    }

    while( token != NULL ) {
        printf( " %s\n", token );
        token = strtok(NULL, " ");
    }


    return matchedurls;
}







int main (int argc, char *argv[]){

    assert (argc >= 2);

    char **querylist = malloc(argc * sizeof(char*));
    for (int i = 0; i < MAX; i++){
        querylist[i] = malloc(MAX * sizeof(char));
        *querylist[i] = 0;
    }

    for (int a = 1; a < argc; a++){
        strcpy(querylist[a - 1], argv[a]);
        printf("%s\n", querylist[a - 1]);
    }


    return 0;
}