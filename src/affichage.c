#include <stdio.h>
#include <stdlib.h>

#include "../include/affichage.h"


void afficher(char **plateau, int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%c", plateau[i][j]);
        }
        printf("\n");
    }
}