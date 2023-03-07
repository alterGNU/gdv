#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>    // pour srand afin de changer la seed
#define BORNSUP 100  // Borne supérieur de l'intervalle des valeurs possibles.
#define DIMMAX 200      // Dimension maximale des matrices = DIM x DIM

int** alloue_matrice(int n){
    // Alloue la taille pour une matrice carré de taille nxn qu'elle retourne
    int **m = (int **)malloc(sizeof(int*) * n);
    if(m == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    for(int i=0;i<n;i++){
        m[i] = (int *)malloc(sizeof(int*)*n);
        if(m[i] == NULL) {printf("Error: Out of memory\n"); exit(-1); }
        for(int j=0;j<n;j++){
            m[i][j]=0;       // Initialisation à zero des valeurs
        }
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

void remplir_matrice_tsup(int **M, int n, int v){
    // Remplie aleatoirement une matrice triangulaire superieur de taille nxn par des valeurs comprises entre [0, v[
    for (int i=0; i<n ; i++){
        for (int j=0; j<n ; j++){
            if(i<=j){
                M[i][j] = rand() % v;
            }else{
                M[i][j] = 0;
            }
        }
    }
}

void remplir_matrice_tinf(int **M, int n, int v){
    // Remplie aleatoirement une matrice triangulaire inferieur de taille nxn par des valeurs comprises entre [0, v[
    for (int i=0; i<n ; i++){
        for (int j=0; j<n ; j++){
            if(i>=j){
                M[i][j] = rand() % v;
            }else{
                M[i][j] = 0;
            }
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
    // retourne le produit d'une matrice carre ~O(n^3)
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

int ** prod_mat_tri(int **m1, int ** m2, int n){
    // retourne le produit d'une matrice triangulaire SUP par une INF
    int **res=alloue_matrice(n);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            for (int k=(i>j)?i:j;k<n;k++){
                res[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
    return res;
}

int identique(int **m1, int **m2, int n){
    //retourne 0 si deux matrices sont identiques, 1 si non.
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if(m1[i][j]!=m2[i][j]){return 1;}
        }
    }
    return 0;
}

int main(){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.

    clock_t tps_init, tps_fin;
    double t1, t2;
    int **m1, **m2, **p, **pt;

    FILE * sortie;
    sortie = fopen("produit_matrice.txt", "w");
    if(sortie==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }


    char * entete="set title \"Comparaison des temps d'execution\" \nset xlabel \"Nbr éléments\" \nset ylabel \"Temps d'execution (s)\" \nplot \"produit_matrice.txt\" using 1:2 title \"Algo1\" with lines lc rgb \"blue\" lw 1.5 \nset term png\nset output \"produit_matrice_carre.png\"\nreplot \"produit_matrice.txt\" using 1:3 title \"Algo2\" with lines lc rgb \"red\" lw 1.5\n\n# Nb. element,	Temps1,	Temps2\n";

    fprintf(sortie,"%s",entete);
    for (int n=2;n<DIMMAX;n++){

        m1=alloue_matrice(n);
        remplir_matrice_tsup(m1,n,10);

        m2=alloue_matrice(n);
        remplir_matrice_tinf(m2,n,10);

        tps_init = clock();
        p=produit_matrice_carre(m1,m2,n);
        tps_fin = clock();
        t1 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

        tps_init = clock();
        pt=prod_mat_tri(m1,m2,n);
        tps_fin = clock();
        t2 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

        assert(identique(p,pt,n)==0);
        fprintf(sortie,"%d,\t%f,\t%f\n",n*n,t1,t2);
        desalloue_matrice(m1,n);
        desalloue_matrice(m2,n);
        desalloue_matrice(p,n);
        desalloue_matrice(pt,n);
    }
    fclose (sortie);
    system("gnuplot produit_matrice.txt");
    return 0;

}
