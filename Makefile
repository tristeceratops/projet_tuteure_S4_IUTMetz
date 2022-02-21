hppv:
	gcc .\src\heuristiques\hppv.c .\src\outils\cpu_time.c .\src\outils\lire_data.c .\src\heuristiques\echange_sommets.c -I ./includes -o ./bin/a.exe
	./bin/a.exe

ha:
	gcc .\src\heuristiques\ha.c .\src\outils\cpu_time.c .\src\outils\lire_data.c .\src\outils\permutation.c .\src\heuristiques\echange_sommets.c  -I ./includes -o ./bin/a.exe
	./bin/a.exe