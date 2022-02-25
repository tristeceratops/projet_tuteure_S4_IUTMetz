#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu_time.h"
#include "lire_data.h"
#include "echange_sommets.h"
#include "permutation.h"

void echange_sommets(Graphe G, int *chemin, int taille) {
    int *chemin_temp = calloc(taille, sizeof(int));
    int poids_chemin_temp;
    int poids_chemin;
    int sommet_temp;

    for (int i=0; i<taille; i++) {
        poids_chemin = poidsMin(G, chemin, taille);

        for (int j=0; j<taille; j++) {
            memcpy(chemin_temp, chemin, taille * sizeof(int));

            sommet_temp = chemin_temp[i];
            chemin_temp[i] = chemin_temp[j]; 
            chemin_temp[j] = sommet_temp;

            poids_chemin_temp = poidsMin(G, chemin_temp, taille);

            if (poids_chemin_temp < poids_chemin) {
                memcpy(chemin, chemin_temp, taille * sizeof(int));
            }
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