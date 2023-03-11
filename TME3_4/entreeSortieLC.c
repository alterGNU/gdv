#include <stdio.h>          // pr printf
#include <stdlib.h>         // pr free, exit
#include "biblioLC.h"       // pour struct Livre et Biblio
#define BUFF 1000           // taille max str

Biblio* charger_n_entreesLC(char * nomfic, int n){
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
        inserer_en_tete(b, num, titre, auteur);
        cpt++;
    }
    fclose(entree);
    return b;
}

void enregistrer_bilbioLC(Biblio* b, char *nomfic){
    FILE * sortie = NULL;
    sortie = fopen (nomfic, "w");
    if(sortie == NULL) {printf("Error: fopen failed\n"); exit(3); }

    Livre *l = b->L;
    while (l!=NULL){
        fprintf(sortie,"%d %s %s\n",l->num, l->titre, l->auteur);
        l = l->suiv;
    }
    fclose(sortie);
}

