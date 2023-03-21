/**
 * \file affichage.h
 * \brief fichier d'entête pour avec des fonction pour l'affichage ( SDL )
 * 
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL.h>
#include <SDL_mixer.h>

#include <stdbool.h>
#include "../include/monstre.h"
#include "../include/joueur.h"
#include "../include/inventaire.h"

struct texture_s{
    SDL_Texture * background_menu;
    SDL_Texture * background_game;
    SDL_Texture * background_fin;
    SDL_Texture * joueur;
    SDL_Texture * monstre;
    SDL_Texture * fleche;
    SDL_Texture * epee;
    SDL_Texture * arc;
};
typedef struct texture_s texture_t;

void InitTexture(SDL_Renderer * renderer, texture_t *textures);

/**
 * \brief fonction pour quitter le programme avec une erreur
 * 
 * \param message : message d'erreur
 */
void SDL_ExitWithError(const char *message);

/**
 * \brief fonction pour initialiser SDL
 * 
 */
void initSDL(SDL_Window** window, SDL_Renderer** renderer, int width, int height);

/**
 * \brief fonction qui permet de crée des hitbox
 * 
 * \param event : event de SDL
 * \param top_left : coordonnée du coin haut gauche
 * \param top_right : coordonnée du coin haut droit
 * \param bottom_left : coordonnée du coin bas gauche
 * \param bottom_right : coordonnée du coin bas droit
 * \return true : la souris est dans la hitbox
 * \return false : la souris n'est pas dans la hitbox
 */
bool hitbox(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right);

/**
 * \brief procedure pour crée une fenetre et un renderer
 * 
 * \param width : largeur de la fenetre
 * \param height : hauteur de la fenetre
 * \param window : pointeur sur la fenetre SDL
 * \param renderer : pointeur sur le renderer SDL
 */
void SDL_WindowAndRendererWithExit(int width, int height, SDL_Window **window, SDL_Renderer **renderer);

/**
 * \brief fonction pour crée une image
 * 
 * \param renderer : pointeur sur le renderer SDL
 * \param path : chemin de l'image
 * \return SDL_Texture* 
 */
SDL_Texture *create_img(SDL_Renderer *renderer, const char *path);

/**
 * \brief fonction pour afficher une image
 * 
 * \param renderer : pointeur sur le renderer SDL
 * \param texture : pointeur sur la texture SDL
 * \param x : coordonnée x
 * \param y : coordonnée y
 * \param w : largeur de l'image
 * \param h : hauteur de l'image
 */
void render_img(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);

/**
 * \brief fonction pour afficher une image avec un angle de rotation
 * 
 * \param renderer : pointeur sur le renderer SDL
 * \param texture : pointeur sur la texture SDL
 * \param x : coordonnée x
 * \param y : coordonnée y
 * \param w : largeur de l'image
 * \param h : hauteur de l'image
 * \param angle : angle de rotation
 */
void render_imgangle(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, double angle);

/**
 * \brief fonction pour afficher les fleches
 * 
 * \param renderer : pointeur sur le renderer SDL
 * \param textures : pointeur sur les textures
 * \param joueur : pointeur sur le joueur
 * \param ticks : pointeur sur les ticks
 * \param direction : direction de la fleche
 * \param distance : si l'arme est à distance
 */
void render_fleche(SDL_Renderer *renderer, texture_t * textures, joueur_t * joueur, float * ticks, char * direction, bool distance);

/**
 * \brief procedure pour crée une barre de vie
 * 
 * \param renderer : pointeur sur le renderer SDL
 * \param x : coordonnée x
 * \param y : coordonnée y
 * \param w : largeur de la barre
 * \param h : hauteur de la barre
 * \param pv : point de vie
 */
void bardevie(SDL_Renderer *renderer, int x, int y, int w, int h, int pv);

/**
 * \brief procedure pour afficher l'inventaire
 * 
 * \param inv : pointeur sur l'inventaire
 * \param renderer : pointeur sur le renderer SDL
 */
void render_inv(inv * inv, texture_t * textures, SDL_Renderer * renderer);



/**
 * \brief procedure pour clean les textures et la fenetre
 * 
 * \param window : pointeur sur la fenetre SDL
 * \param renderer : pointeur sur le renderer SDL
 */
void clean(SDL_Window *window, SDL_Renderer * renderer); //, textures_t *textures , world_t * world);



#endif