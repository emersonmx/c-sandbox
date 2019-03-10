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
    PLAYER1_ACTION_UP, PLAYER1_ACTION_DOWN,
    PLAYER2_ACTION_UP, PLAYER2_ACTION_DOWN,
    ACTIONS_SIZE
} Actions;

typedef struct Pong {
    EngineSettings settings;

    bool actions[ACTIONS_SIZE];

    Player player1;
    Player player2;
    Ball ball;
    Wall top_wall;
    Wall bottom_wall;
} Pong;


Pong* pong_instance(void);
void pong_process_event(SDL_Event* event);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAMES_PONG_PONG_H */
