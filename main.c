#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include "sem.h"

#define NBSEM 3

/***
 * Provides the user with the different options available.
 */
void help(){
    printf("Usage : ./sem [HCAT | NSA | MT] <path_AF_file>\n");
}

int main(int argc, char **argv)
{
    int i;

    int existing_semantics = 0;

    graph *gr = NULL;

    char *sem[NBSEM] = {"HCAT","MT","NSA"};

    void(*fsem[NBSEM])(graph*,char**) = {bh,mt,nsa};

    if(argc != 3){
        printf("Error parsing command-line arguments!\n");
        help();
        exit(1);
    }

    for(i=0;i<NBSEM;i++)
    {
        if(!strcmp(argv[1],sem[i]) && !existing_semantics){
            fsem[i](gr,argv);
            existing_semantics = 1;
            break;
        }
    }

    if(!existing_semantics){
        printf("Unknown semantics.\n");
        help();
        exit(1);
    }

    return 0;
}
