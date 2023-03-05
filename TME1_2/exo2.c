#include<stdio.h>
#include<stdlib.h>

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

int main(){
    int * tab;
    alloue_tableau(&tab, 2);
    desalloue_tableau(tab);
}
