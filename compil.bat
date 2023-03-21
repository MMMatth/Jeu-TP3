@REM Compilation des modules
gcc -c src/affichage.c -o lib/affichage.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc -c src/main.c -o lib/main.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc -c src/inventaire.c -o lib/inventaire.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc -c src/son.c -o lib/son.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc -c src/joueur.c -o lib/joueur.o -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc -c src/monstre.c -o lib/monstre.o  -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc -c src/hud.c -o lib/hud.o  -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf

@REM Compilation des tests
gcc tests/joueur_test.c lib/joueur.o -o bin/joueur_test
gcc tests/monstre_test.c lib/*.o -o bin/monstre_test -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc tests/inventaire_test.c lib/*.o -o bin/inventaire_test -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
gcc tests/main_test.c lib/*.o -o bin/start -I include/SDL -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf


