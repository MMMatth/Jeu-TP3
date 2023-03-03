#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"

int main() {
    joueur_t j = *CreationJoueur();
    while (1) {
        deplacement(&j);
        printf("%s", toStringJr(&j));

    }
    return 0;
}
