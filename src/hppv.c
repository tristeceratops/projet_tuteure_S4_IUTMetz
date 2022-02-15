#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int rnd(int a, int b); // fonction qui retourne un entier au hasard entre a et b
void permut(int * t, int taille); // fonction qui réalise une permutation des éléments de la table t 
void affiche(int * t, int taille); // fonction qui affiche les éléments d'un tableau
// définition du type Graphe comme un tableau à 2 dimensions
// allocation dynamique faite au moment de la lecture des
// données dans un fichier
typedef int ** Graphe;

// lecture des données dans un fichier et construction du graphe
int lire_data(char * nom, Graphe * g, int *n, int *m);

// affichage du graphe, i.e. du tableau des distances
void affiche_km(int ** g, int n);
int poidsMin(Graphe  g, int * t, int taille);
int aDejaEteVisite(int* tab, int taille, int sommet) ;

int main()
{
    int *tab;
    int *tab_min;
    
    int i, depart;
    clock_t t1, t2;
    double cpu_perm;
    char nom[30];
    Graphe G = NULL;
    int n, m;
    int err;
    int v_min = -1; int v;

    int* sommets_visites;

    do
    {
        printf("saisir le nom de fichier de données : ");
        // scanf("%s", nom); while(getchar() != '\n');
        strcpy(nom, "./communes/communes_10.txt");
        err = lire_data(nom, &G, &n, &m);
    }
    while(err == 0);

    tab_min = calloc(n, sizeof(int));
    tab = calloc(n, sizeof(int));
    sommets_visites = calloc(n, sizeof(int));

    for (int i=0; i<n; i++) {
        tab[i] = i;
    }

    affiche_km(G, n);
    
    srand((unsigned int)time(NULL));

  

    printf("ville de départ : \n");
    scanf("%d", &depart);
    
    t1 = clock();

    for (int i=0;i<10;i++) {
        sommets_visites[i] = -1;
    }

    sommets_visites[0] = depart;
    
    for (int i=1; i<n-1; i++) 
    {
        int plus_petit = depart;
        int valeur_plus_petit = 999;

        for (int j=0; j<n;j++)
        {
            if (valeur_plus_petit == 0) 
            {
                printf("valeur modifiée\n");
                plus_petit = 1;
                valeur_plus_petit = G[depart][1];
            } 

            // printf("valeur plus petit : %d\n", valeur_plus_petit);

            // if (!(aDejaEteVisite(sommets_visites, n, j)) && G[depart][j] != 0 && G[depart][j] < valeur_plus_petit) {
            // printf(">> %d\n", plus_petit);
            // printf("> %d ... %d\n", valeur_plus_petit, G[depart][j]);

            if (!(aDejaEteVisite(sommets_visites, n, j)) && G[depart][j] < valeur_plus_petit && G[depart][j] != 0) { 

                // printf("la ville %d de valeur %d n'a pas été visitée et est plus proche que %d\n", j, G[depart][j], valeur_plus_petit);

                valeur_plus_petit = G[depart][j];
                plus_petit = j;

                
            }
        }

        printf("Le plus petit en partant de %d est %d\n", depart, plus_petit);
        depart = plus_petit;
        sommets_visites[i] = depart;

        for (int i=0; i<10; i++) {
            printf("%d ", sommets_visites[i]);
        }

        
        printf("\n");
    }

    

    // for(i = 0; i < depart; i++)
    // {
    //     permut(tab, n);
    //     affiche(tab, n);
    //     printf("\n");
    //     v = poidsMin(G, tab, n);

    //     if (v < v_min || v_min == -1)
    //     {
    //         v_min = v;
    //         printf("%d \n", sizeof(tab));
    //         memcpy(tab_min, tab, n * sizeof(int)); 
    //     }
    // }

    t2 = clock();
    
    // cpu_perm = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
    // printf("les %d permutations ont été générées en %f secondes\n", depart, cpu_perm);
    // printf("la valeur minimum est : %d\n", v_min);

    // printf("la liste des villes voyagés est : ");
    
    // // for (int i = 0; i < sizeof(tab_min); i++)
    // for (int i = 0; i < n; i++)
    // {     
    //     printf("%d ", tab_min[i]);     
    // }    
}

int aDejaEteVisite(int* tab, int taille, int sommet) 
{
    int res = 0;

    for (int i=0; i<taille; i++) 
    {
        if (tab[i] == sommet) {
            // printf("%d == %d", tab[i], sommet);
            res = 1;
        }
    }

    return res;
}

// Question : quel sera le résultat pour l'appel affiche(tab+1, 3) ?
// Question : quel sera le résultat pour l'appel permut(tab+1, 3) ?

int poidsMin(Graphe g, int * t, int taille)
{
    int v = 0;
    int i;
    
    for(i=0; i< taille-1; i++){
        v = v + g[t[i]][t[i+1]];
    }

    printf("dernier i: %d\n", i);

    v = v + g[t[i]][t[0]];

    return v;
}

int lire_data(char * nom, Graphe * g, int *n, int *m)
{
    char str[15];
    int i, s1, s2, km;
    FILE * f = fopen(nom, "r");
    
    if (f == NULL) return 0; // le fichier n'existe pas
    
    // la première ligne contient le nombre de sommets n et le nombre d'arêtes m
    fgets(str, 15, f);
    sscanf(str, "%d %d", n, m);
    
    // allocation dynamique d'un tableau n x n rempli de 0
    *g = (int **)calloc(sizeof(int *), *n);
    for (i = 0; i < *n; i++) (*g)[i] = (int *)calloc(sizeof(int), *n);

    // lecture du fichier et remplissage du tableau G
    for (i = 0; i < *m; i++)
    {
        fgets(str, 15, f);
        sscanf(str, "%d %d %d", &s1, &s2, &km);
        (*g)[s1][s2] = km;
        (*g)[s2][s1] = km;
    }
    fclose(f);
    return 1;
}

void affiche_km(Graphe g, int n)
{
    int i, j;
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++) printf("%5d ", g[i][j]);
        printf("\n");
    }
}