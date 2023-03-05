#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int* alloue_tab(int n){
    // Alloue la taille pour un tableau d'entier n qu'elle retourne
    int *t = (int *)malloc(sizeof(int) * n);
    if(t == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    return t;
}

void alloue_tableau(int **T,int n){
    // Alloua la taille pour un tableau d'entier T de taille n.
    *T = (int *)malloc(sizeof(int) * n);
    if(T == NULL) {printf("Error: Out of memory\n"); exit(-1); }
}

void desalloue_tableau(int *T){
    // Libére l'espace alloué pour un tableau d'entier T
    free(T);
}

void remplir_tableau(int *T, int t, int n){
    // Remplie le tableau T de taille t par des valeurs entières comprise entre [0,n[
    for (int i=0; i<t ; i++){
        T[i] = rand() % n;
    }
}

void afficher_tableau(int *T, int t){
    // Affiche le contenu du tableau T de taille t
    printf("tableau=[");
    for (int i=0; i<t ; i++){
        printf("%d",T[i]);
        if(i+1!=t){printf(",");}
    }
    printf("]\n");
}
int main(){
    srand(time(NULL));
    int taille = 10;
    int * tab;
    alloue_tableau(&tab, taille);
    remplir_tableau(tab,taille,5);
    afficher_tableau(tab,taille);
    desalloue_tableau(tab);
}
