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
### Q1.2 Commande `sha256sum`:
- On ajoute au main.c la commande suivante : `system("sha256sum main.c > file.tmp")`
- Ainsi aprés compilation et exécution de `main.c` on obtient le fichier `file.tmp`:
```bash
cat file.tmp
2e7484cb0a9a5220c0a4bd8cc039668f831497b54dfe175b28dd3599fa6a4681  main.c
```
### Q1.3 Fonction `int hashFile(char* source, char* dest)`:
- Fonction qui calcule le hash du fichier source et l'écrit dans le fichier dest.
