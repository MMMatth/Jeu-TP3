/**
 * \file affichage.h
 * \brief fichier d'entête pour avec des fonction pour l'affichage ( SDL )
 * 
 */


#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL.h>
#include <stdbool.h>
#include "../include/monstre.h"
#include "../include/joueur.h"
#include "../include/inventaire.h"

void SDL_ExitWithError(const char *message);

void SDL_InitWithExit(void);


bool SDL_RectHitbox(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right);

void SDL_WindowAndRendererWithExit(int width, int height, SDL_Window **window, SDL_Renderer **renderer);

SDL_Texture *SDL_CreateIMG(SDL_Renderer *renderer, const char *path);

void SDL_RenderIMG(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);

void CreationBarDeVie(SDL_Renderer *renderer, int x, int y, int w, int h, int pv);

void SDL_RenderMonstre(SDL_Renderer *renderer, SDL_Texture *texture, int w, int h, monstreListe_t *listeM, joueur_t *joueur, inv *inventaire);

void SDL_RenderINV(inv * inv, SDL_Renderer * renderer);

#endif