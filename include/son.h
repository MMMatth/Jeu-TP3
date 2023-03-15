#ifndef SON_H
#define SON_H
#include <SDL_mixer.h>
#include "../include/affichage.h" // Pour la fonction "Erreur"

/**
 * \brief fonction pour crée un son
 * 
 * \param path : chemin du son (wav)
 * \return Mix_Chunk* : pointeur sur le son
 */
Mix_Chunk * CreateSound(const char *path);

/**
 * \brief fonction pour jouer un son
 * 
 * \param sound : pointeur sur le son
 * \param channel : canal de lecture
 * \param loops : nombre de fois que le son doit être joué
 */
void PlaySound(Mix_Chunk *sound, int channel, int loops);

/**
 * \brief fonction pour crée une musique
 * ! on ne peut pas jouer plusieurs musiques en même temps !
 * \param path : fichier de la musique
 * \return Mix_Music* : pointeur sur la musique
 */
Mix_Music * CreateMusic(const char *path);

/**
 * \brief fonction pour jouer une musique
 * 
 * \param music : pointeur sur la musique
 */
void PlayMusic(Mix_Music *music);

/**
 * \brief fonction pour arrêter une musique
 * 
 * \param music : pointeur sur la musique à arrêter
 */
void StopMusic(Mix_Music *music);

#endif