#include<stdio.h>
#include<time.h>

int main()
{
	clock_t t1, t2;
	double cpu_boucle;
	unsigned long i, n, yam=0;	
	
	printf("nombre d'itérations à effectuer : ");
	scanf("%lu", &n);
	
	t1 = clock();
	printf("nombre de ticks d'horloge avant la boucle : %lu\n", t1);
	
	for(i=1; i<n; i++) yam += i;
	
	t2 = clock();
	printf("nombre de ticks d'horloge après la boucle : %lu\n", t2);
	
	cpu_boucle = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
	printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);
}

