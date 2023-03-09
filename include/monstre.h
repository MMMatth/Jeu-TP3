#ifndef MONSTRE_H
#define MONSTRE_H


struct monstre {
    int pv; /**< Les points de vie du monstre. */
    int pos[2]; /**< La position du monstre ([0] = x et [1] = y). */
};
typedef struct monstre monstre_t;

struct monstreListe {
    monstre_t* tab; /**< Le tableau de monstres. */
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
 * \brief fonction qui vérifie si un monstre est présent à une position donnée.
 * 
 * \param listeM : la liste de monstres.
 * \param j_pos0 : la position du joueur.
 * \param j_pos1 : la position du joueur.
 * \return int : l'indice de la liste si le monstre est présent, -1 sinon.
 */
int MstEstPresent(monstreListe_t* listeM, int j_pos0, int j_pos1);

#endif /* MONSTRE_H */
