#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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
    FILE * sortie;
    sortie = fopen("sortie_vitesse.txt", "w");
    if(sortie==NULL){ // Verifie si l'ouverture s'est bien passée.
        printf("Erreur lors de l'ouverture d'un fichier\n");
        exit(1);
    }


    char * entete="set title \"Comparaison des temps d'execution\" \nset xlabel \"Taille tableau\" \nset ylabel \"Temps d'execution (s)\" \nplot \"sortie_vitesse.txt\" using 1:2 title \"Algo1\" with lines lc rgb \"blue\" lw 1.5 \nset term png\nset output \"01_courbes_vitesse.png\"\nreplot \"sortie_vitesse.txt\" using 1:3 title \"Algo2\" with lines lc rgb \"green\" lw 1.5, \"sortie_vitesse.txt\" using 1:4 title \"Algo3\" with lines lc rgb \"red\" lw 3\n\n# Taille tableau,	Temps1,	Temps2,	Temps3\n";

    fprintf(sortie,"%s",entete);

    for (int taille=1;taille<=10001;taille+=100){
        alloue_tableau(&tab, taille);
        remplir_tableau(tab,taille,MAXVAL);

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
        t3 = ((double)(tps_fin - tps_init))/ CLOCKS_PER_SEC;
        
        desalloue_tableau(tab);

        if((s1 == s2)&&(s2 == s3)){
            fprintf(sortie,"%d,\t%f,\t%f,\t%f\n",taille,t1,t2,t3);
        }else{
            fclose (sortie);
            exit(2);
        }
    }
    fclose (sortie);
    system("gnuplot sortie_vitesse.txt");
    return 0;
}
