# TME3_4 : Mini-Projet 2 : Gestion d'une bibliothèque

## Exo1 : Gestion d'une bibliothèque avec une liste chaînée de struct

### Q1.1 : Creation header
### Q1.2 : Creation fonctions manipulation des structures
- Apres avoir créer les fonctions demandées, on les tests via l'execution de ce fichier manipStruct.c :
    ```c
    #include <stdio.h>    // pr printf
    #include <stdlib.h>   // pr free, exit
    #include "biblioLC.h" // pour struct Livre et Biblio
    #define BUFF 100      // taille max str
    
    int main(int argc, char *argv[]){
        printf("Créons une bibliothèque:\n");
    
        char *t2="jeanBLOGUIN";
        char *a2="humourNoir";
    
        char *t3="jean-michelFAURE";
        char *a3="gin&co_obs&trick";
    
        Biblio* b1 = creer_biblio();
    
        inserer_en_tete(b1, 1, t2, a2);
        afficher_biblio(b1);
    
        inserer_en_tete(b1, 2, t3, a3);
        afficher_biblio(b1);
    
        liberer_Biblio(b1);
        
        return 0;
    ```
- La cmd `gcc -Wall -o manipStruct manipStruct.c biblioLC.c && valgrind --leak-check=yes ./manipStruct` retourne alors:
    ```bash
    ...
    Créons une bibliothèque:
    Voici les livres des la bibliothque:
    	- n°:1,"jeanBLOGUIN" de *humourNoir*
    Voici les livres des la bibliothque:
    	- n°:2,"jean-michelFAURE" de *gin&co_obs&trick*
    	- n°:1,"jeanBLOGUIN" de *humourNoir*
    ==62930== 
    ==62930== HEAP SUMMARY:
    ==62930==     in use at exit: 0 bytes in 0 blocks
    ==62930==   total heap usage: 4 allocs, 4 frees, 1,096 bytes allocated
    ...
    ```
### Q1.3 : Creation fonctions manipulation de fichiers
- Apres avoir créer les fonctions demandées, on les tests via l'execution de ce fichier manipES.c :
    ```bash
    ...
    char * nomfichier=argv[1];
    Biblio* b = charger_n_entrees(nomfichier, SIZEDICO);
    afficher_biblio(b);
    enregistrer_bilbio(b, "save.txt");
    liberer_Biblio(b);
    ...
    ```
- La cmd `gcc -Wall -o test manipES.c biblioLC.c entreeSortieLC.c && valgrind --leak-check=yes ./test GdeBiblio.txt` retourne alors:
    ```bash
    ...
    Voici les livres des la bibliothque:
    	- n°:9,"KMLNOZJKPQPXR" de *xkitzyxa*
    	- n°:8,"WPQCA" de *ehchzvf*
    	- n°:7,"SOFS" de *cnuvqhffbsaq*
    	- n°:6,"LJPTNSNFWZQFJMA" de *adrr*
    	- n°:5,"JIVSWMDKQT" de *xixmvtrr*
    	- n°:4,"FWKHOPKMCOQHNWNKUE" de *hsqmgbbuqcl*
    	- n°:3,"KEZXDU" de *xdrwv*
    	- n°:2,"JYBLD" de *efsarcbynecd*
    	- n°:1,"SCDXRJ" de *owfrx*
    	- n°:0,"WLRBBMQBHCDARZOWK" de *yhidd*
    ==78794== HEAP SUMMARY:
    ==78794==     in use at exit: 0 bytes in 0 blocks
    ==78794==   total heap usage: 36 allocs, 36 frees, 10,648 bytes allocated
    ==78794==
    ==78794== All heap blocks were freed -- no leaks are possible
    ...

    ```
- On constate qu'a l'issue de l'execution un ficher `save.txt` à bien été créé et contient l'ensemble de la bibliotheque
  au format demandé.

### Q1.4 : Creation du main
### Q1.5 : Creation du Makefile
- Ajout des commandes:
    - `make` : compile le main de la question 1.4.
    - `make clean` : supprime le binaire du main ainsi que le fichier `save.txt` qu'il génére.
### Q1.6 : Ajout de fonctions utiles
- ` void afficher_livre(Livre *l);` :  ~O(1) Affiche le contenue d'une struct Livre
- ` void afficher_biblio(Biblio* b);` : ~O(n) Parcour la liste chainée de taille n et affiche via la fonction afficher_livre chaque
  cellule (livre) qui la compose
- ` Livre* search_by_num(Biblio* b, int num);` :  ~O(n) Recherche (par son attribut num) et retourne le Livre d'une Biblio, retourn NULL
  si pas trouvé.
- `void supprimer_ouvrage(Biblio* b, int num, char *titre, char *auteur);` ~O(n) Supprime en parcourant la liste le
  livre correspondant aux 3arguments de la fonction
- `Biblio *fusion(Biblio* b1, Biblio* b2);` soit b1 de taille n et b2 de taille m => ~O(n) Ajoute b2 à la suite de b1
  puis supprime b1(b1->NULL, le free de la structure doit se faire dans le main via liberer_Biblio()).
- `void add_if_new(Biblio* b,int num, char *titre, char *auteur);` ~O(n) crée puis ajoute en queue un livre uniquement
  s'il n'est pas deja présent dans la bibliothèque.
- `Biblio* recherche_doublons(Biblio* b)` : ~O(n^2) parcours la bibliothèque à la recherche des doublons(meme auteur et
  meme titre), puis les regroupents dans une bibliotheque qu'elle retourne.
### Q1.{7,8} : main interactif
- ` void menu();` :  Affiche l'ensemble des actions possibles la bibliotheque

