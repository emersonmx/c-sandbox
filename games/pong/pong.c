#include "pong.h"

static Pong game = {0};

Pong* pong_instance(void)
{
    return &game;
}

void pong_process_event(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_w) {
            game.actions[PLAYER1_ACTION_UP] = true;
        }
        if (event->key.keysym.sym == SDLK_s) {
            game.actions[PLAYER1_ACTION_DOWN] = true;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            game.actions[PLAYER2_ACTION_UP] = true;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            game.actions[PLAYER2_ACTION_DOWN] = true;
        }
    }

    if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_w) {
            game.actions[PLAYER1_ACTION_UP] = false;
        }
        if (event->key.keysym.sym == SDLK_s) {
            game.actions[PLAYER1_ACTION_DOWN] = false;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            game.actions[PLAYER2_ACTION_UP] = false;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            game.actions[PLAYER2_ACTION_DOWN] = false;
        }
    }
}
