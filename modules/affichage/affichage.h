
#ifndef CARTE_H
#define CARTE_H
/**
 * \file carte.h
 * \brief Définitions pour le module affichage.
 */

#define TAILLE_CARTE 10

#include "../monstre/monstre.h"

/**
 * \brief Affiche la carte avec les monstres et le joueur.
 *
 * Cette fonction affiche la carte en utilisant des symboles pour représenter les monstres
 * et le joueur. Elle prend en entrée la carte sous forme d'un tableau de caractères,
 * ainsi que la position du joueur. La fonction utilise également la liste des monstres
 * pour placer les symboles correspondants sur la carte.
 *
 * \param carte Le tableau représentant la carte.
 * \param taille La taille de la carte.
 * \param joueur_pos La position du joueur sous forme de tableau de deux entiers (x,y).
 * \param listeM La liste des monstres.
 */
void afficher(char carte[TAILLE_CARTE][TAILLE_CARTE], int taille, int joueur_pos[2], struct listeMst_t* listeM);

#endif /* CARTE_H */