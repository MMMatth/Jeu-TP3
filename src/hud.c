#include "../include/hud.h"


#define SCORE_FONT_SIZE 24

static TTF_Font* hud_font = NULL;
static SDL_Color hud_color = { 255, 255, 255 };
static SDL_Rect chrono_rect = { 0, 0, 0, 0 };
static SDL_Rect manche_rect = { 0, 0, 0, 0 };
static char chrono_text[16] = "";
static char manche_text[16] = "";

void init_hud() {
    if (TTF_Init() == -1) { // Initialisation de l'API TTF
        printf("TTF_Init failed: %s\n", TTF_GetError()); // Si l'initialisation a échoué, on quitte le programme
        exit(EXIT_FAILURE); // On quitte le programme
    }

    hud_font = TTF_OpenFont("assets/font/Roboto-Bold.ttf", SCORE_FONT_SIZE); // Chargement de la police

    if (!hud_font) { // Si la police n'a pas été chargée
        printf("TTF_OpenFont failed: %s\n", TTF_GetError()); // On quitte le programme
        exit(EXIT_FAILURE); // On quitte le programme
    }
}

void update_hud(int seconds, int manches) { // Met à jour le chrono et le nombre de manches
    sprintf(manche_text, "%d / 5", manches); // On écrit le nombre de manches dans la chaîne de caractères
    if (seconds < 10) { 
        sprintf(chrono_text, "00:0%d", seconds);
    } else if (seconds < 60) {
        sprintf(chrono_text, "00:%d", seconds );
    } else if (seconds < 100) {
        sprintf(chrono_text, "0%d:%d", seconds / 60, seconds % 60 );
    }
}

void render_hud(SDL_Renderer* renderer) {
    // On crée les surfaces et les textures à partir des chaînes de caractères
    SDL_Surface* chrono_surface = TTF_RenderText_Blended(hud_font, chrono_text, hud_color);
    SDL_Surface* manche_surface = TTF_RenderText_Blended(hud_font, manche_text, hud_color);

    // On vérifie que les surfaces et les textures ont bien été créées
    if (!chrono_surface || !manche_surface) {
        printf("TTF_RenderText_Blended failed: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // On crée les textures à partir des surfaces
    SDL_Texture* chrono_texture = SDL_CreateTextureFromSurface(renderer, chrono_surface);
    SDL_Texture* manche_texture = SDL_CreateTextureFromSurface(renderer, manche_surface); 

    // On vérifie que les textures ont bien été créées
    if (!chrono_texture || !manche_texture) {
        printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // on recupere la taille du texte pour faire un rectangle de la bonne taille
    SDL_QueryTexture(chrono_texture, NULL, NULL, &chrono_rect.w, &chrono_rect.h);
    chrono_rect.x = 700; // On place le chrono à droite de l'écran
    chrono_rect.y = 35;
    SDL_QueryTexture(manche_texture, NULL, NULL, &manche_rect.w, &manche_rect.h);
    manche_rect.x = 700 + chrono_rect.w / 2 - manche_rect.w / 2; // On place le nombre de manches au milieu du chrono
    manche_rect.y = chrono_rect.y + chrono_rect.h + 5; // On place le nombre de manches en dessous du chrono

    // On affiche le chrono et le nombre de manches
    SDL_RenderCopy(renderer, chrono_texture, NULL, &chrono_rect);
    SDL_RenderCopy(renderer, manche_texture, NULL, &manche_rect);

    // On libère la mémoire
    SDL_DestroyTexture(chrono_texture);
    SDL_DestroyTexture(manche_texture);
    SDL_FreeSurface(chrono_surface);
    SDL_FreeSurface(manche_surface);
}

void save_score(int seconds) {
    FILE *fptr;

    // Ouverture du fichier en mode écriture (le fichier sera créé s'il n'existe pas)
    fptr = fopen("scores.txt", "a");
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier !\n");
        return;
    }

    // Écriture du score dans le fichier
    fprintf(fptr, "%d secondes\n", seconds);

    // Fermeture du fichier
    fclose(fptr);

    // On affiche un message de confirmation
    printf("Score sauvegardé avec succès !\n");
}

void close_hud() {
    TTF_CloseFont(hud_font); // On ferme la police
    TTF_Quit(); // On quitte l'API TTF
}