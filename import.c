#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sem.h"


/****
 Function allowing us to load the graph from the input file (in the ASPARTIX or CNF format) into the structure.
 @s Name of the file
 #gr return the graph
 */
graph* load_graph(const char *s)
{
    int i,num=0,n;
    char c;
    graph *gr = (graph *)malloc(sizeof(graph));
    if(strstr(s,"apx") != NULL)
        gr = parser_ASPARTIX(s,gr);
    else
        gr = parser_CNF(s,gr);

    return gr;
}

/****
 Free the graph memory
 @gr graph
 */
void freeGraph(graph *gr)
{
    int i;
    free(gr->ordre);
    for (i=0 ; i<gr->nbNoeuds ; i++)
    {
        free(gr->noeuds[i].nom);
        free(gr->noeuds[i].attacker);
        free(gr->noeuds[i].attacked);
        free(gr->noeuds[i].score);
        free(gr->noeuds[i].branchLengthN);
    }
    free(gr->noeuds);
    free(gr);
}

/****
 Function that prints the AF with, for each node, the list of its direct attackers and the arguments it attacks.
 @gr a given AF
 */
void printAF(graph *gr)
{
    int i=0,j,k;
    for(;i<gr->nbNoeuds;i++)
    {
        printf("ARGUMENT %d\n",i+1);
        printf("\t -> : ");
        for(j=0;j<gr->noeuds[i].nbAttacker;j++)
            printf("%d ",(gr->noeuds[i].attacker[j])+1);
        printf("\n");

        printf("\t <- : ");
        for(k=0;k<gr->noeuds[i].nbAttacked;k++)
            printf("%d ",(gr->noeuds[i].attacked[k])+1);
        printf("\n");
    }
}

