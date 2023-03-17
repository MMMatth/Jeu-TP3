#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "../include/main.h"
#include "../include/affichage.h"
#include "../include/joueur.h"
#include "../include/monstre.h"
#include "../include/inventaire.h"
#include "../include/son.h"

#include <SDL.h>
#include <SDL_mixer.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define taille 8

void attaque_aux(monstreListe_t *ListeM, int degats, int pos_m, sound_t * son){
    monstre_t* m = ListeM->tab[pos_m];
    m->pv -= degats;
    if (m->pv <= 0){
        enleverMst(m, ListeM);
        PlaySound(son->death, 0, 0);
    }
}

int attaque_contact(joueur_t* j, monstreListe_t* ListeM, int pos_m, int degats, sound_t * son){
    if (pos_m != -1){
        attaque_aux(ListeM, degats, pos_m, son);
        return 1;
    }
    return 0;
}

int attaque_dist(joueur_t* j, monstreListe_t* ListeM, obj objet_equipe, char dir, sound_t * son){
    if (objet_equipe.distance){        
        PlaySound(son->arc, 1, 0);
        return attaque_dist_aux(j, ListeM, dir, objet_equipe.degats, son);
    }
}

int attaque_dist_aux(joueur_t* j, monstreListe_t* ListeM, char dir, int degats, sound_t * son){
    int nbMst = ListeM->nbMst;
    for (int i = 0; i < nbMst; i++) {
        switch (dir){
            case 'n':
                if (j->pos[0] == ListeM->tab[i]->pos[0] && j->pos[1] > ListeM->tab[i]->pos[1])
                    attaque_aux(ListeM, degats, i, son);
                break;
            case 's':
                if (j->pos[0] == ListeM->tab[i]->pos[0] && j->pos[1] < ListeM->tab[i]->pos[1])
                    attaque_aux(ListeM, degats, i, son);
                break;
            case 'o':
                if (j->pos[0] > ListeM->tab[i]->pos[0] && j->pos[1] == ListeM->tab[i]->pos[1])
                    attaque_aux(ListeM, degats, i, son);
                break;
            case 'e':
                if (j->pos[0] < ListeM->tab[i]->pos[0] && j->pos[1] == ListeM->tab[i]->pos[1])
                    attaque_aux(ListeM, degats, i, son);
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
    SetItem(inventaire, "epee", 50, 0, "assets/epee.bmp", renderer, false);
    SetItem(inventaire, "pioche", 10, 1, "assets/pioche.bmp", renderer, false);
    SetItem(inventaire, "arc", 20, 2, "assets/arc.bmp", renderer, true);
}

void InitWorld(world_t * world, SDL_Renderer *renderer){
    world->joueur = CreationJoueur();
    world->ListeM = creationListeM();
    for (int i = 0; i < 10; i++)
        ajoutMst(world->ListeM, rand() % taille, rand() % taille);
    world->inventaire = CreationInventaire();
    InitInventaire(world->inventaire, renderer);
}

void jouer(int argc, char *argv[])
{
    /* --- Initialisation des variables --- */
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    bool game_start = false;
    
    initSDLWithExit(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    world_t * world = malloc(sizeof(world_t));
    InitWorld(world, renderer);

    texture_t * textures = (texture_t*) malloc(sizeof(texture_t));
    InitTexture(renderer, textures);

    music_t * musics = (music_t*) malloc(sizeof(music_t));
    InitMusic(musics);

    sound_t * sons = (sound_t*) malloc(sizeof(sound_t));
    InitSound(sons);

    int item_follow_mouse = -1;
    int i_mst;
    char arc_tirer =' ';
    float compteur_fleche = 0.0;
    int ticks = 0;


    while (program_launched){
        ticks += 1;
        if (!game_start){
            if (ticks == 1) PlayMusic(musics->menu);
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_MOUSEBUTTONDOWN: 
                        if (event.button.button == SDL_BUTTON_LEFT){
                            if (SDL_RectHitbox(event, 250, 550, 250, 340)){
                                PlaySound(sons->click, 0, 0);
                                printf("Jouez au jeu\n");
                                StopMusic(musics->menu);
                                ticks = 0;
                                game_start = true;
                            }else if (SDL_RectHitbox(event, 250, 550, 380, 470)){
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
            SDL_RenderCopy(renderer, textures->background_menu , NULL, NULL); 
            SDL_RenderPresent(renderer);
        }else{ 
            if (ticks == 1)
                PlayMusic(musics->game);
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT){
                            for (int i = 0; i < 3; i++){
                                if (SDL_RectHitbox(event, world->inventaire->cases[i].x, world->inventaire->cases[i].x + 50, world->inventaire->cases[i].y, world->inventaire->cases[i].y + 50) && item_follow_mouse == -1){
                                    item_follow_mouse = i;
                                }else if(SDL_RectHitbox(event, world->inventaire->cases[i].x, world->inventaire->cases[i].x + 50, world->inventaire->cases[i].y, world->inventaire->cases[i].y + 50)){
                                    EchangeItem(world->inventaire, i, item_follow_mouse);
                                    item_follow_mouse = -1;
                                }
                            }
                            printf("x = %d, y = %d\n", event.button.x, event.button.y);
                        }
                        break; 
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym){
                            case SDLK_z:
                                deplacement(world->joueur, taille, 'z');
                                textures->joueur = SDL_CreateIMG(renderer, "assets/joueur_z.bmp");
                                break;
                            case SDLK_s:
                                deplacement(world->joueur, taille, 's');
                                textures->joueur = SDL_CreateIMG(renderer, "assets/joueur_s.bmp");
                                break;
                            case SDLK_q:
                                deplacement(world->joueur, taille, 'q');
                                textures->joueur = SDL_CreateIMG(renderer, "assets/joueur_q.bmp");
                                break;
                            case SDLK_d:
                                deplacement(world->joueur, taille, 'd');
                                textures->joueur = SDL_CreateIMG(renderer, "assets/joueur_d.bmp");
                                break;
                            case SDLK_SPACE:
                                i_mst = IndiceMst(world->ListeM, world->joueur->pos[0], world->joueur->pos[1]);
                                attaque_contact(world->joueur, world->ListeM, i_mst, world->inventaire->objets[0].degats, sons);
                                break;
                            case SDLK_LEFT:
                                attaque_dist(world->joueur, world->ListeM, world->inventaire->objets[0], 'o' , sons);
                                arc_tirer = 'o';
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
                                game_start = false;
                                break;
                            default:
                                break;
                        }
                        break;
                }
                if (item_follow_mouse != -1)
                    RefreshPos(item_follow_mouse, world->inventaire, event.button.x, event.button.y);

            }

            RandomMoove(world->ListeM, taille, SDL_GetTicks());

            SDL_RenderCopy(renderer, textures->background_game, NULL, NULL); 

            SDL_RenderMonstre(renderer, textures->monstre , 30, 40, world->ListeM, world->joueur, world->inventaire);

            SDL_RenderFleche(renderer, textures, world->joueur, &compteur_fleche, &arc_tirer, world->inventaire->objets[0].distance);

            SDL_RenderIMG(renderer, textures->joueur , coord_x(world->joueur) , coord_y(world->joueur) , 30, 40);
            
            SDL_RenderINV(world->inventaire, renderer);

            SDL_RenderPresent(renderer);
            
        }
    }
    
    clean(window, renderer);
}
