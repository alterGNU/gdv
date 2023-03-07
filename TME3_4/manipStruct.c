#include <stdio.h>    // pr printf
#include "biblioLC.h" // pour struct Livre et Biblio
#define BUFF 100      // taille max str

int main(int argc, char *argv[]){
    printf("Créons une bibliothèque:\n");

    char *t2="jeanBLOGUIN";
    char *a2="humourNoir";

    char *t3="jean-michelFAURE";
    char *a3="gin&co_obs&trick";

    Biblio* b1 = creer_biblio();

    inserer_en_tete(b1, 1, t2, a2);
    afficher_biblio(b1);

    inserer_en_tete(b1, 2, t3, a3);
    afficher_biblio(b1);

    liberer_Biblio(b1);
    
    return 0;
}
