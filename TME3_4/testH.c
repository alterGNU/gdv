#include <stdio.h>         // pour printf, FILE , fopen, fclose
#include <stdlib.h>        // pour atoi
#include <time.h>          // pour time...
#include <assert.h>        // pour assert
#include <math.h>          // pour sqrt
#include "biblioH.h"       // pour struct Livre et Biblio
//#include "entreeSortieH.h" // pour fct charger et enregistrer

int nb_alea(int borninf,int bornsup){ 
    // tire un entier compris entre [borninf, bornsup]
    return (int) (((double)(bornsup-borninf+1)/RAND_MAX) * rand() + borninf);
}

char* nom_alea(int t){
    char * res = (char *) malloc(t*sizeof(char));
    for( int i = 0; i < t; ++i){
        res[i] = 'A' + random()%26;
    }
    return res;
}

char* titre_alea(int t){
    char * res = (char *) malloc(t*sizeof(char));
    for( int i = 0; i < t; ++i){
        res[i] = 'a' + rand()%26;
    }
    return res;
}

int main(int argc, char *argv[]){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.
    int n, m;
    if (argc!=3){
        n=10;
        m=10;
    }else{
        n=atoi(argv[1]);
        m=atoi(argv[2]);
    }
    
    //// test fct fonctionClef(char *auteur);
    //assert(0==fonctionClef(""));
    //assert(97==fonctionClef("a"));
    //assert(97+98+99+100==fonctionClef("abcd"));
    //assert(65==fonctionClef("A"));
    //assert(65+66+67+68+69+70+71==fonctionClef("ABCDEFG"));

    ////Genére données livre0 aléatoirement
    //int num0 = nb_alea(0,10);
    //char * auteur0 = nom_alea(nb_alea(3,9));
    //char * titre0 = titre_alea(nb_alea(5,15));
    //printf("Données alea0:(%d,%s,%s)\n",num0,auteur0,titre0);
    //int clef0 = fonctionClef(auteur0);
    //printf("'%s' --> %d\n",auteur0,clef0);

    ////Genére données livre1 aléatoirement
    //int num1 = nb_alea(0,10);
    //char * auteur1 = nom_alea(nb_alea(3,9));
    //char * titre1 = titre_alea(nb_alea(5,15));
    //printf("Données alea0:(%d,%s,%s)\n",num1,auteur1,titre1);
    //int clef1 = fonctionClef(auteur1);
    //printf("'%s' --> %d\n",auteur1,clef1);

    //// creation, affichage et liberation de livreH
    //LivreH* l0 = creer_livre(num0,titre0,auteur0);
    //afficher_livre(l0);

    //LivreH* l1 = creer_livre(num1,titre1,auteur1);
    //afficher_livre(l1);

    //liberer_livre(l0);
    //liberer_livre(l1);

    //// creation, affichage et liberation d'une bilbioH
    //BiblioH * b = creer_biblio(4);
    //afficher_biblio(b);
    //liberer_biblio(b);

    //// free les malloc du main
    //free(auteur0);
    //free(titre0);
    //free(auteur1);
    //free(titre1);

    //// test fonctionHachage
    //for (int i=0;i<n;i++){
    //    char * auteur = nom_alea(nb_alea(3,9));
    //    int clef = fonctionClef(auteur);
    //    int indice = fonctionHachage(clef,m);
    //    printf("%s->%d->%d\n",auteur,clef,indice);
    //    free(auteur);
    //}

    // test fonction d'insertion
    BiblioH * b1 = creer_biblio(m);
    afficher_biblio(b1);

    for (int i=0;i<n;i++){
        int num = nb_alea(0,10);
        char * auteur = nom_alea(nb_alea(3,9));
        char * titre = titre_alea(nb_alea(5,15));
        inserer(b1, num, titre, auteur);
        afficher_biblio(b1);
        free(titre);
        free(auteur);
    }
    liberer_biblio(b1);

    return 0;
}
