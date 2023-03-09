#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour atoi
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "entreeSortieLC.h" // pour fct charger et enregistrer
#define BUFF 256
#define BUFFMAX 1024

    /*
    afficher la bibliothèque
    créer puis inserer en tete un livre
    chercher un livre via son numero 
    chercher un livre via son titre 
    chercher l'ensemble des livres d'un auteur 
    supprimer un ouvrage
    créer puis inserer en queue un livre uniquement s'il n'est pas deja present
    constituer une bibliotheque des doublons
    enregistrer une bibliothèque dans un fichier

    void afficher_biblio(Biblio* b);
    void inserer_en_tete(Biblio* b, int num, char *titre, char *auteur);
    void afficher_biblio(Biblio* b);
    Livre* search_by_num(Biblio* b,int num);
    Livre* search_by_title(Biblio* b,char *title);
    Biblio* same_autor(Biblio* b,char *autor);
    void supprimer_ouvrage(Biblio* b, int num, char *titre, char *auteur);
    void add_if_new(Biblio* b,int num, char *titre, char *auteur);
    Biblio* recherche_doublons(Biblio* b);
    void enregistrer_bilbio(Biblio* b, char *nomfic);
    */

void menu(){
    printf("\n\nVoici vos choix:\n");
    printf("\t- 0 : Quitter le programme\n");
    printf("\t- 1 : Afficher la bibliothèque\n");
    printf("\t- 2 : Créer puis inserer en tete un livre\n");
    printf("\t- 3 : Chercher un livre via son numero \n");
    printf("\t- 4 : Chercher un livre via son titre \n");
    printf("\t- 5 : Créer une bibliotheque contenant tous les ouvrages d'un auteur\n");
    printf("\t- 6 : Supprimer un ouvrage\n");
    printf("\t- 7 : constituer une bibliotheque des doublons(sauvegarde possible)\n");
}

int main(int argc, char *argv[]){
    if (argc<3){
        printf("Manque des arguments:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 1;
    };
    if (argc>3){
        printf("Trop d'argument passé:\nUsage : %s <nom_fichier> <nbr_ligne>\n",argv[0]);
        return 2;
    };

    int n = atoi(argv[2]);   // Conversion deuxieme arg en entier

    printf("\nCreation d'une Biblio en lisant les %d première lignes de %s\n",n,argv[1]);
    char * nomfichier=argv[1];
    Biblio* b = charger_n_entrees(nomfichier, n);
    int rep;
    char input[BUFFMAX];
    do{
        menu();
        fgets(input,BUFF,stdin);
        sscanf(input,"%d",&rep);
        switch(rep){
            case 1 :
                printf("Affichage :\n");
                afficher_biblio(b);
                break;
            case 2 :
                {int num;
                char titre[BUFF];
                char auteur[BUFF];
                printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage a insérer au debut de la bibliotheque:\n");
                fgets(input,BUFF,stdin);
                if (sscanf(input,"%d %s %s",&num,titre,auteur)==3){
                    inserer_en_tete(b,num,titre,auteur);
                    printf("Ajout fait\n");
                }else{
                    printf("Erreur format saisie\n");
                }
                }
                break;
            case 3 :
                {int num;
                printf("Veuillez ecrire le numero du livre recherché:\n");
                fgets(input,BUFF,stdin);
                if (sscanf(input,"%d",&num)==1){
                    printf("Saisie correcte\n");
                    Livre* l = search_by_num(b,num);
                    if (l){
                        printf("Voici le livre recherché:\n\t (%d,%s,%s)\n",l->num,l->titre,l->auteur);
                    }else{
                        printf("Il n'y a pas de livre n°:%d dans la bibliotheque\n",num);
                    }
                }else{
                    printf("Erreur format saisie\n");
                }
                }
                break;
            case 4 :
                {char titre[BUFF];
                printf("Veuillez ecrire le titre du livre recherché:\n");
                fgets(input,BUFF,stdin);
                if (sscanf(input,"%s",titre)==1){
                    printf("Saisie correcte\n");
                    Livre* l = search_by_title(b,titre);
                    if (l){
                        printf("Voici le livre recherché:\n\t (%d,%s,%s)\n",l->num,l->titre,l->auteur);
                    }else{
                        printf("Il n'y a pas de livre nommé '%s' dans la bibliotheque\n",titre);
                    }
                }else{
                    printf("Erreur format saisie\n");
                }
                }
                break;
            case 5 :
                {char auteur[BUFF];
                printf("Veuillez ecrire le nom de l'auteur dont on souhaite récupérer l'ensemble de ses ouvrages:\n");
                fgets(input,BUFF,stdin);
                if (sscanf(input,"%s",auteur)==1){
                    printf("Saisie correcte\n");
                    Biblio* b2 = same_autor(b,auteur);
                    if (b2->L){
                        printf("Voici l'ensemble des ouvrages de `%s`:\n",auteur);
                        afficher_biblio(b2);
                        liberer_Biblio(b2);
                    }else{
                        printf("Aucune oeuvre de `%s` n'est présente dans la bibliotheque\n",auteur);
                    }
                }else{
                    printf("Erreur format saisie\n");
                }
                }
                break;
            case 6 :
                {int num;
                char titre[BUFF];
                char auteur[BUFF];
                printf("Veuillez donner le numero, le titre ainsi que l'auteur de l'ouvrage que vous souhaité supprimer de la bibliothéque:\n");
                fgets(input,BUFF,stdin);
                if (sscanf(input,"%d %s %s",&num,titre,auteur)==3){
                    printf("Saisie correcte\n");
                    supprimer_ouvrage(b, num,titre,auteur);
                }else{
                    printf("Erreur format saisie\n");
                }
                }
                break;
            case 7 :
                {int lignes;
                char nomfichier[BUFF];
                char save[BUFF];
                printf("Veuillez donner le <nom_du_fichier_source> ainsi que le <nombre_de_ligne> à traiter suivi du <nom_fichier> dans lequel vous souhaitez faire la sauvegarde\n");
                fgets(input,BUFF,stdin);
                if (sscanf(input,"%s %d %s",nomfichier,&lignes, save)==3){
                    printf("Saisie correcte\n");
                    printf("Tache:construction de la bibliotheque...");
                    Biblio* b1 = charger_n_entrees(nomfichier, lignes);
                    printf("FIN!\n");
                    printf("Tache:construction de la bibliotheque des doublons...");
                    Biblio* b2 =  recherche_doublons(b1);
                    printf("FIN!\n");
                    printf("Tache:sauvegarde dans `%s` de la bibliotheque suivante:\n",save);
                    afficher_biblio(b2);
                    enregistrer_bilbio(b2, save);
                    printf("SAUVEGARDE TERMINÉE LE FICHIER './%s' A ÉTÉ CRÉÉ!\n",save);
                    liberer_Biblio(b1);
                    liberer_Biblio(b2);
                }else{
                    printf("Erreur format saisie\n");
                }
                }
                break;
        }
    }while(rep!=0);

    liberer_Biblio(b);
    printf("CIAO\n");
    return 0;
}
