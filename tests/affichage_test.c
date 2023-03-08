#include <stdio.h>
#include <stdlib.h>

#include "../include/affichage.h"

int main(){
    char ** plateau = malloc(sizeof(char*)*10);
    for (int i = 0; i < 10; i++) {
        plateau[i] = malloc(sizeof(char)*10);
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            plateau[i][j] = ' ';
        }
    }
    afficher(plateau, 10);

    return 0;
}