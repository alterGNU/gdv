void supprimer_ouvrage(Biblio* b, int num, char *titre, char *auteur){
    char* t = (char *)malloc(sizeof(strlen(titre)*sizeof(char)));
    if(t == NULL) {printf("Error: Out of memory\n"); exit(-2); }
    strcpy(t, titre);
    char* a = (char *)malloc(sizeof(strlen(auteur)*sizeof(char)));
    if(a == NULL) {printf("Error: Out of memory\n"); exit(-2); }
    strcpy(a, auteur);
    Livre* tmp = b->L;
    Livre* ante = tmp;
    while ((tmp!=NULL)&&(tmp->num!=num || strcmp(tmp->titre,t)!=0 || strcmp(tmp->auteur,a)!=0)){
        ante = tmp;
        tmp=tmp->suiv;
    }
    ante->suiv = tmp->suiv;
    free(t);
    free(a);
}
//
    // test supprimer_ouvrage() --> utilisation de la biblio b1 de l'auteur xdrwv
    printf("Avant:\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,-1,"C2lard","deCochon");// echec car rien de bon
    printf("Apres suppression n:NO, t:NO, a:NO\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,0,"KEZXDU","xdrwv");// echec car pas bon num
    printf("Apres suppression n:YES, t:NO, a:NO\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,3,"yo","xdrwv");// echec car pas bon titre
    printf("Apres suppression n:NO, t:YES, a:NO\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,3,"KEZXDU","yu");// echec car pas bon auteur
    printf("Apres suppression n:NO, t:NO, a:YES\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,544,"KEZXDU","xdrwv");// suppression élément de la LC
    printf("Apres suppression n:YES, t:YES, a:YES\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,2261,"KEZXDU","xdrwv");// suppression élément de la LC
    printf("Apres suppression n:YES, t:YES, a:YES\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,4211,"KEZXDU","xdrwv");// suppression du dernier élément de la LC
    printf("Apres suppression n:YES, t:YES, a:YES\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,3,"KEZXDU","xdrwv");// suppression du premier et seul élément de la LC
    printf("Apres suppression n:YES, t:YES, a:YES\n");
    afficher_biblio(b1);
    supprimer_ouvrage(b1,0,"00","000");// echec car biblio vide
    printf("Apres suppression mais biblio vide\n");
    afficher_biblio(b1);

    liberer_Biblio(b1);
