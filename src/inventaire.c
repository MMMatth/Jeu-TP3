#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "../include/inventaire.h"


inv * CreationInventaire(){
    inv * inventaire = malloc(sizeof(inv)); // allocation de mémoire pour l'inventaire
    for (int i = 0; i < 3; i++){ // 3 objet max dans l'inventaire
        inventaire->cases[i].nb = i; // on definit le numero de la case
        inventaire->cases[i].x = 43; // on definit la position x de la case
        inventaire->cases[i].y = 195 + i * 80; // on definit la position y de la case
    }
    return inventaire;
}

void SetItem(inv* inv, char* nom, int degats, int position, bool distance){
    inv->objets[position].nom = malloc(sizeof(char) * strlen(nom)); // allocation de mémoire pour le nom de l'objet
    strcpy(inv->objets[position].nom, nom); // on definit le nom de l'objet
    inv->objets[position].degats = degats; // on definit les degats de l'objet
    inv->objets[position].position = position; // on definit la position de l'objet
    inv->objets[position].x = inv->cases[position].x; // on definit la position x de l'objet
    inv->objets[position].y = inv->cases[position].y; // on definit la position y de l'objet
    inv->objets[position].distance = distance; // on definit si l'objet est à distance ou non
}

void EchangeItem(inv* inventaire, int pos1, int pos2) {
    obj temp; // objet temporaire pour stocker l'objet à la position pos1
    if (inventaire->objets[pos2].nom != NULL){ // si l'objet à la position pos2 existe (ca evite de faire des echanges avec des objets qui n'existent pas)
        temp = inventaire->objets[pos1]; // on stocke l'objet à la position pos1 dans l'objet temporaire
        inventaire->objets[pos1] = inventaire->objets[pos2]; // on echange l'objet à la position pos1 avec l'objet à la position pos2
        inventaire->objets[pos2] = temp; // on echange l'objet à la position pos2 avec l'objet temporaire

        // on defini la position des objets par rapport à leur case
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

char * ToStringInv(inv * inventaire)
{
    char * chaine = malloc(1024 * sizeof(char)); /* allocation de mémoire pour la chaîne de caractères */
    strcpy(chaine, "Inventaire : "); /* initialisation de la chaîne de caractères */
    
    for(int i = 0; i < 3; i++) /* parcours des objets de l'inventaire */
    {
        if(inventaire->objets[i].nom != NULL) /* vérification que l'objet existe */
        {
            strcat(chaine, inventaire->objets[i].nom); /* ajout du nom de l'objet à la chaîne de caractères */
            
            if(i < 2 && inventaire->objets[i+1].nom != NULL) /* si l'objet suivant existe, on ajoute une virgule */
            {
                strcat(chaine, ", ");
            }
        }
    }
    return chaine; /* renvoi de la chaîne de caractères */
}