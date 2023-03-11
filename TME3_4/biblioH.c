#include <stdio.h>    // pr printf
#include <stdlib.h>   // pr free, exit #include <string.h> 
#include <string.h>   // pr strdup
#include <math.h>     // pour sqrt
#include "biblioH.h"  // pour struct Livre et Biblio

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

LivreH* creer_livre(int num, char *titre, char *auteur){
    LivreH* res = malloc(sizeof(LivreH));
    if(res == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    res->clef = fonctionClef(auteur);;
    res->num = num;
    res->titre = strdup(titre); // alloue et copie la chaîne de caractères titre
    res->auteur = strdup(auteur); // alloue et copie la chaîne de caractères auteur
    res->suiv = NULL;
    return res;
}

void afficher_livre(LivreH *l){
    if (l!=NULL){
        printf("clef:%d->(n°:%d,\"%s\" de *%s*)\n",l->clef,l->num,l->titre,l->auteur);
    }else{
        printf("Il n'y a pas de livre\n");
    }
}

void liberer_livre(LivreH* l){
    if (l){              // Libére le livre passé en argument s'il n'est pas NULL
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}


BiblioH* creer_biblio(int m){
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

void afficher_biblio(BiblioH* b){
    if(b==NULL){printf("Il n'y a pas de tableau\n");return;}
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

void liberer_biblio(BiblioH* b){
    if(b==NULL){return;}
    for (int i=0;i<b->m;i++){
        LivreH *l = b->T[i],*n;
        while (l!=NULL){
            n = l->suiv;
            liberer_livre(l);
            l = n;
        }
    }
    free(b->T);
    free(b);
}

int fonctionHachage(int cle, int m){
    double a = ((sqrt(5)-1)/2);
    double kA = (double) cle * a;
    return (int) (m*(kA - ((int)kA)));
}

void inserer(BiblioH* b, int num, char *titre, char *auteur){
    //etape1: Creation du nouveau livre à ajouter
    LivreH * l = creer_livre(num,titre,auteur);
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

LivreH* search_by_num(BiblioH* b,int num){
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

//LivreH* search_by_autor(BiblioH* b,char * auteur){
//    int clef = fonctionClef(auteur);
//    int indice = fonctionHachage(clef, b->m);
//    LivreH* tmp = b->T[indice];
//    while (tmp!=NULL && tmp->auteur!=auteur){ tmp=tmp->suiv; }
//    return tmp;
//}

LivreH* search_by_title(BiblioH* b,char *title){
    for(int i=0;i<b->m;i++){
        LivreH* tmp = b->T[i];
        while (tmp!=NULL){
            if (strcmp(tmp->titre,title)==0){return tmp;}
            tmp=tmp->suiv;
        }
    }
    return NULL;
}

BiblioH* same_autor(BiblioH* b,char *auteur){
    BiblioH* res=creer_biblio(1);
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

void supprimer_ouvrage(BiblioH* b, int num, char *titre, char *auteur){
    // ne pas oublier de décrémenter le b->nE
    if (b==NULL){exit(-1);}                                                                 // evite le cas où biblioH est vide/NULL
    int clef = fonctionClef(auteur);
    int indice = fonctionHachage(clef, b->m);
    LivreH* tmp = b->T[0];
    LivreH* ante;
    while(tmp!=NULL){                                                                          // permet d'eviter le cas ou bibliotheque est vide
        if(tmp->num==num && strcmp(tmp->titre,titre)==0 && strcmp(tmp->auteur,auteur)==0){  // cas où 1er octmpence = 1 LivreH de la liste chainée
            if (ante){            // cas match au premier element de la liste
                ante->suiv = (tmp) ? tmp->suiv : tmp; // ternaire pr cas où tmp est NULL ou non
            }else{                      // autre cas!milieu ou fin de liste
                b->T[0] = tmp->suiv;
            }
            liberer_livre(tmp);
            b->nE--;
        }
        ante = tmp;
        tmp=tmp->suiv;
    }
}

void fusion(BiblioH* b1, BiblioH* b2){
    if (b2==NULL){return ;}                           // Cas trivial où b2 vide
    for(int i=0;i<b2->m;i++){
        LivreH *l = b2->T[i];
        while(l){
            LivreH *ante=l;
            inserer(b1, l->num, l->titre, l->auteur);
            l = l->suiv;
        }
    }
    liberer_biblio(b2);
}

//void add_if_new(Biblio* b,int num, char *titre, char *auteur){
//    Livre * p = b->L;
//    if(!p){inserer_en_tete(b,num,titre,auteur);return;}// si biblio vide ajoute au debut
//    Livre * last;
//    while(p){
//        if(p->num == num && strcmp(p->titre,titre)==0 && strcmp(p->auteur,auteur)==0){ return; }
//        last = p;
//        p = p->suiv;
//    }
//    last->suiv = creer_livre(num, titre, auteur);
//}
//
//Biblio* recherche_doublons(Biblio* b){
//    Biblio* res =  creer_biblio();
//    Livre* tmp1 = b->L;
//    while(tmp1){
//        Livre * tmp2=tmp1->suiv;
//        while(tmp2){
//            if(strcmp(tmp1->titre,tmp2->titre)==0 && strcmp(tmp1->auteur,tmp2->auteur)==0){
//                add_if_new(res, tmp1->num, tmp1->titre, tmp1->auteur);
//                add_if_new(res, tmp2->num, tmp2->titre, tmp2->auteur);
//            }
//            tmp2 = tmp2->suiv;
//        }
//        tmp1 = tmp1->suiv;
//    }
//    return res;
//}
//
