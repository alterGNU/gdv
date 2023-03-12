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
// =[     NUM ]===========================================================================
    FILE * sortie1 = fopen("compareSearchByNum.txt", "w");
    if(sortie1==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }
    FILE * sortie2 = fopen("compareSearchByTitle.txt", "w");
    if(sortie2==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }

    char * entete1="set title \"Comparaison des temps de recherche par NUMERO\"\nset xlabel \"Nbr livre\"\nset ylabel \"Temps de recherche (s)\"\nplot \"compareSearchByNum.txt\" using 1:2 title \"ListeChainée_(_p_r_e_s_e_n_t_)_\" with lines lc rgb \"red\" lw 1.2\nset term png\nset output \"searchByNum.png\"\nreplot \"compareSearchByNum.txt\" using 1:3 title \"ListeChainée_(_a_b_s_e_n_t_)_\" with lines lc rgb \"orange\" lw 1.2 ,\"compareSearchByNum.txt\" using 1:4 title \"TableHash_(_p_r_e_s_e_n_t_)_\" with lines lc rgb \"blue\" lw 1.2 ,\"compareSearchByNum.txt\" using 1:5 title \"TableHash_(_a_b_s_e_n_t_)_\" with lines lc rgb \"green\" lw 1.2\n";
    fprintf(sortie1,"%s",entete1);

    char * entete2="set title \"Comparaison des temps de recherche par TITRE\"\nset xlabel \"Nbr livre\"\nset ylabel \"Temps de recherche (s)\"\nplot \"compareSearchByTitle.txt\" using 1:2 title \"ListeChainée_(_p_r_e_s_e_n_t_)_\" with lines lc rgb \"red\" lw 1.2\nset term png\nset output \"searchByTitle.png\"\nreplot \"compareSearchByTitle.txt\" using 1:3 title \"ListeChainée_(_a_b_s_e_n_t_)_\" with lines lc rgb \"orange\" lw 1.2 ,\"compareSearchByTitle.txt\" using 1:4 title \"TableHash_(_p_r_e_s_e_n_t_)_\" with lines lc rgb \"blue\" lw 1.2 ,\"compareSearchByTitle.txt\" using 1:5 title \"TableHash_(_a_b_s_e_n_t_)_\" with lines lc rgb \"green\" lw 1.2\n";
    fprintf(sortie2,"%s",entete2);

    for(int nbL = 100;nbL<=10000;nbL+=100){
        clock_t t1, t2;
        int t = (int) nbL / 2;       // taille de la table de hachage => moitié du nb d'element
        // Structures sur lesquelles travailler
        Biblio* bLC = charger_n_entreesLC("GdeBiblio.txt", nbL);
        BiblioH* bH = charger_n_entreesH("GdeBiblio.txt", nbL, t);
        // Livres presents
        Biblio* livrePresent = charger_n_entreesLC("GdeBiblio.txt", NBMESURE);
        // Livre non present
        int numAbs = nbL + 2; // Comme dans GdeBiblio les num = ligne + 1, un numero abs est nbl+2
        Livre* lLC_abs = creer_livreLC(-1 , "Data_Structures_Using_C", "REEMA_THAREJA");
        LivreH* lH_abs = creer_livreH(-1 , "Data_Structures_Using_C", "REEMA_THAREJA");

        double moy_num_tpLC[NBMESURE], moy_num_tpH[NBMESURE], moy_num_taLC[NBMESURE], moy_num_taH[NBMESURE];
        double moy_title_tpLC[NBMESURE], moy_title_tpH[NBMESURE], moy_title_taLC[NBMESURE], moy_title_taH[NBMESURE];
        for (int i = 0;i<NBMESURE;i++){
            // Parcour la liste chainée pour trouver le <i+1>eme livre present à chercher
            Livre* obj = livrePresent->L;
            int cpt = 0;
            while(cpt<i){
                obj = obj->suiv;
                cpt++;
            }
            // NUM
            t1 = clock();
            Livre* resLC_num =  search_by_numLC(bLC,obj->num);
            t2 = clock();
            moy_num_tpLC[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            t1 = clock();
            Livre* resLCabs_num =  search_by_numLC(bLC,numAbs);
            t2 = clock();
            moy_num_taLC[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            t1 = clock();
            LivreH* resH_num =  search_by_numH(bH,obj->num);
            t2 = clock();
            moy_num_tpH[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            t1 = clock();
            LivreH* resHabs_num =  search_by_numH(bH,numAbs);
            t2 = clock();
            moy_num_taH[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            // verification des résultats
            assert(sameBook(resLC_num,resH_num)==0);         // check si meme livres trouvés dans les deux structures.
            assert(resLCabs_num==NULL && resHabs_num==NULL); // check qu'aucun livre n'a été trouvé par les 2methodes.
            // TITRE
            t1 = clock();
            Livre* resLC_tit =  search_by_titleLC(bLC,obj->titre);
            t2 = clock();
            moy_title_tpLC[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            t1 = clock();
            Livre* resLCabs_tit =  search_by_titleLC(bLC,lLC_abs->titre);
            t2 = clock();
            moy_title_taLC[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            t1 = clock();
            LivreH* resH_tit =  search_by_titleH(bH,obj->titre);
            t2 = clock();
            moy_title_tpH[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            t1 = clock();
            LivreH* resHabs_tit =  search_by_titleH(bH,lH_abs->titre);
            t2 = clock();
            moy_title_taH[i] = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
            // verification des résultats
            assert(sameBook(resLC_tit,resH_tit)==0);         // check si meme livres trouvés dans les deux structures.
            assert(resLCabs_tit==NULL && resHabs_tit==NULL); // check qu'aucun livre n'a été trouvé par les 2methodes.

        }
        // NUM
        double num_tpLC = moyenne(moy_num_tpLC, NBMESURE);
        double num_taLC = moyenne(moy_num_taLC, NBMESURE);
        double num_tpH = moyenne(moy_num_tpH, NBMESURE);
        double num_taH = moyenne(moy_num_taH, NBMESURE);
        //TITRE
        double tit_tpLC = moyenne(moy_title_tpLC, NBMESURE);
        double tit_taLC = moyenne(moy_title_taLC, NBMESURE);
        double tit_tpH = moyenne(moy_title_tpH, NBMESURE);
        double tit_taH = moyenne(moy_title_taH, NBMESURE);

        if(DEBUG){ printf("La moyenne des temps pour %d livres est de [pLC:%f, aLC%f, pH%f, aH%f]\n", nbL, num_tpLC, num_taLC, num_tpH, num_taH);}
        fprintf(sortie1,"%d,\t%f,\t%f,\t%f,\t%f\n", nbL, num_tpLC, num_taLC, num_tpH, num_taH);
        if(DEBUG){ printf("La moyenne des temps pour %d livres est de [pLC:%f, aLC%f, pH%f, aH%f]\n", nbL, tit_tpLC, tit_taLC, tit_tpH, tit_taH);}
        fprintf(sortie2,"%d,\t%f,\t%f,\t%f,\t%f\n", nbL, tit_tpLC, tit_taLC, tit_tpH, tit_taH);

        liberer_livreLC(lLC_abs);
        liberer_livreH(lH_abs);
        liberer_BiblioLC(livrePresent);
        liberer_BiblioLC(bLC);
        liberer_biblioH(bH);
    }
    fclose (sortie1);
    fclose (sortie2);

    system("gnuplot compareSearchByNum.txt");
    system("gnuplot compareSearchByTitle.txt");
    return 0;
    }
