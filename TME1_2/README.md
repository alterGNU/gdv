# Mini Projet 1 : Outils de débogue, tableaux et complexité

## Exo 1 : Utilisation d'outils de débogue
 
### Partie 1 : Pb avec l'indice de boucle

#### Q1.1
- A la lecture du programme on suppose qu'il doit:
    - Allouer l'espace pour un tableau de 10 entiers.
    - Remplir ce tableau en partant de la fin par la valeur de son indice.(À rebour, commence a 9 puis fini a 0)
    - Libérer l'espace alloué dynamiquement via la commande malloc précédemment.
- Compilation, execution et retour:
    ```bash
    gcc -o tme1_exo1p1 tme1_exo1p1.c && ./tme1_exo1p1
    Segmentation fault (core dumped) 
    ```
    - On constate que la compilation se passe sans encombre mais qu'a l'exécution le programme plante car il essaye
      d'acceder à une zone mémoire non précédemment alloué: `Segmentation fault`

#### Q1.2
- Recompilation avec l'option -ggdb puis utilisation de l'outil gdb:

```bash
gcc -ggdb -o tme1_exo1p1 tme1_exo1p1.c && gdb tme1_exo1p1
```
- Une fois dans gdb on introduit le point d'arret à la ligne 13 puis on lance avec la commande run
- Afin de voir ce qu'il se passe, on alterne les commandes `continue` et `print i` pour suivre la variable i
- On constate alors que tout se passe bien jusqu'a ce qu'on atteigne la valeur 0:
    - le pas de boucle suivant applique une décrémentation de 1 a 0 ce qui devrait retourner -1 mais on constate que la
      valeur de i=4294967295, soit la valeur maximale d'un entier non signé.
    - La sortie de boucle ne se fait pas car le condition n'est pas respectée.
    - Cela génére une erreur car nous n'avions alloué que 10 cases au tableau et là il essaye d'accéder à la case
      t[4294967295].

#### Q1.3
- Pour résoudre ce problème il suffit donc d'enlever le mot clé `unsigned`.On constate alors que cela resoud l'erreur.

### Partie 2 : Pb d'allocation mémoire

#### Q1.4
- A la lecture du programme on suppose qu'il doit:
    - Utiliser la fonction `creer_adresse` qui :
        - alloue dynamiquement l'espace necessaire pour la structure adresse
        - affectation des valeurs aux differents attributs de cette structure
        - puis retourne le pointeur vers l'instance de la structure ainsi créée
    - Affiche les valeurs de l'instance d'adresse crée.
- Compilation, execution et retour:
    ```bash
    gcc -o tme1_exo1p2 tme1_exo1p2.c && ./tme1_exo1p2
    Segmentation fault (core dumped) 
    ```
    - Meme constat que précédemment.(cf Q1.1)

#### Q1.5
```bash
...
15	    strcpy(new->rue, r);
(gdb) p new->rue
$1 = 0x0
(gdb) c
Continuing.

Program received signal SIGSEGV, Segmentation fault.
__strcpy_sse2_unaligned () at ../sysdeps/x86_64/multiarch/strcpy-sse2-unaligned.S:668
668	../sysdeps/x86_64/multiarch/strcpy-sse2-unaligned.S: No such file or directory.
...
```
- constate que l'erreur survient à l'execution de la commande `strcpy`, cela pourrait venir du fait que la taille de la
  destination(new->rue) ne soit pas suffisante pour acceuillir la source(r).
- Pour corriger cela on alloue dynamiquement l'espace necessaire de la cible.
    ```bash
    ...
    new->numero = n;
    new->rue= (char*) malloc(sizeof(strlen(r)+1));
    strcpy(new->rue, r);
    ...
    ```
    Puis penser dans le main a tout libérer (ou faire fonciton pour ca)
    ```bash
    ...
    free(maison->rue);
    free(maison);
    ```

### Partie 3 : fuite mémoire

#### Q1.6
- A la lecture du programme on suppose qu'il doit:
    - Initialise une structure tableau contenant un tableau d'entier tableau->tab de taille 100 via la fonction
      `initTableau` qui:
        - alloue dynamiquement l'espace necessaire pour la structure tableau
        - affectations des valeurs des differents attributs de cette structure
        - alloue dynamiquement l'espace necessaire pour l'attribut tableau->tab
        - puis retourne le pointeur vers l'instance de la structure ainsi créée
    - Ajout de 5 éléments via la fonction `ajouterElement` qui:
        - ajoute a la derniére position du tableau l'element a passé en argument
        - incrémente l'attribut tableau->position (correspond au dernier indice du tableau->tab)
    - Affiche le tableau ainsi crée et modifié via la commande `affichageTableau`
- Compilation, execution et retour:
    ```bash
    gcc -o tme1_exo1p3 tme1_exo1p3.c && ./tme1_exo1p3
    t->position = 5
    [ 5 18 99999 -452 4587 ]
    ```
    - Contrairement aux questions précédentes, l'execution ne génére pas d'erreur.

#### Q1.7 
- Au vue du titre de la partie et à la lecture du programme on peut en déduire que le problème de ce programme est la
  fuite de mémoire. En effet, malgrés deux mallocs dans la fonction `initTableau` on ne voit qu'un `free(...)`.

#### Q1.8
- Utilisation de valgrind:
```bash
valgrind --leak-check=yes ./tme1 exo1p3
==12996== Memcheck, a memory error detector
==12996== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==12996== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==12996== Command: ./tme1_exo1p3
==12996== 
==12996== 
==12996== HEAP SUMMARY:
==12996==     in use at exit: 400 bytes in 1 blocks
==12996==   total heap usage: 3 allocs, 2 frees, 1,440 bytes allocated
==12996== 
==12996== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12996==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==12996==    by 0x108793: initTableau (in /home/trollo974/gdv/TME1_2/tme1_exo1p3)
==12996==    by 0x10883D: main (in /home/trollo974/gdv/TME1_2/tme1_exo1p3)
==12996== 
==12996== LEAK SUMMARY:
==12996==    definitely lost: 400 bytes in 1 blocks
==12996==    indirectly lost: 0 bytes in 0 blocks
==12996==      possibly lost: 0 bytes in 0 blocks
==12996==    still reachable: 0 bytes in 0 blocks
==12996==         suppressed: 0 bytes in 0 blocks
==12996== 
==12996== For counts of detected and suppressed errors, rerun with: -v
==12996== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
- On constate que des fuites mémoires sont détéctées, les 400bytes correspondent à l'espace alloué pour lL'attribut
  tableau->tab correspondant à un tableau de 5 entiers

#### Q1.9
- Pour corriger ce probleme on peut créer une fonction qui libére l'espace du tableau d'entier puis de la structure:
```bash
...
void libereTableau(Tableau *t){
	free(t->tab);
	free(t);
}

int main(){
	Tableau* t;
	t = initTableau(100);
	ajouterElement(5,t);
	ajouterElement(18,t);
	ajouterElement(99999,t);
	ajouterElement(-452,t);
	ajouterElement(4587,t);
	affichageTableau(t);	
	libereTableau(t);
}
```
