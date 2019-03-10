#include <stdio.h>
#include <stdbool.h>

#include <utils/macros.h>
#include <utils/random.h>

#include "pong.h"
#include "utils.h"

static Pong* game = NULL;

static void initialize(void);
static void process_events(SDL_Event* event);
static void fixed_update(double delta);
static void update(double delta);
static void render(void);

static int window_width(void);
static int window_height(void);
static Player* player1(void);
static Player* player2(void);
static Ball* ball(void);
static Wall* top_wall(void);
static Wall* bottom_wall(void);

int main(void)
{
    randomize();

    game = pong_instance();

    game->settings = engine_default_settings();
    game->settings.window.title = "Pong";

    engine_set_init_func(initialize);
    engine_set_process_events_func(process_events);
    engine_set_fixed_update_func(fixed_update);
    engine_set_update_func(update);
    engine_set_render_func(render);

    return engine_main_loop(game->settings);
}

void initialize(void)
{
    memset(game->actions, 0, sizeof(game->actions));

    PlayerInputVelocityFunc player_controls[2];
    player_controls[PLAYER1] = player_default_input_velocity_func;
    player_controls[PLAYER2] = player_default_input_velocity_func;

    SDL_Color white = {255, 255, 255, SDL_ALPHA_OPAQUE};
    float center_x = window_width() / 2.0f;
    float center_y = window_height() / 2.0f;

    game->players[PLAYER1] = (Player){
        .index = PLAYER1,
        .color = white,
        .rect = {0, 0, 20, 80},
        .position = {15, center_y, 0},
        .speed = PLAYER_MAX_SPEED,
        .input_velocity_func = player_controls[PLAYER1],
    };
    game->players[PLAYER2] = (Player){
        .index = PLAYER2,
        .color = white,
        .rect = {200, 0, 20, 80},
        .position = {window_width() - 15, center_y, 0},
        .speed = PLAYER_MAX_SPEED,
        .input_velocity_func = player_controls[PLAYER2],
    };

    game->ball = (Ball){
        .color = white,
        .rect = {center_x, center_y, 10, 10},
        .position = {0},
        .speed = BALL_MAX_SPEED
    };
    ball_reset(ball());

    game->walls[TOP_WALL] = (Wall){
        .color = white,
        .rect = {0, 0, window_width(), 10},
        .position = {center_x, 5},
    };
    game->walls[BOTTOM_WALL] = (Wall){
        .color = white,
        .rect = {0, 0, window_width(), 10},
        .position = {center_x, window_height() - 5},
    };
}

void pong_process_event(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_w) {
            game->actions[PLAYER1_ACTION_UP] = true;
        }
        if (event->key.keysym.sym == SDLK_s) {
            game->actions[PLAYER1_ACTION_DOWN] = true;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            game->actions[PLAYER2_ACTION_UP] = true;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            game->actions[PLAYER2_ACTION_DOWN] = true;
        }
    }

    if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_w) {
            game->actions[PLAYER1_ACTION_UP] = false;
        }
        if (event->key.keysym.sym == SDLK_s) {
            game->actions[PLAYER1_ACTION_DOWN] = false;
        }
        if (event->key.keysym.sym == SDLK_UP) {
            game->actions[PLAYER2_ACTION_UP] = false;
        }
        if (event->key.keysym.sym == SDLK_DOWN) {
            game->actions[PLAYER2_ACTION_DOWN] = false;
        }
    }
}

void process_events(SDL_Event* event)
{
    if (event->type == SDL_QUIT) {
        engine_quit_loop();
    }

    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            engine_quit_loop();
        }
    }

    pong_process_event(event);
}

void fixed_update(double delta)
{
    player_fixed_update(player1(), delta);
    player_fixed_update(player2(), delta);
    ball_fixed_update(ball(), delta);
}

void update(double delta)
{
    player_update(player1(), delta);
}

void render(void)
{
    player_render(player1());
    player_render(player2());
    ball_render(ball());
    wall_render(top_wall());
    wall_render(bottom_wall());
}

int window_width(void)
{
    return game->settings.window.width;
}

int window_height(void)
{
    return game->settings.window.height;
}

Player* player1(void)
{
    return &game->players[PLAYER1];
}

Player* player2(void)
{
    return &game->players[PLAYER2];
}

Ball* ball(void)
{
    return &game->ball;
}

Wall* top_wall(void)
{
    return &game->walls[TOP_WALL];
}

Wall* bottom_wall(void)
{
    return &game->walls[BOTTOM_WALL];
}
