#ifndef CSB_GAMES_PONG_PONG_H
#define CSB_GAMES_PONG_PONG_H

#include <sdl2/engine.h>

#include "player.h"
#include "ball.h"
#include "wall.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BALL_OUT_OF_BOUNDS_SIGNAL, PLAY_BALL_SIGNAL, SIGNAL_SIZE
} Signals;

typedef enum {
    PLAYER1_ACTION_UP, PLAYER1_ACTION_DOWN,
    PLAYER2_ACTION_UP, PLAYER2_ACTION_DOWN,
    ACTIONS_SIZE
} Actions;

typedef struct Pong {
    EngineSettings settings;

    Uint32 event_id;
    bool actions[ACTIONS_SIZE];

    Player player1;
    Player player2;
    Ball ball;
    Wall top_wall;
    Wall bottom_wall;
    SDL_Rect play_area;
} Pong;


Pong* pong_instance(void);

void pong_initialize(void);
void pong_process_event(SDL_Event* event);
void pong_fixed_update(double delta);
void pong_render(void);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAMES_PONG_PONG_H */
