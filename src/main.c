#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/main.h"
#include "../include/affichage.h"
#include "../include/joueur.h"
#include "../include/monstre.h"
#include "../include/inventaire.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define taille 8

int attaque(joueur_t* j, monstre_t* m){
    if (j->pos[0] == m->pos[0] && j->pos[1] == m->pos[1]){
        m->pv -= 10;
        return 1;
    }
    return 0;
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

void jouer(int argc, char *argv[])
{
    /* --- Initialisation des variables --- */
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    bool game_start = false;
    int tick = 0;
    /* --- Inititalisation du joueur et des Monstres --- */
    joueur_t*  j = CreationJoueur();
    monstreListe_t* listeM = creationListeM();
    srand(time(NULL));
    ajoutMst(listeM, rand() % taille, rand() % taille);
    ajoutMst(listeM, rand() % taille, rand() % taille);
    ajoutMst(listeM, rand() % taille, rand() % taille);

    /* --- Initialisation de la SDL --- */
    SDL_InitWithExit(); // Initialisation de la SDL
    SDL_WindowAndRendererWithExit(WINDOW_WIDTH, WINDOW_HEIGHT, &window, &renderer); // Création de la fenêtre et du renderer
    SDL_SetWindowTitle(window, "DIABLO MMXXIII"); // Titre de la fenêtre
    SDL_Surface *icon = SDL_LoadBMP("assets/joueur_s.bmp"); // Chargement de l'icône
    SDL_SetWindowIcon(window, icon); // Définition de l'icône

    /*--- Chargement des images ---*/
    SDL_Texture *bg_menu_texture = SDL_CreateIMG(renderer, "assets/bg_menu.bmp"); // Chargement de l'image de fond du menu
    SDL_Texture *bg_jeu_texture = SDL_CreateIMG(renderer, "assets/bg_jeu.bmp"); // Chargement de l'image de fond du jeu
    SDL_Texture *joueur_texture = SDL_CreateIMG(renderer, "assets/joueur_s.bmp"); // Chargement de l'image du joueur
    SDL_Texture *monstre_texture = SDL_CreateIMG(renderer, "assets/monstre.bmp"); // Chargement de l'image du monstre

    int val;


    /* --- Initialisation de l'inv --- */
    inv * inventaire = CreeINV();
    SetItem(inventaire, "epee", 10, 0, "assets/epee.bmp", renderer);
    SetItem(inventaire, "pioche", 5, 1, "assets/pioche.bmp", renderer);
    SetItem(inventaire, "bouclier", 0, 2, "assets/shield.bmp", renderer);

while (program_launched) // Boucle de jeu
    {
        if (!game_start){ // Si le jeu n'a pas commencé ( menu )
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_MOUSEBUTTONDOWN: // Si l'utilisateur clique sur la souris
                        if (event.button.button == SDL_BUTTON_LEFT){ // Si c'est le bouton gauche
                            if (SDL_RectHitbox(event, 250, 550, 250, 340)){
                                printf("Jouez au jeu\n");
                                game_start = true;
                            }else if (SDL_RectHitbox(event, 250, 550, 380, 470)){
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

            SDL_RenderCopy(renderer, bg_menu_texture, NULL, NULL); 
            SDL_RenderPresent(renderer);

        }else{ // Si le jeu a commencé
            tick += 1;
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym){
                        case SDLK_z:
                            deplacement(j, taille, 'z');
                            joueur_texture = SDL_CreateIMG(renderer, "assets/joueur_z.bmp");
                            break;
                        case SDLK_s:
                            deplacement(j, taille, 's');
                            joueur_texture = SDL_CreateIMG(renderer, "assets/joueur_s.bmp");

                            break;
                        case SDLK_q:
                            deplacement(j, taille, 'q');
                            joueur_texture = SDL_CreateIMG(renderer, "assets/joueur_q.bmp");
                            break;
                        case SDLK_d:
                            deplacement(j, taille, 'd');
                            joueur_texture = SDL_CreateIMG(renderer, "assets/joueur_d.bmp");
                            break;
                        case SDLK_SPACE:
                            if (IndiceMst(listeM, j->pos[0], j->pos[1]) != -1){
                                int i_mst = IndiceMst(listeM, j->pos[0], j->pos[1]);
                                attaque(j, listeM->tab[i_mst]);
                                if (listeM->tab[i_mst]->pv <= 0)
                                    enleverMst(listeM->tab[i_mst] , listeM);
                            }
                            break;
                        case SDLK_ESCAPE:
                            game_start = false;
                            break;
                        case SDLK_e:
                            EchangeItem(inventaire, 2, 0);
                            ToStringInv(inventaire);
                            break;
                        case SDLK_r:
                            inventaire->objets[0].x += 30;
                            break;
                        default:
                            break;
                        }                 
                        break;
                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;
                    default:
                        break;

 
                }
            }
            
            /* --- On affiche de point rouge sur les cases --- */
            // for (int j = 61; j < 600; j += 68){
            //     for (int i = 158; i < 700; i += 69){
            //         SDL_RenderDrawPoint(renderer, i, j);
            //     }
            // }



            RandomMoove(listeM, taille, tick);

            SDL_RenderCopy(renderer, bg_jeu_texture, NULL, NULL); 

            SDL_RenderMonstre(renderer, monstre_texture, 30, 40, listeM, j);

            SDL_RenderIMG(renderer, joueur_texture, ((j->pos[0] * 69) + 158 ) - 15 , ((j->pos[1] * 68) + 61) - 20 , 30, 40);
            
            SDL_RenderINV(inventaire, renderer);

            SDL_RenderPresent(renderer);
        }
    }
    /* --- Libération de la memoire --- */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
