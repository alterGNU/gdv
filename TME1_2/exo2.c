#include<stdio.h>
#include<stdlib.h>

int* alloue_tableau(int n){
    // Alloue la taille pour un tableau d'entier n qu'elle retourne
    int *t = (int *)malloc(sizeof(int) * n);
    if(t == NULL) {printf("Error: Out of memory\n"); exit(-1); }
    return t;
}

void al(int **T,int n){
    *T = (int *)malloc(sizeof(int) * n);
}

int main(){
    int * tab=alloue_tableau(1);
    int * tab1;
    al(&tab1, 2);
}
