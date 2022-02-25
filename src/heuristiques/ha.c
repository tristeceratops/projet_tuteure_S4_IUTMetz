#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "echange_sommets.h"
#include "cpu_time.h"
#include "lire_data.h"
#include "permutation.h"
#include "decroisement.h"

/*   Mettre 1 si on veut des affichages de ce qu'il se passe. 
    /!\ Augmente beaucoup le temps d'éxécution. /!\ 
 */
#define AFFICHAGE 0
 
void afficher_chemin(int *chemin, int taille);

int main()
{
    // pour calculer le temps d'éxécution
    clock_t t1, t2;

    // pour le fichier à lire
    char nom[30];
    int nombre_villes, m;
    int err;

    // pour gérer les chemins
    Graphe G = NULL;
    int *chemin;
    int *meilleur_chemin;
    int *chemin_ameliore;
   
    int i, nb_perm;
    int v_min = -1; int v;

    do
    {
        printf("saisir le nom de fichier de données : ");
        scanf("%s", nom); while(getchar() != '\n');
        // strcpy(nom, "./communes/communes_10.txt");
        err = lire_data(nom, &G, &nombre_villes, &m);
    }
    while(err == 0);

    chemin_ameliore = calloc(nombre_villes, sizeof(int));
    meilleur_chemin = calloc(nombre_villes, sizeof(int));
    chemin = calloc(nombre_villes, sizeof(int));

    for (int i=0; i<nombre_villes; i++) {
        chemin[i] = i;
    }
    
    // if (AFFICHAGE) {
    //     affiche_km(G, nombre_villes);
    // }
    
    srand((unsigned int)time(NULL));
    printf("nombre de permutations à générer :\n");
    scanf("%d", &nb_perm);
    
    clock_start(&t1);

    for(i = 0; i < nb_perm; i++)
    {
        permut(chemin, nombre_villes);
        // affiche(chemin, nombre_villes);
        v = poidsMin(G, chemin, nombre_villes);

        // if (AFFICHAGE) {
        //     affiche(chemin, nombre_villes);
        // }

        if (v < v_min || v_min == -1)
        {
            v_min = v;
            memcpy(meilleur_chemin, chemin, nombre_villes * sizeof(int)); 
        }
    }
    
    memcpy(chemin_ameliore, meilleur_chemin, nombre_villes * sizeof(int));
    
    /*  Ci-dessous se trouve l'appel aux heuristiques d'amélioration d'échange de sommet et de décroisement. On peut effectuer ces deux heuristiques l'un après l'autre ou bien en laisser qu'un seul/
     */
    echange_sommets(G, chemin_ameliore, nombre_villes);
    decroisement(G, chemin_ameliore, nombre_villes);
    
    clock_end(&t2);
    print_clock(t1, t2);

    printf("la valeur minimum est : %d\n", v_min);
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
