#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Pour la fonction getch()


#include "../include/joueur.h"

void deplacement (joueur_t *j, int taille, char touche) {
    if (touche=='z' || touche=='q' || touche=='s' || touche=='d' || touche=='!'){
        printf("%c\n", touche);
        if (touche=='!') {
            exit(0);
        }
        if (touche=='z' && j->pos[1] > 0) {
            j->pos[1] -= 1;
        }
        if (touche=='q' && j->pos[0] > 0){
            j->pos[0] -= 1;
        }    
        if (touche=='s' && j->pos[1] < taille-1) {
            j->pos[1] += 1;
        }
        if (touche=='d' && j->pos[0] < taille-1  ) {
            j->pos[0] += 1;
        }
    }
}


joueur_t* CreationJoueur(){
    joueur_t *j = malloc(sizeof(joueur_t));
    j->pos[0] = 0;
    j->pos[1] = 0;
    return j;
}

char* toStringJr(joueur_t* j){
    char* str = malloc(sizeof(char)*100);
    sprintf(str, "Joueur en position (%d, %d)", j->pos[0], j->pos[1]);
    return str;
}