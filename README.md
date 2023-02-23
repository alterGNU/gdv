# GDV
Gestionnaire De Version

## Notes Exo1 : Prise en main du langage Bash
### Q1.1 Commandes Usuelles
```bash
mkdir projet_scv && cd projet_scv && touch main.c Makefile test.txt
```
- Commande permettant de créer l'arborescence suivante:
```bash
tree
.
├── README.md
└── projet_scv
    ├── Makefile
    ├── main.c
    └── test.txt
```
- Modification de main.c via vim:
```bash
cat main.c
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Hello World!\n");
}
```
- Utilisation de la commande `rm` pour supprimer le fichier `test.txt`:
```bash
rm projet_scv/test.txt && tree
.
├── README.md
└── projet_scv
    ├── Makefile
    └── main.c
```
