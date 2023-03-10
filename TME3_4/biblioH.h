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
LivreH* creer_livre(int num, char *titre, char *auteur);
void afficher_livre(LivreH *l);
void liberer_livre(LivreH *l);
BiblioH* creer_biblio(int m);
void afficher_biblio(BiblioH* b);
void liberer_biblio(BiblioH* b);
//Q2.4
int fonctionHachage(int cle, int m);
//void inserer_en_tete(Biblio* b, int num, char *titre, char *auteur);
//
////Q1.6
//void afficher_biblio(Biblio* b);
//Livre* search_by_num(Biblio* b,int num);
//Livre* search_by_title(Biblio* b,char *title);
//Biblio* same_autor(Biblio* b,char *autor);
//void supprimer_ouvrage(Biblio* b, int num, char *titre, char *auteur);
//void fusion(Biblio* b1, Biblio* b2);
//void add_if_new(Biblio* b,int num, char *titre, char *auteur);
//Biblio* recherche_doublons(Biblio* b);

#endif
