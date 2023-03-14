#ifndef UTILS_H_
#define UTILS_H_


char* mot_maj_alea(int t);              // Génére mot de longueur t contenant des majuscules
char* mot_min_alea(int t);              // Génére mot de longueur t contenant des minuscules
int nb_alea(int mini,int maxi);         // Génére un nombre entier compris entre [mini, maxi]
int is_a_file(char *nomFichier);        // Retourne 0 si <nomFichier> est un fichier, 1 sinon

int hashFile(char* source, char* dest);// Exo1 Q1.3
#endif
