/**
 * \file hud.h
 * \brief fichier pour le hud
 * 
 */

#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief fonction pour initialiser le hud
 * 
 */
void init_hud();

/**
 * \brief fonction pour mettre à jour le hud
 * 
 * \param seconds : les secondes écoulées
 * \param manches : le numéro de la manche
 */
void update_hud(int seconds, int manches);

/**
 * \brief fonction pour afficher le hud
 * 
 * \param renderer : le renderer SDL
 */ 
void render_hud(SDL_Renderer* renderer);

/**
 * \brief fonction pour sauvegarder le score dans un fichier
 * 
 * \param seconds : les secondes écoulées
 */
void save_score(int seconds);

/**
 * \brief fonction pour fermer le hud
 * 
 */
void close_hud();

#endif