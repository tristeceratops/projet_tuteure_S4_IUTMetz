#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu_time.h"
#include "lire_data.h"
#include "echange_sommets.h"
#include "permutation.h"

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

                memcpy(chemin, chemin_temp, taille * sizeof(int));

                // printf("\n\n\n%d < %d \n\n\n", poidsMin(G, chemin_temp, taille), poidsMin(G, chemin, taille));
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