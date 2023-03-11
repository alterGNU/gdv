#ifndef ENTREESORTIEH_H
#define ENTREESORTIEH_H
#include "biblioH.h"

BiblioH* charger_n_entreesH(char * nom_fichier, int nb_ligne, int taille_table);
void enregistrer_bilbioH(BiblioH* b, char *nom_fichier);

#endif
