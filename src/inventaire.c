#include "../include/inventaire.h"
#include "../include/affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>


inv * CreeINV(){
    inv * inventaire = malloc(sizeof(inv));
    for (int i = 0; i < 3; i++){
        inventaire->cases[i].nb = i;
        inventaire->cases[i].x = 43;
        inventaire->cases[i].y = 195 + i * 80;

        inventaire->objets[i].nom[0] = '\0';
        inventaire->objets[i].degats = 0;
        inventaire->objets[i].position = i;
        inventaire->objets[i].image[0] = '\0';
        inventaire->objets[i].texture = NULL;
    }
    return inventaire;
}

void SetItem(inv* inv, char* nom, int degats, int position, char* image, SDL_Renderer * renderer){
    strcat(inv->objets[position].nom, nom);
    inv->objets[position].degats = degats;
    inv->objets[position].position = position;
    inv->objets[position].x = inv->cases[position].x;
    inv->objets[position].y = inv->cases[position].y;
    strcat(inv->objets[position].image, image);
    inv->objets[position].texture = SDL_CreateIMG(renderer, image);
}

void SDL_RenderINV(inv * inv, SDL_Renderer * renderer){
    for (int i = 0; i < 3; i++){
        SDL_Rect rect = {inv->objets[i].x, inv->objets[i].y, 50, 50};
        SDL_RenderCopy(renderer, inv->objets[i].texture, NULL, &rect);
    }
}

void EchangeItem(inv* inv, int pos1, int pos2){
    obj temp = inv->objets[pos1];
    inv->objets[pos1] = inv->objets[pos2];
    inv->objets[pos2] = temp;
}

// void RefreshPos(obj * objet, int x, int y){
//     objet->x = x;
//     objet->y = y;
// }

void ToStringInv(inv * inv){
    printf("Objet 1 : %s %d %d %s\n", inv->objets[0].nom, inv->objets[0].degats, inv->objets[0].position, inv->objets[0].image);
    printf("Objet 2 : %s %d %d %s\n", inv->objets[1].nom, inv->objets[1].degats, inv->objets[1].position, inv->objets[1].image);
    printf("Objet 3 : %s %d %d %s\n", inv->objets[2].nom, inv->objets[2].degats, inv->objets[2].position, inv->objets[2].image);
    }

// inv * CreeInventaire(){
//     inv * inv = malloc(sizeof(inv));
//     inv->nb_objets = 3;
//     // On def les coord des trois cases
//     for (int i = 0; i < inv->nb_objets; i++ ){
//         inv->case[i].nb = i;
//         inv->case[i].x = 43;
//         inv->case[i].x = 195 + i * 80;
//         inv->case[i].objet = malloc(sizeof(obj))
//     }
//     return inv;
// } 


// void SetObjet(inv * inv, char* nom, int nc, char * path ){
//     strcat(inv->case[nc].objet->nom, nom);
//     strcat(inv->case[nc].objet->image, path);
//     inv->case[nc].objet->nb_cases = nc;
// }
