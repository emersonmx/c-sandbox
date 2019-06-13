#ifndef PONG_ACTION_H
#define PONG_ACTION_H

#include <stdbool.h>

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    PLAYER1_UP_ACTION, PLAYER1_DOWN_ACTION,
    PLAYER2_UP_ACTION, PLAYER2_DOWN_ACTION,
    ACTIONS_SIZE
};


void action_process_events(SDL_Event* event);

bool action_is_pressed(uint8_t action);
bool action_is_released(uint8_t action);

#ifdef __cplusplus
}
#endif

#endif /* PONG_ACTION_H */
