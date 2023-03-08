#ifndef CARTE_H
#define CARTE_H

#include <SDL.h>
#include <stdbool.h>


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
bool SDL_HITBOX(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right);

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

#endif /* CARTE_H */