#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // pour srand afin de changer la seed
#define DIM 4        // dimension de la matrice carre.
#define BORNSUP 10  // Borne supérieur de l'intervalle des valeurs possibles.

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

int check_elements_differents(int **M, int n){
    // retourne 0 si tous les éléments de la matice sont différents sinon retourne 1
    // fait toujours le pire des cas, soit une complexité de 0(n^4)
    int res = 0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int val = M[i][j];
            for (int l=0;l<n;l++){
                for (int c=0;c<n;c++){
                    if ((val == M[l][c])&&(i!=l)&&(c!=j)){
                        res += 1;
                    }
                }
            }
        }
    }
    return res;
}

int main(){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.
    int n = DIM;
    int **mat1, **mat2;

    // Matrice ayant une faible probabilité d'avoir des éléments différents
    mat1=alloue_matrice(n);
    remplir_matrice(mat1,n,BORNSUP);
    afficher_matrice(mat1,n);
    int diff1 = check_elements_differents(mat1,n);
    printf((diff1>0) ? "Les elements de la matrice NE sont PAS tous differents\n" : "Les éléments de la matrices SONT tous differents\n");
    desalloue_matrice(mat1,n);

    // Matrice dont tous les éléments sont differents
    mat2=alloue_matrice(n);
    remplir_indice(mat2,n,BORNSUP);
    afficher_matrice(mat2,n);
    int diff2 = check_elements_differents(mat2,n);
    printf((diff2>0) ? "Les elements de la matrice NE sont PAS tous differents\n" : "Les éléments de la matrices SONT tous differents\n");
    desalloue_matrice(mat2,n);
}
