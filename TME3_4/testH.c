#include <stdio.h>         // pour printf, FILE , fopen, fclose
#include <stdlib.h>        // pour atoi
#include <time.h>          // pour time...
#include <assert.h>        // pour assert
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

    // free les malloc du main
    free(auteur0);
    free(titre0);
    free(auteur1);
    free(titre1);
    
    //if (argc<3){
    //    printf("Manque des arguments:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
    //    return 1;
    //};
    //if (argc>3){
    //    printf("Trop d'argument passé:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
    //    return 2;
    //};

    //int n = atoi(argv[2]);   // Conversion deuxieme arg en entier

    //// Q1.{1,4} 
    //// test charger_n_entrees();
    //printf("\nCreation d'une Biblio en lisant les %d première lignes de %s\n",n,argv[1]);
    //char * nomfichier=argv[1];
    //Biblio* b = charger_n_entrees(nomfichier, n);
    //afficher_biblio(b);

    //// test enregistrer_biblio()
    //printf("\nEnregistrement de la Biblio créée dans le ficher save.txt\n");
    //enregistrer_bilbio(b, "save.txt");

    //// Q1.6
    //// test search_by_num()
    //printf("\nRecherche par num:\n");
    //Livre* l1 = search_by_num(b,5);
    //printf("Pour num=5: -->  ");
    //afficher_livre(l1);
    //Livre* l2 = search_by_num(b,1000);
    //printf("Pour num=1000: -->  ");
    //afficher_livre(l2);
    //
    //// test search_by_title()
    //char *titre1 = "WPQCA";
    //printf("\nRecherche par titre:\n");
    //Livre* l3 = search_by_title(b,titre1);
    //printf("Pour titre='%s': -->  ",titre1);
    //afficher_livre(l3);
    //
    //Livre* l4 = search_by_title(b,"ccPetitePerruche");
    //printf("Pour titre='ccPetitePerruche': -->  ");
    //afficher_livre(l4);
    //
    //// test same_autor()
    //// par pointeur sur str
    //char *name1 = "xdrwv";
    //printf("\nConstruction de Biblio par auteur:\n");
    //Biblio* b1 = same_autor(b,name1);
    //printf("\nVoici la biblio de l'auteur '%s':\n",name1);
    //afficher_biblio(b1);
    //// par str n'ayant qu'une occurence
    //Biblio* b2 = same_autor(b,"yhidd");
    //printf("\nVoici la biblio de l'auteur 'yhidd':\n");
    //afficher_biblio(b2);
    //liberer_Biblio(b2);
    //// par str n'ayant aucune occurence
    //Biblio* b3 = same_autor(b,"jeanneDo");
    //printf("\nVoici la biblio de l'auteur 'jeanneDo':\n");
    //afficher_biblio(b3);
    //liberer_Biblio(b3);
    //
    //// test supprimer_ouvrage() --> utilisation de la biblio b1 de l'auteur xdrwv
    //int i[5]={-1,3,544,2261,4211};
    //char *t[2]={"ProgMath", "KEZXDU"};
    //char *a[2]={"M.Minoux", "xdrwv"};
    //printf("Avant:\n");
    //afficher_biblio(b1);
    //supprimer_ouvrage(b1,i[0],t[0],a[0]);// echec car rien de bon
    //printf("Apres tentative de suppression\n\t- Livre = %d, %s, %s\n",i[0],t[0],a[0]);
    //supprimer_ouvrage(b1,i[1],t[0],a[0]);// echec que num bon
    //printf("\t- Livre = %d, %s, %s\n",i[1],t[0],a[0]);
    //supprimer_ouvrage(b1,i[0],t[1],a[0]);// echec que titre bon
    //printf("\t- Livre = %d, %s, %s\n",i[0],t[1],a[0]);
    //supprimer_ouvrage(b1,i[0],t[0],a[1]);// echec que auteur bon
    //printf("\t- Livre = %d, %s, %s\n",i[0],t[0],a[1]);
    //afficher_biblio(b1);
    //supprimer_ouvrage(b1,i[4],t[1],a[1]);// Suppression dernier
    //printf("Apres suppression dernier livre:(%d, %s, %s)\n",i[4],t[1],a[1]);
    //afficher_biblio(b1);
    //supprimer_ouvrage(b1,i[2],t[1],a[1]);// Suppression millieu
    //printf("Apres suppression du livre central:(%d, %s, %s)\n",i[2],t[1],a[1]);
    //afficher_biblio(b1);
    //supprimer_ouvrage(b1,i[3],t[1],a[1]);// Suppression debut
    //printf("Apres suppression du 1er livre:(%d, %s, %s)\n",i[3],t[1],a[1]);
    //afficher_biblio(b1);
    //supprimer_ouvrage(b1,i[1],t[1],a[1]);// Suppression debut
    //printf("Apres suppression du seul livre:(%d, %s, %s)\n",i[1],t[1],a[1]);
    //afficher_biblio(b1);
    //supprimer_ouvrage(b1,i[0],t[0],a[0]);// echec car rien de bon
    //printf("Apres tentative de suppression d'une biblioVide\n");
    //afficher_biblio(b1);

    //liberer_Biblio(b1);
    //
    ////test fusion(f1, f2)
    //
    //// creation aleatoire de livre pour la biblio f1
    //Biblio *f1 = creer_biblio();
    //for (int i=1;i<=4;i++){
    //    char* titre=titre_alea(4*i);
    //    char* auteur=nom_alea(2*i);
    //    inserer_en_tete(f1, i,titre , auteur);
    //    free(titre);
    //    free(auteur);
    //}
    //// creation aleatoire de livre pour la biblio f2
    //Biblio *f2=creer_biblio();
    //for (int i=1;i<=2;i++){
    //    char* titre=titre_alea(4*i);
    //    char* auteur=nom_alea(2*i);
    //    inserer_en_tete(f2, i,titre , auteur);
    //    free(titre);
    //    free(auteur);
    //}

    //printf("AVANT:\n");
    //afficher_biblio(f1);
    //afficher_biblio(f2);

    //fusion(f1,f2);
    //printf("APRES FUSION:\n");
    //afficher_biblio(f1);
    //afficher_biblio(f2);

    //liberer_Biblio(f1);
    //liberer_Biblio(f2);

    //// Test de add_if_new
    //char *  tLivre[6] = { "Le_Petit_Prince", "Les_Misérables", "Voyage_au_centre_de_la_Terre", "1984", "Le_Comte_de_Monte-Cristo", "Les_Fourmis"};
    //char *  aLivre[6] = { "Antoine_de_Saint-Exupéry", "Victor_Hugo", "Jules_Verne", "George_Orwell", "Alexandre_Dumas", "Bernard_Werber"};

    //Biblio* testAdd = creer_biblio();
    //for (int i=0;i<12;i++){
    //    int indice = i%6;
    //    add_if_new(testAdd, indice, tLivre[indice], aLivre[indice]);
    //    afficher_biblio(testAdd);
    //}
    //liberer_Biblio(testAdd);
    //
    //// Retourne la liste des doublons (mm titre and auteur)
    //Biblio* multi = recherche_doublons(b);
    //afficher_biblio(multi);
    //printf("\nEnregistrement de la Biblio créée dans le ficher doublons.txt\n");
    //enregistrer_bilbio(multi, "doublons.txt");
    //liberer_Biblio(multi);
    //liberer_Biblio(b);

    return 0;
}
