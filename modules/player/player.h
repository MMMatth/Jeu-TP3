#ifndef PLAYER_H
#define PLAYER_H

/**
 * \brief  structure qui contient les données du joueur. Vous pouvez ajouter les champs dont vous avez besoin.
 * 
 */
struct joueur_t {
    int pos[2];
};

/**
 * \brief procedure crée un joueur. Vous aurez besoin de malloc(sizeof(struct
 *   joueur_t)). Vous pouvez ajouter les arguments dont vous avez besoin à cette fonction.
 * 
 * 
 */
void creationJoueur();

/**
 * \brief fonction qui renvoie une chaîne de caractères destinée
 * à être affichée et contenant les données du joueur, pour les besoins des tests.
 * 
 * \param j 
 * \return char* 
 */
char *toStringJr(struct joueur_t *j);

/**
 * \brief fonction qui demande au joueur de saisir une touche
 *  parmis wasd et fait le déplacement correspondant. Elle rendra 1 si le déplacement
 *  s’effectue avec succès, 0 sinon (par exemple en atteignant les bords de la carte).
 * 
 * \param j 
 * \return int 
 */
int deplacement(struct joueur_t *j);

#endif /* PLAYER_H */
