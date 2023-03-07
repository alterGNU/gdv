#include <stdio.h>    // pr printf
#include <stdlib.h>   // pr free
#include "biblioLC.h" // pour struct Livre et Biblio

Livre* creer_livre(int num, char *titre, char *auteur){
    Livre* res = (Livre*) malloc(sizeof(Livre*));
    res->num = num;
    res->titre = titre;
    res->auteur = auteur;
    res->suiv = NULL;
}

void liberer_livre(Livre* l){
    free(l);
}

void afficher_livre(Livre *l){
    printf("n°:%d,\"%s\" de *%s*\n",l->num,l->titre,l->auteur);
}

