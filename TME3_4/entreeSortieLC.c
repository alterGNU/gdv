#include <stdio.h>          // pr printf
#include <stdlib.h>         // pr free, exit
#include "biblioLC.h"       // pour struct Livre et Biblio
#define BUFF 1000           // taille max str

Biblio* charger_n_entrees(char * nomfic, int n){
    Biblio* b = creer_biblio();
    FILE * entree = NULL;
    entree = fopen (nomfic, "r");
    if(entree == NULL) {printf("Error: fopen failed\n"); exit(2); }

    char str[BUFF];
    int cpt=0;
    while(fgets(str,BUFF,entree)!=NULL && cpt<n){
        int num;
        char titre[BUFF], auteur[BUFF];
        sscanf(str,"%d %s %s",&num,titre,auteur);
        printf("Le livre n°:%d à pour titre '%s' et pour auteur: '%s'\n",num,titre,auteur);
        inserer_en_tete(b, num, titre, auteur);
        afficher_biblio(b);
        cpt++;
    }
    fclose(entree);
    return b;
}

//void enregistrer_bilbio(Biblio* b, char *nomfic){
//}

