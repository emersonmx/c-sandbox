#include "action.h"

static bool actions[ACTIONS_SIZE] = {0};

void action_process_events(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_w) {
            actions[PLAYER1_ACTION_UP] = true;
        }
        if (event->key.keysym.sym == SDLK_s) {
            actions[PLAYER1_ACTION_DOWN] = true;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            actions[PLAYER2_ACTION_UP] = true;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            actions[PLAYER2_ACTION_DOWN] = true;
        }
    }

    if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_w) {
            actions[PLAYER1_ACTION_UP] = false;
        }
        if (event->key.keysym.sym == SDLK_s) {
            actions[PLAYER1_ACTION_DOWN] = false;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            actions[PLAYER2_ACTION_UP] = false;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            actions[PLAYER2_ACTION_DOWN] = false;
        }
    }
}

bool action_is_pressed(int action)
{
    return actions[action];
}

bool action_is_released(int action)
{
    return !actions[action];
}
