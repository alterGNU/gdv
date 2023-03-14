#include <stdio.h>   // pr struct:FILE, fct:fopen, fclose, sprintf, fprintf
#include <stdlib.h>  // pr fcts:system, rand
#include <string.h>  // pr fcts:strcat
#include "utils.h"   // pr signatures fcts suivantes
#define BUFFER 256  

char* mot_maj_alea(int t){
    // Genere un mot de longueur t contenant uniquement des majuscules
    char * res = (char *) malloc(t*sizeof(char));
    for( int i = 0; i < t; ++i){ res[i] = 'A' + random()%26; }
    return res;
}

char* mot_min_alea(int t){
    // Genere un mot de longueur t contenant uniquement des minuscules
    char * res = (char *) malloc(t*sizeof(char));
    for( int i = 0; i < t; ++i){ res[i] = 'a' + rand()%26; }
    return res;
}

int nb_alea(int borninf,int bornsup){ 
    // Titre un entier compris entre [bornInf, bornSup]
    return (int) (((double)(bornsup-borninf+1)/RAND_MAX) * rand() + borninf);
}

int is_a_file(char *nomFichier){
    // Retourne 0 si <nomFichier> est un fichier, 1 sinon
    int res=1;
    FILE *f = fopen(nomFichier, "r");
    if (f){
        res = 0;
        fclose(f);
    }
    return res;
}

int hashFile(char* source, char* dest){      // Exo1 Q1.3
    // calcul le hash du contenu du fichier source dans le fichier dest
    // retourne 0 si tout s'est bien passé sinon entier naturel
    char cmd[BUFFER];
    sprintf(cmd,"sha256sum %s > %s", source, dest);
    return system(cmd);
}

