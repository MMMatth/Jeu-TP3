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
#include <SDL.h>
#include <SDL_mixer.h>

/**
 * \brief fonction pour appliquer les dégats à un monstre et gerer sa mort
 * 
 * \param ListeM 
 * \param degats 
 * \param pos_m 
 */
void attaque_aux(monstreListe_t *ListeM, int degats, int pos_m);

/**
 * \brief fonction pour lancer une attaque au contact
 * 
 * \param j : joueur
 * \param ListeM : liste des monstres
 * \param pos_m : position du monstre dans la liste
 * \param degats : degats de l'arme
 * \return int 1 si attaque réussie, 0 sinon
 */
int attaque_contact(joueur_t* j, monstreListe_t* ListeM, int pos_m, int degats);

/**
 * \brief fonction pour lancer une attaque à distance
 * 
 * \param j : joueur
 * \param ListeM : liste des monstres
 * \param objet_equipe : objet équipé
 * \param dir : direction de l'attaque
 * \return int 1 si attaque réussie, 0 sinon
 */
int attaque_dist(joueur_t* j, monstreListe_t* ListeM, obj objet_equipe, char dir, Mix_Music * son);

/**
 * \brief fonction pour recuper le jeu sous forme de tableau de char (pas utiliser depuis longtemps)
 * 
 * \param j : joueur
 * \param listeM : liste des monstres
 * \return char** 
 */
char ** generationListeAff(joueur_t* j, monstreListe_t* listeM);

/**
 * \brief procédure pour lancer le jeu
 * 
 * \param argc : argument du main
 * \param argv : argument du main
 */
void jouer(int argc, char *argv[]);

#endif