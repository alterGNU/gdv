#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour atoi
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

    int n = atoi(argv[2]);   // Conversion deuxieme arg en entier

    // Q1.{1,4} 
    // test charger_n_entrees();
    printf("\nCreation d'une Biblio en lisant les %d première lignes de %s\n",n,argv[1]);
    char * nomfichier=argv[1];
    Biblio* b = charger_n_entrees(nomfichier, n);
    afficher_biblio(b);

    // test enregistrer_biblio()
    printf("\nEnregistrement de la Biblio créée dans le ficher save.txt\n");
    enregistrer_bilbio(b, "save.txt");

    // Q1.6
    // test search_by_num()
    printf("\nRecherche par num:\n");
    Livre* l1 = search_by_num(b,5);
    printf("Pour num=5:");
    afficher_livre(l1);
    Livre* l2 = search_by_num(b,1000);
    printf("Pour num=1000:");
    afficher_livre(l2);
    
    // test search_by_title()
    char *titre1 = "WPQCA";
    printf("\nRecherche par titre:\n");
    Livre* l3 = search_by_title(b,titre1);
    printf("\nPour titre='%s':",titre1);
    afficher_livre(l3);
    
    Livre* l4 = search_by_title(b,"ccPetitePerruche");
    printf("\nPour titre='ccPetitePerruche':");
    afficher_livre(l4);


    liberer_Biblio(b);
   
    return 0;
}
