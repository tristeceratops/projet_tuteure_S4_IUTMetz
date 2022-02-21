#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "cpu_time.h"
#include "lire_data.h"

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
    int *meilleur_chemin;
    int valeur_meilleur_chemin;
    int *sommets_visites;

    // pour le fichier à lire
    char nom[30];
    int nombre_villes, m;
    int err;

    do {
        // on demande à l'utilisateur quel fichier il veut ouvrir

        printf("saisir le nom de fichier de données : ");
        // scanf("%s", nom); while(getchar() != '\n');
        strcpy(nom, "./communes/communes_100.txt");
        err = lire_data(nom, &G, &nombre_villes, &m);
    }
    while(err == 0);

    meilleur_chemin = calloc(nombre_villes, sizeof(int));
    sommets_visites = calloc(nombre_villes, sizeof(int));
    
    srand((unsigned int)time(NULL));

    // on demande à l'utilisateur de quelle ville il veut partir
    printf("ville de départ : \n");
    scanf("%d", &depart);
    
    clock_start(&t1);

    for (int i=0;i<10;i++) {
        // initialisation de la liste des sommets visités
        sommets_visites[i] = -1;
    }

    sommets_visites[0] = depart;
    
    for (int i=1; i<nombre_villes - 1; i++) 
    {
        int plus_petit = depart;
        int valeur_plus_petit = 999;

        for (int j=0; j<nombre_villes;j++)
        {
            if (valeur_plus_petit == 0) 
            {
                printf("valeur modifiée\n");
                plus_petit = 1;
                valeur_plus_petit = G[depart][1];
            } 

            if (!(aDejaEteVisite(sommets_visites, nombre_villes, j)) && G[depart][j] < valeur_plus_petit && G[depart][j] != 0) { 
                valeur_plus_petit = G[depart][j];
                plus_petit = j;

            }
        }

        if (AFFICHAGE) {
            printf("Le plus petit en partant de %d est %d\n", depart, plus_petit);
        }

        depart = plus_petit;
        sommets_visites[i] = depart;

        if (AFFICHAGE) {
            for (int i=0; i<10; i++) {
                printf("%d ", sommets_visites[i]);
            }

            printf("\n");
        }        
    }

    clock_end(&t2);
    print_clock(t1, t2);
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
