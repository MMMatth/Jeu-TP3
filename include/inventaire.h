#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct{
    char * nom; /* Le nom de l'objet */
    int degats; /* Les degats de l'objet */
    int position; /* La case de l'objet */
    int x;
    int y;
    bool distance;
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

/**
 * \brief fonction pour créer un inventaire
 * 
 * \return inv* : inventaire créé
 */
inv * CreationInventaire();

/**
 * \brief procedure pour initialiser un objet
 * 
 * \param inv : inventaire
 * \param nom : nom de l'objet
 * \param degats : degats de l'objet
 * \param position : position de l'objet
 * \param image : path de l'image de l'objet
 * \param distance : true si l'objet est à distance, false sinon
 */
void SetItem(inv* inv, char* nom, int degats, int position, bool distance);

/**
 * \brief procedure pour échanger deux objets dans l'inventaire
 * 
 * \param inventaire : inventaire
 * \param pos1 : position de l'objet 1
 * \param pos2 : position de l'objet 2
 */
void EchangeItem(inv* inventaire, int pos1, int pos2);

/**
 * \brief procedure pour actualiser la position d'un objet dans l'inventaire
 * 
 * \param indice 
 * \param inv 
 * \param x 
 * \param y 
 */
void RefreshPos(int indice, inv * inv, int x, int y);

/**
 * \brief fonction pour recuperer les informations de l'inventaire sous forme de chaine de caractères
 * 
 * \param inventaire : inventaire
 * \return char*
 */
char * ToStringInv(inv * inventaire);

#endif