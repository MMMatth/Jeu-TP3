#include "../include/son.h"
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>


Mix_Chunk * CreateSound(const char *path){
    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (sound == NULL)
        SDL_ExitWithError("Chargement sonore echouee");
    return sound;
}

void PlaySound(Mix_Chunk *sound, int channel, int loops){
    if (Mix_PlayChannel(channel, sound, loops) == -1)
        SDL_ExitWithError("Lecture sonore echouee");
}

Mix_Music * CreateMusic(const char *path){
    Mix_Music *music = Mix_LoadMUS(path);
    if (music == NULL)
        SDL_ExitWithError("Chargement musique echouee");
    return music;
}

void PlayMusic(Mix_Music *music){
    if (Mix_PlayMusic(music, 0) == -1)
        SDL_ExitWithError("Lecture musique echouee");
}

void StopMusic(Mix_Music *music){
    if Mix_HaltMusic();
    Mix_FreeMusic(music);
}