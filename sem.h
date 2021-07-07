#define SIZE 1000000
#define DIFF 0.00001

#define MAX 100000
#define TAILLE_MAX 1000

#define ENSEMBLE 1 /* MULTI-ENSEMBLE=0, ENSEMBLE=1 */
#define TOUT 0 /* 1=>nbNoeuds 0=>nbNoeuds*nbNoeuds+1 */




/* Structure of a node (argument) in a graph */
typedef struct node
{
    char *nom; /* name of the node (argument) */

    int nbAttacker; /* Number of arguments which are directly attacked by this argument */
    int nbAttacked; /* Number of arguments which directly attack this argument */
    int *attacker; /* Set of direct attackers */
    int *attacked; /* Set of direct attackees */
    double *score; /* Score of this score step by step */

    /* FOR MT*/
    int nbEns;
    int *ens;


    unsigned long int *branchLengthN; /* Nombre de fois où l'argument à l'indice i est présent au bout de la branche de longueur N*/
}noeud;


/* Structure du graphe */
typedef struct graphe
{
    int nbNoeuds; /* Nombre de noeuds dans le graphe */
    noeud *noeuds; /* Liste des noeuds */
    int *ordre; /* Ordre obtenu entre les arguments */
}graph;

typedef struct tab
{
    int nbNoeuds; /* Nombre d'arguments non-attaqué */
    int *tabANA;  /* Tableau contenant les arguments jamais attaqués */
}tableau;


graph* load_graph(const char *s);
graph* parser_ASPARTIX(const char *s, graph *gr);
graph* parser_CNF(const char *s, graph *gr);

void freeGraph(graph *gr);
void printAF(graph *gr);

/* MT */
void mt(graph *gr, char **argv);

/* BH */
void bh(graph *gr, char **argv);

/* NSA */
void nsa(graph *gr, char **argv);


