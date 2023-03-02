#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int deplacement(struct joueur_t *j) {
    char c;
    c = getch();
    if (c=='z' || c=='q' || c=='s' || c=='d' || c=='!'){
        printf("%c\n", c);
        //si touche p, on quitte le jeu
        if (c=='!') exit(0);
        if (c=='z') j->pos[1] -= 1;
        if (c=='q') j->pos[0] -= 1;
        if (c=='s') j->pos[1] += 1;
        if (c=='d') j->pos[0] += 1;
        printf("%d %d\n", j->pos[0], j->pos[1]);
        }
    else{
        printf("touche '%c' non definie", c);
    return 0;
}}

void CreationJoueur(struct joueur_t *j){
    j->pos[0] = 0;
    j->pos[1] = 0;
}

int main() {
    struct joueur_t j;
    CreationJoueur(&j);
    while (1) {
        deplacement(&j);
    }
    return 0;
}