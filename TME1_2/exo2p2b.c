#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>    // pour srand afin de changer la seed
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

void remplir_indice(int **M, int n, int v){
    // Remplie aleatoirement une matrice carré de taille nxn par des valeurs comprises entre [0, v[
    int indice = 0;
    for (int l=0; l<n ; l++){
        for (int c=0; c<n ; c++){
            M[l][c] = indice++;
        }
    }
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
    printf("\n");
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


int ** produit_matrice_carre(int **m1, int ** m2, int n){
    // retourne le produit d'une matrice carre statique ~O(n^3)
    int **res=alloue_matrice(n);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            res[i][j]=0;
            for (int k=0;k<n;k++){
                res[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
    return res;
}

int main(){
    int n = 2;

    int **m1=alloue_matrice(n);
    remplir_matrice(m1,n,10);
    afficher_matrice(m1,n);

    int **m2=alloue_matrice(n);
    remplir_matrice(m2,n,10);
    afficher_matrice(m2,n);

    int **p=produit_matrice_carre(m1,m2,n);
    afficher_matrice(p,n);

    desalloue_matrice(m1,n);
    desalloue_matrice(m2,n);
    desalloue_matrice(p,n);
    return 0;

}
