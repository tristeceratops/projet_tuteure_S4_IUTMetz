#ifndef ECHANGE_SOMMETS
#define ECHANGE_SOMMETS

#include "lire_data.h"

void echange_sommets(Graphe G, int *chemin, int taille);
int poidsMin(Graphe g, int * t, int taille);
void echange_sommets_recursif(Graphe G, int *chemin, int taille, int i, int j);

#endif