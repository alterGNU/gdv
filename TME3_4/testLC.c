#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour atoi
#include <time.h>           // pour time...
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "entreeSortieLC.h" // pour fct charger et enregistrer
#include "utilalea.h"       // pour fct nom_alea et titre_alea
#define BUFF 256

int main(int argc, char *argv[]){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.
    if (argc<3){
        printf("Manque des arguments:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 1;
    };
    if (argc>3){
        printf("Trop d'argument passé:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 2;
    };

    int n = atoi(argv[2]);   // Conversion deuxieme arg en entier

    // Q1.{1,4} 
    // test charger_n_entreesLC();
    printf("\nCreation d'une Biblio en lisant les %d première lignes de %s\n",n,argv[1]);
    char * nomfichier=argv[1];
    Biblio* b = charger_n_entreesLC(nomfichier, n);
    afficher_biblioLC(b);

    // test enregistrer_biblioLC()
    printf("\nEnregistrement de la Biblio créée dans le ficher saveLC.txt\n");
    enregistrer_bilbioLC(b, "saveLC.txt");

    // Q1.6
    // test search_by_numLC()
    printf("\nRecherche par num:\n");
    Livre* l1 = search_by_numLC(b,5);
    printf("Pour num=5: -->  ");
    afficher_livreLC(l1);
    Livre* l2 = search_by_numLC(b,1000);
    printf("Pour num=1000: -->  ");
    afficher_livreLC(l2);
    
    // test search_by_titleLC()
    char *titre1 = "WPQCA";
    printf("\nRecherche par titre:\n");
    Livre* l3 = search_by_titleLC(b,titre1);
    printf("Pour titre='%s': -->  ",titre1);
    afficher_livreLC(l3);
    
    Livre* l4 = search_by_titleLC(b,"ccPetitePerruche");
    printf("Pour titre='ccPetitePerruche': -->  ");
    afficher_livreLC(l4);
    
    // test same_autorLC()
    // par pointeur sur str
    char *name1 = "xdrwv";
    printf("\nConstruction de Biblio par auteur:\n");
    Biblio* b1 = same_autorLC(b,name1);
    printf("\nVoici la biblio de l'auteur '%s':\n",name1);
    afficher_biblioLC(b1);
    // par str n'ayant qu'une occurence
    Biblio* b2 = same_autorLC(b,"yhidd");
    printf("\nVoici la biblio de l'auteur 'yhidd':\n");
    afficher_biblioLC(b2);
    liberer_BiblioLC(b2);
    // par str n'ayant aucune occurence
    Biblio* b3 = same_autorLC(b,"jeanneDo");
    printf("\nVoici la biblio de l'auteur 'jeanneDo':\n");
    afficher_biblioLC(b3);
    liberer_BiblioLC(b3);
    
    // test supprimer_ouvrage() --> utilisation de la biblio b1 de l'auteur xdrwv
    int i[5]={-1,3,544,2261,4211};
    char *t[2]={"ProgMath", "KEZXDU"};
    char *a[2]={"M.Minoux", "xdrwv"};
    printf("Avant:\n");
    afficher_biblioLC(b1);
    supprimer_ouvrageLC(b1,i[0],t[0],a[0]);// echec car rien de bon
    printf("Apres tentative de suppression\n\t- Livre = %d, %s, %s\n",i[0],t[0],a[0]);
    supprimer_ouvrageLC(b1,i[1],t[0],a[0]);// echec que num bon
    printf("\t- Livre = %d, %s, %s\n",i[1],t[0],a[0]);
    supprimer_ouvrageLC(b1,i[0],t[1],a[0]);// echec que titre bon
    printf("\t- Livre = %d, %s, %s\n",i[0],t[1],a[0]);
    supprimer_ouvrageLC(b1,i[0],t[0],a[1]);// echec que auteur bon
    printf("\t- Livre = %d, %s, %s\n",i[0],t[0],a[1]);
    afficher_biblioLC(b1);
    supprimer_ouvrageLC(b1,i[4],t[1],a[1]);// Suppression dernier
    printf("Apres suppression dernier livre:(%d, %s, %s)\n",i[4],t[1],a[1]);
    afficher_biblioLC(b1);
    supprimer_ouvrageLC(b1,i[2],t[1],a[1]);// Suppression millieu
    printf("Apres suppression du livre central:(%d, %s, %s)\n",i[2],t[1],a[1]);
    afficher_biblioLC(b1);
    supprimer_ouvrageLC(b1,i[3],t[1],a[1]);// Suppression debut
    printf("Apres suppression du 1er livre:(%d, %s, %s)\n",i[3],t[1],a[1]);
    afficher_biblioLC(b1);
    supprimer_ouvrageLC(b1,i[1],t[1],a[1]);// Suppression debut
    printf("Apres suppression du seul livre:(%d, %s, %s)\n",i[1],t[1],a[1]);
    afficher_biblioLC(b1);
    supprimer_ouvrageLC(b1,i[0],t[0],a[0]);// echec car rien de bon
    printf("Apres tentative de suppression d'une biblioVide\n");
    afficher_biblioLC(b1);

    liberer_BiblioLC(b1);
    
    //test fusionLC(f1, f2)
    
    // creation aleatoire de livre pour la biblio f1
    Biblio *f1 = creer_biblioLC();
    for (int i=1;i<=4;i++){
        char* titre=titre_alea(4*i);
        char* auteur=nom_alea(2*i);
        inserer_en_teteLC(f1, i,titre , auteur);
        free(titre);
        free(auteur);
    }
    // creation aleatoire de livre pour la biblio f2
    Biblio *f2=creer_biblioLC();
    for (int i=1;i<=2;i++){
        char* titre=titre_alea(4*i);
        char* auteur=nom_alea(2*i);
        inserer_en_teteLC(f2, i,titre , auteur);
        free(titre);
        free(auteur);
    }

    printf("AVANT:\n");
    afficher_biblioLC(f1);
    afficher_biblioLC(f2);

    fusionLC(f1,f2);

    printf("APRES FUSION:\n");
    afficher_biblioLC(f1);
    printf("\n\nici\n\n");
    afficher_biblioLC(f2);

    liberer_BiblioLC(f1);

    // Test de add_if_new
    char tLivre[6][BUFF] = { "Le_Petit_Prince", "Les_Misérables", "Voyage_au_centre_de_la_Terre", "1984", "Le_Comte_de_Monte-Cristo", "Les_Fourmis"};
    char aLivre[6][BUFF] = { "Antoine_de_Saint-Exupéry", "Victor_Hugo", "Jules_Verne", "George_Orwell", "Alexandre_Dumas", "Bernard_Werber"};

    Biblio* testAdd = creer_biblioLC();
    for (int i=0;i<12;i++){
        int indice = i%6;
        add_if_newLC(testAdd, indice, tLivre[indice], aLivre[indice]);
        afficher_biblioLC(testAdd);
    }
    liberer_BiblioLC(testAdd);
    
    // Retourne la liste des doublons (mm titre and auteur)
    Biblio* multi = recherche_doublonsLC(b);
    afficher_biblioLC(multi);
    printf("\nEnregistrement de la Biblio créée dans le ficher doublons.txt\n");
    enregistrer_bilbioLC(multi, "doublonsLC.txt");
    liberer_BiblioLC(multi);
    liberer_BiblioLC(b);

    return 0;
}
