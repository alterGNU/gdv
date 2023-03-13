#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour exit() ...
#include <time.h>           // pour time
#include <assert.h>         // pour assert
#include "biblioLC.h"       // pour struct Livre et Biblio et leurs fcts
#include "biblioH.h"        // pour struct LivreH et BiblioH et leurs fcts
#include "entreeSortieLC.h" // pour fct chargerLC et enregistrerLC
#include "entreeSortieH.h"  // pour fct chargerH et enregistrerH
#include "utilalea.h"       // pour fct utilitaire et generation aléatoire
#define NBMESURE 100        // correspond au nombre de mesure faite pour une valeur de temps calculé (moyenne)

int main(int argc, char *argv[]){
// =[     NUM ]===========================================================================
    FILE * sortie = fopen("compareHashTableSize.txt", "w");
    if(sortie==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }

    char * entete1="set title \"Comparaison des temps en fonction de la TAILLE DE LA TABLE DE HACHAGE\"\nset xlabel \"Nbr livre\"\nset ylabel \"Temps de recherche (s)\"\nplot \"compareHashTableSize.txt\" using 1:2 title \"Table=_n_E_/_5_0\" with lines lc rgb \"red\" lw 1.2\nset term png\nset output \"hashTableSize.png\"\nreplot \"compareHashTableSize.txt\" using 1:3 title \"Table=_n_E_/_2_5_\" with lines lc rgb \"orange\" lw 1.2 ,\"compareHashTableSize.txt\" using 1:4 title \"Table=_n_E\" with lines lc rgb \"blue\" lw 1.2 ,\"compareHashTableSize.txt\" using 1:5 title \"Table=_4_*_n_E\" with lines lc rgb \"green\" lw 1.2\n";
    fprintf(sortie,"%s",entete1);


    for(int nbL = 100;nbL<=50000;nbL+=500){
        // Structures sur lesquelles travailler
        int size1 = (int) nbL/50 ; // taille table hash = 1/8 eme du nombre total d'ouvrage
        BiblioH* b1 = charger_n_entreesH("GdeBiblio.txt", nbL, size1);
        int size2 = (int) nbL/25 ; // taille table hash = 1/4 du nombre total d'ouvrage
        BiblioH* b2 = charger_n_entreesH("GdeBiblio.txt", nbL, size2);
        int size3 = (int) nbL ;  // taille table hash = 1/2 du nombre total d'ouvrage
        BiblioH* b3 = charger_n_entreesH("GdeBiblio.txt", nbL, size3);
        int size4 = (int) 4*nbL;     // taille table hash = 3/4 du nombre total d'ouvrage
        BiblioH* b4 = charger_n_entreesH("GdeBiblio.txt", nbL, size4);
        // panel=moitier de livre présent et moitié de livre inconnu (pour assurer pire des cas)
        int moitie = (int) NBMESURE / 2;
        Biblio* panel = charger_n_entreesLC("GdeBiblio.txt", moitie);
        for (int i = 0;i<moitie;i++){
            int nu = nb_alea(50000,50020);
            char* ti = titre_alea(10);
            char* au = nom_alea(5);
            inserer_en_teteLC(panel, nu, ti, au);
            free(ti);
            free(au);
        }

        double moy1[NBMESURE], moy2[NBMESURE], moy3[NBMESURE], moy4[NBMESURE];
        for (int i = 0;i<NBMESURE;i++){
            clock_t t1, t2;
            // Parcour la liste chainée pour trouver le <i+1>eme livre present à chercher
            Livre* obj = panel->L;
            int cpt = 0;
            while(cpt<i){
                obj = obj->suiv;
                cpt++;
            }
            t1 = clock();
            LivreH* res1 = search_by_autorH(b1,obj->num,obj->titre,obj->auteur);
            t2 = clock();
            moy1[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;

            t1 = clock();
            LivreH* res2 = search_by_autorH(b2,obj->num,obj->titre,obj->auteur);
            t2 = clock();
            moy2[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;

            t1 = clock();
            LivreH* res3 = search_by_autorH(b3,obj->num,obj->titre,obj->auteur);
            t2 = clock();
            moy3[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;

            t1 = clock();
            LivreH* res4 = search_by_autorH(b4,obj->num,obj->titre,obj->auteur);
            t2 = clock();
            moy4[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
        }
        // NUM
        double tm1 = moyenne(moy1, NBMESURE);
        double tm2 = moyenne(moy2, NBMESURE);
        double tm3 = moyenne(moy3, NBMESURE);
        double tm4 = moyenne(moy4, NBMESURE);

        fprintf(sortie,"%d,\t%f,\t%f,\t%f,\t%f\n", nbL,tm1,tm2,tm3,tm4);

        liberer_BiblioLC(panel);
        liberer_biblioH(b1);
        liberer_biblioH(b2);
        liberer_biblioH(b3);
        liberer_biblioH(b4);
    }
    fclose (sortie);

    system("gnuplot compareHashTableSize.txt");
    return 0;
    }
