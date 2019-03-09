#ifndef CSB_GAMES_PONG_PONG_H
#define CSB_GAMES_PONG_PONG_H

#include <sdl2/engine.h>

#include "player.h"
#include "ball.h"

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

    Player players[2];
    Ball ball;
} Pong;


Pong* pong_instance(void);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAMES_PONG_PONG_H */