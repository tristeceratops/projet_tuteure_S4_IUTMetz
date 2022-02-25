hppv:
	gcc .\src\heuristiques\hppv.c .\src\outils\cpu_time.c .\src\outils\lire_data.c .\src\heuristiques\echange_sommets.c .\src\outils\permutation.c .\src\heuristiques\decroisement.c -I ./includes -o ./bin/a.exe -O3
	./bin/a.exe 

ha:
	gcc .\src\heuristiques\ha.c .\src\outils\cpu_time.c .\src\outils\lire_data.c .\src\outils\permutation.c .\src\heuristiques\echange_sommets.c .\src\heuristiques\decroisement.c -I ./includes -o ./bin/a.exe -O3
	./bin/a.exe 

brute:
	gcc .\src\heuristiques\brute.c .\src\outils\cpu_time.c .\src\outils\lire_data.c .\src\outils\permutation.c .\src\heuristiques\echange_sommets.c .\src\heuristiques\decroisement.c -I ./includes -o ./bin/a.exe -O3
	./bin/a.exe 