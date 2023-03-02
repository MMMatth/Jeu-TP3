#ifndef MONSTRE_H
#define MONSTRE_H


struct monstre {
    int pv; /**< Les points de vie du monstre. */
    int pos[2]; /**< La position du monstre ([0] = x et [1] = y). */
};
typedef struct monstre monstre_t;

struct monstreListe {
    struct monstre_t* tab; /**< Le tableau de monstres. */
    int taille; /**< La taille du tableau. */
    int nb; /**< Le nombre de monstres dans la liste. */
};
typedef struct monstreListe monstreListe_t; ;

struct monstreListe_t* creationListeM();

int ajoutMst(struct monstreListe_t* listeM, int j_pos0, int j_pos1);

void enleverMst(struct monstre_t* m, struct monstreListe_t* listeMst);

char* toStringMst(struct monstre_t* M);

char* toStringLstMst(struct monstreListe_t* listeM);

#endif /* MONSTRE_H */
