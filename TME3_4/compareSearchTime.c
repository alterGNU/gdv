#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour exit() ...
#include <time.h>           // pour time
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "biblioH.h"        // pour struct LivreH et BiblioH
#include "entreeSortieLC.h" // pour fct chargerLC et enregistrerLC
#include "entreeSortieH.h"  // pour fct chargerH et enregistrerH
#include "utilalea.h"       // pour fct utilitaire et generation aléatoire
#define MOY 10

int main(int argc, char *argv[]){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.
    //clock_t tps_init, tps_fin;
    //double t1, t2, t3; // temps

    FILE * sortie;
    sortie = fopen("compareSearchByNum.txt", "w");
    if(sortie==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }


    char * entete="set title \"Comparaison des temps de recherche\" \nset xlabel \"Nbr livre\" \nset ylabel \"Temps de recherche (s)\" \nplot \"compareSearchByNum.txt\" using 1:2 title \"ListeChainée\" with lines lc rgb \"red\" lw 1.5 \nset term png\nset output \"searchByNum.png\"\nreplot \"compareSearchByNum.txt\" using 1:3 title \"TableHash\" with lines lc rgb \"red\" lw 1.5\n\n# Nbr Livre, Temps1, Temps2\n";

    fprintf(sortie,"%s",entete);

    for(int nbL = 4;nbL<=10000;nbL+=100){
        int t = (int) nbL / 2;
        Biblio* b1 = charger_n_entreesLC("GdeBiblio.txt", nbL);
        BiblioH* b2 = charger_n_entreesH("GdeBiblio.txt", nbL, t);
        printf(".");
        liberer_BiblioLC(b1);
        liberer_biblioH(b2);
    }
        

        

    //tps_init = clock();
    ///////////// à mesurer
    //tps_fin = clock();
    //t1 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

    //    if(s1 == s2){
    //        fprintf(sortie,"%d,\t%f,\t%f,\t%f\n",taille,t1,t2,t3);
    //    }else{
    //        fclose (sortie);
    //        exit(2);
    //    }
    //}
    fclose (sortie);
    system("gnuplot compareSearchByNum.txt");
    return 0;
}
