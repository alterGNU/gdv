#include <stdio.h>
#include "utils.h"
#define BUFFER 150                           // Taille max du buffer

int main(int nbarg, char * argv[]){
    // exo1 Q1.3 : passage d'argument à la commande possible, sinon valeur par default.
    char *original = (nbarg != 3) ? "main.c" : argv[1];
    char *destination = (nbarg != 3) ? "file.txt" : argv[2];
    int cmd = hashFile(original, destination);
    printf((cmd==0)?"Fct hashFile réussie.\n":"Fct hashFile échouée.\n");
    return 0;
}

