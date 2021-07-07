#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sem.h"

/***
 *  Print the score of each argument at each step of the iterative phase until the step "max".
 *  gr : the argumentation framework
 *  max : the convergence step
 ***/
static void printScoreDetails(graph *gr, int max)
{
    int i,j;
    printf("\nTABLE NSA\n\n");
    for (j = 0 ; j < max ; j++)
    {
        for (i = 0 ; i < gr->nbNoeuds ; i++)
        {
            printf("\t %.6f ",gr->noeuds[i].score[max]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

/***
 *  Print the acceptability degree of each argument w.r.t. the nsa semantics.
 *  gr : the argumentation framework
 *  max : the convergence step
 ***/
static void printScoresNSA(graph *gr, int max)
{
    int i;

    /*printScoreDetails(gr,max);*/

    for (i=0 ; i < gr->nbNoeuds ; i++)
        printf("Deg(%s) = %f\n", gr->noeuds[i].nom, gr->noeuds[i].score[max]);
}

/***
 *  Function to check if an argument is a self-attacking argument.
 **/
int isSelfAttackedArgument(graph *gr, int arg)
{
    int j=0;
    while (j < gr->noeuds[arg].nbAttacked)
    {
        if(gr->noeuds[arg].attacked[j] == arg)
        {
            return 1;
        }
        j++;
    }
    return 0;
}

/***
 * Function that assigns the initial score of 1 to all arguments (before starting the propagation phase)
 ***/
static void initNSA(graph *gr)
{
    int i;
    for (i=0 ; i < gr->nbNoeuds ; i++)
    {
        if(isSelfAttackedArgument(gr,i))
            gr->noeuds[i].score[0] = 0.;
        else
            gr->noeuds[i].score[0] = 1.;
    }
}

/***
 *  Function to compute the nsa score of each argument in the AF (fixed point method).
 *  gr : the argumentation framework
 **/
static int computeScoreNSA(graph *gr)
{
    
    int node,j;
    double score = 0.;

    int step = 1; /* Variable indicating the number of steps needed to reach the fixed point */

    int pointFixe = 0; /*Variable indicating the number of arguments having reached its fixed point */

    /* Initialization of argument scores */
    initNSA(gr);

    while (pointFixe != gr->nbNoeuds) /* as long as the fixed point has not been reached (i.e., there exists an argument such that the absolute value of the difference between its scores at step i and at step i-1 is greater than DIFF)*/
    {
        pointFixe = 0;
        for (node=0 ; node < gr->nbNoeuds ; node++)
        {
            score = gr->noeuds[node].score[step-1];

            if (!gr->noeuds[node].nbAttacked || isSelfAttackedArgument(gr,node))
            {
                gr->noeuds[node].score[step] = score;
            }
            else
            {
                score = 0;
                for(j=0;j < gr->noeuds[node].nbAttacked;j++)
                {
                    score += gr->noeuds[gr->noeuds[node].attacked[j]].score[step-1];
                }
                score = 1. / (1. + score);
                gr->noeuds[node].score[step] = score;
            }
            if(fabs(gr->noeuds[node].score[step] - gr->noeuds[node].score[step-1]) < DIFF)
                pointFixe++;
        }
        step++;
    }
    return step-1;
}

void nsa(graph *gr, char **argv)
{
    int laststep;
    const char *inputFile = argv[2];
    gr = load_graph(inputFile);
    laststep = computeScoreNSA(gr);
    printScoresNSA(gr,laststep);
    freeGraph(gr);
}
