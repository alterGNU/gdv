#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour exit() ...
#include <time.h>           // pour time
#include <assert.h>         // pour assert
#include "biblioLC.h"       // pour struct Livre et Biblio et leurs fcts
#include "biblioH.h"        // pour struct LivreH et BiblioH et leurs fcts
#include "entreeSortieLC.h" // pour fct chargerLC et enregistrerLC
#include "entreeSortieH.h"  // pour fct chargerH et enregistrerH
#include "utilalea.h"       // pour fct utilitaire et generation aléatoire
#define NBMESURE 10         // correspond au nombre de mesure faite pour une valeur de temps calculé (moyenne)
#define DEBUG 0             // si 1 afficher tous les printfs sinon ne fait rien

int main(int argc, char *argv[]){
    FILE * sortie;
    sortie = fopen("compareSearchByNum.txt", "w");
    if(sortie==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }

    char * entete="set title \"Comparaison des temps de recherche\"\n set xlabel \"Nbr livre\"\n set ylabel \"Temps de recherche (s)\"\n plot \"compareSearchByNum.txt\" using 1:2 title \"ListeChainée_(_p_r_e_s_e_n_t_)_\" with lines lc rgb \"red\" lw 1.2\n set term png\n set output \"searchByNum.png\"\n replot \"compareSearchByNum.txt\" using 1:3 title \"ListeChainée_(_a_b_s_e_n_t_)_\" with lines lc rgb \"orange\" lw 1.2 ,\"compareSearchByNum.txt\" using 1:4 title \"TableHash_(_p_r_e_s_e_n_t_)_\" with lines lc rgb \"blue\" lw 1.2 ,\"compareSearchByNum.txt\" using 1:5 title \"TableHash_(_a_b_s_e_n_t_)_\" with lines lc rgb \"green\" lw 1.2\n";
    fprintf(sortie,"%s",entete);

    for(int nbL = 10;nbL<=10000;nbL+=100){
        int t = (int) nbL / 2;       // taille de la table de hachage => moitié du nb d'element
        Biblio* livrePresent = charger_n_entreesLC("GdeBiblio.txt", NBMESURE);
        Biblio* bLC = charger_n_entreesLC("GdeBiblio.txt", nbL);
        BiblioH* bH = charger_n_entreesH("GdeBiblio.txt", nbL, t);

        
        // Comme dans GdeBiblio les num = ligne + 1, un numero abs est nbl+2
        int numAbs = nbL + 2;
        double moytpLC[NBMESURE];
        double moytpH[NBMESURE];
        double moytaLC[NBMESURE];
        double moytaH[NBMESURE];
        for (int i = 0;i<NBMESURE;i++){
            // Parcour la liste chainée pour trouver le <i+1>eme livre present à chercher
            Livre* obj = livrePresent->L;
            int cpt = 0;
            while(cpt<i){
                obj = obj->suiv;
                cpt++;
            }
            clock_t tps_initLC = clock();
            Livre* resLC =  search_by_numLC(bLC,obj->num);
            clock_t tps_finLC = clock();
            moytpLC[i] = ((double)(tps_finLC - tps_initLC))/ CLOCKS_PER_SEC;

            clock_t tps_initLC_abs = clock();
            Livre* resLCabs =  search_by_numLC(bLC,numAbs);
            clock_t tps_finLC_abs = clock();
            moytaLC[i] = ((double)(tps_finLC_abs - tps_initLC_abs))/ CLOCKS_PER_SEC;

            clock_t tps_initH = clock();
            LivreH* resH =  search_by_numH(bH,obj->num);
            clock_t tps_finH = clock();
            moytpH[i] = ((double)(tps_finH - tps_initH))/ CLOCKS_PER_SEC;

            clock_t tps_initH_abs = clock();
            LivreH* resHabs =  search_by_numH(bH,numAbs);
            clock_t tps_finH_abs = clock();
            moytaH[i] = ((double)(tps_finH_abs - tps_initH_abs))/ CLOCKS_PER_SEC;

            // verification des résultats
            assert(sameBook(resLC,resH)==0);         // check si meme livres trouvés dans les deux structures.
            assert(resLCabs==NULL && resHabs==NULL); // check qu'aucun livre n'a été trouvé par les 2methodes.

            if(DEBUG){
                printf("LC->");
                printf((resLC!=NULL)?"FOUND:":"NOT FOUND:");
                printf("la recherche du %deme livre de num=%d à pris %f(m.sec)\n",i+1,obj->num,moytpLC[i]);
                printf("\nH->");
                printf((resH!=NULL)?"FOUND:":"NOT FOUND:");
                printf("la recherche du %deme livre de num=%d à pris %f(m.sec)\n",i+1,obj->num,moytpH[i]);
            }
        }
        double tpLC = moyenne(moytpLC, NBMESURE);
        double taLC = moyenne(moytaLC, NBMESURE);
        double tpH = moyenne(moytpH, NBMESURE);
        double taH = moyenne(moytaH, NBMESURE);

        if(DEBUG){ printf("La moyenne des temps pour %d livres est de [pLC:%f, aLC%f, pH%f, aH%f]\n", nbL, tpLC, taLC, tpH, taH);}
        fprintf(sortie,"%d,\t%f,\t%f,\t%f,\t%f\n", nbL, tpLC, taLC, tpH, taH);

        liberer_BiblioLC(livrePresent);
        liberer_BiblioLC(bLC);
        liberer_biblioH(bH);
    }
    fclose (sortie);
    system("gnuplot compareSearchByNum.txt");
    return 0;
    }
