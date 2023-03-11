# TME3_4 : Mini-Projet 2 : Gestion d'une bibliothèque

## Exo1 : Gestion d'une bibliothèque avec une liste chaînée de struct

### Q1.1 : Creation des fichiers
- `biblioLC.c` : contient les fonctions permettant de gérer les listes chainées.
- `biblioLC.h` : header contenant signatures des fonctions et structures propre à la table de hachage.
### Q1.2 : Creation fonctions manipulation des structures
- `Livre* creer_livre(int num, char *titre, char *auteur)` :  ~O(1) : copie les arguments, alloue l'espace necessaire
  puis crée l'instance de Livre correspondant et retourne le pointeur vers cette instance de Livre.
- `void liberer_livre(Livre *l)` : ~O(1) : libére les champs de l'instance de Livre passée en argument.
- `Biblio* creer_biblio()` :   ~O(1) : alloue l'espace necessaire puis crée l'instance de Biblio vide (champ b->L=NULL)
  puis retourne le pointeur vers cette intance.
- `void liberer_Biblio(Biblio* b)` : ~O(n) où n est la taille de la liste chainée : parcoure l'ensemble de la liste
  chainée afin de libérer tous ses éléments, puis libére le pointeur vers b avant de mettre la valeur du pointeur vers
  l'entéte de la liste Chainée a NULL(utilisé par la fonction affichage pour determiner si bilbio vide ou non existante)
- `void inserer_en_tete(Biblio* b, int num, char *titre, char *auteur)` : ~0(1) : insére un Livre en téte de la liste
  chainée.
### Q1.3 : Creation fonctions manipulation de fichiers
- `Biblio* charger_n_entrees(char * nom_fichier, int nb_ligne )` : créer un instance de Biblio en lisant les
  *<nb_ligne>* premières lignes du fichier *<nom_fichier>*
- `void enregistrer_bilbio(Biblio* b, char *nom_fichier)` : Enregistre la bilbio *<b>* dans le fichier *<nom_fichier>*
### Q1.4 : Creation du mainLC.c
- La commande `make LC` permet la compilation de `mainLC.c` et produit le binaire `mainLC`.
- Ainsi la commande `./mainLC GdeBiblio.txt 5000` commence par créer une biblio à partir des 5000 premiéres lignes du
  fichier GdeBiblio.txt puis affiche le panel des commandes disponible à l'utilisateur:
