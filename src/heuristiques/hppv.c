#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "echange_sommets.h"
#include "cpu_time.h"
#include "lire_data.h"
#include "decroisement.h"
#include "permutation.h"

#define AFFICHAGE 0

int poidsMin(Graphe  g, int * t, int taille);
int aDejaEteVisite(int* tab, int taille, int sommet) ;

int main()
{
    // pour calculer le temps d'éxécution
    clock_t t1, t2;

    // pour gérer les chemins
    Graphe G = NULL;
    int depart;
    
    int valeur_meilleur_chemin = INT_MAX;
    int *meilleur_chemin;
    int *sommets_visites;
    int *chemin_ameliore;

    // pour le fichier à lire
    char nom[30];
    int nombre_villes, m;
    int err;

    do {
        // on demande à l'utilisateur quel fichier il veut ouvrir

        printf("saisir le nom de fichier de données : ");
        scanf("%s", nom); while(getchar() != '\n');
        // strcpy(nom, "./communes/communes_150.txt");
        err = lire_data(nom, &G, &nombre_villes, &m);
    }
    while(err == 0);

    chemin_ameliore = calloc(nombre_villes, sizeof(int));
    meilleur_chemin = calloc(nombre_villes, sizeof(int));
    sommets_visites = calloc(nombre_villes, sizeof(int));
    
    srand((unsigned int)time(NULL));

    // on demande à l'utilisateur de quelle ville il veut partir
    // printf("ville de départ : \n");
    // scanf("%d", &depart);
    
    clock_start(&t1);    
    
    for (int l=0; l<nombre_villes; l++) {
        for (int i=0; i<nombre_villes; i++) { 
            // initialisation de la liste des sommets visités
            
            sommets_visites[i] = -1;
        }

        depart = l;
        sommets_visites[0] = l;

        for (int i=1; i<nombre_villes; i++) 
        {
            int plus_petit = depart;
            int valeur_plus_petit = 999;

            for (int j=0; j<nombre_villes; j++)
            {
                if (!(aDejaEteVisite(sommets_visites, nombre_villes, j)) && G[depart][j] < valeur_plus_petit && G[depart][j] != 0) { 
                    valeur_plus_petit = G[depart][j];
                    plus_petit = j;
                }
            }

            // if (AFFICHAGE) {
            //     printf("Le plus petit en partant de %d est %d = %d km\n ", depart, plus_petit, G[depart][plus_petit]);
            // }

            depart = plus_petit;
            sommets_visites[i] = depart;

            // if (AFFICHAGE) {
            //     affiche(sommets_visites, nombre_villes);

            //     printf("\n");
            // }       
        }

        if (poidsMin(G, sommets_visites, nombre_villes) < valeur_meilleur_chemin) {
            valeur_meilleur_chemin = poidsMin(G, sommets_visites, nombre_villes);
            memcpy(meilleur_chemin, sommets_visites, nombre_villes * sizeof(int));
        }
    }

    memcpy(chemin_ameliore, meilleur_chemin, nombre_villes * sizeof(int));

    decroisement(G, chemin_ameliore, nombre_villes);
    echange_sommets(G, chemin_ameliore, nombre_villes);

    clock_end(&t2);
    print_clock(t1, t2);

    printf("la valeur minimum est : %d\n", valeur_meilleur_chemin);
    printf("la liste des villes voyagés est : ");

    for (int i = 0; i < nombre_villes; i++)
    {     
        printf("%d ", meilleur_chemin[i]);     
    }    

    printf("\nAprès amélioration le nouveau chemin est :");

    for (int i=0; i<nombre_villes; i++) {
        printf("%d ", chemin_ameliore[i]);
    }

    printf(" de poids: %d.", poidsMin(G, chemin_ameliore, nombre_villes));

    FILE * f = fopen("./python/chemin.txt", "w");

    for (int i=0; i<nombre_villes;i++) {
        // printf("%d ", meilleur_chemin[i]);
        fprintf(f, "%d ", meilleur_chemin[i]);
    }

    fclose(f);

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
