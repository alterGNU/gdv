#include <stdio.h>    // pr printf
#include <stdlib.h>   // pr free, exit #include <string.h> 
#include <string.h>   // pr strdup
#include <math.h>     // pour sqrt
#include "biblioH.h"  // pour struct LivreH et BiblioH

int fonctionClef(char *auteur){
    int som = 0;
    int i = 0;
    while (auteur[i]){
        //printf("%c %d\n",auteur[i],auteur[i]);
        som+=(int) auteur[i];
        i++;
    }
    return som;
}

LivreH* creer_livreH(int num, char *titre, char *auteur){
    LivreH* res = malloc(sizeof(LivreH));
    if(res == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    res->clef = fonctionClef(auteur);;
    res->num = num;
    res->titre = strdup(titre); // alloue et copie la chaîne de caractères titre
    res->auteur = strdup(auteur); // alloue et copie la chaîne de caractères auteur
    res->suiv = NULL;
    return res;
}

void afficher_livreH(LivreH *l){
    if (l!=NULL){
        printf("clef:%d->(n°:%d,\"%s\" de *%s*)\n",l->clef,l->num,l->titre,l->auteur);
    }else{
        printf("Il n'y a pas de livre\n");
    }
}

void liberer_livreH(LivreH* l){
    if (l){              // Libére le livre passé en argument s'il n'est pas NULL
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}


BiblioH* creer_biblioH(int m){
    if(m<1){printf("Taille tableau doit etre strictement positive\n");return NULL;}
    BiblioH* res = (BiblioH*) malloc(sizeof(BiblioH));
    if(res == NULL) {printf("Error1: Out of memory\n"); exit(-1); }
    res->nE = 0;
    res->m = m;
    res->T = (LivreH**) malloc(m*sizeof(LivreH*));
    if(res->T == NULL) {printf("Error2: Out of memory\n"); exit(-2); }
    for (int i=0;i<m;i++){
        res->T[i]=NULL;
    }
    return res;
}

void afficher_biblioH(BiblioH* b){
    if(b->T==NULL){printf("Il n'y a pas de tableau\n");return;}
    printf("La biblio contient %d livre",b->nE);
    printf((b->nE>0)?"s":"");
    printf(" pour un talbeau de %d cases:\n",b->m);
    printf(" _____ \n|  T  |\n|-----|\n");
    for (int i=0;i<b->m;i++){
        printf("| %3d | --> ",i);
        LivreH *l = b->T[i];
        while (l!=NULL){
            printf("(%d,%s,%s)->",l->num,l->titre,l->auteur);
            l = l->suiv;
        }
        printf("Null\n");
    }
    printf("'-----'\n");
}

void liberer_biblioH(BiblioH* b){
    if(b==NULL){return;}
    for (int i=0;i<b->m;i++){
        LivreH *l = b->T[i];
        while (l!=NULL){
            LivreH *next = l->suiv;
            liberer_livreH(l);
            l = next;
        }
    }
    free(b->T);
    b->T=NULL;
    free(b);
}

int fonctionHachage(int cle, int m){
    double a = ((sqrt(5)-1)/2);
    double kA = (double) cle * a;
    return (int) (m*(kA - ((int)kA)));
}

void inserer(BiblioH* b, int num, char *titre, char *auteur){
    //etape1: Creation du nouveau livre à ajouter
    LivreH * l = creer_livreH(num,titre,auteur);
    //etape2: Calcul de l'indice de la case de la table de hachage
    int indice = fonctionHachage(l->clef,b->m);
    //etape3: Insertion en tête de la liste chainée à cette case
    LivreH * tete = b->T[indice] ;
    if (tete){
        l->suiv = tete;
        b->T[indice] = l;
    }else{
        b->T[indice] = l;
    }
    //etape4: Màj du champ contenant le nombre d'élément du tableau
    b->nE++;
}

LivreH* search_by_numH(BiblioH* b,int num){
    LivreH* tmp ;
    for(int i=0;i<b->m;i++){
        tmp = b->T[i];
        while (tmp!=NULL){
            if (tmp->num==num){return tmp;}
            tmp=tmp->suiv;
        }
    }
    return tmp;
}

LivreH* search_by_autorH(BiblioH* b,char * auteur){
    int clef = fonctionClef(auteur);
    int indice = fonctionHachage(clef, b->m);
    LivreH* tmp = b->T[indice];
    while (tmp!=NULL && tmp->auteur!=auteur){ tmp=tmp->suiv; }
    return tmp;
}

LivreH* search_by_titleH(BiblioH* b,char *title){
    for(int i=0;i<b->m;i++){
        LivreH* tmp = b->T[i];
        while (tmp!=NULL){
            if (strcmp(tmp->titre,title)==0){return tmp;}
            tmp=tmp->suiv;
        }
    }
    return NULL;
}

BiblioH* same_autorH(BiblioH* b,char *auteur){
    BiblioH* res=creer_biblioH(1);
    int clef = fonctionClef(auteur);
    int indice = fonctionHachage(clef, b->m);
    LivreH* tmp = b->T[indice];
    while (tmp!=NULL){
        if(strcmp(tmp->auteur,auteur)==0){
            inserer(res, tmp->num, tmp->titre, tmp->auteur);
        }
        tmp=tmp->suiv;
    }
    return res;
}

void supprimer_ouvrageH(BiblioH* b, int num, char *titre, char *auteur){
    if (b->T==NULL){exit(-1);}                                                            // evite le cas où biblioH est vide/NULL
    int clef = fonctionClef(auteur);
    int indice = fonctionHachage(clef, b->m);
    LivreH* cour = b->T[indice];
    LivreH* ante = NULL;
    while(cour){
        if(cour->num == num && strcmp(cour->titre,titre)==0 && strcmp(cour->auteur,auteur)==0){
            // Parcour pour supprimer les éléments contigues s'ils existent, place cour sur le dernier d'entre eux.
            LivreH* tmp = cour;
            while(tmp && tmp->num == num && strcmp(tmp->titre,titre)==0 && strcmp(tmp->auteur,auteur)==0){
                tmp = tmp->suiv;
                liberer_livreH(cour);
                cour = tmp;
            }
            // CAS : Match n'est pas le premier élément de la listeC
            if(ante){
                ante->suiv = cour;
            // CAS : Match au premier element de la listeC
            }else{ 
                b->T[indice] = cour;
            }
        }else{
            ante = cour;
            cour = cour->suiv;
        }
    }
}

void fusionH(BiblioH* b1, BiblioH* b2){
    if (b2==NULL){return ;}            // Cas trivial où b2 vide
    for(int i=0;i<b2->m;i++){
        LivreH *l = b2->T[i];
        while(l){
            inserer(b1, l->num, l->titre, l->auteur);
            l = l->suiv;
        }
    }
    liberer_biblioH(b2);
}

void add_if_newH(BiblioH* b,int num, char *titre, char *auteur){
    int clef = fonctionClef(auteur);
    int indice = fonctionHachage(clef, b->m);
    LivreH* tmp = b->T[indice];
    LivreH* ante;
    if(!tmp){ b->T[indice] = creer_livreH(num,titre,auteur);b->nE++;return;} // Cas où liste vide => insertion
    while (tmp){
        if(tmp->num==num && strcmp(tmp->titre,titre)==0 && strcmp(tmp->auteur,auteur)==0){ return;}
        ante = tmp;
        tmp=tmp->suiv;
    }
    LivreH *new = creer_livreH(num,titre,auteur);
    ante->suiv = new ;
    b->nE++;
}

BiblioH* recherche_doublonsH(BiblioH* b){
    BiblioH* res =  creer_biblioH(1);
    for(int i=0;i<b->m;i++){
        LivreH* l1 = b->T[i];
        while(l1){
            LivreH * l2 = l1->suiv;
            while(l2){
                if(strcmp(l1->titre,l2->titre)==0 && strcmp(l1->auteur,l2->auteur)==0){
                    add_if_newH(res, l1->num, l1->titre, l1->auteur);
                    add_if_newH(res, l2->num, l2->titre, l2->auteur);
                }
                l2 = l2->suiv;
            }
            l1 = l1->suiv;
        }
    }
    return res;
}

