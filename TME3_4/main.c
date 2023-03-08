#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>          // pour atoi
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "entreeSortieLC.h" // pour struct Livre et Biblio

int main(int argc, char *argv[]){
    if (argc<3){
        printf("Manque des arguments:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 1;
    };
    if (argc>3){
        printf("Trop d'argument passé:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 2;
    };

    char * nomfichier=argv[1];
    Biblio* b = charger_n_entrees(nomfichier, atoi(argv[2]));
    afficher_biblio(b);
    enregistrer_bilbio(b, "save.txt");
    liberer_Biblio(b);
   
    return 0;
}
