## Jeu en C
Ce projet a été réalisé dans le cadre du cours de méthodologie de la conception et de la programmation partie I pour les étudiants de la Licence 1 M-I-SPI de l'Université de Lorraine. Il consiste à créer un jeu solo qui se joue sur un plateau carré. Le joueur doit éliminer les monstres qui apparaissent aléatoirement sur la carte afin de protéger l'univers.

## Règles du jeu
Il ne peut y avoir qu'un seul monstre par case.
Le joueur peut être sur la même case qu'un monstre.
Le joueur ne peut engager un combat qu'en se déplaçant sur un monstre.
Les monstres ont un certain nombre de points de vie (PV). Chaque attaque leur enlève un nombre aléatoire de PV compris entre 10 et 20. Un monstre atteignant 0 PV meurt et disparaît de la carte.
Le joueur peut se déplacer d'une case à gauche, à droite, en haut ou en bas en utilisant les touches wasd. Il ne peut pas sortir des limites de la carte.
Modules
Ce jeu est divisé en au moins trois modules et un fichier/module principal. Chaque module doit être indépendant des autres, comporter un fichier header, un fichier source, un fichier test et une documentation doxygen. Vous pouvez également avoir un fichier header commun à tous les modules et contenant des constantes. La seule constante obligatoire est TMAP, la taille de la carte.

## Les modules obligatoires sont les suivants :

### Le joueur
Le joueur est défini par une structure joueur_t comportant au moins un tableau de deux entiers pos, la position du joueur sur la carte. Le module doit implémenter et tester au moins les fonctions suivantes :

- int deplacement(struct joueur_t* j): Demande au joueur de saisir une touche parmi wasd et fait le déplacement correspondant. Renvoie 1 si le déplacement s'effectue avec succès, 0 sinon (par exemple en atteignant les bords de la carte).
- struct joueur_t* creationJoueur(): Crée un joueur. Vous aurez besoin de malloc(sizeof(struct joueur_t)). Vous pouvez ajouter les arguments dont vous avez besoin à cette fonction.
- char* toStringJr(struct joueur_t* j): Renvoie une chaîne de caractères destinée à être affichée et contenant les données du joueur, pour les besoins des tests.
### Les monstres
Ce module implémente deux structures : monstre_t et listeMst_t. listeMst_t a deux champs : struct monstre_t* listeM[TMAP*TMAP], un tableau de pointeurs vers les monstres, et int nbMst, la taille effective du tableau. Il implémente les fonctions suivantes :

- struct monstreListe_t* creationListeM(): Crée un tableau vide de taille TMAP*TMAP de monstres.
- int ajoutMst(struct monstreListe_t* listeM, int j_pos0, int j_pos1): Ajoute un monstre avec une position aléatoire à la liste. Le monstre naîtra avec un nombre de PV aléatoire. Il ne doit pas naître sur une case
0.0.4 Le jeu
Ce module sera le module principal du programme et comportera la fonction principale
int main(int argc, char** argv). Cette fonction appellera les autres fonctions nécessaires
pour le fonctionnement du jeu. Elle gèrera l’affichage de la carte, le déplacement du joueur,
l’ajout et la suppression des monstres, ainsi que la gestion des combats. Elle appellera les
fonctions de test au besoin.

## Comment utiliser le jeu
Pour utiliser le jeu, il faut tout d'abord cloner le répertoire GitHub sur votre machine. Pour cela, il faut copier l'URL du répertoire depuis GitHub et lancer la commande git clone dans un terminal en utilisant l'URL copiée.

Ensuite, pour lancer le jeu, il faut compiler le programme en utilisant la commande make dans le terminal. Cette commande va compiler tous les fichiers sources nécessaires au fonctionnement du jeu et créer un exécutable nommé "jeu".

Pour lancer le jeu, il suffit d'exécuter le fichier "jeu" en utilisant la commande "./jeu" dans le terminal.

## Contributions
Toutes les contributions au projet sont les bienvenues. Si vous souhaitez apporter des modifications ou corriger des bugs, vous pouvez le faire en créant une branche depuis la branche principale et en soumettant une demande de fusion une fois vos modifications effectuées.

## License
Ce projet est sous licence MIT. Vous pouvez l'utiliser et le modifier comme bon vous semble, mais vous ne pouvez pas le vendre sans autorisation préalable des auteurs.

## Auteurs
Ce projet a été réalisé par Gaudel Matthieu et Colin Gabin, étudiants en première année de licence MI-SPI à l'Université de Lorraine.