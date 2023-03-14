#include <stdio.h>  // pr fcts:sprintf
#include <stdlib.h> // pr fcts:system,
#include <assert.h> // pr fcts:assert,
#include "utils.h"  // pr fcts à tester
#define BUFFER 1024

int main(int nbarg, char * argv[]){
    char *f1="main.c";
    char *f2="main256.txt";

    // test is_a_file()
    printf("test utils.is_a_file()");
    assert(is_a_file(f1)==0);
    assert(is_a_file(f2)==1);
    printf(" --> OK.\n");

    // test de hashFile()             // Exo1 Q1.2
    printf("test utils.hashFile()");
    int hf1 = hashFile(f1,f2);
    assert(hf1==0 && is_a_file(f2)==0);// check si exec réussié et creation <dest> réussie
    char cmd1[BUFFER];
    sprintf(cmd1,"rm %s", f2);
    int rm1 = system(cmd1);
    assert(rm1==0 && is_a_file(f2)==1);// check si remove réussié et suppression <dest> réussie
    printf(" --> OK.\n");

    return 0;
}
