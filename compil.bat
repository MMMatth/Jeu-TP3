@REM Compilation des modules
gcc -c src/main.c -o lib/main.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2
gcc -c src/affichage.c -o lib/affichage.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2
gcc -c src/joueur.c -o lib/joueur.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2
gcc -c src/monstre.c -o lib/monstre.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2

@REM Compilation des tests
gcc tests/affichage_test.c lib/*.o -o bin/affichage_test -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2
@REM gcc tests/joueur_test.c lib/*.o -o bin/joueur_test -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2
@REM gcc tests/monstre_test.c lib/*.o -o bin/monstre_test -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2
@REM gcc tests/main_test.c lib/*.o -o bin/main_test -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2


