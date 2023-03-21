#include <stdio.h>
#include <stdlib.h>


#include "../include/joueur.h"

int main(int argc, char* argv[]) {
    char dir;
    joueur_t*  j = CreationJoueur();
    while (1) {
        scanf("%c", &dir);
        deplacement(j, 8, dir);
        printf("%s", toStringJr(j));
    }
    return 0;
}
