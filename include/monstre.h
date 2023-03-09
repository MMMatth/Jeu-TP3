#ifndef MONSTRE_H
#define MONSTRE_H


struct monstre {
    int pv; /**< Les points de vie du monstre. */
    int pos[2]; /**< La position du monstre ([0] = x et [1] = y). */
};
typedef struct monstre monstre_t;

struct monstreListe {
    monstre_t ** tab; /**< Le tableau de monstres. */
    int nbMst; /**< La taille du tableau. */
};
typedef struct monstreListe monstreListe_t; ;


/**
 * \brief Création d'une liste de monstres.
 * 
 * \return monstreListe_t* 
 */
monstreListe_t* creationListeM();

/**
 * \brief Ajout d'un monstre dans la liste.
 * 
 * \param listeM La liste de monstres.
 * \param j_pos0 La position du monstre en x.
 * \param j_pos1 La position du monstre en y. 
 * \return int 
 */
int ajoutMst(monstreListe_t* listeM, int j_pos0, int j_pos1);

/**
 * \brief Enlever un monstre de la liste.
 * 
 * \param m le monstre à enlever.
 * \param listeMst la liste de monstres.
 */
void enleverMst(monstre_t* m, monstreListe_t* listeMst);

/**
 * \brief Affichage d'un monstre.
 * 
 * \param M le monstre.
 * \return char* 
 */
char* toStringMst(monstre_t* M);

/**
 * \brief Affichage de la liste de monstres.
 * 
 * \param listeM la liste de monstres.
 * \return char* 
 */
char* toStringLstMst(monstreListe_t* listeM);

/**
 * \brief fonction qui renvoie l'indice du monstre dans une case
 * 
 * \param listeM : la liste de monstres.
 * \param j_pos0 : la position du joueur.
 * \param j_pos1 : la position du joueur.
 * \return indice du monstre dans la case, -1 si pas de monstre.
 */
int IndiceMst(monstreListe_t* listeM, int j_pos0, int j_pos1);

/**
 * \brief fonction qui déplace les monstres de manière aléatoire.
 * 
 * \param m : la liste de monstres.
 * \param taille : la taille de la grille.
 * \param tick : le tick du jeu.
 * \return 1 si réussite, -1 sinon.
 */
int RandomMoove(monstreListe_t *m, int taille, int tick);


#endif /* MONSTRE_H */
