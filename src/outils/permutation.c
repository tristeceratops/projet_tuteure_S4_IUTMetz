#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

#include "permutation.h"

// int main()
// {
// 	int tab[] = {21,45,18,37,52,89,63,97,78,11};
// 	int i, nb_perm;
// 	clock_t t1, t2;
// 	double cpu_perm;
	
// 	srand((unsigned int)time(NULL));
	
// 	printf("nombre de permutations à générer : ");
// 	scanf("%d", &nb_perm);
	
// 	t1 = clock();
// 	for(i = 0; i < nb_perm; i++)
// 	{
// 		permut(tab, 10);
// 		affiche(tab, 10);
// 		printf("\n");
// 	}
// 	t2 = clock();
	
// 	cpu_perm = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
// 	printf("les %d permutations ont été générées en %f secondes\n", nb_perm, cpu_perm);
// }

// Question : quel sera le résultat pour l'appel affiche(tab+1, 3) ?
// Question : quel sera le résultat pour l'appel permut(tab+1, 3) ?

int rnd(int a, int b)
{
    return a + rand() % (b + 1 - a);
}

void permut(int * t, int taille)
{
	int i, j, yam;
	for(i = 0; i < taille-1; i++)
	{
		j = rnd(i, taille-1);
		yam = t[i];
		t[i] = t[j];
		t[j] = yam;
	}
}

void affiche(int * t, int taille)
{
	int i;
	for(i = 0; i < taille; i++) printf("%d ", t[i]);
	printf("\n");
}
