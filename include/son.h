#ifndef SON_H
#define SON_H
#include <SDL_mixer.h>
#include "../include/affichage.h" // Pour la fonction "Erreur"


struct sound_s{
    Mix_Chunk  * arc;
    Mix_Chunk  * death;
    Mix_Chunk  * click;
};
typedef struct sound_s sound_t;

struct music_s{
    Mix_Music * menu;
    Mix_Music * game;
};
typedef struct music_s music_t;


/**
 * \brief fonction pour initialiser l'audio
 * 
 */
void InitAudioWithError();


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

/**
 * \brief fonction pour libérer la mémoire allouée pour un son
 * 
 */
void CleanAudio();

/**
 * \brief fonction pour initialiser les sons
 * 
 * \param sound : pointeur sur la structure sound_t
 */
void InitSound(sound_t *sound);

/**
 * \brief fonction pour initialiser les musiques
 * 
 * \param music : pointeur sur la structure music_t
 */
void InitMusic(music_t *music);

#endif