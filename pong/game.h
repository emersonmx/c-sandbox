#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <sdl2/sdl2.h>

#include "player.h"
#include "ball.h"
#include "wall.h"
#include "midfield.h"
#include "score.h"
#include "shade.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Game {
    Player player1;
    Player player2;
    Ball ball;
    Wall top_wall;
    Wall bottom_wall;
    MidField midfield;
    Score player1_score;
    Score player2_score;
    Shade shade;

    SDL_Rect play_area;
    bool paused;
} Game;


void game_init(Game* game);
void game_quit(Game* game);
void game_process_events(Game* game, SDL_Event* event);
void game_fixed_update(Game* game, double delta);
void game_update(Game* game, double delta);
void game_render(Game* game);

void game_pause(Game* game);
void game_unpause(Game* game);

#ifdef __cplusplus
}
#endif

#endif /* PONG_GAME_H */
