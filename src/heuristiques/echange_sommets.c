#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu_time.h"
#include "lire_data.h"
#include "echange_sommets.h"
#include "permutation.h"

int poids_total_recursif(Graphe G, int * t, int taille, int valeur, int i);
int test();

void echange_sommets(Graphe G, int *chemin, int taille) {
    int *chemin_temp = calloc(taille, sizeof(int));
    // printf("\n%d\n", poidsMin(G, chemin_temp, taille));

    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++) {
            memcpy(chemin_temp, chemin, taille * sizeof(int));

            int sommet_temp = chemin_temp[i];
            chemin_temp[i] = chemin_temp[j]; 
            chemin_temp[j] = sommet_temp;

            if (poidsMin(G, chemin_temp, taille) < poidsMin(G, chemin, taille)) {
                // for (int i=0; i<taille; i++) {
                //     printf("%d = %d\n", chemin_temp[i], chemin[i]);
                // }

                // printf("%d < %d\n", poidsMin(G, chemin_temp, taille), poidsMin(G, chemin, taille));
                printf("meilleur chemin trouvé\n");
                memcpy(chemin, chemin_temp, taille * sizeof(int));

                // printf("\n\n\n%d < %d \n\n\n", poidsMin(G, chemin_temp, taille), poidsMin(G, chemin, taille));
            }
        }
    }
}

void echange_sommets_recursif(Graphe G, int *chemin, int taille, int i, int j) {
    if (i == 0 && j == 0) {
        return;

    } else if (j == 0) {
        echange_sommets_recursif(G, chemin, taille, i - 1, taille);

    } else {
        echange_sommets_recursif(G, chemin, taille, i, j - 1);

        int *chemin_temp = calloc(taille, sizeof(int));
        memcpy(chemin_temp, chemin, taille * sizeof(int));

        int sommet_temp = chemin_temp[j];
        chemin_temp[j] = chemin_temp[i];
        chemin_temp[i] = sommet_temp;

        // printf("POIDS TOTAL RECURSIF: %d\n", poids_total_recursif(G, chemin, taille, 0, taille));
        // test();
        // printf("%d\n", test());

        // le if fait est EXTREMEMENT lennt, fait perdre ~10ms
        // if (poids_total_recursif(G, chemin_temp, taille, 0, taille) < poids_total_recursif(G, chemin, taille, 0, taille)) {
        if (poidsMin(G, chemin_temp, taille) < poidsMin(G, chemin, taille)) {
            memcpy(chemin, chemin_temp, taille * sizeof(int));
        }

    }
}

int poidsMin(Graphe G, int * t, int taille) // 
{
    int v = 0;
    int i;
    
    for(i=0; i< taille-1; i++){
        // printf("total: %d\n", v);
        v = v + G[t[i]][t[i+1]];
    }

    v = v + G[t[i]][t[0]];

    return v;
}

int poids_total_recursif(Graphe G, int * t, int taille, int valeur, int i) {
    if (i == 0) {
        return 0;

    } else {
        return poids_total_recursif(G, t, taille, valeur, i - 1) + G[t[i]][t[i+1]];

    }

    return 0;
}
