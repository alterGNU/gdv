#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // pour srand afin de changer la seed
#define DIM 6        // dimension de la matrice carre.
#define BORNSUP 100  // Borne supérieur de l'intervalle des valeurs possibles.

int** alloue_matrice(int n){
    // Alloue la taille pour une matrice carré de taille nxn qu'elle retourne
    int **m = (int **)malloc(sizeof(int*) * n);
    if(m == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    for(int i=0;i<n;i++){
        m[i] = (int *)malloc(sizeof(int*)*n);
        if(m[i] == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    }
    return m;
}

void desalloue_matrice(int **M, int n){
    // Libére l'espace alloué pour pour une matrice carré.
    for (int i=0;i<n;i++){
        free(M[i]);
    }
    free(M);
}

void remplir_matrice(int **M, int n, int v){
    // Remplie aleatoirement une matrice carré de taille nxn par des valeurs comprises entre [0, v[
    for (int l=0; l<n ; l++){
        for (int c=0; c<n ; c++){
            M[l][c] = rand() % v;
        }
    }
}

void afficher_matrice(int **M, int n){
    // Affiche le contenu d'une matrice carré de taille nxn.
    for (int l=0; l<n ; l++){
        printf("[");
        for (int c=0; c<n ; c++){
            if(c+1!=n){
                printf("%3d,",M[l][c]);
            }else{
                printf("%3d]\n",M[l][c]);
            }
        }
    }
}

int main(){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.
    int n = DIM;
    int **mat;
    mat=alloue_matrice(n);
    remplir_matrice(mat,n,BORNSUP);
    afficher_matrice(mat,n);
    desalloue_matrice(mat,n);
}
