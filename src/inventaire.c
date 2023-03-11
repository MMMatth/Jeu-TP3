#include "../include/inventaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


inv * CreeINV(){
    inv * inv = malloc(sizeof(inv));
    for (int i = 0; i < 3; i++){
        inv->cases[i].nb = i;
        inv->cases[i].x = 43;
        inv->cases[i].y = 195 + i * 80;

        // inv->objets[i].position = malloc(sizeof(int));
        // inv->objet[i].nom = malloc(sizeof(char) * 20);
        // inv->objet[i].image = malloc(sizeof(char) * 100);
        // inv->objets[i].degats = malloc(sizeof(int));
    }
}

void SetItem(inv* inv, char* nom, int degats, int position, char* image){
    strcat(inv->objets[position].nom, nom);
    inv->objets[position].degats = degats;
    inv->objets[position].position = position;
    strcat(inv->objets[position].image, image);
}

void EchangeItem(inv* inv, int pos1, int pos2){
    obj temp = inv->objets[pos1];
    inv->objets[pos1] = inv->objets[pos2];
    inv->objets[pos2] = temp;
}


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
