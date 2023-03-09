#include <stdio.h>
#include <stdlib.h>

#include "../include/main.h"
#include "../include/affichage.h"
#include "../include/joueur.h"
#include "../include/monstre.h"

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
        listeAff[listeM->tab[i].pos[0]][listeM->tab[i].pos[1]] = 'M';
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

    /* --- Inititalisation du joueur et des Monstres --- */
    joueur_t*  j = CreationJoueur();
    monstreListe_t* listeM = creationListeM();
    ajoutMst(listeM, 1, 1);
    ajoutMst(listeM, 2, 2);
    ajoutMst(listeM, 3, 3);

    /* --- Initialisation de la SDL --- */
    SDL_InitWithExit(); // Initialisation de la SDL
    SDL_WindowAndRendererWithExit(WINDOW_WIDTH, WINDOW_HEIGHT, &window, &renderer); // Création de la fenêtre et du renderer
    SDL_SetWindowTitle(window, "DIABLO MMXXIII"); // Titre de la fenêtre
    SDL_Surface *icon = SDL_LoadBMP("assets/joueur.bmp"); // Chargement de l'icône
    SDL_SetWindowIcon(window, icon); // Définition de l'icône

    /*--- Chargement des images ---*/
    SDL_Texture *bg_menu_texture = SDL_CreateIMG(renderer, "assets/bg_menu.bmp"); // Chargement de l'image de fond du menu
    SDL_Texture *bg_jeu_texture = SDL_CreateIMG(renderer, "assets/bg_jeu.bmp"); // Chargement de l'image de fond du jeu
    SDL_Texture *joueur_texture = SDL_CreateIMG(renderer, "assets/joueur.bmp"); // Chargement de l'image du joueur
    SDL_Texture *monstre_texture = SDL_CreateIMG(renderer, "assets/monstre.bmp"); // Chargement de l'image du monstre

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
                    case SDL_QUIT: // Si l'utilisateur ferme la fenêtre
                        program_launched = SDL_FALSE;
                        break;
                    default:
                        break;
                }
            }
            /* --- affichage --- */
            SDL_RenderCopy(renderer, bg_menu_texture, NULL, NULL); // fond du menu
            SDL_RenderPresent(renderer);

        }else{ // Si le jeu a commencé
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT){
                            printf("%d %d\n", event.button.x, event.button.y);
                        }
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym){
                        case SDLK_z:
                            deplacement(j, taille, 'z');
                            break;
                        case SDLK_s:
                            deplacement(j, taille, 's');
                            break;
                        case SDLK_q:
                            deplacement(j, taille, 'q');
                            break;
                        case SDLK_d:
                            deplacement(j, taille, 'd');
                            break;
                        case SDLK_SPACE:
                            if (MstEstPresent(listeM, j->pos[0], j->pos[1]) != -1){
                                int i_mst = MstEstPresent(listeM, j->pos[0], j->pos[1]);
                                attaque(j, &listeM->tab[i_mst]);
                                if (listeM->tab[i_mst].pv <= 0)
                                    enleverMst(&listeM->tab[i_mst] , listeM);
                            }
                            break;
                        case SDLK_ESCAPE:
                            game_start = false;
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

            /* --- affichage --- */
            SDL_RenderCopy(renderer, bg_jeu_texture, NULL, NULL);

            for(int i = 0; i < listeM->nbMst ; i++){ 
                if (MstEstPresent(listeM, j->pos[0], j->pos[1]) == i){
                    SDL_RenderIMG(renderer, monstre_texture, 
                        ((listeM->tab[i].pos[0] * 69) + 138) - 15 ,
                        ((listeM->tab[i].pos[1] * 68) + 41) - 20 , 
                        30, 40);
                }else {
                    SDL_RenderIMG(renderer, monstre_texture, 
                        ((listeM->tab[i].pos[0] * 69) + 158) - 15 ,
                        ((listeM->tab[i].pos[1] * 68) + 61) - 20 , 
                        30, 40);
                }

            }

            SDL_RenderIMG(renderer, joueur_texture, ((j->pos[0] * 69) + 158 ) - 15 , ((j->pos[1] * 68) + 61) - 20 , 30, 40); // affichage du joueur
            SDL_RenderPresent(renderer); // affichage du rendu
        }
    }
    /* --- Libération de la memoire --- */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
