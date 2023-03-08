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
Livre* creer_livre(int num, char *titre, char *auteur);
void liberer_livre(Livre *l);

Biblio* creer_biblio();
void afficher_biblio(Biblio* b);
void liberer_Biblio(Biblio* b);
void inserer_en_tete(Biblio* b, int num, char *titre, char *auteur);

//Q1.6
void afficher_livre(Livre *l);
void afficher_biblio(Biblio* b);
Livre* search_by_num(Biblio* b,int num);
Livre* search_by_title(Biblio* b,char *title);
Biblio* same_autor(Biblio* b,char *autor);

#endif
