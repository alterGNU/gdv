#ifndef BIBLIOLC_H_
#define BIBLIOLC_H_

typedef struct livre{
    int num;
    char *titre;
    char *auteur;
    struct livre * suiv;
} Livre;

typedef struct{
    Livre* L;
} Biblio;

Livre* creer_livre(int num, char *titre, char *auteur);
void liberer_livre(Livre *l);
void afficher_livre(Livre *l);

Biblio* creer_biblio();
void afficher_biblio(Biblio* b);
void liberer_Biblio(Biblio* b);
void inserer_en_tete(Biblio* b, int num, char *titre, char *auteur);

#endif
