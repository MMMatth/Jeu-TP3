#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/inventaire.h"

int main() {
    inv*  inventaire = CreationInventaire();
    SetItem(inventaire, "epee", 50, 0, false);
    SetItem(inventaire, "potion", 20, 2, false);
    SetItem(inventaire, "arc", 30, 1, true);
    printf("%s\n", ToStringInv(inventaire));
    EchangeItem(inventaire, 0, 1);
    printf("%s\n", ToStringInv(inventaire));
    return 0;
}