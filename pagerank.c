#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#include "readData.h"

struct VtexProperties {
    char *url;
    double PR;
    int wOut;
    int wIn;
    double wPR;
};
typedef struct VtexProperties *VtexProperties;

VtexProperties newNode (char *url, double PR, char **collection){
    VtexProperties new = malloc(sizeof(*new));
    new->url = url;
    new->PR = PR;
    new->wOut = numOutLinks(url);
    new->wIn = numInLinks(collection, url);
    new->wPR = 0;

    return new;
}

double sumOutDeg (char **list_of_outlinks, int how_many_outlinks){

    double sum = 0;

    for (int a = 0; a < how_many_outlinks; a++){
        sum = sum + numOutLinks(list_of_outlinks[a]);
    }

    if (sum == 0)
        return 0.5;

    return sum;
}

double sumInDeg (char **list_of_inlinks, int how_many_inlinks, char **collection){

    double sum = 0;

    for (int a = 0; a < how_many_inlinks; a++){
        sum = sum + numInLinks(collection, list_of_inlinks[a]);
    }

    if (sum == 0)
        return 0.5;

    return sum;
}


void PageRankW(double d, double diffPR, int maxIterations){
    char **collection = GetCollection("collection.txt");

    int N = numCollection(collection);

    Graph g = newGraph(N);

    VtexProperties vertexes[N];

    double PR = 1/(double)N;

    for (int a = 0; a < N; a++){
        vertexes[a] = newNode(collection[a], PR, collection);
        // printf("%s + ", vertexes[a]->url);
        // printf("%f\n", vertexes[a]->PR);
        // printf("%d + ", vertexes[a]->wOut);
        // printf("%d\n", vertexes[a]->wIn);
    }

    int iteration = 0;
    double diff = diffPR;


    // char **outlinks = OutLinks(vertexes[0]->url);
    // printf("%d\n", sumOutDeg(outlinks, numOutLinks(vertexes[0]->url)));

    // char **inlinks = InLinks(collection, vertexes[0]->url);
    // printf("%d\n", sumInDeg(inlinks, numInLinks(collection, vertexes[0]->url), collection));

    double temp2 = 0;

    while (iteration < maxIterations && diff >= diffPR){
        for (int b = 0; strncmp(collection[b], "url", 2) == 0; b++){     //for every URL
            double temp = 0;
            char **links = OutLinks(collection[b]);     //outlinks of each URL
            for (int c = 0; strncmp(links[c], "url", 2) == 0; c++){     //calc sum of PR * Wi *Wo
                char **outlinks = OutLinks(links[c]);
                double Wo = sumOutDeg(outlinks, numOutLinks(links[c]));
                // printf("%f\n", Wo);
                char **inlinks = InLinks(collection, links[c]);
                double Wi = sumInDeg(inlinks, numInLinks(collection, links[c]), collection);
                // printf("%f\n", Wi);

                temp = temp + ((1/(numOutLinks(collection[b]))) * (1/Wi) * (1/Wo));       //I dont understand the formula so PR is FUCKED which fucks EVERYTHING ELSE CMON CUH
            }
            vertexes[b]->wPR = ((1 - d)/N) + (d * temp);



            for (int d = 1; d < N; d++){
                temp2 = temp2 + fabs(vertexes[b]->wPR - PR);
                // printf("%f\n", temp2);       //temp2 always increasing because something wrong with PR
            }
        }

        diff = temp2;
        // printf("%f\n", diff);
        break;      //remove break to see the program not even produce txt file :(
    }

    //testing ordering
    // vertexes[0]->wPR = 4;
    // vertexes[1]->wPR = 3;
    // vertexes[2]->wPR = 7;
    // vertexes[3]->wPR = 2;
    // vertexes[4]->wPR = 8;
    // vertexes[5]->wPR = 1;
    // vertexes[6]->wPR = 5;



    //ordering the list

    for (int i = 0; i < N; i++){
        for (int j = i + 1; j < N; j++){
            if (vertexes[i]->wPR < vertexes[j]->wPR){
                VtexProperties tmp = vertexes[i];
                vertexes[i] = vertexes[j];
                vertexes[j] = tmp;
            }
        }
    }

    FILE *fp = fopen("pagerankList.txt", "w");
    for (int i = 0; strncmp(collection[i], "url", 2) == 0; i++){
        if (numOutLinks(collection[i]) == 0.5){

        }
        fprintf(fp, "%s, %d, %.7f\n", vertexes[i]->url, vertexes[i]->wOut, vertexes[i]->wPR);
    }
    fclose(fp);

    dropGraph(g);
    for (int a = 0; a < N; a++){
        free(vertexes[a]);
    }
}

int main(int argc, char *argv[]){

    assert(argc == 4);

    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    // printf("%f\n", d);
    // printf("%f\n", diffPR);
    // printf("%d\n", maxIterations);

    PageRankW(d, diffPR, maxIterations);

    return 0;
}