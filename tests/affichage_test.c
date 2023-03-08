#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "../include/affichage.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[]){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    bool game_start = false;

    SDL_InitWithExit();

    SDL_WindowAndRendererWithExit(WINDOW_WIDTH, WINDOW_HEIGHT, &window, &renderer); // Création de la fenêtre et du renderer

    SDL_SetWindowTitle(window, "Jeu de la vie"); // Titre de la fenêtre

    SDL_Surface *icon = SDL_LoadBMP("assets/icon.bmp"); // Chargement de l'icône
    SDL_SetWindowIcon(window, icon); // Définition de l'icône

    // Chargement de l'image de fond du menu
    SDL_Texture *bg_menu_texture = SDL_CreateIMG(renderer, "assets/bg_menu.bmp");

    // Chargement de l'image de fond du jeu
    SDL_Texture *bg_jeu_texture = SDL_CreateIMG(renderer, "assets/bg_jeu.bmp");

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

                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;

                    default:
                        break;
                }
            }

            SDL_RenderCopy(renderer, bg_jeu_texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}