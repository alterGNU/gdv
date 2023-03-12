#ifndef UTILALEA_H_
#define UTILALEA_H_

#include "biblioLC.h"       // pour la struct Livre utilisée par la fct sameBook
#include "biblioH.h"        // pour la struct LivreH utilisée par la fct sameBook


// ---[ UTILE ]---------------------------------------------------------------------------
void menu();
double moyenne(double *tab, int nbElement);
int sameBook(Livre* lLC, LivreH* lH); // compare une instance de Livre avec LivreH

// ---[ ALÉATOIRE ]----------------------------------------------------------------------
char* nom_alea(int t);
char* titre_alea(int t);
int nb_alea(int borninf,int bornsup);

#endif
