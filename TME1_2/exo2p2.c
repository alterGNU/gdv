#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>      // pour srand afin de changer la seed
#define BORNSUP 10000  // Borne supérieur de l'intervalle des valeurs possibles.

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
                    if ((val == M[l][c])&&((i!=l)||(c!=j))){
                        res = 1;
                    }
                }
            }
        }
    }
    return res;
}

int check_elem_diff(int **M, int n){
    // retourne 0 si tous les éléments de la matice sont différents sinon retourne 1
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int val = M[i][j];
            for (int l=0;l<n;l++){
                for (int c=0;c<n;c++){
                    if ((val == M[l][c])&&((i!=l)||c!=j)){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int ced(int **M, int n){
    // retourne 0 si tous les éléments de la matice sont différents sinon retourne 1
    // connaissant le nombre maximal distinct de l'intervalle des valeurs, utilise une
    // matrice d'une dimension=V qu'il remplie en ne parcourant qu'une fois la matrice.
    if (BORNSUP < n*n){return 1;} // cas trivial où il n'est pas possible d'avoir des elements distincts.
    int v = BORNSUP;
    int *grille=(int*)malloc(sizeof(int)*v);
    if(grille == NULL) {printf("Error: Out of memory\n"); exit(-1); }

    for (int i=0;i<v;i++){ grille[i]=-1; } // met l'ensemble des éléments de la grille à -1

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int ind = M[i][j] ;
            if (grille[ind]>0){
                free(grille);
                return 1;
            }
            grille[ind] = ind ;
        }
    }
    free(grille);
    return 0;
}

int main(){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.

    clock_t tps_init, tps_fin;
    int diff1, diff2, diff3;
    double t1, t2, t3;

    FILE * sortie;
    sortie = fopen("matrice_elem_unique.txt", "w");
    if(sortie==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }


    char * entete="set title \"Comparaison des temps d'execution\" \nset xlabel \"Nbr éléments\" \nset ylabel \"Temps d'execution (s)\" \nplot \"matrice_elem_unique.txt\" using 1:2 title \"Algo2\" with lines lc rgb \"blue\" lw 1.5 \nset term png\nset output \"vitesse_elem_uniq.png\"\nreplot \"matrice_elem_unique.txt\" using 1:3 title \"Algo3\" with lines lc rgb \"red\" lw 1.5\n\n# Nb. element,	Temps1,	Temps2\n";

    fprintf(sortie,"%s",entete);

    for (int n = 1;n<=110;n++){
        int **mat;
        mat=alloue_matrice(n);
        remplir_matrice(mat,n,BORNSUP);

        tps_init = clock();
        diff2 = check_elem_diff(mat,n);
        tps_fin = clock();
        t2 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

        tps_init = clock();
        diff3 = ced(mat,n);
        tps_fin = clock();
        t3 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

        desalloue_matrice(mat,n);

        if(diff2 == diff3){
            fprintf(sortie,"%d,\t%f,\t%f\n",n*n,t2,t3);
        }else{
            printf("ERREUR SUR LES FONCTIONS DE VERIFICATION D'UNICITE DES ELEMENTS\n");
            exit(2);
        }
    }
    fclose (sortie);
    system("gnuplot matrice_elem_unique.txt");
    return 0;

}
