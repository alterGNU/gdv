# Mini Projet 1 : Outils de débogue, tableaux et complexité

## Exo 1 : Utilisation d'outils de débogue

### Q1.1
- A la lecture du programme on suppose qu'il doit:
    - Allouer l'espace pour un tableau de 10 entiers.
    - Remplir ce tableau en partant de la fin par la valeur de son indice.(À rebour, commence a 9 puis fini a 0)
    - Libérer l'espace alloué dynamiquement via la commande malloc précédemment.
- Compilation, execution et retour:
    - ```bash
    gcc -o tme1_exo1p1 tme1_exo1p1.c && ./tme1_exo1p1
    Segmentation fault (core dumped) 
    ```
    - On constate que la compilation se passe sans encombre mais qu'a l'exécution le programme plante car il essaye
      d'acceder à une zone mémoire non précédemment alloué: `Segmentation fault`
