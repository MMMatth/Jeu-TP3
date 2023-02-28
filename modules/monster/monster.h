#ifndef MONSTER_H
#define MONSTER_H

struct Monster {
    char name[50];
    int health;
    int attack;
};

void monster_init(struct Monster *monster, const char *name, int health, int attack);

void monster_attack(struct Monster *monster, struct joueur_t *player);

int monster_is_defeated(struct Monster *monster);

#endif /* MONSTER_H */
