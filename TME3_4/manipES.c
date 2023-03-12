#include <stdio.h>          // pr printf, FILE , fopen, fclose
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "entreeSortieLC.h" // pour chargerLC et enregistrerLC
#define SIZEDICO 10         // nbr de livre de la biblio

int main(int argc, char *argv[]){
    if (argc==1){
        printf("Aucun nom de fichier passé en argument:\nUsage : %s <nom_fichier>\n",argv[0]);
        return 1;
    };
    if (argc>2){
        printf("Trop d'argument passé:\nUsage : %s <nom_fichier>\n",argv[0]);
        return 2;
    };

    char * nomfichier=argv[1];
    Biblio* b = charger_n_entreesLC(nomfichier, SIZEDICO);
    afficher_biblioLC(b);
    enregistrer_bilbioLC(b, "save.txt");
    liberer_BiblioLC(b);
   
    return 0;
}
