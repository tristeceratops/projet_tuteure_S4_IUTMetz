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
void methodeDamien(int * tab, int taille,Graphe G);
void switchSommet(int * tab, int a, int b);
int factorielle(int x);
int arrayEqual(int * a, int * b,int taille);
int poidsMin2(Graphe g, int * t, int taille);
int main()
{
    Graphe G = NULL;
    char nom[30];
    int nombre_villes, m;
    int err;
    int tab[] = {0,1,2,3,4,5,6,7,8,9};
    int tabcopie[] = {0,1,2,3,4,5,6,7,8,9};
    do
    {
        printf("saisir le nom de fichier de données : ");
        // scanf("%s", nom); while(getchar() != '\n');
        strcpy(nom, "./communes/communes_10.txt");
        err = lire_data(nom, &G, &nombre_villes, &m);
    }
    while(err == 0);
    for (int i=0; i<nombre_villes; i++) {
        tab[i] = i;
    }
//    for (int j = 0; j < 9; j++)
//    {
        // for (int i = 0; i < 10; i++)
        // {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ",tab[j]);
        }
         printf("\n");
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 10-1; i++)
            {
                methodeDamien(tab,10,G);
            }
            switchSommet(tab,0,j+1);
        }
        

        

        // }
//         memcpy(tab,tabcopie,10);
//         switchSommet(tab,0,j);
//    }
    

   
}

void methodeDamien(int * tab, int taille,Graphe G) {
    int * tabCopie;
    // int factoTaille = factorielle(taille);
    memcpy(tabCopie,tab,taille);
    int a = 1;
    int pM = poidsMin2(G,tab,taille);
    int pM2;
    int * tabCopie2;
    for (int i = taille-1; i > 1; i--)
    {
        switchSommet(tab,i,i-1);
        int h = 0;
        for (int j = 0; j < taille; j++)
        {
            printf("%d ",tab[j]);
        }
        printf("\n");
        // if (poidsMin2(G,tab,taille) > pM)
        // {
            if (poidsMin2(G,tab,taille)<pM)
            {
                printf("poids = %d\n",poidsMin2(G,tab,taille));
                //pM = poidsMin2(G,tab,taille);
                pM2 = poidsMin2(G,tab,taille);
                // memcpy(tabCopie2,tab,taille);
            }
  
        // }
        
        // if (arrayEqual(tab,tabCopie,taille))
        // {
        //     memcpy(tab,tabCopie,taille);
        //     switchSommet(tab,0,a);
        //     a++;
        // }
        
    }
    printf("le poids minimum est : %d\n",pM2);
    printf("Pour le parcours suivant\n");
    // for (int i = 0; i < taille; i++)
    // {
    //     printf("%d",tabCopie2[i]);
    // }
    

    
}

void switchSommet(int * tab, int a, int b){
    int reserve = tab[a];
    tab[a] = tab[b];
    tab[b] = reserve;
}

int factorielle(int x){
    int f = 1;
    for (int i = 1; i <= x; i++)
    {
        f = f * i;
    }
    return f;

}

int arrayEqual(int * a, int * b,int taille){
    for (int i = 0; i < taille; i++)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
        
    }
    return 1;
}

int poidsMin2(Graphe g, int * t, int taille) // 
{
    int v = 0;
    int i;
    
    for(i=0; i< taille-1; i++){
        v = v + g[t[i]][t[i+1]];
    }

    v = v + g[t[i]][t[0]];

    return v;
}
