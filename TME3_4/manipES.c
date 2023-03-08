#include <stdio.h>          // pr printf, FILE , fopen, fclose
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "entreeSortieLC.h" // pour struct Livre et Biblio
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
    Biblio* b = charger_n_entrees(nomfichier, SIZEDICO);
    afficher_biblio(b);
    enregistrer_bilbio(b, "save.txt");
    liberer_Biblio(b);
   
    return 0;
}
