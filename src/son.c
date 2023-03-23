#include "../include/son.h"
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>




void InitAudioWithError(){ 
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1){ // Initialisation de l'API Mixer
        SDL_ExitWithError("Initialisation audio echouee"); // Si l'initialisation a échoué, on quitte le programme
    }
}

Mix_Chunk * CreateSound(const char *path){
    Mix_Chunk *sound = Mix_LoadWAV(path); // Chargement du son
    if (sound == NULL) // Si le son n'a pas été chargé
        SDL_ExitWithError("Chargement sonore echouee"); // On quitte le programme
    return sound;
}

void PlaySound(Mix_Chunk *sound, int channel, int loops){
    if (Mix_PlayChannel(channel, sound, loops) == -1) // On joue le son sur le canal 1, en boucle
        SDL_ExitWithError("Lecture sonore echouee"); // Si le son n'a pas été joué, on quitte le programme
}

Mix_Music * CreateMusic(const char *path){
    Mix_Music *music = Mix_LoadMUS(path); // Chargement de la musique
    if (music == NULL) // Si la musique n'a pas été chargée
        SDL_ExitWithError("Chargement musique echouee"); // On quitte le programme
    return music;
}

void PlayMusic(Mix_Music *music){ 
    if (Mix_PlayMusic(music, 0) == -1) // On joue la musique indéfiniment
        SDL_ExitWithError("Lecture musique echouee"); // Si la musique n'a pas été jouée, on quitte le programme
}

void StopMusic(Mix_Music *music){
    Mix_HaltMusic(); // On arrête la musique
    Mix_FreeMusic(music); // On libère la musique
}

void CleanAudio(){
    Mix_CloseAudio(); // On ferme l'API Mixer
    Mix_Quit(); // On quitte l'API Mixer
}

void InitSound(sound_t *sound){ 
    sound->arc = CreateSound("assets/son/bowshot.wav"); 
    sound->death = CreateSound("assets/son/death.wav");
    sound->click = CreateSound("assets/son/click.wav");
}

void InitMusic(music_t *music){
    Mix_Init(MIX_INIT_MP3); // Initialisation de l'API Mixer
    InitAudioWithError();  
    music->menu = CreateMusic("assets/son/menu.mp3");
    music->game = CreateMusic("assets/son/game.mp3");
}