#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct adresse {
    int numero;
    char* rue;
    int code_postal;
} Adresse;

Adresse* creer_adresse(int n, char* r, int c) {
    Adresse* new = (Adresse*) malloc(sizeof(Adresse));

    new->numero = n;
    new->rue= (char*) malloc(sizeof(strlen(r)+1));
    strcpy(new->rue, r);
    new->code_postal = c;
    return new;
}

int main(void) {
    Adresse* maison = creer_adresse (12, "manoeuvre", 15670);
    printf("Adresse courante maison: %d rue %s %d France\n", maison->numero, maison->rue, maison->code_postal);
    free(maison->rue);
    free(maison);

    return 0;
}

