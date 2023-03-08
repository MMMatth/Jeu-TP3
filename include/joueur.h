/**
 * \file joueur.h
 * \brief fichier d'entête pour le joueur
 * 
 */

#ifndef JOUEUR_H
#define JOUEUR_H

struct joueur {
    int pos[2]; /**< position du joueur*/
};
typedef struct joueur joueur_t;

/**
 * \brief Création d'un joueur
 * 
 * \return joueur_t* pointeur sur le joueur créé
 */
joueur_t* CreationJoueur();

/**
 * \brief Affichage de la position du joueur
 * 
 * \param j pointeur sur le joueur
 * \return char* chaine de caractère contenant la position du joueur
 */
char * toStringJr(joueur_t *j);

/**
 * \brief Déplacement du joueur
 * 
 * \param j pointeur sur le joueur
 */
void deplacement(joueur_t *j, int taille, char touche);

#endif /* JOUEUR_H */
