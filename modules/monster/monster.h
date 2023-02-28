#include "player.h"

#ifndef MONSTER_H
#define MONSTER_H

struct monstre_t {
    int x; // position en x du monstre
    int y; // position en y du monstre
    char* nom; // nom du monstre
    int sante; // santé du monstre
    int force; // force du monstre
};

#define TMAP 10 // Taille du tableau bidimensionnel
struct listeMst_t {
    struct monstre_t* listeM[TMAP][TMAP]; // tableau de pointeurs vers les monstres
    int nbMst; // taille effective du tableau
};

void monster_init(struct monstre_t *monster, const char *name, int health, int attack);

void monster_attack(struct monstre_t *monster, struct joueur_t *player);

int monster_is_defeated(struct monstre_t *monster);

#endif /* MONSTER_H */
