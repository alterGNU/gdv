#include <stdio.h>    // pr printf
#include <stdlib.h>   // pr free, exit
#include <string.h>   // pr strdup
#include "biblioLC.h" // pour struct Livre et Biblio

Livre* creer_livreLC(int num, char *titre, char *auteur){
    Livre* res = malloc(sizeof(Livre));
    if(res == NULL) {printf("Error: Out of memory\n"); exit(-1); }

    res->num = num;
    res->titre = strdup(titre); // alloue et copie la chaîne de caractères titre
    res->auteur = strdup(auteur); // alloue et copie la chaîne de caractères auteur
    res->suiv = NULL;
    return res;
}

void liberer_livreLC(Livre* l){
    if (l){              // Libére le livre passé en argument s'il n'est pas NULL
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}

void afficher_livreLC(Livre *l){
    if (l!=NULL){
        printf("n°:%d,\"%s\" de *%s*\n",l->num,l->titre,l->auteur);
    }else{
        printf("Il n'y a pas de livre\n");
    }
}

Biblio* creer_biblioLC(){
    Biblio* res = (Biblio*) malloc(sizeof(Biblio));
    if(res == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    res->L = NULL;
    return res;
}

void afficher_biblioLC(Biblio* b){
    if (b->L){
        Livre *tmp = b->L;
        printf("Voici les livres de la bibliothque:\n");
        int cpt=0;
        while (tmp!=NULL){
            printf("\t- ");
            afficher_livreLC(tmp);
            tmp = tmp->suiv;
            cpt++;
        }
        printf("La bibliotheque contient %d livre%s\n",cpt,(cpt!=0)?"s.":".");
    }else{
        printf("Il n'y a pas de bibliotheque ici\n");
    }
}

void liberer_BiblioLC(Biblio* b){
    Livre *l = b->L;
    Livre *n;
    while (l!=NULL){
        n = l->suiv;
        liberer_livreLC(l);
        l = n;
    }
    free(b);
    b->L = NULL;
}

void inserer_en_teteLC(Biblio* b, int num, char *titre, char *auteur){
    Livre *new = creer_livreLC(num, titre, auteur);
    new->suiv = b->L;
    b->L = new;
}


Livre* search_by_numLC(Biblio* b,int num){
    Livre* tmp = b->L;
    while (tmp!=NULL){
        if (tmp->num==num){ return tmp; }
        tmp=tmp->suiv;
    }
    return tmp;
}

Livre* search_by_titleLC(Biblio* b,char *title){
    Livre* tmp = b->L;
    while (tmp!=NULL){
        if(strcmp(tmp->titre,title)!=0){
            return tmp;
        }
        tmp=tmp->suiv;
    }
    return tmp;
}

Livre* search_by_autorLC(Biblio* b,char *auteur){
    Livre* tmp = b->L;
    while (tmp!=NULL){
        if(strcmp(tmp->auteur,auteur)!=0){
            return tmp;
        }
        tmp=tmp->suiv;
    }
    return tmp;
}

Biblio* same_autorLC(Biblio* b,char *autor){
    Biblio* res=creer_biblioLC();
    Livre* tmp = b->L;
    while (tmp!=NULL){
        if(strcmp(tmp->auteur,autor)==0){
            inserer_en_teteLC(res,tmp->num,tmp->titre,tmp->auteur);
        }
        tmp=tmp->suiv;
    }
    return res;
}

void supprimer_ouvrageLC(Biblio* b, int num, char *titre, char *auteur){
    Livre* cour = b->L;
    Livre* ante = NULL;
    while(cour){
        if(cour->num == num && strcmp(cour->titre,titre)==0 && strcmp(cour->auteur,auteur)==0){
            // Parcour pour supprimer les éléments contigues s'ils existent, place cour sur le dernier d'entre eux.
            Livre* tmp = cour;
            while(tmp && tmp->num == num && strcmp(tmp->titre,titre)==0 && strcmp(tmp->auteur,auteur)==0){
                tmp = tmp->suiv;
                liberer_livreLC(cour);
                cour = tmp;
            }
            // CAS : Match n'est pas le premier élément de la listeC
            if(ante){
                ante->suiv = cour;
            // CAS : Match au premier element de la listeC
            }else{ 
                b->L = cour;
            }
        }else{
            ante = cour;
            cour = cour->suiv;
        }
    }
}

void fusionLC(Biblio* b1, Biblio* b2){
    if (b2==NULL){return ;}                           // Cas trivial où b2 vide
    Livre *tmp1 = b1->L;
    if (tmp1!=NULL){
        while (tmp1->suiv!=NULL){ tmp1 = tmp1->suiv;} // parcour b1 jusqu'au bout
    }
    tmp1->suiv = b2->L;                               // joint fin b1 avec debur b2
    free(b2);                                         
    b2->L = NULL;
}

void add_if_newLC(Biblio* b,int num, char *titre, char *auteur){
    Livre * p = b->L;
    if(!p){inserer_en_teteLC(b,num,titre,auteur);return;}// si biblio vide ajoute au debut
    Livre * last;
    while(p){
        if(p->num == num && strcmp(p->titre,titre)==0 && strcmp(p->auteur,auteur)==0){ return; }
        last = p;
        p = p->suiv;
    }
    last->suiv = creer_livreLC(num, titre, auteur);
}

Biblio* recherche_doublonsLC(Biblio* b){
    Biblio* res =  creer_biblioLC();
    Livre* tmp1 = b->L;
    while(tmp1){
        Livre * tmp2=tmp1->suiv;
        while(tmp2){
            if(strcmp(tmp1->titre,tmp2->titre)==0 && strcmp(tmp1->auteur,tmp2->auteur)==0){
                add_if_newLC(res, tmp1->num, tmp1->titre, tmp1->auteur);
                add_if_newLC(res, tmp2->num, tmp2->titre, tmp2->auteur);
            }
            tmp2 = tmp2->suiv;
        }
        tmp1 = tmp1->suiv;
    }
    return res;
}

