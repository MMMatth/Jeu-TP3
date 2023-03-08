#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "monstre.h"
#include "joueur.h"

int attaque(joueur_t* j, monstre_t* m);

int ** creationPlateau();

char ** generationListeAff(joueur_t* j, monstreListe_t* listeM);

void jouer();

#endif