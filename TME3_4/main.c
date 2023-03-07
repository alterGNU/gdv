#include <stdio.h>    // pr printf scanf ...
#include "biblioLC.h" // pr struct
#define BUFF 100      // taille max str

int main(int argc, char *argv[]){
    printf("Hello World!\nCréons des livres:\n");

    char t[BUFF], a[BUFF];
    printf("Entrer le titre du livre <espace> le nom de l'auteur (titre et non sans espace svp)\n");
    scanf("%s %s", t, a);

    char *title=t;
    char *autor=a;

    Livre* l1 = creer_livre(1 ,title ,autor);
    afficher_livre(l1);
    liberer_livre(l1);
    return 0;
}
