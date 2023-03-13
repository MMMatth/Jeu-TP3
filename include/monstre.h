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
 * \brief fonction pour initialiser la liste de monstre
 * 
 * \return monstreListe_t* 
 */
monstreListe_t* creationListeM();

/**
 * \brief fonction pour ajouter un monstre a la liste
 * 
 * \param listeM : la liste de monstre
 * \param x : la position x du nouveau monstre
 * \param y : la position y du nouveau monstre
 */
void ajoutMst(monstreListe_t* listeM, int x, int y);

/**
 * \brief fonction pour enlever un monstre de la liste
 * 
 * \param m : le monstre a enlever
 * \param listeMst : la liste de monstre ou il faut enlever le monstre
 */
void enleverMst(monstre_t* m, monstreListe_t* listeMst);

/**
 * \brief fonction pour recuperer l'indice d'un monstre dans la liste par rapport a sa position
 * 
 * \param listeM : la liste de monstre
 * \param x  : la position du monstre
 * \param y : la position du monstre
 * \return int l'id du monstre dans la liste ou -1 si il n'y a pas de monstre a cette position
 */
int IndiceMst(monstreListe_t* listeM, int x, int y);

/**
 * \brief fonction pour deplacer un monstre aleatoirement
 * 
 * \param m : La liste de monstre
 * \param taille : la taille de la map
 * \param tick : le tick actuel
 * \return int 
 */
int RandomMoove(monstreListe_t *m, int taille, int tick);

/**
 * \brief fonction pour recuperer un monstre sous forme de chaine de caractere
 * 
 * \param M : le monstre a afficher
 * \return char* 
 */
char* toStringMst(monstre_t* M);

/**
 * \brief fonction pour recuperer la liste de monstre sous forme de chaine de caractere
 * 
 * \param listeM : la liste de monstre a afficher
 * \return char* 
 */
char* toStringLstMst(monstreListe_t* listeM);

#endif /* MONSTRE_H */
