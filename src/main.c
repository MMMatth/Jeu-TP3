#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/main.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define taille 8

void attaque(monstreListe_t *ListeM, int degats, int pos_m, sound_t * son){
    monstre_t* m = ListeM->tab[pos_m]; // on récupère le monstre
    m->pv -= degats; // on lui enlève les dégats
    if (m->pv <= 0){ // si il est mort on le supprime
        enleverMst(m, ListeM); // on le supprime de la liste 
        PlaySound(son->death, 0, 0); // on joue le son de mort
    }
}

int attaque_contact(joueur_t* j, monstreListe_t* ListeM, int pos_m, int degats, sound_t * son){
    if (pos_m != -1){ // si le joueur est en contact avec un monstre
        attaque(ListeM, degats, pos_m, son); // on attaque le monstre
        return 1; 
    }
    return 0;
}

int attaque_dist(joueur_t* j, monstreListe_t* ListeM, obj objet_equipe, char dir, sound_t * son){
    if (objet_equipe.distance){ // si l'objet est à distance
        PlaySound(son->arc, 1, 0); // on joue le son de l'arc
        return attaque_dist_aux(j, ListeM, dir, objet_equipe.degats, son); // on attaque
    }
}

int attaque_dist_aux(joueur_t* j, monstreListe_t* ListeM, char dir, int degats, sound_t * son){ 
    int nbMst = ListeM->nbMst; // on récupère le nombre de monstre
    for (int i = 0; i < nbMst; i++) { // on parcours la liste de monstre
        switch (dir){
            case 'n': // si le tir est vers le haut
                if (j->pos[0] == ListeM->tab[i]->pos[0] && j->pos[1] > ListeM->tab[i]->pos[1]) // si le monstre est au dessus du joueur
                    attaque(ListeM, degats, i, son); // on attaque le monstre
                break;
            case 's':
                if (j->pos[0] == ListeM->tab[i]->pos[0] && j->pos[1] < ListeM->tab[i]->pos[1])
                    attaque(ListeM, degats, i, son);
                break;
            case 'o':
                if (j->pos[0] > ListeM->tab[i]->pos[0] && j->pos[1] == ListeM->tab[i]->pos[1])
                    attaque(ListeM, degats, i, son);
                break;
            case 'e':
                if (j->pos[0] < ListeM->tab[i]->pos[0] && j->pos[1] == ListeM->tab[i]->pos[1])
                    attaque(ListeM, degats, i, son);
                break;
            default:
                break;
        }
    }return 0;
}

char ** generationListeAff( joueur_t* j, monstreListe_t* listeM){
    // on fait un tableau de 2D de taille 10 rempli de 0
    char ** listeAff = malloc(taille * sizeof(char *));
    for (int i = 0; i < taille; i++) {
        listeAff[i] = malloc(taille * sizeof(char));
    }
    // on remplie le tableau de vide
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            listeAff[i][j] = '/';
        }
    }

    // on place le joueur
    listeAff[j->pos[0]][j->pos[1]] = 'J';

    // on place les monstres
    for (int i = 0; i < listeM->nbMst; i++) {
        listeAff[listeM->tab[i]->pos[0]][listeM->tab[i]->pos[1]] = 'M';
    }

    return listeAff;
}

void InitInventaire(inv *inventaire, SDL_Renderer *renderer){
    SetItem(inventaire, "epee", 50, 0, false); // on ajoute l'épée
    SetItem(inventaire, "arc", 20, 1, true); // on ajoute l'arc
}

void InitMonstres(monstreListe_t *ListeM, int manche){
    for (int i = 0; i < manche * 3 ; i++) // on ajoute 3 monstres par manche
        ajoutMst(ListeM, rand() % taille, rand() % taille); // on ajoute un monstre à une position aléatoire
}

void InitWorld(world_t * world, SDL_Renderer *renderer){
    world->joueur = CreationJoueur(); // on crée le joueur
    world->ListeM = creationListeM(); // on crée la liste de monstre
    InitMonstres(world->ListeM, 1); // on initialise les monstres
    world->inventaire = CreationInventaire(); // on crée l'inventaire
    InitInventaire(world->inventaire, renderer); // on initialise l'inventaire
}

void CleanWorld(world_t * world){
    free(world->joueur); // on libère la mémoire du joueur
    free(world->ListeM); // on libère la mémoire de la liste de monstre
    free(world->inventaire); // on libère la mémoire de l'inventaire
    free(world); // on libère la mémoire du monde
}

