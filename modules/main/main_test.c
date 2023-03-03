#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "../affichage/affichage.h"
#include "../monstre/monstre.h"
#include "../joueur/joueur.h"

int main(){
    joueur_t* joueur = CreationJoueur();

    monstreListe_t* listeM = creationListeM();
    ajoutMst(listeM, 1, 1);
    ajoutMst(listeM, 2, 2);
    ajoutMst(listeM, 3, 3);

    while(1){
        char ** listeAff = generationListeAff(joueur, listeM);    
        afficher(listeAff, 10);
        deplacement(joueur, 10);
    }
    return 0;
}