### Q1.5 : Creation du Makefile
- Voici les commandes actuelles du makefile:
    - `make testLC`: compile puis test (y compris les fuites memoires avec `valgrind`) l'ensemble des fonctions de manipulation des Listes Chainées.
    - `make testH`: compile puis test (y compris les fuites memoires avec `valgrind`) l'ensemble des fonctions de manipulation des tables de Hashages.
    - `make LC`: compile le mainLC permettant de lancer le menu pour l'utilisateur : `make LC && ./mainLC GdeBiblio.txt
      5000` crée une instance de Biblio à partir des 5000 premiéres lignes du fichier GdeBiblio.txt puis affiche le menu
      des actions possibles pour l'utilisateur.
    - `make H`: compile le mainH permettant de lancer le menu pour l'utilisateur : `make H && ./mainH GdeBiblio.txt
      5000` crée une instance de Biblio à partir des 5000 premiéres lignes du fichier GdeBiblio.txt puis affiche le menu
      des actions possibles pour l'utilisateur.
    - `make clean`: permet de supprimer les binaires produits par les commandes ci-dessus

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
- La commande `make H && ./mainH GdeBiblio.txt 5000` crée une instance de Biblio à partir des 5000 premiéres lignes du
  fichier GdeBiblio.txt puis affiche le menu suivant:

```bash
...
Voici vos choix:
- 0 : Quitter le programme
- 1 : Afficher la bibliothèque
- 2 : Créer puis inserer en tete un livre
- 3 : Chercher un livre via son numero
- 4 : Chercher un livre via son titre
- 5 : Créer une bibliotheque contenant tous les ouvrages d'un auteur
- 6 : Supprimer un ouvrage
- 7 : constituer une bibliotheque des doublons(sauvegarde possible)
```

## Exo2 : Gestion d'une bibliothèque avec une table de hachage

### Q2.1 : Creation des fichiers:
- `biblioH.c` : contient les fonctions permettant de gérer la table de hachage.
- `biblioH.h` : header contenant signatures des fonctions et structures propre à la table de hachage.

### Q2.2 : Creation de la fonction:
- `int fonctionClef(char *auteur)` : 

### Q2.3 : Creation des fonctions:
- `LivreH* creer_livre(int num, char *titre, char *auteur)` : 
- `void afficher_livre(LivreH *l)` : 
- `void liberer_livre(LivreH *l)` : 
- `BiblioH* creer_biblio(int m)` : 
- `void afficher_biblio(BiblioH* b)` : 
- `void liberer_biblio(BiblioH* b)` : 

### Q2.4 : Creation de la fonction:
- `int fonctionHachage(int cle, int m)`:
    
### Q2.5 : Creation de la fonction:
- ` void inserer(BiblioH* b, int num, char *titre, char *auteur)`:

### Q2.6 : Creation des fonctions:
- `BiblioH* charger_n_entrees(char * nom_fichier, int nb_ligne, int taille_table)` :
- `void enregistrer_bilbio(BiblioH* b, char *nom_fichier)`:
- Le test de ces deux fonctions:
    ```c
    ...
    BiblioH* b2 = charger_n_entrees("GdeBiblio.txt", 10, 10);
    afficher_biblio(b2);
    enregistrer_bilbio(b2,"saveH.txt");
    liberer_biblio(b2);
    ```
- retourne :
```bash
     ...
     _____
    |  T  |
    |-----|
    |   0 | --> (7,SOFS,cnuvqhffbsaq)->Null
    |   1 | --> (9,KMLNOZJKPQPXR,xkitzyxa)->(5,JIVSWMDKQT,xixmvtrr)->Null
    |   2 | --> Null
    |   3 | --> Null
    |   4 | --> (4,FWKHOPKMCOQHNWNKUE,hsqmgbbuqcl)->Null
    |   5 | --> (8,WPQCA,ehchzvf)->(0,WLRBBMQBHCDARZOWK,yhidd)->Null
    |   6 | --> (6,LJPTNSNFWZQFJMA,adrr)->Null
    |   7 | --> Null
    |   8 | --> (3,KEZXDU,xdrwv)->(2,JYBLD,efsarcbynecd)->(1,SCDXRJ,owfrx)->Null
    |   9 | --> Null
    '-----'
    ==8119==
    ==8119== HEAP SUMMARY:
    ==8119==     in use at exit: 0 bytes in 0 blocks
    ==8119==   total heap usage: 37 allocs, 37 frees, 10,772 bytes allocated
    ...
```
- et créé le fichier `saveH.txt` suivant :
```txt
7 SOFS cnuvqhffbsaq
9 KMLNOZJKPQPXR xkitzyxa
5 JIVSWMDKQT xixmvtrr
4 FWKHOPKMCOQHNWNKUE hsqmgbbuqcl
8 WPQCA ehchzvf
0 WLRBBMQBHCDARZOWK yhidd
6 LJPTNSNFWZQFJMA adrr
3 KEZXDU xdrwv
2 JYBLD efsarcbynecd
1 SCDXRJ owfrx
```
- ` LivreH* search_by_num(BiblioH* b,int num)` : cherche et retourne le livre si son numero correspond, sinon NULL.
- ` LivreH* search_by_title(BiblioH* b,char * titre)` : cherche et retourne le livre si son titre correspond, sinon NULL.
- ` LivreH* search_by_autor(BiblioH* b,char * auteur)` : cherche et retourne le livre si son auteur correspond, sinon NULL.
- ` BiblioH* same_autor(BiblioH* b,char *autor)` : retourne la biblioH ayant un tableau de taille 1 contenant tous les
  ouvrages d'un meme auteur.
- ` supprimer_ouvrage(BiblioH* b, int num, char *titre, char *auteur)` : supprime toutes les occurences d'un ouvrage
  dans une BilbioH
- ` fusion(BiblioH* b1, BiblioH* b2)` : fusionne b2 avec b1 puis supprime b2
- ` add_if_new(BiblioH* b, int num, char *titre, char *auteur)` : créer puis ajoute en queue de la liste chainée (dans
  tab) le livre s'il n'est pas deja dans la biblio.
- `BiblioH* recherche_doublons(BiblioH* b)` : comme deux ouvrages sont identiques s'ils ont le meme titre et auteur,
  alors dans une bilbioH ils se trouveront forcement dans la meme liste chainée (car mm clef => mm indice du tableau).
  on cherche donc uniquement dans chaque listes chainées du tableau. La bilbioH retournée elle ne contiendrat qu'une
  case dans son tableau car on ne demande qu'une liste chainée en retour.
