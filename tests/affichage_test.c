#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "../include/affichage.h"
#include "../include/joueur.h"
#include "../include/monstre.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[]){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    bool game_start = false;

    joueur_t*  j = CreationJoueur();
    monstreListe_t* listeM = creationListeM();
    ajoutMst(listeM, 1, 1);
    ajoutMst(listeM, 2, 2);
    ajoutMst(listeM, 3, 3);

    SDL_InitWithExit();

    SDL_WindowAndRendererWithExit(WINDOW_WIDTH, WINDOW_HEIGHT, &window, &renderer); // Création de la fenêtre et du renderer

    SDL_SetWindowTitle(window, "DIABLO MMXXIII"); // Titre de la fenêtre

    SDL_Surface *icon = SDL_LoadBMP("assets/joueur.bmp"); // Chargement de l'icône
    SDL_SetWindowIcon(window, icon); // Définition de l'icône

    // Chargement de l'image de fond du menu
    SDL_Texture *bg_menu_texture = SDL_CreateIMG(renderer, "assets/bg_menu.bmp");

    // Chargement de l'image de fond du jeu
    SDL_Texture *bg_jeu_texture = SDL_CreateIMG(renderer, "assets/bg_jeu.bmp");

    // Chargement de l'image du joueur 
    SDL_Texture *joueur_texture = SDL_CreateIMG(renderer, "assets/joueur.bmp");

    SDL_Texture *monstre_texture = SDL_CreateIMG(renderer, "assets/monstre.bmp");

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Définir la couleur de rendu en rouge


    while (program_launched)
    {
        if (!game_start){
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT){
                            if (SDL_HITBOX(event, 250, 550, 250, 340)){
                                printf("Jouez au jeu\n");
                                game_start = true;
                            }
                            else if (SDL_HITBOX(event, 250, 550, 380, 470)){
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

        }else{
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT){
                            printf("%d %d\n", event.button.x, event.button.y);
                        }
                        break;
                    case SDL_KEYDOWN:
                        // touche z :
                        if (event.key.keysym.sym == SDLK_z)
                            deplacement(j, 8, 'z');
                        // touche s :
                        if (event.key.keysym.sym == SDLK_s)
                            deplacement(j, 8, 's');
                        if (event.key.keysym.sym == SDLK_q)
                            deplacement(j, 8, 'q');
                        if (event.key.keysym.sym == SDLK_d)
                            deplacement(j, 8, 'd');
                        else 
                            deplacement(j, 0, 'O');
                        break;                    


                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;

                    default:
                        break;
                }
            }

            SDL_RenderCopy(renderer, bg_jeu_texture, NULL, NULL);
            for (int j = 61; j < 600; j += 68){
                for (int i = 158; i < 700; i += 69){
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
            // Changer la position du joueur
            
            
            for(int i = 0; i < listeM->nbMst ; i++){
                SDL_Rect position_monstre = {((listeM->tab[i].pos[0] * 69) + 158 ) - 15 , ((listeM->tab[i].pos[1] * 68) + 61) - 20, 30, 40};
                SDL_RenderCopy(renderer, monstre_texture, NULL, &position_monstre);
            }
            SDL_Rect position_joueur = {((j->pos[0] * 69) + 158 ) - 15 , ((j->pos[1] * 68) + 61) - 20, 30, 40};
            SDL_RenderCopy(renderer, joueur_texture, NULL, &position_joueur);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}