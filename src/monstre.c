#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/monstre.h"


monstreListe_t* creationListeM(){
    monstreListe_t* listeM = malloc(sizeof(monstreListe_t)); // on alloue de la memoire pour la liste
    listeM->nbMst = 0; // on initialise le nombre de monstre a 0
    listeM->tab = malloc(100 * sizeof(monstre_t)); // on alloue de la memoire pour 100 monstres
    return listeM;
}

int ajoutMst( monstreListe_t* listeM, int j_pos0, int j_pos1){
    if (IndiceMst(listeM, j_pos0, j_pos1) != -1) {
        if (j_pos0 == 0) // si il est coller en haut
            return ajoutMst(listeM, j_pos0 + 1, j_pos1);
        else if (j_pos0 == 7) // si il est coller en bas
            return ajoutMst(listeM, j_pos0 - 1, j_pos1);
        else if (j_pos1 == 0) // si il est coller a gauche
            return ajoutMst(listeM, j_pos0, j_pos1 + 1);
        else if (j_pos1 == 7) // si il est coller a droite
            return ajoutMst(listeM, j_pos0, j_pos1 - 1);
        else // sinon on peut le decaler de partout
            return ajoutMst(listeM, j_pos0 + 1, j_pos1);
        printf("monstre apparue sur un autre mais décalé");
    }

    monstre_t * m = malloc(sizeof(monstre_t)); // on alloue de la memoire pour le monstre
    // on initialise les positions du monstre
    m->pos[0] = j_pos0; 
    m->pos[1] = j_pos1;
    m->pv = rand() % 100 + 1; // nombre de pv alleatoire enttier entre 1 et 100
    // on ajoute le monstre a la liste
    listeM->tab[listeM->nbMst] = m;
    listeM->nbMst++;
    return 0;
}

void enleverMst(monstre_t* m, monstreListe_t* listeMst){

    int i = IndiceMst(listeMst, m->pos[0], m->pos[1]);
    // on remplace le monstre par le dernier de la liste
    free(listeMst->tab[i]);
    listeMst->tab[i] = listeMst->tab[listeMst->nbMst - 1];
    // free(listeMst->tab[listeMst->nbMst - 1]);
    // on enleve le dernier de la liste
    listeMst->nbMst--;
}

char* toStringMst(monstre_t* M){
    // on cree une chaine de caractere assez grande pour contenir le monstre
    char* str = malloc(50 * sizeof(char));
    // on ajoute le monstre a la chaine
    sprintf(str, "Monstre : pv = %d, pos = (%d, %d) \n", M->pv, M->pos[0], M->pos[1]);
    return str;
}

char * toStringLstMst(monstreListe_t* listeM){
    // on cree une chaine de caractere assez grande pour contenir tous les monstres
    char* str = malloc(listeM->nbMst * 50 * sizeof(char)); 
    // on ajoute tous les monstres a la chaine
    for (int i = 0; i < listeM->nbMst; i++){
        strcat(str, toStringMst(listeM->tab[i]));
    }
    return str;
}


int IndiceMst(monstreListe_t* listeM, int j_pos0, int j_pos1){
    for (int i = 0; i < listeM->nbMst; i++){
        if (listeM->tab[i]->pos[0] == j_pos0 && listeM->tab[i]->pos[1] == j_pos1){
            return i; // on retourne l'indice du monstre
        }
    }
    return -1; // pas de monstre
}