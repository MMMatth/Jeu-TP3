#include <stdio.h>
#include <stdlib.h>

#include "monstre.h"


int main(){
    monstreListe_t* listeM = creationListeM();
    ajoutMst(listeM, 1, 1);
    ajoutMst(listeM, 2, 2);
    ajoutMst(listeM, 3, 3);
    
    printf("--- On ajoute trois monstres --- \n");
    printf("%s", toStringLstMst(listeM));

    printf("--- On enleve le deuxieme monstre --- \n");
    enleverMst(&listeM->tab[1], listeM);
    printf("%s", toStringLstMst(listeM));
    return 0;
}