void jouer(int argc, char *argv[])
{
    /* --- Initialisation des variables --- */
    SDL_Window *window = NULL; // on crée une fenêtre
    SDL_Renderer *renderer = NULL; // on crée un renderer
    SDL_bool program_launched = SDL_TRUE; // on crée un booléen pour savoir si le programme est lancé
    SDL_Event event; // on crée un événement
    int game_phase = 0;
    
    init_hud();

    initSDL(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT); // on initialise SDL

    world_t * world = malloc(sizeof(world_t)); // on crée le monde
    InitWorld(world, renderer); // on initialise le monde

    texture_t * textures = (texture_t*) malloc(sizeof(texture_t)); // on crée les textures
    InitTexture(renderer, textures); // on initialise les textures

    music_t * musics = (music_t*) malloc(sizeof(music_t)); // on crée la musique
    InitMusic(musics); // on initialise la musique

    sound_t * sons = (sound_t*) malloc(sizeof(sound_t)); // on crée les sons
    InitSound(sons); // on initialise les sons


    int item_follow_mouse = -1; // on crée une variable pour savoir si un item est suivi par la souris
    int i_mst, timer = 0; // on crée une variable pour savoir si un monstre est touché et un timer
    char arc_tirer =' '; // on crée une variable pour savoir si l'arc est tiré et dans quelle direction
    float compteur_fleche = 0.0; // on crée un compteur pour gerer le temp de voyage des fleches
    int ticks = 0; // on crée un compteur de ticks
    int manche = 1; // on crée un compteur de manche


    while (program_launched){
        ticks += 1; // on incrémente le compteur de ticks
        if (game_phase == 0){ // si on est dans le menu
            if (ticks == 1) PlayMusic(musics->menu); // on joue la musique du menu si le menu vient d'être ouvert
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_MOUSEBUTTONDOWN: 
                        if (event.button.button == SDL_BUTTON_LEFT){
                            if (hitbox(event, 250, 550, 250, 340)){ // si on clique sur le bouton jouer
                                PlaySound(sons->click, 0, 0); // on joue le son du click
                                printf("Jouez au jeu\n"); // on affiche un message dans la console
                                StopMusic(musics->menu); // on arrête la musique du menu
                                ticks = 0; // on remet le compteur de ticks à 0
                                game_phase = 1; // on passe à la phase de jeu
                            }else if (hitbox(event, 250, 550, 380, 470)){
                                PlaySound(sons->click, 0, 0);
                                SDL_Delay(200);
                                printf("Quitter le jeu\n");
                                program_launched = SDL_FALSE;
                                break;
                            }
                        }
                        break;
                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;
                    default:
                        break;
                }
            }
            SDL_RenderCopy(renderer, textures->background_menu , NULL, NULL); // on affiche le fond d'écran du menu
            SDL_RenderPresent(renderer); // on affiche le rendu
        }else if(game_phase == 1){  // si on est dans la phase de jeu
            if (ticks == 1) PlayMusic(musics->game); // on joue la musique du jeu si le jeu vient d'être ouvert
            
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT){
                            for (int i = 0; i < 3; i++){
                                if (hitbox(event, world->inventaire->cases[i].x, world->inventaire->cases[i].x + 50, world->inventaire->cases[i].y, world->inventaire->cases[i].y + 50) && item_follow_mouse == -1){
                                    item_follow_mouse = i; // l'objet est suivi par la souris si on clique dessus
                                }else if(hitbox(event, world->inventaire->cases[i].x, world->inventaire->cases[i].x + 50, world->inventaire->cases[i].y, world->inventaire->cases[i].y + 50)){
                                    EchangeItem(world->inventaire, i, item_follow_mouse); // on échange les items si on clique sur un item et qu'on un item suivi par la souris
                                    item_follow_mouse = -1; // on arrête de suivre l'item
                                }
                            }
                        }
                        break; 
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym){
                            case SDLK_z:
                                deplacement(world->joueur, taille, 'z'); // on déplace le joueur vers le haut
                                textures->joueur = create_img(renderer, "assets/img/joueur_z.bmp"); // on change l'image du joueur
                                break;
                            case SDLK_s:
                                deplacement(world->joueur, taille, 's'); // on déplace le joueur vers le bas
                                textures->joueur = create_img(renderer, "assets/img/joueur_s.bmp"); // on change l'image du joueur
                                break;
                            case SDLK_q:
                                deplacement(world->joueur, taille, 'q');
                                textures->joueur = create_img(renderer, "assets/img/joueur_q.bmp");
                                break;
                            case SDLK_d:
                                deplacement(world->joueur, taille, 'd');
                                textures->joueur = create_img(renderer, "assets/img/joueur_d.bmp");
                                break;
                            case SDLK_SPACE:
                                i_mst = IndiceMst(world->ListeM, world->joueur->pos[0], world->joueur->pos[1]); // on récupère l'indice du monstre touché
                                attaque_contact(world->joueur, world->ListeM, i_mst, world->inventaire->objets[0].degats, sons); // on attaque le monstre
                                break;
                            case SDLK_LEFT:
                                attaque_dist(world->joueur, world->ListeM, world->inventaire->objets[0], 'o' , sons); // on attaque le monstre dans la direction de la flèche
                                arc_tirer = 'o'; // on indique que l'arc est tiré vers la gauche (ouest)
                                break;
                            case SDLK_RIGHT:
                                attaque_dist(world->joueur, world->ListeM, world->inventaire->objets[0], 'e' , sons);
                                arc_tirer = 'e';
                                break;
                            case SDLK_UP:
                                attaque_dist(world->joueur, world->ListeM, world->inventaire->objets[0], 'n' , sons);
                                arc_tirer = 'n';
                                break;
                            case SDLK_DOWN:
                                attaque_dist(world->joueur, world->ListeM, world->inventaire->objets[0], 's' , sons);
                                arc_tirer = 's';
                                break;
                            case SDLK_ESCAPE:
                                program_launched = SDL_FALSE; // on passe à la phase du menu
                                StopMusic(musics->game); // on arrête la musique du jeu
                            
                                break;
                            default:
                                break;
                        }
                        break;
                }
                if (item_follow_mouse != -1) // si on suit un item
                    RefreshPos(item_follow_mouse, world->inventaire, event.button.x, event.button.y); // on actualise sa position
            }


            update_hud(timer, manche); // on actualise l'HUD

            RandomMoove(world->ListeM, taille, ticks); // on fait bouger les monstres

            SDL_RenderCopy(renderer, textures->background_game, NULL, NULL); // on affiche le fond d'écran du jeu

            render_monstre(renderer, textures->monstre , 30, 40, world->ListeM, world->joueur, world->inventaire); // on affiche les monstres

            render_fleche(renderer, textures, world->joueur, &compteur_fleche, &arc_tirer, world->inventaire->objets[0].distance); // on affiche la flèche

            render_img(renderer, textures->joueur , coord_x(world->joueur) , coord_y(world->joueur) , 30, 40); // on affiche le joueur
            
            render_inv(world->inventaire, textures, renderer); // on affiche l'inventaire

            render_hud(renderer); // on affiche l'HUD

            SDL_RenderPresent(renderer); // on affiche tout
            
            SDL_Delay(1000/60); // on met en pause le programme pour avoir 60 fps

            if (world->ListeM->nbMst == 0 && manche != 5){ // si on a tué tous les monstres et qu'on est pas à la dernière manche
                manche += 1; // on passe à la manche suivante
                InitMonstres(world->ListeM, manche); // On met les monstres de la nouvelle manche
            }else if (world->ListeM->nbMst == 0 && manche == 5){ // si on a gagner
                save_score(timer); // on sauvegarde le score
                printf("Vous avez gagné\n"); // on affiche un message
                game_phase = 2; // on passe à la phase de fin de jeu
            }

            if (ticks % 60 == 0) // on incrémente le timer toutes les secondes
                timer += 1; // on incrémente le timer toutes les secondes

        }else{ // si on est dans la phase de fin de jeu
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (hitbox(event, 250, 550, 324, 400)){ // si on clique sur le bouton "Quitter"
                            PlaySound(sons->click, 0, 0); // on joue le son du clic
                            SDL_Delay(200); // on met en pause le programme pour avoir le temps de jouer le son
                            StopMusic(musics->game); // on arrête la musique du jeu
                            printf("Quitter le jeu\n"); // on affiche un message
                            program_launched = SDL_FALSE; // on quitte le programme
                            break;
                        }
                }
            }
            SDL_RenderCopy(renderer, textures->background_fin , NULL, NULL); // on affiche le fond d'écran de fin de jeu
            SDL_RenderPresent(renderer); // on affiche tout
            
            SDL_Delay(1000/60); // on met en pause le programme pour avoir 60 fps
        }
    }
    CleanWorld(world); // on libère la mémoire allouée pour le monde
    clean(window, renderer); // on libère la mémoire allouée pour la fenêtre et le renderer
    close_hud(); // on libère la mémoire allouée pour l'HUD
}
