#include <stdio.h>         // pour printf, FILE , fopen, fclose
#include <stdlib.h>        // pour atoi
#include <time.h>          // pour time...
#include <assert.h>        // pour assert
#include <string.h>        // pour strcmp
#include <math.h>          // pour sqrt
#include "biblioH.h"       // pour struct Livre et Biblio
#include "entreeSortieH.h" // pour fct charger et enregistrer
#include "utilalea.h"      // pour fcts nom_alea, titre_alea, nb_alea

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
    

    // test fct fonctionClef(char *auteur);
    assert(0==fonctionClef(""));
    assert(97==fonctionClef("a"));
    assert(97+98+99+100==fonctionClef("abcd"));
    assert(65==fonctionClef("A"));
    assert(65+66+67+68+69+70+71==fonctionClef("ABCDEFG"));

    //Genére données livre0 aléatoirement
    int num0 = nb_alea(0,10);
    char * auteur0 = nom_alea(nb_alea(3,9));
    char * titre0 = titre_alea(nb_alea(5,15));
    printf("Données alea0:(%d,%s,%s)\n",num0,auteur0,titre0);
    int clef0 = fonctionClef(auteur0);
    printf("'%s' --> %d\n",auteur0,clef0);

    //Genére données livre1 aléatoirement
    int num1 = nb_alea(0,10);
    char * auteur1 = nom_alea(nb_alea(3,9));
    char * titre1 = titre_alea(nb_alea(5,15));
    printf("Données alea0:(%d,%s,%s)\n",num1,auteur1,titre1);
    int clef1 = fonctionClef(auteur1);
    printf("'%s' --> %d\n",auteur1,clef1);

    // creation, affichage et liberation de livreH
    LivreH* l0 = creer_livre(num0,titre0,auteur0);
    afficher_livre(l0);

    LivreH* l1 = creer_livre(num1,titre1,auteur1);
    afficher_livre(l1);

    liberer_livre(l0);
    liberer_livre(l1);

    // creation, affichage et liberation d'une bilbioH
    BiblioH * b = creer_biblio(4);
    afficher_biblio(b);
    liberer_biblio(b);

    // free les malloc du main
    free(auteur0);
    free(titre0);
    free(auteur1);
    free(titre1);

    // test fonctionHachage
    for (int i=0;i<n;i++){
        char * auteur = nom_alea(nb_alea(3,9));
        int clef = fonctionClef(auteur);
        int indice = fonctionHachage(clef,m);
        printf("%s->%d->%d\n",auteur,clef,indice);
        free(auteur);
    }

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

    // test charger_n_entrees()
    char *nomFichier = "GdeBiblio.txt";
    printf("\nCreation d'une Biblio en lisant les %d premières lignes de %s\n",n,nomFichier);
    BiblioH* b2 = charger_n_entreesH(nomFichier, 5000, 500);
    afficher_biblio(b2);
    enregistrer_bilbioH(b2,"saveH.txt");

    // test search_by_num()
    LivreH* lnumero0 = search_by_num(b2,0);
    afficher_livre(lnumero0);
    assert(0==lnumero0->num);
    LivreH* lpasla = search_by_num(b2,-1);
    assert(NULL==lpasla);
    afficher_livre(lpasla);
    // test search_by_title()
    LivreH* ltitreconnu = search_by_title(b2,"SOFS");
    assert(strcmp("SOFS",ltitreconnu->titre)==0);
    afficher_livre(ltitreconnu);
    LivreH* ltitreinconnu = search_by_title(b2,"lePetitPoussait");
    assert(NULL==ltitreinconnu);
    afficher_livre(ltitreinconnu);
    // test same_autor()
    BiblioH* b_de_xdrwv  = same_autor(b2,"xdrwv");
    inserer(b_de_xdrwv, 4211,"KEZXDU","xdrwv"); 
    printf("ADD (4211, KEZXDU, xdhwv)\n");
    inserer(b_de_xdrwv, 544,"KEZXDU","xdrwv"); 
    printf("ADD (544, KEZXDU, xdrwv)\n");
    afficher_biblio(b_de_xdrwv);
    
    // test supprimer_ouvrage()
    supprimer_ouvrage(b_de_xdrwv, 4211, "KEZXDU", "xdrwv");
    printf("DEL (4211, KEZXDU, xdhwv)--> 2éme et dernier élément de la liste:\n");
    afficher_biblio(b_de_xdrwv);
    
    supprimer_ouvrage(b_de_xdrwv, 544, "KEZXDU", "xdrwv");
    printf("DEL (544, KEZXDU, xdhwv)--> 1er et 3eme element de la liste:\n");
    afficher_biblio(b_de_xdrwv);
    liberer_biblio(b_de_xdrwv);

    // test fusion_biblio()
    BiblioH * trunks = creer_biblio(8);
    BiblioH * goten = creer_biblio(8);

    for (int i=0;i<10;i++){
        char * auteur = nom_alea(nb_alea(3,9));
        char * titre = titre_alea(nb_alea(5,15));
        inserer(((i%2)?trunks:goten), i, titre, auteur);
        free(titre);
        free(auteur);
    }
    printf("Voici trunks AVANT LA FUSION\n:");
    afficher_biblio(trunks);
    printf("Voici goten AVANT LA FUSION\n:");
    afficher_biblio(goten);
    fusion(trunks, goten);

    printf("Voici trunks APRES LA FUSION (aka GOTENKS)\n:");
    afficher_biblio(trunks);
    printf("\nVoici goten APRES LA FUSIO\n:");
    afficher_biblio(goten);

    liberer_biblio(trunks);
    
    // test add_if_new()
    char tab_titres[5][50] = { "1984", "LeParrain", "Fondation", "Dune", "LeSeigneurDesAnneaux" };
    char tab_auteurs[5][50] = { "George_Orwell", "Mario_Puzo", "Isaac_Asimov", "Frank_Herbert", "J.R.R._Tolkien" };

    BiblioH* testAdd = creer_biblio(10);
    for (int i=0;i<10;i++){
        int indice = i%5;
        printf((i<5)?"ADD NOUVEL OUVRAGE:":"ADD OUVRAGE DEJA CONNU:");
        printf("(%d,%s,%s)\n",indice,tab_titres[indice],tab_auteurs[indice]);
        add_if_new(testAdd, indice, tab_titres[indice], tab_auteurs[indice]);
        afficher_biblio(testAdd);
    }
    liberer_biblio(testAdd);
    
    // test doublons
    BiblioH* multi = recherche_doublons(b2);
    afficher_biblio(multi);
    printf("\nEnregistrement de la Biblio créée dans le ficher doublons.txt\n");
    enregistrer_bilbioH(multi, "doublonsH.txt");
    liberer_biblio(multi);
    liberer_biblio(b2);

    return 0;
}
