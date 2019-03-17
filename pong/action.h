#ifndef PONG_ACTION_H
#define PONG_ACTION_H

#include <stdbool.h>

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PLAYER1_ACTION_UP, PLAYER1_ACTION_DOWN,
    PLAYER2_ACTION_UP, PLAYER2_ACTION_DOWN,
    ACTIONS_SIZE
} Actions;


void action_process_events(SDL_Event* event);

bool action_is_pressed(int action);
bool action_is_released(int action);

#ifdef __cplusplus
}
#endif

#endif /* PONG_ACTION_H */
