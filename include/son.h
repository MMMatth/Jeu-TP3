#ifndef SON_H
#define SON_H
#include <SDL_mixer.h>
#include "../include/affichage.h" // Pour la fonction "Erreur"

Mix_Music * CreateMusic(const char *path);

Mix_Chunk * CreateSound(const char *path);

void PlayMusic(Mix_Music *music);

void PlaySound(Mix_Chunk *sound, int channel, int loops);

void StopMusic(Mix_Music *music);

#endif