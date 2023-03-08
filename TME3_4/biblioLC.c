#include <stdio.h>    // pr printf
#include <stdlib.h>   // pr free, exit
#include <string.h>    // pr strlen
#include "biblioLC.h" // pour struct Livre et Biblio

Livre* creer_livre(int num, char *titre, char *auteur){
    Livre* res = malloc(sizeof(Livre));
    if(res == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    char* title = (char *)malloc(sizeof(strlen(titre)*sizeof(char)));
    if(title == NULL) {printf("Error: Out of memory\n"); exit(-2); }
    char* autor = (char *)malloc(sizeof(strlen(auteur)*sizeof(char)));
    if(title == NULL) {printf("Error: Out of memory\n"); exit(-2); }
    res->num = num;
    strcpy(title, titre);
    strcpy(autor, auteur);
    res->titre=title;
    res->auteur=autor;
    res->suiv = NULL;
    return res;
}

void liberer_livre(Livre* l){
    free(l->titre);
    free(l->auteur);
    free(l);
}

void afficher_livre(Livre *l){
    printf("n°:%d,\"%s\" de *%s*\n",l->num,l->titre,l->auteur);
}

Biblio* creer_biblio(){
    Biblio* res = (Biblio*) malloc(sizeof(Biblio));
    if(res == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    res->L = NULL;
    return res;
}

void afficher_biblio(Biblio* b){
    Livre *tmp = b->L;
    if (tmp==NULL){
        printf("La bibliotheque est vide\n");
    }else{
        printf("Voici les livres des la bibliothque:\n");
        while (tmp!=NULL){
            printf("\t- ");
            afficher_livre(tmp);
            tmp = tmp->suiv;
        }
    }
}

void liberer_Biblio(Biblio* b){
    Livre *l = b->L;
    Livre *n;
    while (l!=NULL){
        n = l->suiv;
        liberer_livre(l);
        l = n;
    }
    free(b);
}

void inserer_en_tete(Biblio* b, int num, char *titre, char *auteur){
    Livre *new = creer_livre(num, titre, auteur);
    (new->suiv) = (b->L);
    (b->L) = new;
}
