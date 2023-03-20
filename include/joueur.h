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
 * \brief fonction pour créer un joueur
 * 
 * \return joueur_t* : joueur créé
 */
joueur_t* CreationJoueur();

/**
 * \brief fonction qui permet de donner la position x du joueur
 * 
 * \param j : le joueur
 * \return int 
 */
int coord_x(joueur_t *j);

/**
 * \brief fonction qui permet de donner la position y du joueur
 * 
 * \param j : le joueur
 * \return int 
 */
int coord_y(joueur_t *j);

/**
 * \brief fonction pour appliquer un déplacement au joueur
 * 
 * \param j : joueur
 * \param taille : taille de la map
 * \param touche : touche recupérée par SDL
 */
void deplacement(joueur_t *j, int taille, char touche);

/**
 * \brief fonction pour recuper le joueur sous forme de chaine de caractère
 * 
 * \param j : joueur
 * \return char* 
 */
char * toStringJr(joueur_t *j);


#endif /* JOUEUR_H */
