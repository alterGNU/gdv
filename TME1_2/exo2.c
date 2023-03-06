#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#define MAXVAL 100

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

long somme_carre_difference(int *T, int t){
    // retourne la somme des carrés des différences entre les éléments du tableau 2a2 en
    // compte les doublons : (a,b) et (b,a) 
    // compte les elements avec eux meme : (a,a) (b,b)
    long tot = 0;
    for (int i=0;i<t;i++){
        for (int j=0;j<t;j++){
            long diff=T[i]-T[j];
            tot+=diff*diff;
        }
    }
    return tot/2;
}

long som_car_dif(int *T, int t){
    // première amélioration, ne prend en compte que les éléments de la matrice triangulaire
    // pas de doublons : (a,b) et (b,a) 
    // pas de comparaions des elements avec eux meme : (a,a) (b,b)
    long tot = 0;
    for (int i=0;i<t;i++){
        for (int j=i+1;j<t;j++){
            long diff=T[i]-T[j];
            tot+=diff*diff;
        }
    }
    return tot;
}

long scd(int *T, int t){
    // version plus performante de la fonction somme_carre_diff
    long x=0, y=0;
    for (int i=0;i<t;i++){
        y+=T[i];
        x+=T[i]*T[i];
    }
    return t*x-y*y;
}

int main(){
    srand(time(NULL)); // change la seed pour faire varier la génération de nombre aléatoire.
    clock_t tps_init, tps_fin;
    long s1, s2, s3;
    double t1, t2, t3;
    int * tab;
    printf("Les valeurs du tableau sont comprises entre [0, %d[.\n",MAXVAL);
        printf("[Taille tableau|Valeur trouvée|  Temps1  |  Temps2  |  Temps 3  ]\n");
    for (int i=0;i<5;i++){
        int taille = pow(10,i);
        alloue_tableau(&tab, taille);
        remplir_tableau(tab,taille,MAXVAL);
        //afficher_tableau(tab,taille); // Pas d'affichage car trop long

        tps_init = clock();
        s1 = somme_carre_difference(tab,taille);
        tps_fin = clock();
        t1 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

        tps_init = clock();
        s2 = som_car_dif(tab,taille) ;
        tps_fin = clock();
        t2 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

        tps_init = clock();
        s3 = scd(tab, taille);
        tps_fin = clock();
        t2 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;

        assert((s1 == s2)&&(s2 == s3));
        printf("[%13d | %12ld |%10f|%10f|%10f ]\n",taille,s1,t1,t2,t3);
        desalloue_tableau(tab);
    }
}
