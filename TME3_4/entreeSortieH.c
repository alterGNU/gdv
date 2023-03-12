#include <stdio.h>          // pr printf
#include <stdlib.h>         // pr free, exit
#include "biblioH.h"        // pour struct LivreH et BiblioH
#include "entreeSortieH.h"  // pour struct LivreH et BiblioH
#define BUFF 1000           // taille max str

BiblioH* charger_n_entreesH(char * nom_fichier, int nb_ligne, int taille_table){
    BiblioH* b = creer_biblioH(taille_table);
    FILE * entree = NULL;
    entree = fopen (nom_fichier, "r");
    if(entree == NULL) {printf("Error: fopen failed\n"); exit(2); }

    char str[BUFF];
    int cpt=0;
    while(fgets(str,BUFF,entree)!=NULL && cpt<nb_ligne){
        int num;
        char titre[BUFF], auteur[BUFF];
        sscanf(str,"%d %s %s",&num,titre,auteur);
        inserer(b, num, titre, auteur);
        cpt++;
    }
    fclose(entree);
    return b;
}

void enregistrer_bilbioH(BiblioH* b, char *nom_fichier){
    FILE * sortie = NULL;
    sortie = fopen (nom_fichier, "w");
    if(sortie == NULL) {printf("Error: fopen failed\n"); exit(3); }

    for (int i=0;i<b->m;i++){
        LivreH *l = b->T[i];
        while (l!=NULL){
            fprintf(sortie,"%d %s %s\n",l->num, l->titre, l->auteur);
            l = l->suiv;
        }
    }
    fclose(sortie);
}

