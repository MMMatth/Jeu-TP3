/**
 * \file main.h
 * \brief fichier d'entête pour le main
 * 
 */

#ifndef MAIN_H
#define MAIN_H

#include "../include/affichage.h"
#include "../include/joueur.h"
#include "../include/monstre.h"


int attaque(joueur_t* j, monstre_t* m, int degats);

/**
 * \brief permet de créer un plateau de jeu
 * 
 * \return int** 
 */

/**
 * \brief permet de créer une liste d'affichage
 * 
 * \param j : pointeur sur le joueur
 * \param listeM : pointeur sur la liste de monstre
 * \return char** 
 */
char ** generationListeAff(joueur_t* j, monstreListe_t* listeM);

/**
 * \brief fonction principale du jeu ou l'affichage SDL est géré
 *  ! ne pas oublier int main(int argc, char *argv[]) car SDL ne fonctionne pas sans
 * \param argc 
 * \param argv 
 */
void jouer(int argc, char *argv[]);

#endif