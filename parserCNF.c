#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sem.h"

/****
Creating a new node in the graph
 @num Place of the argument in the table
 @gr AF
 @type 0 if it is the fixed point method, 1 if it is the lexicographic method
*/
void new_noeud(int num, graph *gr)
{
    gr->noeuds[num].nom = (char *)calloc(TAILLE_MAX,sizeof(char));
    gr->noeuds[num].nbAttacker = 0;
    gr->noeuds[num].nbAttacked = 0;
    gr->noeuds[num].attacker = (int *)malloc(sizeof(int)*gr->nbNoeuds);
    gr->noeuds[num].attacked = (int *)malloc(sizeof(int)*gr->nbNoeuds);
    gr->noeuds[num].branchLengthN = (unsigned long int *)calloc((gr->nbNoeuds),sizeof(unsigned long int));
    gr->noeuds[num].score = (double *)calloc(SIZE,sizeof(double));
}

/****
 Creating a new attack in the graph
 @atter Number of the attacking argument
 @gr AF
 @atted Number of the attacked argument
 */
void new_attack(int atter, int atted, graph *gr)
{

    int nb1 = gr->noeuds[atter].nbAttacker;
    int nb2 = gr->noeuds[atted].nbAttacked;

    gr->noeuds[atter].attacker[nb1] = atted;
    gr->noeuds[atted].attacked[nb2] = atter;

    gr->noeuds[atter].nbAttacker++;
    gr->noeuds[atted].nbAttacked++;
}


/****
 Function to load the graph described in the text file into the structure
 @s Name of the text file containing the graph
 @type returns 1 if the lexicographical order is used, 0 if the fixed point method is used.
 #gr returns the graph with the filled structure
 */
graph* parser_CNF(const char *s, graph *gr)
{
    int i,num=0,n;
    char c;
    FILE *f;

    /* We check that we can read the file s */
    if(!(f=fopen(s,"r")))
        perror("Unreadable file: "),exit(1);

    /* We get the number of arguments we want and load them into the structure */
    if(fscanf(f,"p AF %d\n",&(gr->nbNoeuds)) != 1)
        fprintf(stderr,"Invalid format (no p AF line)\n"),exit(2);

    gr->noeuds=(noeud *)malloc(sizeof(noeud)*(gr->nbNoeuds));
    gr->ordre = (int *)malloc(sizeof(int)*(gr->nbNoeuds));

    /* We initialise the array containing the final order and allocate memory for each node */
    for(i=0;i<gr->nbNoeuds;i++)
    {
        new_noeud(i,gr);
        gr->ordre[i] = i;
    }

    /* We skip the comments */
    while(fscanf(f,"c%*[^\n]%c",&c));


    while(fscanf(f,"%d",&n) != EOF)
    {
        if(n)
            new_attack(num,n-1,gr);
        else
            num++;
    }

    fclose(f);
    return gr;
}


