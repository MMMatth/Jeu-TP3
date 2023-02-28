#ifndef MONSTRE_H
#define MONSTRE_H

/**
 * \file monstre.h
 * \brief Fichier d'en-tête contenant la définition des structures et fonctions pour les monstres.
 */



/**
 * \brief La structure représentant un monstre.
 */
struct monstre_t {
    int pv; /**< Les points de vie du monstre. */
    int pos[2]; /**< La position du monstre ([0] = x et [1] = y). */
};

/**
 * \brief La structure représentant une liste de monstres.
 */
struct listeMst_t {
    struct monstre_t* tab; /**< Le tableau de monstres. */
    int taille; /**< La taille du tableau. */
    int nb; /**< Le nombre de monstres dans la liste. */
};

/**
 * \brief Crée un tableau vide de monstres de taille TMAP*TMAP.
 *
 * \return Un pointeur vers la structure de liste de monstres créée.
 */
struct listeMst_t* creationListeM();

/**
 * \brief Ajoute un monstre avec une position aléatoire à la liste.
 * Le monstre n'apparaîtra pas sur une case occupée par le joueur ou un autre monstre.
 *
 * \param listeM La liste de monstres.
 * \param j_pos0 La position x du joueur.
 * \param j_pos1 La position y du joueur.
 *
 * \return 1 si le monstre a été ajouté avec succès, 0 sinon.
 */
int ajoutMst(struct listeMst_t* listeM, int j_pos0, int j_pos1);

/**
 * \brief Enlève un monstre de la liste.
 * La liste ne doit pas avoir de trous.
 *
 * \param m Le monstre à enlever.
 * \param listeMst La liste de monstres.
 */
void enleverMst(struct monstre_t* m, struct listeMst_t* listeMst);

/**
 * \brief Convertit un monstre en une chaîne de caractères pour l'affichage.
 *
 * \param M Le monstre à convertir.
 *
 * \return La chaîne de caractères correspondant au monstre.
 */
char* toStringMst(struct monstre_t* M);

/**
 * \brief Convertit une liste de monstres en une chaîne de caractères pour l'affichage.
 *
 * \param listeM La liste de monstres à convertir.
 *
 * \return La chaîne de caractères correspondant à la liste de monstres.
 */
char* toStringLstMst(struct listeMst_t* listeM);

#endif /* MONSTRE_H */
