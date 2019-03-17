#ifndef CSB_GAMES_PONG_PONG_H
#define CSB_GAMES_PONG_PONG_H

#include <sdl2/engine.h>
#include <sdl2/sdl2_ttf.h>

#include "action.h"
#include "player.h"
#include "ball.h"
#include "wall.h"
#include "midfield.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BALL_OUT_OF_BOUNDS_SIGNAL, PLAY_BALL_SIGNAL, SIGNALS_SIZE
} Signals;

typedef struct Pong {
    EngineSettings settings;

    Uint32 event_id;

    Player player1;
    Player player2;
    Ball ball;
    Wall top_wall;
    Wall bottom_wall;
    MidField midfield;

    SDL_Rect play_area;
} Pong;


Pong* pong_instance(void);

void pong_initialize(void);
void pong_finalize(void);
void pong_process_events(SDL_Event* event);
void pong_fixed_update(double delta);
void pong_render(void);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAMES_PONG_PONG_H */
