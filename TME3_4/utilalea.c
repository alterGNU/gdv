#include <stdio.h>    // pr printf
#include <stdlib.h>   // pr free, exit #include <string.h> 
#include <string.h>   // pr strdup
#include <math.h>     // pour sqrt
#include "utilalea.h" // pour headers

// ===[ UTILE ]===========================================================================

void menu(){
    // Affiche le menu des choix possibles
    printf("\n\nVoici vos choix:\n");
    printf("\t- 0 : Quitter le programme\n");
    printf("\t- 1 : Afficher la bibliothèque\n");
    printf("\t- 2 : Créer puis inserer en tete un livre\n");
    printf("\t- 3 : Chercher un livre via son numero \n");
    printf("\t- 4 : Chercher un livre via son titre \n");
    printf("\t- 5 : Créer une bibliotheque contenant tous les ouvrages d'un auteur\n");
    printf("\t- 6 : Supprimer un ouvrage\n");
    printf("\t- 7 : constituer une bibliotheque des doublons(sauvegarde possible)\n");
}

// ===[ ALÉATOIRE ]======================================================================
char* nom_alea(int t){
    // Genere un nom (Composé uniquement de majuscule) de longueur t
    char * res = (char *) malloc(t*sizeof(char));
    for( int i = 0; i < t; ++i){
        res[i] = 'A' + random()%26;
    }
    return res;
}

char* titre_alea(int t){
    // Genere un titre (Composé uniquement de minuscule) de longueur t
    char * res = (char *) malloc(t*sizeof(char));
    for( int i = 0; i < t; ++i){
        res[i] = 'a' + rand()%26;
    }
    return res;
}

int nb_alea(int borninf,int bornsup){ 
    // Titre un entier compris entre [bornInf, bornSup]
    return (int) (((double)(bornsup-borninf+1)/RAND_MAX) * rand() + borninf);

}
