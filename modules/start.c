#include "main/main.h"
#include "affichage/affichage.h"

int main(int argc, char *argv[])
{
    int plateau = creationPlateau();
    afficher(plateau);
    return 0;
}