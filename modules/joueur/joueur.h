#ifndef PLAYER_H
#define PLAYER_H

struct joueur {
    int pos[2]; /**< position du joueur*/
};
typedef struct joueur joueur_t;

void creationJoueur();

char * toStringJr(struct joueur_t *j);

int deplacement(struct joueur *j);

#endif /* PLAYER_H */
