#include <stdio.h>
#include <time.h>

#include "cpu_time.h"

// int main()
// {
// 	clock_t t1, t2;
// 	double cpu_boucle;
// 	unsigned long i, n, yam=0;	
	
// 	printf("nombre d'itérations à effectuer : ");
// 	scanf("%lu", &n);
	
// 	t1 = clock();
// 	printf("nombre de ticks d'horloge avant la boucle : %lu\n", t1);
	
// 	for(i=1; i<n; i++) yam += i;
	
// 	t2 = clock();
// 	printf("nombre de ticks d'horloge après la boucle : %lu\n", t2);
	

// 	printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);
// }

void clock_start(clock_t *t) {
	*t = clock();
}

void clock_end(clock_t *t) {
	*t = clock();
}

void print_clock(clock_t t1, clock_t t2) {
	printf("Le programme s'est éxécuté en %f ms.\n", (double)(t2-t1)/(double)(CLOCKS_PER_SEC) * 1000);
}
