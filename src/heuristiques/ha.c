#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "echange_sommets.h"
#include "cpu_time.h"
#include "lire_data.h"
#include "permutation.h"

#define AFFICHAGE 0

int main()
{
    // pour calculer le temps d'éxécution
    clock_t t1, t2;

    // pour gérer les chemins
    Graphe G = NULL;
    int depart;
    int *meilleur_chemin;
    int valeur_meilleur_chemin = 999999;
    int *sommets_visites;

    int *chemin_ameliore;

    // pour le fichier à lire
    char nom[30];
    int nombre_villes, m;
    int err;

    int *tab;
    int *tab_min;
    
    int i, nb_perm;
    int v_min = -1; int v;

    do
    {
        printf("saisir le nom de fichier de données : ");
        // scanf("%s", nom); while(getchar() != '\n');
        strcpy(nom, "./communes/communes_10.txt");
        err = lire_data(nom, &G, &nombre_villes, &m);
    }
    while(err == 0);

    chemin_ameliore = calloc(nombre_villes, sizeof(int));
    tab_min = calloc(nombre_villes, sizeof(int));
    tab = calloc(nombre_villes, sizeof(int));

    for (int i=0; i<nombre_villes; i++) {
        tab[i] = i;
    }
    
    if (AFFICHAGE) {
        affiche_km(G, nombre_villes);
    }
    
    srand((unsigned int)time(NULL));
    printf("nombre de permutations à générer :\n");
    scanf("%d", &nb_perm);
    
    clock_start(&t1);

    for(i = 0; i < nb_perm; i++)
    {
        permut(tab, nombre_villes);
        // affiche(tab, nombre_villes);
        v = poidsMin(G, tab, nombre_villes);

        if (v < v_min || v_min == -1)
        {
            v_min = v;
            memcpy(tab_min, tab, nombre_villes * sizeof(int)); 
        }
    }
    
 
    

    memcpy(chemin_ameliore, tab_min, nombre_villes * sizeof(int));

    
    echange_sommets(G, chemin_ameliore, nombre_villes);
    

    clock_end(&t2);
    print_clock(t1, t2);


    printf("la valeur minimum est : %d\n", v_min);
    printf("la liste des villes voyagés est : ");

    for (int i = 0; i < nombre_villes; i++)
    {     
        printf("%d ", tab_min[i]);     
    }    

    printf("\nAprès amélioration le nouveau chemin est :");

    for (int i=0; i<nombre_villes; i++) {
        printf("%d ", chemin_ameliore[i]);
    }

    printf(" de poids: %d.", poidsMin(G, chemin_ameliore, nombre_villes));
}

