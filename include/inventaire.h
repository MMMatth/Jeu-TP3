#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>



typedef struct{
    char nom[20]; /* Le nom de l'objet */
    int degats; /* Les degats de l'objet */
    int position; /* La case de l'objet */
    int x;
    int y;
    char image[100]; /* L'image de l'objet */
    SDL_Texture * texture;
} obj;

typedef struct {
    int nb;
    int x;
    int y;
} box;

typedef struct {
    obj objets[3];
    box cases[3];
} inv;

inv * CreeINV();

void SetItem(inv* inv, char* nom, int degats, int position, char* image, SDL_Renderer * renderer);

void ToStringInv(inv * inv);

void EchangeItem(inv* inventaire, int pos1, int pos2);

void SDL_RenderINV(inv * inv, SDL_Renderer * renderer);

void RefreshPos(obj * objet, int x, int y);

#endif