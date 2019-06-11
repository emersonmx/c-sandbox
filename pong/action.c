#include "action.h"

static bool actions[ACTIONS_SIZE] = {0};

void action_process_events(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_w) {
            actions[PLAYER1_UP_ACTION] = true;
        }
        if (event->key.keysym.sym == SDLK_s) {
            actions[PLAYER1_DOWN_ACTION] = true;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            actions[PLAYER2_UP_ACTION] = true;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            actions[PLAYER2_DOWN_ACTION] = true;
        }
    }

    if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_w) {
            actions[PLAYER1_UP_ACTION] = false;
        }
        if (event->key.keysym.sym == SDLK_s) {
            actions[PLAYER1_DOWN_ACTION] = false;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            actions[PLAYER2_UP_ACTION] = false;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            actions[PLAYER2_DOWN_ACTION] = false;
        }
    }
}

bool action_is_pressed(uint8_t action)
{
    return actions[action];
}

bool action_is_released(uint8_t action)
{
    return !actions[action];
}
