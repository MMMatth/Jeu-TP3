#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_hud();
void update_hud(int seconds, int manches);
void render_hud(SDL_Renderer* renderer);
void save_score(int seconds);
void close_hud();

#endif