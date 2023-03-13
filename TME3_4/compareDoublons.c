#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour exit() ...
#include <time.h>           // pour time
#include <assert.h>         // pour assert
#include "biblioLC.h"       // pour struct Livre et Biblio et leurs fcts
#include "biblioH.h"        // pour struct LivreH et BiblioH et leurs fcts
#include "entreeSortieLC.h" // pour fct chargerLC et enregistrerLC
#include "entreeSortieH.h"  // pour fct chargerH et enregistrerH
#include "utilalea.h"       // pour fct utilitaire
#define NBMESURE 10         // correspond au nombre de mesure faite pour une valeur de temps calculé (moyenne)

int main(int argc, char *argv[]){
// =[     NUM ]===========================================================================
    FILE * sortie1 = fopen("compareSearchDoublons.txt", "w");
    if(sortie1==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }

    char * entete1="set title \"Comparaison des temps de recherche des DOUBLONS\"\nset xlabel \"Nbr livre\"\nset ylabel \"Temps de recherche (s)\"\nplot \"compareSearchDoublons.txt\" using 1:2 title \"ListeChainée\" with lines lc rgb \"red\" lw 2\nset term png\nset output \"searchDoublons.png\"\nreplot \"compareSearchDoublons.txt\" using 1:3 title \"TableHash_(_t_a_i_l_l_e_=_3_x_n_E_)\" with lines lc rgb \"blue\" lw 3\n";
    fprintf(sortie1,"%s",entete1);
       
    Biblio *bLC, *dLC;
    BiblioH *bH, *dH;
    for(int nbL = 1000;nbL<=50000;nbL+=1000){
        clock_t t1, t2;
        // Structures sur lesquelles travailler
        bLC = charger_n_entreesLC("GdeBiblio.txt", nbL);
        bH = charger_n_entreesH("GdeBiblio.txt", nbL, 3*nbL);// taille de la table de hachage => trois fois le nb d'elements

        double *moy_tLC, *moy_tH;
        moy_tLC = (double*) malloc(NBMESURE * sizeof(double));  
        if (moy_tLC == NULL) {printf("Erreur d'allocation de mémoire\n"); return 1;}
        moy_tH = (double*) malloc(NBMESURE * sizeof(double));
        if (moy_tH == NULL) {printf("Erreur d'allocation de mémoire\n"); return 1;}
        for (int i = 0;i<NBMESURE;i++){
            // MESURE PR LC
            t1 = clock();
            dLC = recherche_doublonsLC(bLC);
            t2 = clock();
            moy_tLC[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            // MERSURE PR H
            t1 = clock();
            dH = recherche_doublonsH(bH);
            t2 = clock();
            moy_tH[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            // LIBERER
            liberer_BiblioLC(dLC);
            liberer_biblioH(dH);
        }

        double tLC = moyenne(moy_tLC, NBMESURE);
        double tH = moyenne(moy_tH, NBMESURE);
        fprintf(sortie1,"%d,\t%f,\t%f\n", nbL, tLC, tH);
        free(moy_tLC);
        free(moy_tH);

    liberer_BiblioLC(bLC);
    liberer_biblioH(bH);
    }
    fclose (sortie1);

    system("gnuplot compareSearchDoublons.txt");
    return 0;
    }
