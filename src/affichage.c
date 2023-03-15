#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../include/affichage.h"
#include "../include/joueur.h"
#include "../include/monstre.h"
#include "../include/inventaire.h"


void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_InitVideoWithExit(void){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }
}

void SDL_WindowAndRendererWithExit(int width, int height, SDL_Window **window, SDL_Renderer **renderer){
    if (SDL_CreateWindowAndRenderer(width, height, 0, window, renderer) != 0){
        SDL_ExitWithError("Creation fenetre et renderer echouee");
    }
}

bool SDL_RectHitbox(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right){   
    if (event.button.x >= top_left
        && event.button.x <= top_right
        && event.button.y >= bottom_left 
        && event.button.y <= bottom_right)
        return true;
    else
        return false;
}

SDL_Texture *SDL_CreateIMG(SDL_Renderer *renderer, const char *path){
    SDL_Surface *surface = SDL_LoadBMP(path); // Chargement de l'image
    if (surface == NULL) {SDL_ExitWithError("Chargement image echouee");} // On gère l'erreur

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface); // Chargement de la texture
    if (texture == NULL) {SDL_ExitWithError("Creation texture echouee");} // On gère l'erreur

    SDL_FreeSurface(surface); // On libère la surface
    return texture;
}

void SDL_RenderIMG(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h){
    SDL_Rect rect = {x, y, w, h}; // Création d'un rectangle
    SDL_RenderCopy(renderer, texture, NULL, &rect); // On affiche la texture
}

void SDL_RenderIMG_Angle(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, double angle) {
    SDL_Rect rect = {x, y, w, h}; // Création d'un rectangle
    SDL_Point center = {w / 2, h / 2}; // Centre de rotation (au milieu de l'image)

    // On affiche la texture en appliquant l'angle de rotation et le centre de rotation
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, &center, SDL_FLIP_NONE);
}

void SDL_RenderMonstre(SDL_Renderer *renderer, SDL_Texture *texture, int w, int h, monstreListe_t *listeM, joueur_t *joueur, inv * inventaire){
    int i_mst;
    for (int i = 0; i < listeM->nbMst; i++){ // on parcour tout les monstres
        i_mst = IndiceMst(listeM, joueur->pos[0], joueur->pos[1]);
        if (i_mst == i){ 
            int mst_pos[] = {
                listeM->tab[i]->pos[0] * 69 + 138 - 15, 
                listeM->tab[i]->pos[1] * 68 + 41 - 20
                }; 
            CreationBarDeVie(renderer, mst_pos[0], mst_pos[1], 30, 5, listeM->tab[i]->pv);
            SDL_RenderIMG(renderer, texture, mst_pos[0], mst_pos[1], w, h);
        }else{
            int mst_pos[] = {
                listeM->tab[i]->pos[0] * 69 + 158 - 15, 
                listeM->tab[i]->pos[1] * 68 + 61 - 20
                }; 
            if ((listeM->tab[i]->pos[0] == joueur->pos[0] || listeM->tab[i]->pos[1] == joueur->pos[1]) && inventaire->objets[0].distance)
                CreationBarDeVie(renderer, mst_pos[0], mst_pos[1], 30, 5, listeM->tab[i]->pv);
            SDL_RenderIMG(renderer, texture, mst_pos[0], mst_pos[1], w, h);
        }
    }
}


void CreationBarDeVie(SDL_Renderer *renderer, int x, int y, int w, int h, int pv){
    SDL_Rect rect = {x - 5, y - 15, w, h}; // Création d'un rectangle
    SDL_SetRenderDrawColor(renderer, 109, 7, 26, 255); // Couleur rouge
    SDL_RenderFillRect(renderer, &rect); // On affiche le rectangle
    SDL_SetRenderDrawColor(renderer, 9, 128, 40, 255); // Couleur verte
    rect.w = (pv * w) / 100; // On change la largeur du rectangle
    SDL_RenderFillRect(renderer, &rect); // On affiche le rectangle
}

void SDL_RenderINV(inv * inv, SDL_Renderer * renderer){
    for (int i = 0; i < 3; i++){
        SDL_Rect rect = {inv->objets[i].x, inv->objets[i].y, 50, 50};
        SDL_RenderCopy(renderer, inv->objets[i].texture, NULL, &rect);
    }
}


void SDL_AfficherFleche(char * direction, SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, float * ticks){
    float angle;
    x = x * 69 + 158 - 15; // on applique la formule pour avoir la position en pixel
    y = y * 68 + 61 - 20;
    switch (*direction){
    case 'n':
        y -= *ticks; // on applique le déplacement en fonction de la direction
        angle = 315.0; // on applique l'angle de rotation en fonction de la direction
        break;
    case 's':
        y += *ticks;
        angle = 135;
        break;
    case 'e':
        x += *ticks;
        angle = 45;
        break;
    case 'o':
        x -= *ticks;
        angle = 225;
        break;
    default:
        break;
    }
    SDL_RenderIMG_Angle(renderer, texture, x , y, w, h, angle); // on affiche la flèche

    if (x <= 120 || x >= 670 || y <= 30 || y >= 570){ 
        *ticks = 0.0; // on remet le déplacement à 0 si la flèche sort du plateau
        *direction = ' '; // on remet la direction à vide
    }
}   




void InitAudioWithError(){
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1){
        SDL_ExitWithError("Initialisation audio echouee");
    }
}

Mix_Music * CreateMusic(const char *path){
    Mix_Music *music = Mix_LoadMUS(path);
    if (music == NULL)
        SDL_ExitWithError("Chargement musique echouee");
    return music;
}

Mix_Chunk * CreateSound(const char *path){
    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (sound == NULL)
        SDL_ExitWithError("Chargement sonore echouee");
    return sound;
}

void PlayMusic(Mix_Music *music){
    if (Mix_PlayMusic(music, 0) == -1)
        SDL_ExitWithError("Lecture musique echouee");
}

void PlaySound(Mix_Chunk *sound, int channel, int loops){
    if (Mix_PlayChannel(channel, sound, loops) == -1)
        SDL_ExitWithError("Lecture sonore echouee");
}

void StopMusic(Mix_Music *music){
    Mix_HaltMusic();
}