#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"


void afficher(int **plateau, int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}