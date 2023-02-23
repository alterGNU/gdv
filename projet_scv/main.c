#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 150                           // Taille max du buffer

int main(int nbarg, char * argv[]){
    //printf("Hello World!\n");              // exo1 Q1.1
    //system("sha256sum main.c > file.tmp"); // exo1 Q1.2
    // exo1 Q1.3 : passage d'argument à la commande possible, sinon valeur par default.
    int hashFile(char*, char*);              // Prototype de la fonction exo 1 Q1.3
    char* original;
    char* destination;
    if (nbarg != 3){
        original="main.c";
        destination="file.txt";
    }else{
        original=argv[1];
        destination=argv[2];
    }
    // version operateur ternaire:
    //original = (nbarg != 3) ? "main.c" : argv[1];
    //destination = (nbarg != 3) ? "file.txt" : argv[2];
    hashFile(original, destination);
}

int hashFile(char* source, char* dest){      // Exo1 Q1.3
    // calcul le hash du contenu du fichier source dans le fichier dest
    // retourne 0 si tout s'est bien passé sinon entier naturel
    printf("Le fichier source est:'%s'\n",source);
    printf("Le fichier destination est:'%s'\n",dest);
    char cmd[BUFFER]="sha256sum ";
    strcat(cmd,source);
    strcat(cmd," > ");
    strcat(cmd,dest);
    printf("Execution de la commande:\n\t-'%s'\n",cmd);
    system(cmd);
}
