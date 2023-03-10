#include <stdio.h>    // pr printf
#include <stdlib.h>   // pr free, exit
#include <string.h>   // pr strdup
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


//Biblio* creer_biblio(){
//    Biblio* res = (Biblio*) malloc(sizeof(Biblio));
//    if(res == NULL) {printf("Error: Out of memory\n"); exit(-1); }
//    res->L = NULL;
//    return res;
//}
//
//void afficher_biblio(Biblio* b){
//    Livre *tmp = b->L;
//    printf("Voici les livres de la bibliothque:\n");
//    int cpt=0;
//    while (tmp!=NULL){
//        printf("\t- ");
//        afficher_livre(tmp);
//        tmp = tmp->suiv;
//        cpt++;
//    }
//    printf("La bibliotheque contient %d livre%s\n",cpt,(cpt!=0)?"s.":".");
//}
//
//void liberer_Biblio(Biblio* b){
//    Livre *l = b->L;
//    Livre *n;
//    while (l!=NULL){
//        n = l->suiv;
//        liberer_livre(l);
//        l = n;
//    }
//    b->L = NULL;
//    free(b);
//}
//
//void inserer_en_tete(Biblio* b, int num, char *titre, char *auteur){
//    Livre *new = creer_livre(num, titre, auteur);
//    (new->suiv) = (b->L);
//    (b->L) = new;
//}
//
//
//Livre* search_by_num(Biblio* b,int num){
//    Livre* tmp = b->L;
//    while (tmp!=NULL && tmp->num!=num){
//        tmp=tmp->suiv;
//    }
//    return tmp;
//}
//
//Livre* search_by_title(Biblio* b,char *title){
//    char * t = strdup(title); // alloue et copie la chaîne de caractères titre
//    Livre* tmp = b->L;
//    while (tmp!=NULL && strcmp(tmp->titre,t)!=0){
//        tmp=tmp->suiv;
//    }
//    free(t);
//    return tmp;
//}
//
//Biblio* same_autor(Biblio* b,char *autor){
//    Biblio* res=creer_biblio();
//    char* a = strdup(autor);
//    Livre* tmp = b->L;
//    while (tmp!=NULL){
//        if(strcmp(tmp->auteur,a)==0){
//            inserer_en_tete(res,tmp->num,tmp->titre,tmp->auteur);
//        }
//        tmp=tmp->suiv;
//    }
//    free(a);
//    return res;
//}
//
//void supprimer_ouvrage(Biblio* b, int num, char *titre, char *auteur){
//    char* t = strdup(titre);
//    char* a = strdup(auteur);
//    Livre* tmp = b->L;
//    if(tmp!=NULL){                                                                // permet d'eviter le cas ou bibliotheque est vide
//        if(tmp->num==num && strcmp(tmp->titre,t)==0 && strcmp(tmp->auteur,a)==0){ // cas où 1er octmpence = 1 livre de la liste chainée
//            b->L=tmp->suiv;
//        }else{                                                                    // autre cas
//            Livre* ante = tmp;
//            while ((tmp!=NULL)&&(tmp->num!=num || strcmp(tmp->titre,t)!=0 || strcmp(tmp->auteur,a)!=0)){
//                ante = tmp;
//                tmp=tmp->suiv;
//            }
//            ante->suiv = (tmp) ? tmp->suiv : tmp; // ternaire pr cas où tmp est NULL ou non
//        }
//        liberer_livre(tmp); // Possible car liberer_livre verifie si Livre != NULL
//    }
//    free(t);
//    free(a);
//}
//
//void fusion(Biblio* b1, Biblio* b2){
//    if (b2==NULL){return ;}                           // Cas trivial où b2 vide
//    Livre *tmp1 = b1->L;
//    if (tmp1!=NULL){
//        while (tmp1->suiv!=NULL){ tmp1 = tmp1->suiv;} // parcour b1 jusqu'au bout
//    }
//    tmp1->suiv = b2->L;                               // joint fin b1 avec debur b2
//    b2->L = NULL;                                     // supprime l'entéte de b2
//}
//
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
