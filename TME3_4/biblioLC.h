#ifndef BIBLIOLC_H_
#define BIBLIOLC_H_

//Q1.1
typedef struct livre{
    int num;
    char *titre;
    char *auteur;
    struct livre * suiv;
} Livre;

typedef struct{
    Livre* L;
} Biblio;

//Q1.2
Livre* creer_livreLC(int num, char *titre, char *auteur);
void liberer_livreLC(Livre *l);
Biblio* creer_biblioLC();
void liberer_BiblioLC(Biblio* b);
void inserer_en_teteLC(Biblio* b, int num, char *titre, char *auteur);
//Q1.6
void afficher_livreLC(Livre *l);
void afficher_biblioLC(Biblio* b);
Livre* search_by_numLC(Biblio* b,int num);
Livre* search_by_titleLC(Biblio* b,char *title);
Biblio* same_autorLC(Biblio* b,char *autor);
void supprimer_ouvrageLC(Biblio* b, int num, char *titre, char *auteur);
void fusionLC(Biblio* b1, Biblio* b2);
void add_if_newLC(Biblio* b,int num, char *titre, char *auteur);
Biblio* recherche_doublonsLC(Biblio* b);
//Q3.1
Livre* search_by_autorLC(Biblio* b,char *auteur);

#endif
