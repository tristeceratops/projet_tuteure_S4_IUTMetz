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

int force_brute(Graphe G, int *chemin, int debut, int nombre_villes, int* meilleur_chemin, int meilleur_valeur);
void swap(int *chemin, int a, int b);
int next_permutation(int array[], size_t length);

int main() {
    // pour calculer le temps d'éxécution
    clock_t t1, t2;

    // pour gérer les chemins
    Graphe G = NULL;
    int depart;
    int *chemin;
    int *meilleur_chemin;
    int valeur_meilleur_chemin = INT_MAX;


    // pour le fichier à lire
    char nom[30];
    int nombre_villes, m;
    int err;

    do {
        // on demande à l'utilisateur quel fichier il veut ouvrir

        printf("saisir le nom de fichier de données : ");
        scanf("%s", nom); while(getchar() != '\n');
        // strcpy(nom, "./communes/communes_10.txt");
        err = lire_data(nom, &G, &nombre_villes, &m);
    }
    while(err == 0);

    chemin = calloc(nombre_villes, sizeof(int));
    meilleur_chemin = calloc(nombre_villes, sizeof(int));

    for (int i=0; i<nombre_villes; i++) {
        chemin[i] = i;
    }
    
    clock_start(&t1);

    while (next_permutation(chemin, nombre_villes)) {
        int poids = poidsMin(G, chemin, nombre_villes);
        
        if (poids < valeur_meilleur_chemin) {
            valeur_meilleur_chemin = poids;
            memcpy(meilleur_chemin, chemin, nombre_villes * sizeof(int));
        }
    }

    clock_end(&t2);
    print_clock(t1, t2);

    affiche(meilleur_chemin, nombre_villes);
    printf("poids%d", valeur_meilleur_chemin);

    FILE * f = fopen("./python/chemin.txt", "w");

    for (int i=0; i<nombre_villes;i++) {
        // printf("%d ", meilleur_chemin[i]);
        fprintf(f, "%d ", meilleur_chemin[i]);
    }

    fclose(f);

    return 0;
}

void swap(int *chemin, int a, int b) {
    int temp = chemin[a];
    chemin[a] = chemin[b];
    chemin[b] = temp;
}

int next_permutation(int *array, size_t length) {
	if (length == 0)
		return 0;
	size_t i = length - 1;
	while (i > 0 && array[i - 1] >= array[i])
		i--;
	if (i == 0)
		return 0;
	
	size_t j = length - 1;
	while (array[j] <= array[i - 1])
		j--;
	int temp = array[i - 1];
	array[i - 1] = array[j];
	array[j] = temp;
	
	j = length - 1;
	while (i < j) {
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		i++;
		j--;
	}
	return 1;
}




