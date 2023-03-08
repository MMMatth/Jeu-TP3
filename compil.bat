@REM Compilation des modules
gcc -c src/main.c -o lib/main.o
gcc -c src/affichage.c -o lib/affichage.o
gcc -c src/joueur.c -o lib/joueur.o
gcc -c src/monstre.c -o lib/monstre.o

@REM Compilation des tests
gcc tests/affichage_test.c lib/*.o -o bin/affichage_test
gcc tests/joueur_test.c lib/*.o -o bin/joueur_test
gcc tests/monstre_test.c lib/*.o -o bin/monstre_test
gcc tests/main_test.c lib/*.o -o bin/main_test

