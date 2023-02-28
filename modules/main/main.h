#include "monster.h"
#include "player.h"


#ifndef AFFICHAGE_H
#define AFFICHAGE_H


/**
 * \brief gère une attaque du
 * joueur sur le monstre. Cette attaque ne peut être lancée que si ces deux participants 
 * sont sur la même case. Elle retournera 1 si le monstre meurt, 0 sinon.
 * 
 * \param j 
 * \param m 
 * \return int 
 */
int attaque(struct joueur_t* j, struct monstre_t* m);


/**
 * \brief crée la carte (si besoin). Un tableau de tableaux d’int de
 * taille [TMAP][TMAP].
 * 
 * \return int** 
 */
int ** creationPlateau();


/**
 * \brief génère à partir de la liste des monstres et de la position du joueur le tableau de 
 * tableaux de char contenant les caractères à afficher. La tableau généré sera de taille
 * [TMAP][TMAP].
 * 
 * \param j 
 * \param listeM 
 * \return char** 
 */
char** generationListeAff(struct joueur_t* j, struct listeMst_t* listeM);

/**
 * \brief lance une partie. 
 * 
 */
void jouer();

#endif