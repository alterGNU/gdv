#include <stdio.h>    // pour printf
#include <stdlib.h>   // pour free, exit #include <string.h> 
#include <string.h>   // pour strdup, strcmp
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

double moyenne(double *tab, int nbElement){
    // Fait la moyenne de tous les éléments d'un tableau de n double
    double res = 0;
    for(int i=0;i<nbElement;i++){ res += tab[i]; }
    return (double) res/nbElement;
}

int sameBook(Livre* lLC, LivreH* lH){ // compare deux livres : Livre et LivreH, placé ici et pas dans utilalea.c car import circulaire...
    // retourne 0 si le Livre lLC à les meme champs que le LivreH lH.
    // retourne 1 si un des champs (num,titre,auteur) différes.
    if ((lLC && !lH)||(!lLC && lH)){return 1;}                                                                       // cas où un des deux livres est NULL et pas l'autre
    if (!lLC && !lH){return 0;}                                                                                      // cas où les deux livres sont NULL, considéré comme identique ici.
    return ((lLC->num == lH->num) && strcmp(lLC->titre, lH->titre)==0 && strcmp(lLC->auteur, lH->auteur)==0)? 0 : 1; // autres cas
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
