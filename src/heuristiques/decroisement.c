#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "echange_sommets.h"
#include "cpu_time.h"
#include "lire_data.h"
#include "decroisement.h"

void afficher_chemin(int *chemin, int taille);

int decroisement(Graphe G, int *sommets_visites, int nombre_villes) {
     printf("SOMMETS VISITES = ");
    afficher_chemin(sommets_visites, nombre_villes);

    int *chemin_temp = calloc(nombre_villes, sizeof(int));


    for (int i=0; i<nombre_villes - 1; i++) {
        memcpy(chemin_temp, sommets_visites, nombre_villes * sizeof(int));

        
        // printf("CHEMIN TEMP = ");
        // afficher_chemin(chemin_temp, nombre_villes);

        int poids_actuel = poidsMin(G, sommets_visites, nombre_villes);

        for (int j=1; j<nombre_villes - 1; j++) {
            if (i == 0) {
                printf("blc 1 : %d, %d\n", i, i + 1);
                printf("bloc 2: %d, %d\n", j, j + 1);
            }
           
            int temp = chemin_temp[i];
            chemin_temp[i] = chemin_temp[j + 1];
            chemin_temp[j + 1] = temp;

            int poids_nouveau = poidsMin(G, chemin_temp, nombre_villes);

            afficher_chemin(chemin_temp, nombre_villes);


            if (poids_nouveau < poids_actuel) {
                memcpy(sommets_visites, chemin_temp, nombre_villes * sizeof(int));
                // printf("le décroisement un trouvé un meilleur chemin\n");

            } else {
                memcpy(chemin_temp, sommets_visites, nombre_villes * sizeof(int));

            }
        }
    }
}

void afficher_chemin(int *chemin, int taille) {
    for(int i=0; i<taille; i++) {
        printf("%d ", chemin[i]);
    }

    printf("\n");
}