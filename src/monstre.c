#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/monstre.h"


monstreListe_t* creationListeM(){
    monstreListe_t* listeM = malloc(sizeof(monstreListe_t)); // on alloue de la memoire pour la liste
    listeM->nbMst = 0; // on initialise le nombre de monstre a 0
    listeM->tab = malloc(1000 * sizeof(monstre_t)); // on alloue de la memoire pour 100 monstres
    return listeM;
}

void ajoutMst( monstreListe_t* listeM, int x, int y){
    if (IndiceMst(listeM, x, y) != -1) // si il y a deja un monstre a la position on relance la fonction pour en trouver une autre
        return ajoutMst(listeM, rand() % 8, rand() % 8);
    monstre_t * m = malloc(sizeof(monstre_t)); // on alloue de la memoire pour le monstre
    m->pos[0] = x; // on initialise la position du monstre
    m->pos[1] = y;
    m->pv = rand() % 100 + 1; // nombre de pv alleatoire enttier entre 1 et 100
    listeM->tab[listeM->nbMst] = m; // on ajoute le monstre a la liste
    listeM->nbMst++;
}

void enleverMst(monstre_t* m, monstreListe_t* listeMst){
    int i = IndiceMst(listeMst, m->pos[0], m->pos[1]); // on recupere l'indice du monstre a enlever
    free(listeMst->tab[i]); // on libere la memoire du monstre
    listeMst->tab[i] = listeMst->tab[listeMst->nbMst - 1]; // on decale les monstres pour ne pas avoir de trou
    listeMst->nbMst--; // on decremente le nombre de monstre
}


int IndiceMst(monstreListe_t* listeM, int x, int y){
    for (int i = 0; i < listeM->nbMst; i++){ // on parcours la liste de monstre
        if (listeM->tab[i]->pos[0] == x && listeM->tab[i]->pos[1] == y) // si on trouve un monstre a la position
            return i; // on retourne l'indice du monstre
    }
    return -1; // pas de monstre a la position
}

int RandomMoove(monstreListe_t *listeM, int taille, int tick){
    if (tick % 200 == 0 ){ 
        for (int i = 0; i < listeM->nbMst; i++){ // on pacours la liste de monstre
            int r = rand() % 4; // on choisi une direction aleatoire
            int x = listeM->tab[i]->pos[0]; // on recupere la position du monstre
            int y = listeM->tab[i]->pos[1];
            switch (r){
                case 0: // gauche
                    if (x != 0 && IndiceMst(listeM, x - 1, y) == -1) // si il n'y a pas de monstre a gauche et que le monstre n'est pas coller a gauche
                        listeM->tab[i]->pos[0]--; 
                    else return RandomMoove(listeM, taille, tick); // sinon on recommence
                    break;
                case 1: // droite
                    if (x != taille - 1 && IndiceMst(listeM, x + 1, y) == -1)
                        listeM->tab[i]->pos[0]++;
                    else return RandomMoove(listeM, taille, tick);
                    break;
                case 2: // haut
                    if (y != 0 && IndiceMst(listeM, x, y - 1) == -1)
                        listeM->tab[i]->pos[1]--;
                    else return RandomMoove(listeM, taille, tick);
                    break;
                case 3: // bas
                    if (y != taille - 1 && IndiceMst(listeM, x, y + 1) == -1) 
                        listeM->tab[i]->pos[1]++;
                    else return RandomMoove(listeM, taille, tick);
                    break;
                default:
                    break;
            }
        }
    }
}

char* toStringMst(monstre_t* M){
    char* str = malloc(50 * sizeof(char));
    sprintf(str, "Monstre : pv = %d, pos = (%d, %d) \n", M->pv, M->pos[0], M->pos[1]);
    return str;
}

char * toStringLstMst(monstreListe_t* listeM){
    char* str = malloc(listeM->nbMst * 50 * sizeof(char)); 
    for (int i = 0; i < listeM->nbMst; i++)
        strcat(str, toStringMst(listeM->tab[i]));
    return str;
}

void render_monstre(SDL_Renderer *renderer, SDL_Texture *texture, int w, int h, monstreListe_t *listeM, joueur_t *joueur, inv * inventaire){
    int i_mst;
    for (int i = 0; i < listeM->nbMst; i++){ // on parcour tout les monstres
        i_mst = IndiceMst(listeM, joueur->pos[0], joueur->pos[1]);
        if (i_mst == i){ 
            int mst_pos[] = {
                listeM->tab[i]->pos[0] * 69 + 138 - 15, 
                listeM->tab[i]->pos[1] * 68 + 41 - 20
                }; 
            bardevie(renderer, mst_pos[0], mst_pos[1], 30, 5, listeM->tab[i]->pv);
            render_img(renderer, texture, mst_pos[0], mst_pos[1], w, h);
        }else{
            int mst_pos[] = {
                listeM->tab[i]->pos[0] * 69 + 158 - 15, 
                listeM->tab[i]->pos[1] * 68 + 61 - 20
                }; 
            if ((listeM->tab[i]->pos[0] == joueur->pos[0] || listeM->tab[i]->pos[1] == joueur->pos[1]) && inventaire->objets[0].distance)
                bardevie(renderer, mst_pos[0], mst_pos[1], 30, 5, listeM->tab[i]->pv);
            render_img(renderer, texture, mst_pos[0], mst_pos[1], w, h);
        }
    }
}