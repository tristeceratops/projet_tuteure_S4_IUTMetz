#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int rnd(int a, int b); // fonction qui retourne un entier au hasard entre a et b
void permut(int * t, int taille); // fonction qui réalise une permutation des éléments de la table t 
void affiche(int * t, int taille); // fonction qui affiche les éléments d'un tableau
// définition du type Graphe comme un tableau à 2 dimensions
// allocation dynamique faite au moment de la lecture des
// données dans un fichier
typedef int ** Graphe;

// lecture des données dans un fichier et construction du graphe
int lire_data(char * nom, Graphe * g, int *n, int *m);

// affichage du graphe, i.e. du tableau des distances
void affiche_km(int ** g, int n);
int poidsMin(Graphe  g, int * t, int taille);


int main()
{
	int tab[] = {0,1,2,3,4,5,6,7,8,9};
	int *tab_min;
	tab_min = calloc(10,sizeof(int));
	int i, nb_perm;
	clock_t t1, t2;
	double cpu_perm;
    char nom[30];
	Graphe G = NULL;
	int n, m;
	int err;
	int v_min = -1; int v;
	do // pour récupérer toutes les villes avec les km
	{
		printf("saisir le nom de fichier de données : ");
		// scanf("%s", nom); while(getchar() != '\n');
        strcpy(nom, "communes/communes_10.txt");
		err = lire_data(nom, &G, &n, &m);
	}

	while(err == 0);
	affiche_km(G, n);
	
	srand((unsigned int)time(NULL));
	printf("nombre de permutations à générer : ");
	scanf("%d", &nb_perm);
	
	t1 = clock();
	for(i = 0; i < nb_perm; i++)
	{
		permut(tab, 10);
		// affiche(tab, 10);
		// printf("\n");
		v = poidsMin(G,tab,10);
		if (v < v_min || v_min == -1)
		{
			v_min = v;
			memcpy(tab_min,tab,10 * sizeof(int)); 
		}
		
	}
	t2 = clock();
	
	cpu_perm = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
	printf("les %d permutations ont été générées en %f secondes\n", nb_perm, cpu_perm);
	printf("la valeur minimum est : %d\n", v_min);
	printf("la liste des villes voyagés est : ");
	   for (int i = 0; i < 10; i++) {     
        printf("%d ", tab_min[i]);     
    }    
}

// Question : quel sera le résultat pour l'appel affiche(tab+1, 3) ?
// Question : quel sera le résultat pour l'appel permut(tab+1, 3) ?

int rnd(int a, int b)
{
    return a + rand() % (b + 1 - a);
}

int poidsMin(Graphe g, int * t, int taille){
	int v = 0;
	int i;
	for(i=0; i< taille-1; i++){
		v = v + g[t[i]][t[i+1]];
	}
	v = v + g[t[i]][t[0]];
	return v;
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
}

int lire_data(char * nom, Graphe * g, int *n, int *m)
{
	char str[15];
	int i, s1, s2, km;
	FILE * f = fopen(nom, "r");
	
	if (f == NULL) return 0; // le fichier n'existe pas
	
	// la première ligne contient le nombre de sommets n et le nombre d'arêtes m
	fgets(str, 15, f);
	sscanf(str, "%d %d", n, m);
	
	// allocation dynamique d'un tableau n x n rempli de 0
	*g = (int **)calloc(sizeof(int *), *n);
	for (i = 0; i < *n; i++) (*g)[i] = (int *)calloc(sizeof(int), *n);

	// lecture du fichier et remplissage du tableau G
	for (i = 0; i < *m; i++)
	{
		fgets(str, 15, f);
		sscanf(str, "%d %d %d", &s1, &s2, &km);
		(*g)[s1][s2] = km;
		(*g)[s2][s1] = km;
	}
	fclose(f);
	return 1;
}

void affiche_km(Graphe g, int n)
{
	int i, j;
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++) printf("%5d ", g[i][j]);
		printf("\n");
	}
}
