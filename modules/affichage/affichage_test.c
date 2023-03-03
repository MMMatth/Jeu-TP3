#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"

int main(){
    int ** plateau = malloc(sizeof(int*)*10);
    for (int i = 0; i < 10; i++) {
        plateau[i] = malloc(sizeof(int)*10);
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            plateau[i][j] = 0;
        }
    }
    afficher(plateau, 10);

    return 0;
}