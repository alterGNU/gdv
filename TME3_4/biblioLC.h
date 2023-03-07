typedef struct livre{
    int num;
    char *titre;
    char *auteur;
    struct livre * suiv;
} Livre;

typedef struct{
    Livre* L;
} Biblio;
