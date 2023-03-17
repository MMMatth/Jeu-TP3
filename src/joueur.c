#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Pour la fonction getch()


#include "../include/joueur.h"

joueur_t* CreationJoueur(){
    joueur_t *j = malloc(sizeof(joueur_t));
    j->pos[0] = 0;
    j->pos[1] = 0;
    return j;
}

int coord_x(joueur_t *j){
    return ((j->pos[0] * 69) + 158 ) - 15 ;
}

int coord_y(joueur_t *j){
    return ((j->pos[1] * 69) + 61 ) - 20 ;
}

void deplacement (joueur_t *j, int taille, char touche) {
    if (touche=='z' && j->pos[1] > 0)
        j->pos[1] -= 1;
    if (touche=='q' && j->pos[0] > 0)
        j->pos[0] -= 1;  
    if (touche=='s' && j->pos[1] < taille-1)
        j->pos[1] += 1;
    if (touche=='d' && j->pos[0] < taille-1  )
        j->pos[0] += 1;
}


char* toStringJr(joueur_t* j){
    char* str = malloc(sizeof(char)*100);
    sprintf(str, "Joueur en position (%d, %d)", j->pos[0], j->pos[1]);
    return str;
}