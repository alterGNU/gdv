# TME3_4 : Mini-Projet 2 : Gestion d'une bibliothèque

## Exo1 : Gestion d'une bibliothèque avec une liste chaînée de struct

### Q1.1 : Creation header
### Q1.2 : Creation fonctions
- Apres avoir créer les fonctions demandées, on les tests via l'execution de ce main.c :
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
- Le test (valgrind) retourne alors:
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
