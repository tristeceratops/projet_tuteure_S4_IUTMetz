run:
	gcc .\src\heuristiques\hppv.c .\src\outils\cpu_time.c .\src\outils\lire_data.c -I ./includes -o ./bin/a.exe
	./bin/a.exe