/**
 * \file player.h
 * \brief fichier d'en-tête du module joueur
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

struct joueur {
    int pos[2]; /**< position du joueur*/
};
typedef struct joueur joueur_t;

struct joueur_t creationJoueur();

char * toStringJr(struct joueur_t *j);

int deplacement(struct joueur *j);

#endif /* PLAYER_H */
