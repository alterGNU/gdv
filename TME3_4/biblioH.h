#ifndef BIBLIOH_H_
#define BIBLIOH_H_

//Q2.1
typedef struct livreh{
    int clef;               // Cles du livre
    int num;                // Numero du livre
    char *titre;            // Titre du livre
    char *auteur;           // Auteur du livre
    struct livreh *suiv;    // Livre suivant dans la liste chainée.
} LivreH;

typedef struct table{
    int nE;                 // nombre d'éléments contenus dans la table
    int m;                  // Taille de la table de hachage
    LivreH ** T;            // Table de hachage avec resolution des collisions par chainage
} BiblioH;

//Q2.2
int fonctionClef(char *auteur);
//Q2.3
LivreH* creer_livreH(int num, char *titre, char *auteur);
void afficher_livreH(LivreH *l);
void liberer_livreH(LivreH *l);
BiblioH* creer_biblioH(int m);
void afficher_biblioH(BiblioH* b);
void liberer_biblioH(BiblioH* b);
//Q2.4
int fonctionHachage(int cle, int m);
//Q2.5
void inserer(BiblioH* b, int num, char *titre, char *auteur);
//Q2.6
LivreH* search_by_numH(BiblioH* b, int num, char *titre, char *auteur);
LivreH* search_by_autorH(BiblioH* b, int num, char *titre, char *auteur);
BiblioH* same_autorH(BiblioH* b,char *autor);
void supprimer_ouvrageH(BiblioH* b, int num, char *titre, char *auteur);
void fusionH(BiblioH* b1, BiblioH* b2);
void add_if_newH(BiblioH* b,int num, char *titre, char *auteur);
BiblioH* recherche_doublonsH(BiblioH* b);
//Q3.1
LivreH* search_by_titleH(BiblioH* b, int num, char *titre, char *auteur);
#endif
