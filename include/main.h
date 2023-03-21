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
    inv * inventaire; /**< l'inventaire du joueur*/
    joueur_t * joueur; /**< le joueur*/
    monstreListe_t * ListeM; /**< la liste des monstres*/
};
typedef struct world_s world_t;

/**
 * \brief fonction pour initialiser le monde
 * 
 * \param world : le monde à initialiser
 * \param renderer : le renderer SDL
 */
void InitWorld(world_t * world, SDL_Renderer *renderer);


/**
 * \brief fonction pour appliquer les dégats à un monstre et gerer sa mort
 * 
 * \param ListeM : liste des monstres
 * \param degats : degats de l'arme
 * \param pos_m : position du monstre dans la liste
 */
void attaque(monstreListe_t *ListeM, int degats, int pos_m, sound_t * son);

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

/**
 * \brief fonction pour lancer une attaque à distance
 * 
 * \param j : joueur
 * \param ListeM : liste des monstres
 * \param objet_equipe : objet équipé
 * \param dir : direction de l'attaque
 * \param son : son
 * \return int 
 */
int attaque_dist(joueur_t* j, monstreListe_t* ListeM, obj objet_equipe, char dir, sound_t * son);

/**
 * \brief fonction pour lancer une attaque à distance (auxiliaire)
 * 
 * \param j : joueur
 * \param ListeM : liste des monstres
 * \param dir : direction de l'attaque
 * \param degats : degats de l'arme
 * \param son : son
 * \return int 
 */
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