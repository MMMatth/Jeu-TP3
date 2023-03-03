#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Pour la fonction getch()


#include "joueur.h"

void deplacement (joueur_t *j, int taille) {
    char c;
    c = getch();
    if (c=='z' || c=='q' || c=='s' || c=='d' || c=='!'){
        printf("%c\n", c);
        //si touche p, on quitte le jeu
        if (c=='!') {
            exit(0);
        }
        if (c=='z' && j->pos[0] > 0) {
            j->pos[0] -= 1;
        }
        if (c=='q' && j->pos[1] > 0){
            j->pos[1] -= 1;
        }    
        if (c=='s' && j->pos[0] < taille-1) {
            j->pos[0] += 1;
        }
        if (c=='d' && j->pos[1] < taille-1) {
            j->pos[1] += 1;
        }
        }
    else{
        printf("touche '%c' non definie\n", c);
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