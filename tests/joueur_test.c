#include <stdio.h>
#include <stdlib.h>

#include "../include/joueur.h"

int main() {
    joueur_t*  j = CreationJoueur();
    while (1) {
        deplacement(j, 10, getch());
        printf("%s", toStringJr(j));

    }
    return 0;
}
