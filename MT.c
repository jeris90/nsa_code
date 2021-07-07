#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sem.h"

#define f(a) (a)/((a)+1.)
#define deg(a,b) 0.5*(1+(a)-(b))

/***
 *  Print the acceptability degree of each argument w.r.t. the M&T semantics.
 *  gr : the argumentation framework
 ***/
void printScoresMT(graph *gr)
{
    int i;
    for (i=0 ; i < gr->nbNoeuds ; i++)
        printf("Deg(%s) = %f\n", gr->noeuds[i].nom, gr->noeuds[i].score[0]);
}

int checkArgPresent(graph *gr, int node, int val)
{
    return (1<<((gr->nbNoeuds-1) - node) & val) == (1<<((gr->nbNoeuds-1) - node));
}

int conflictfree(graph *gr, int val)
{
    int i,j;
    for(i=0; i<gr->nbNoeuds; i++)
    {
        if (checkArgPresent(gr,i,val))
        {
            for(j=0;j < gr->noeuds[i].nbAttacked;j++)
            {
                if(checkArgPresent(gr,gr->noeuds[i].attacked[j],val))
                    return 0;
            }
        }
    }
    return 1;
}

void freeGraphMT(graph *gr)
{
    int i;
    free(gr->ordre);
    for (i=0 ; i<gr->nbNoeuds ; i++)
    {
        free(gr->noeuds[i].attacker);
        free(gr->noeuds[i].attacked);
        free(gr->noeuds[i].score);
        free(gr->noeuds[i].branchLengthN);
        free(gr->noeuds[i].ens);
    }
    free(gr->noeuds);
    free(gr);
}

/***
 * Calculates the number of attacks from one strategy to another: val1 -> val2
 **/
int computeAttack(graph *gr,int val1, int val2)
{
    int i,j;
    int res=0;
    for(i=0 ; i<gr->nbNoeuds ; i++)
    {
        if (checkArgPresent(gr,i,val1))
        {
            for(j=0;j < gr->noeuds[i].nbAttacked;j++)
            {
                if(checkArgPresent(gr,gr->noeuds[i].attacked[j],val2))
                    res++;
            }
        }
    }
    return res;
}

float computeFormula(graph *gr,int val1, int val2)
{
    return deg(f(computeAttack(gr,val2,val1)),f(computeAttack(gr,val1,val2)));
}

void initMT(graph *gr)
{
	int node,val1;
	for (node=0 ; node<gr->nbNoeuds ; node++)
	{
		gr->noeuds[node].nbEns = 0;
		gr->noeuds[node].ens = (int *)calloc(SIZE,sizeof(int));
		for(val1=0 ; val1<1<<gr->nbNoeuds ; val1++)
        {
        	if(checkArgPresent(gr,node,val1) && conflictfree(gr,val1))
            {
            	gr->noeuds[node].ens[gr->noeuds[node].nbEns++] = val1;
            }
        }
	}
}

void computeScoreMT(graph *gr)
{
    int node,val1,val2;
    float max,res,res2;

    initMT(gr);

    for (node=0 ; node<gr->nbNoeuds ; node++)
    {
        max = 0;
        for(val1=0 ; val1<gr->noeuds[node].nbEns ; val1++)
        {
            /*if(checkArgPresent(gr,node,val1) && conflictfree(gr,val1))
            {*/
                res = 1.;
                for(val2=0; val2<1<<gr->nbNoeuds; val2++)
                {
                    if(!computeAttack(gr,gr->noeuds[node].ens[val1],val2))
                        res2 = 1.;
                    else
                        res2 = computeFormula(gr,gr->noeuds[node].ens[val1],val2);
                    if(res2 < res)
                    	res=res2;
                }
                if(res > max)
                	max = res;
            /*}*/
        }
        gr->noeuds[node].score[0] = max;
    }
}

void mt(graph *gr, char **argv)
{
    const char *inputFile = argv[2];

    gr = load_graph(inputFile);

    computeScoreMT(gr);
    printScoresMT(gr);
    freeGraphMT(gr);
}
