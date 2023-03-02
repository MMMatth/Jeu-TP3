#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "../monstre/monstre.h"
#include "../joueur/joueur.h"

int attaque(struct joueur_t* j, struct monstre_t* m);

int ** creationPlateau();

char ** generationListeAff(struct joueur_t* j, struct monstreListe_t* listeM);

void jouer();

#endif