#include <stdio.h>          // pour printf, FILE , fopen, fclose
#include <stdlib.h>         // pour atoi
#include "biblioLC.h"       // pour struct Livre et Biblio
#include "entreeSortieLC.h" // pour fct charger et enregistrer
#include "utilalea.h"       // pour fct menu
#define BUFF 256
#define BUFFMAX 1024


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
    Biblio* b = charger_n_entreesLC(nomfichier, n);
    int rep;
    char input[BUFFMAX];
    do{
        menu();
        fgets(input,BUFF,stdin);
        sscanf(input,"%d",&rep);
        switch(rep){
            case 1 :
                printf("Affichage :\n");
                afficher_biblioLC(b);
                break;
            case 2 :
                {int num;
                char titre[BUFF];
                char auteur[BUFF];
                printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage a insérer au debut de la bibliotheque:\n");
                fgets(input,BUFF,stdin);
                if (sscanf(input,"%d %s %s",&num,titre,auteur)==3){
                    inserer_en_teteLC(b,num,titre,auteur);
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
                    Livre* l = search_by_numLC(b,num);
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
                    Livre* l = search_by_titleLC(b,titre);
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
                    Biblio* b2 = same_autorLC(b,auteur);
                    if (b2->L){
                        printf("Voici l'ensemble des ouvrages de `%s`:\n",auteur);
                        afficher_biblioLC(b2);
                        liberer_BiblioLC(b2);
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
                    supprimer_ouvrageLC(b, num,titre,auteur);
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
                    Biblio* b1 = charger_n_entreesLC(nomfichier, lignes);
                    printf("FIN!\n");
                    printf("Tache:construction de la bibliotheque des doublons...");
                    Biblio* b2 =  recherche_doublonsLC(b1);
                    printf("FIN!\n");
                    printf("Tache:sauvegarde dans `%s` de la bibliotheque suivante:\n",save);
                    afficher_biblioLC(b2);
                    enregistrer_bilbioLC(b2, save);
                    printf("SAUVEGARDE TERMINÉE LE FICHIER './%s' A ÉTÉ CRÉÉ!\n",save);
                    liberer_BiblioLC(b1);
                    liberer_BiblioLC(b2);
                }else{
                    printf("Erreur format saisie\n");
                }
                }
                break;
        }
    }while(rep!=0);

    liberer_BiblioLC(b);
    printf("CIAO\n");
    return 0;
}
