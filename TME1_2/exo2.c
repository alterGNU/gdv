#include <stdio.h>
#include <stdlib.h>
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

int somme_carre_difference(int *T, int t){
    // retourne la somme des carrés des différences entre les éléments du tableau 2a2 en
    // compte les doublons : (a,b) et (b,a) 
    // compte les elements avec eux meme : (a,a) (b,b)
    int tot = 0;
    for (int i=0;i<t;i++){
        for (int j=0;j<t;j++){
            int diff=T[i]-T[j];
            tot+=diff*diff;
        }
    }
    return tot/2;
}

int som_car_dif(int *T, int t){
    // première amélioration, ne prend en compte que les éléments de la matrice triangulaire
    // pas de doublons : (a,b) et (b,a) 
    // pas de comparaions des elements avec eux meme : (a,a) (b,b)
    int tot = 0;
    for (int i=0;i<t;i++){
        for (int j=i+1;j<t;j++){
            int diff=T[i]-T[j];
            tot+=diff*diff;
        }
    }
    return tot;
}

int scd(int *T, int t){
    // version plus performante de la fonction somme_carre_diff
    int x=0, y=0;
    for (int i=0;i<t;i++){
        y+=T[i];
        x+=T[i]*T[i];
    }
    return t*x-y*y;
}

int main(){
    srand(time(NULL));
    int taille = 100;
    int * tab;
    alloue_tableau(&tab, taille);
    remplir_tableau(tab,taille,100);
    afficher_tableau(tab,taille);
    printf("V1-La somme des carres des differences vaut:%d\n",somme_carre_difference(tab,taille));
    printf("V2-La somme des carres des differences vaut:%d\n",som_car_dif(tab,taille));
    printf("V3-La somme des carres des differences vaut:%d\n",scd(tab,taille));
    desalloue_tableau(tab);
}
