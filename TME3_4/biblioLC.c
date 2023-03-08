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
    if(autor == NULL) {printf("Error: Out of memory\n"); exit(-2); }
    res->num = num;
    strcpy(title, titre);
    strcpy(autor, auteur);
    res->titre=title;
    res->auteur=autor;
    res->suiv = NULL;
    return res;
}

void liberer_livre(Livre* l){
    if (l){              // Libére le livre passé en argument s'il n'est pas NULL
        free(l->titre);
        free(l->auteur);
        free(l);
    }
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
    printf("Voici les livres de la bibliothque:\n");
    int cpt=0;
    while (tmp!=NULL){
        printf("\t- ");
        afficher_livre(tmp);
        tmp = tmp->suiv;
        cpt++;
    }
    printf("La bibliotheque contient %d livre%s\n",cpt,(cpt!=0)?"s.":".");
}

void liberer_Biblio(Biblio* b){
    Livre *l = b->L;
    Livre *n;
    while (l!=NULL){
        n = l->suiv;
        liberer_livre(l);
        l = n;
    }
    b->L = NULL;
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
    if(t == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    strcpy(t, title);
    Livre* tmp = b->L;
    while (tmp!=NULL && strcmp(tmp->titre,t)!=0){
        tmp=tmp->suiv;
    }
    free(t);
    return tmp;
}

Biblio* same_autor(Biblio* b,char *autor){
    Biblio* res=creer_biblio();
    char* a = (char *)malloc(sizeof(strlen(autor)*sizeof(char)));
    if(a == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    strcpy(a, autor);
    Livre* tmp = b->L;
    while (tmp!=NULL){
        if(strcmp(tmp->auteur,a)==0){
            inserer_en_tete(res,tmp->num,tmp->titre,tmp->auteur);
        }
        tmp=tmp->suiv;
    }
    free(a);
    return res;
}

void supprimer_ouvrage(Biblio* b, int num, char *titre, char *auteur){
    char* t = (char *)malloc(sizeof(strlen(titre)*sizeof(char)));
    if(t == NULL) {printf("Error: Out of memory\n"); exit(-2); }
    strcpy(t, titre);
    char* a = (char *)malloc(sizeof(strlen(auteur)*sizeof(char)));
    if(a == NULL) {printf("Error: Out of memory\n"); exit(-2); }
    strcpy(a, auteur);
    Livre* tmp = b->L;
    if(tmp!=NULL){                                                                // permet d'eviter le cas ou bibliotheque est vide
        if(tmp->num==num && strcmp(tmp->titre,t)==0 && strcmp(tmp->auteur,a)==0){ // cas où 1er occurence = 1 livre de la liste chainée
            b->L=tmp->suiv;
        }else{                                                                    // autre cas
            Livre* ante = tmp;
            while ((tmp!=NULL)&&(tmp->num!=num || strcmp(tmp->titre,t)!=0 || strcmp(tmp->auteur,a)!=0)){
                ante = tmp;
                tmp=tmp->suiv;
            }
            ante->suiv = (tmp) ? tmp->suiv : tmp; // ternaire pr cas où tmp est NULL ou non
        }
        liberer_livre(tmp); // Possible car liberer_livre verifie si Livre != NULL
    }
    free(t);
    free(a);
}

void fusion(Biblio* b1, Biblio* b2){
    if (b2==NULL){return ;}                           // Cas trivial où b2 vide
    Livre *tmp1 = b1->L;
    if (tmp1!=NULL){
        while (tmp1->suiv!=NULL){ tmp1 = tmp1->suiv;} // parcour b1 jusqu'au bout
    }
    tmp1->suiv = b2->L;                               // joint fin b1 avec debur b2
    b2->L = NULL;                                     // supprime l'entéte de b2
}

