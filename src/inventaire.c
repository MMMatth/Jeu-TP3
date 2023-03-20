#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "../include/inventaire.h"


inv * CreationInventaire(){
    inv * inventaire = malloc(sizeof(inv));
    for (int i = 0; i < 3; i++){
        inventaire->cases[i].nb = i;
        inventaire->cases[i].x = 43;
        inventaire->cases[i].y = 195 + i * 80;
    }
    return inventaire;
}

void SetItem(inv* inv, char* nom, int degats, int position, bool distance){
    inv->objets[position].nom = malloc(sizeof(char) * strlen(nom));
    strcpy(inv->objets[position].nom, nom);
    inv->objets[position].degats = degats;
    inv->objets[position].position = position;
    inv->objets[position].x = inv->cases[position].x;
    inv->objets[position].y = inv->cases[position].y;
    inv->objets[position].distance = distance;
}

void EchangeItem(inv* inventaire, int pos1, int pos2) {
    obj temp; // objet temporaire pour stocker l'objet à la position pos1
    if (inventaire->objets[pos2].nom != NULL){
        temp = inventaire->objets[pos1];
        inventaire->objets[pos1] = inventaire->objets[pos2];
        inventaire->objets[pos2] = temp;

        inventaire->objets[pos1].x = inventaire->cases[pos1].x;
        inventaire->objets[pos1].y = inventaire->cases[pos1].y;
        inventaire->objets[pos2].x = inventaire->cases[pos2].x;
        inventaire->objets[pos2].y = inventaire->cases[pos2].y;
    }

}

void RefreshPos(int indice, inv * inv, int x, int y){
    inv->objets[indice].x = x;
    inv->objets[indice].y = y;
}

char * ToStringInv(inv * inventaire){
    char * str = malloc(1000 * sizeof(char));
    for (int i = 0; i < 3; i++){
        strcat(str, inventaire->objets[i].nom);
        strcat(str, " ");
        char degats[10];
        sprintf(degats, "%d", inventaire->objets[i].degats);
        strcat(str, degats);
        strcat(str, " ");
        char position[10];
        sprintf(position, "%d", inventaire->objets[i].position);
        strcat(str, position);
        strcat(str, " ");
        char distance[10];
        sprintf(distance, "%s\n", inventaire->objets[i].distance ? "true" : "false");
        strcat(str, distance);
        strcat(str, " ");
    }
    return str;
}