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
