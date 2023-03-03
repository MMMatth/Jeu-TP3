#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "../affichage/affichage.h"

#define taille 10

int ** creationPlateau(){
    // on fait un tableau de 2D de taille 10 rempli de 0
    int ** plateau = malloc(taille * sizeof(int *));
    for (int i = 0; i < taille; i++) {
        plateau[i] = malloc(taille * sizeof(int));
    }
    return plateau;
}

char ** generationListeAff( joueur_t* j, monstreListe_t* listeM){
    // on fait un tableau de 2D de taille 10 rempli de 0
    char ** listeAff = malloc(taille * sizeof(char *));
    for (int i = 0; i < taille; i++) {
        listeAff[i] = malloc(taille * sizeof(char));
    }
    // on remplie le tableau de vide
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            listeAff[i][j] = '/';
        }
    }

    // on place le joueur
    listeAff[j->pos[0]][j->pos[1]] = 'J';

    // on place les monstres
    for (int i = 0; i < listeM->nbMst; i++) {
        listeAff[listeM->tab[i].pos[0]][listeM->tab[i].pos[1]] = 'M';
    }

    return listeAff;
}