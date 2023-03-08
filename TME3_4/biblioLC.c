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
    if (l!=NULL){
        printf("n°:%d,\"%s\" de *%s*\n",l->num,l->titre,l->auteur);
    }else{
        printf("Il n'y a pas de livre\n");
    }
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
        printf("Voici les livres de la bibliothque:\n");
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

Livre* search_by_num(Biblio* b,int num){
    Livre* tmp = b->L;
    while (tmp!=NULL && tmp->num!=num){
        tmp=tmp->suiv;
    }
    return tmp;
}

Livre* search_by_title(Biblio* b,char *title){
    char* t = (char *)malloc(sizeof(strlen(title)*sizeof(char)));
    strcpy(t, title);
    Livre* tmp = b->L;
    while (tmp!=NULL && strcmp(tmp->titre,title)!=0){
        tmp=tmp->suiv;
    }
    return tmp;
}

Biblio* same_autor(Biblio* b,char *autor){
    Biblio* res=creer_biblio();
    char* a = (char *)malloc(sizeof(strlen(autor)*sizeof(char)));
    strcpy(a, autor);
    Livre* tmp = b->L;
    while (tmp!=NULL){
        if(strcmp(tmp->auteur,a)==0){
            inserer_en_tete(res,tmp->num,tmp->titre,tmp->auteur);
        }
        tmp=tmp->suiv;
    }
    return res;
}
