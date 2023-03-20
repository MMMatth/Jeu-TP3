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
#include "../include/son.h"
#include "../include/inventaire.h"
#include "../include/son.h"
#include "../include/hud.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>



struct world_s{
    inv * inventaire;
    joueur_t * joueur;
    monstreListe_t * ListeM;
};
typedef struct world_s world_t;

void InitWorld(world_t * world, SDL_Renderer *renderer);


/**
 * \brief fonction pour appliquer les dégats à un monstre et gerer sa mort
 * 
 * \param ListeM 
 * \param degats 
 * \param pos_m 
 */
void attaque_aux(monstreListe_t *ListeM, int degats, int pos_m, sound_t * son);

/**
 * \brief fonction pour lancer une attaque au contact
 * 
 * \param j : joueur
 * \param ListeM : liste des monstres
 * \param pos_m : position du monstre dans la liste
 * \param degats : degats de l'arme
 * \return int 1 si attaque réussie, 0 sinon
 */
int attaque_contact(joueur_t* j, monstreListe_t* ListeM, int pos_m, int degats, sound_t * son);


int attaque_dist(joueur_t* j, monstreListe_t* ListeM, obj objet_equipe, char dir, sound_t * son);

int attaque_dist_aux(joueur_t* j, monstreListe_t* ListeM, char dir, int degats, sound_t * son);


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