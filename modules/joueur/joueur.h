#ifndef PLAYER_H
#define PLAYER_H

struct joueur {
    int pos[2]; /**< position du joueur*/
};
typedef struct joueur joueur_t;

void creationJoueur();

char * toStringJr(joueur_t *j);

int deplacement(joueur_t *j);

#endif /* PLAYER_H */
