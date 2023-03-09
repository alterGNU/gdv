#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour atoi
#include <time.h>           // pour time...
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "entreeSortieLC.h" // pour struct Livre et Biblio

int main(int argc, char *argv[]){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.
    if (argc<3){
        printf("Manque des arguments:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 1;
    };
    if (argc>3){
        printf("Trop d'argument passé:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 2;
    };

    int n = atoi(argv[2]);   // Conversion deuxieme arg en entier

    printf("\nCreation d'une Biblio en lisant les %d première lignes de %s\n",n,argv[1]);
    char * nomfichier=argv[1];
    Biblio* b = charger_n_entrees(nomfichier, n);
    liberer_Biblio(b);

    return 0;
}
