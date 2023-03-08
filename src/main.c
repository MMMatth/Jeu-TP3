#include <stdio.h>
#include <stdlib.h>

#include "../include/main.h"
#include "../include/affichage.h"

#define taille 10

int attaque(joueur_t* j, monstre_t* m){
    if (j->pos[0] == m->pos[0] && j->pos[1] == m->pos[1]){
        m->pv -= rand() % 10;
        return 1;
    }
    return 0;
}

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


void jouer(){
        joueur_t* joueur = CreationJoueur();

    monstreListe_t* listeM = creationListeM();
    ajoutMst(listeM, 1, 1);
    ajoutMst(listeM, 2, 2);
    ajoutMst(listeM, 3, 3);

    while(1){
        char ** listeAff = generationListeAff(joueur, listeM);    
        afficher(listeAff, 10);
        deplacement(joueur, 10);
        printf("%s\n", toStringJr(joueur));
        printf("%d\n", joueur->pos[0] + joueur->pos[1]);
        printf("%s\n", toStringLstMst(listeM));
        // attaque(joueur, &listeM->tab[joueur->pos[0]+joueur->pos[1]]);

    }
}