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

void attaque_aux(monstreListe_t *ListeM, int degats, int pos_m){
    monstre_t* m = ListeM->tab[pos_m];
    m->pv -= degats;
    if (m->pv <= 0)
        enleverMst(m, ListeM);

}
int attaque_contact(joueur_t* j, monstreListe_t* ListeM, int pos_m, int degats){
    if (pos_m != -1){
        attaque_aux(ListeM, degats, pos_m);
        return 1;
    }
    return 0;
}
int attaque_dist(joueur_t* j, monstreListe_t* ListeM, obj objet_equipe, char dir){
    int nbMst = ListeM->nbMst;
    if (objet_equipe.distance){
        for (int i = 0; i < nbMst; i++) {
            switch (dir){
                case 'n':
                    if (j->pos[0] == ListeM->tab[i]->pos[0] && j->pos[1] > ListeM->tab[i]->pos[1])
                        attaque_aux(ListeM, objet_equipe.degats, i);
                    break;
                case 's':
                    if (j->pos[0] == ListeM->tab[i]->pos[0] && j->pos[1] < ListeM->tab[i]->pos[1])
                        attaque_aux(ListeM, objet_equipe.degats, i);
                    break;
                case 'o':
                    if (j->pos[0] > ListeM->tab[i]->pos[0] && j->pos[1] == ListeM->tab[i]->pos[1])
                        attaque_aux(ListeM, objet_equipe.degats, i);
                    break;
                case 'e':
                    if (j->pos[0] < ListeM->tab[i]->pos[0] && j->pos[1] == ListeM->tab[i]->pos[1])
                        attaque_aux(ListeM, objet_equipe.degats, i);
                    break;
                default:
                    break;
            }
        }
        return 1;
    }else{
        return 0;
    }
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
    SDL_Texture *fleche_texture = SDL_CreateIMG(renderer, "assets/fleche.bmp"); // Chargement de l'image de la flèche
    int item_follow_mouse = -1;
    int i_mst;
    char arc_tirer;
    float compteur_fleche = 0.0;
    /* --- Initialisation de l'inv --- */
    inv * inventaire = CreeINV();
    SetItem(inventaire, "epee", 50, 0, "assets/epee.bmp", renderer, false);
    SetItem(inventaire, "pioche", 10, 1, "assets/pioche.bmp", renderer, false);
    SetItem(inventaire, "arc", 20, 2, "assets/arc.bmp", renderer, true);

    while (program_launched){
        if (!game_start){
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_MOUSEBUTTONDOWN: 
                        if (event.button.button == SDL_BUTTON_LEFT){
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
        }else{ 
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT){
                            for (int i = 0; i < 3; i++){
                                if (SDL_RectHitbox(event, inventaire->cases[i].x, inventaire->cases[i].x + 50, inventaire->cases[i].y, inventaire->cases[i].y + 50) && item_follow_mouse == -1){
                                    item_follow_mouse = i;
                                }else if(SDL_RectHitbox(event, inventaire->cases[i].x, inventaire->cases[i].x + 50, inventaire->cases[i].y, inventaire->cases[i].y + 50)){
                                    EchangeItem(inventaire, i, item_follow_mouse);
                                    item_follow_mouse = -1;
                                }
                            }
                            printf("x = %d, y = %d\n", event.button.x, event.button.y);
                        }
                        break; 
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym){
                            case SDLK_z:
                                deplacement(j, taille, 'z');
                                joueur_texture = SDL_CreateIMG(renderer, "assets/joueur_z.bmp"); // on recharge l'image du joueur
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
                                i_mst = IndiceMst(listeM, j->pos[0], j->pos[1]);
                                attaque_contact(j, listeM, i_mst, inventaire->objets[0].degats);
                                break;
                            case SDLK_LEFT:
                                attaque_dist(j, listeM, inventaire->objets[0], 'o' );
                                arc_tirer = 'o';
                                break;
                            case SDLK_RIGHT:
                                attaque_dist(j, listeM, inventaire->objets[0], 'e' );
                                arc_tirer = 'e';
                                break;
                            case SDLK_UP:
                                attaque_dist(j, listeM, inventaire->objets[0], 'n' );
                                arc_tirer = 'n';
                                break;
                            case SDLK_DOWN:
                                attaque_dist(j, listeM, inventaire->objets[0], 's' );
                                arc_tirer = 's';
                                break;
                            case SDLK_ESCAPE:
                                game_start = false;
                                break;
                            case SDLK_p:
                                printf("%s",ToStringInv(inventaire));
                                break;
                            case SDLK_i:
                                printf("%f", compteur_fleche);
                                break;
                            default:
                                break;
                        }
                        break;
                }
                if (item_follow_mouse != -1)
                    RefreshPos(item_follow_mouse, inventaire, event.button.x, event.button.y);

            }



            RandomMoove(listeM, taille, SDL_GetTicks());

            SDL_RenderCopy(renderer, bg_jeu_texture, NULL, NULL); 

            SDL_RenderMonstre(renderer, monstre_texture, 30, 40, listeM, j, inventaire);

            if ((arc_tirer == 'n' || arc_tirer == 's' || arc_tirer == 'o' || arc_tirer == 'e') && inventaire->objets[0].distance){
                compteur_fleche += 0.5;
                SDL_AfficherFleche(&arc_tirer, renderer, fleche_texture, j->pos[0], j->pos[1], 40, 40, &compteur_fleche);
            }else if (!inventaire->objets[0].distance){
                arc_tirer = ' ';
                compteur_fleche = 0;
            }

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
