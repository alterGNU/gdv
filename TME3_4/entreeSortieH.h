#ifndef ENTREESORTIEH_H
#define ENTREESORTIEH_H
#include "biblioH.h"

BiblioH* charger_n_entrees(char * nom_fichier, int nb_ligne, int taille_table);
void enregistrer_bilbio(BiblioH* b, char *nom_fichier);

#endif
