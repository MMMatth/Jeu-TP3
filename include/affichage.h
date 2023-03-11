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

/**
 * \brief permet de quitter le programme en cas d'erreur
 * 
 * \param message : le message d'erreur
 */
void SDL_ExitWithError(const char *message);

/**
 * \brief permet d'initialiser SDL avec gestion des erreurs
 * 
 */
void SDL_InitWithExit(void);

/**
 * \brief permet de crée des hitbox pour des bouton par exemple
 * 
 * \param event : l'evenement SDL
 * \param top_left : le point en haut a gauche de la hitbox
 * \param top_right : le point en haut a droite de la hitbox
 * \param bottom_left : le point en bas a gauche de la hitbox
 * \param bottom_right : le point en bas a droite de la hitbox
 * \return true : si ca touche
 * \return false : si ca touche pas
 */
bool SDL_RectHitbox(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right);

/**
 * \brief permet de créer une fenêtre et un renderer avec gestion des erreurs
 * 
 * \param width : largeur de la fenêtre
 * \param height : hauteur de la fenêtre
 * \param window : pointeur sur la fenêtre
 * \param renderer : pointeur sur le renderer
 */
void SDL_WindowAndRendererWithExit(int width, int height, SDL_Window **window, SDL_Renderer **renderer);

/**
 * \brief fonction qui permet de gerer plus facilement les images
 * 
 * \param renderer : le rendere SDL
 * \param path : chemin de l'image
 * \return SDL_Texture* 
 */
SDL_Texture *SDL_CreateIMG(SDL_Renderer *renderer, const char *path);

/**
 * \brief permet d'afficher une image plus facilement
 * 
 * \param renderer : le renderer SDL
 * \param texture : la texture de l'image
 * \param x : position x
 * \param y : position y
 * \param w : largeur
 * \param h : hauteur
 */
void SDL_RenderIMG(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);

/**
 * \brief permet de créer une barre de vie pour un personnage 
 *  ! max 100 hp !
 * \param renderer : le renderer SDL
 * \param x : position x
 * \param y : position y
 * \param w : largeur
 * \param h : hauteur
 * \param pv : point de vie
 */
void CreationBarDeVie(SDL_Renderer *renderer, int x, int y, int w, int h, int pv);

/**
 * \brief permet d'afficher les monstres
 * 
 * \param renderer : le renderer SDL
 * \param texture : la texture de l'image ( monstre)
 * \param w : largeur
 * \param h : hauteur
 * \param listeM : la liste de monstre
 * \param joueur : le joueur
 */
void SDL_RenderMonstre(SDL_Renderer *renderer, SDL_Texture *texture, int w, int h, monstreListe_t *listeM, joueur_t *joueur);

// void SDL_RenderINV(SDL_Renderer *renderer, SDL_Texture *c1,SDL_Texture *c2,SDL_Texture *c3, inv * inv);

#endif