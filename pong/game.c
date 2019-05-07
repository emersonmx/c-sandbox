#include "game.h"

#include <utils/macros.h>

#include "utils.h"

#define WINDOW_WIDTH game.settings.window.width
#define WINDOW_HEIGHT game.settings.window.height
#define WINDOW_CENTER_X WINDOW_WIDTH/2.0
#define WINDOW_CENTER_Y WINDOW_HEIGHT/2.0

static Game game;

Game* game_instance(void)
{
    return &game;
}

void game_initialize(void)
{
    sdl2_ttf_initialize();

    game.score_font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 32);
    if (!game.score_font) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s\n", TTF_GetError());
    }

    game.event_id = SDL_RegisterEvents(1);
    if (game.event_id == (Uint32)-1) {
        SDL_Log("Can't register game event\n\tError: %s\n", SDL_GetError());
        engine_quit_loop();
        return;
    }

    PlayerInputVelocityFunc* player_controls[2];
    player_controls[PLAYER1] = player_default_input_velocity_func;
    // player_controls[PLAYER2] = player_default_input_velocity_func;
    // player_controls[PLAYER1] = player_ia_input_velocity_func;
    player_controls[PLAYER2] = player_ia_input_velocity_func;

    game.player1 = (Player){
        .id = PLAYER1,
        .color = COLOR_WHITE,
        .rect = {0, 0, 20, 80},
        .position = {15, WINDOW_CENTER_Y, 0},
        .speed = PLAYER_MAX_SPEED,
        .hit_force = PLAYER_DEFAULT_HIT_FORCE,
        .damp_force = PLAYER_DEFAULT_DAMP_FORCE,
        .is_strong_hit = false,
        .input_velocity_func = player_controls[PLAYER1],
    };
    game.player2 = (Player){
        .id = PLAYER2,
        .color = COLOR_WHITE,
        .rect = {200, 0, 20, 80},
        .position = {WINDOW_WIDTH - 15, WINDOW_CENTER_Y, 0},
        .speed = PLAYER_MAX_SPEED,
        .hit_force = PLAYER_DEFAULT_HIT_FORCE,
        .damp_force = PLAYER_DEFAULT_DAMP_FORCE,
        .is_strong_hit = false,
        .input_velocity_func = player_controls[PLAYER2],
    };

    game.ball = (Ball){
        .color = COLOR_WHITE,
        .rect = {WINDOW_CENTER_X, WINDOW_CENTER_Y, 10, 10},
        .position = {0},
        .play_delay = 1000,
    };
    ball_reset(&game.ball);
    ball_play_with_delay(&game.ball);

    game.top_wall = (Wall){
        .color = COLOR_WHITE,
        .rect = {0, 0, WINDOW_WIDTH, 10},
        .position = {WINDOW_CENTER_X, 5},
    };
    game.bottom_wall = (Wall){
        .color = COLOR_WHITE,
        .rect = {0, 0, WINDOW_WIDTH, 10},
        .position = {WINDOW_CENTER_X, WINDOW_HEIGHT - 5},
    };

    game.midfield = (MidField){
        .color = COLOR_WHITE,
        .rect = {0, 0, 4, 4},
        .position = {WINDOW_CENTER_X, WINDOW_CENTER_Y},
    };

    score_reset(&game.player1_score);
    score_reset(&game.player2_score);
    game.player1_score = (Score){
        .color = COLOR_WHITE,
        .position = {WINDOW_CENTER_X - 27, 35},
        .origin = {1, 0, 0},
    };
    game.player2_score = (Score){
        .color = COLOR_WHITE,
        .position = {WINDOW_CENTER_X + 27, 35},
        .origin = {0, 0, 0},
    };
    score_update_score(&game.player1_score, 0);
    score_update_score(&game.player2_score, 0);

    game.play_area = (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
}

void game_finalize(void)
{
    TTF_CloseFont(game.score_font);
    game.score_font = NULL;

    sdl2_ttf_finalize();
}

void game_process_events(SDL_Event* event)
{
    if (event->type == SDL_QUIT) {
        engine_quit_loop();
    }
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            engine_quit_loop();
        }
    }

    action_process_events(event);

#ifdef DEBUG
    if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_r) {
            ball_reset(&game.ball);
            ball_play(&game.ball);
        }
    }
#endif

    if (event->type == game.event_id) {
        if (event->user.code == BALL_OUT_OF_BOUNDS_SIGNAL) {
#ifdef DEBUG
            printf("Ball out of bounds\n");
#endif
            uint8_t player_side = (uintptr_t) event->user.data1;
            if (player_side == PLAYER1) {
                score_update_score(
                    &game.player2_score, game.player2_score.value + 1
                );
            } else if (player_side == PLAYER2) {
                score_update_score(
                    &game.player1_score, game.player1_score.value + 1
                );
            } else {
                SDL_Log("WAT?! O.o\n");
            }

            ball_reset(&game.ball);
            ball_play_with_delay(&game.ball);
        }
        if (event->user.code == PLAY_BALL_SIGNAL) {
#ifdef DEBUG
            printf("Play ball\n");
#endif
            ball_play(&game.ball);
        }
    }
}

void game_fixed_update(double delta)
{
    player_fixed_update(&game.player1, delta);
    player_fixed_update(&game.player2, delta);
    ball_fixed_update(&game.ball, delta);
}

void game_render(void)
{
    midfield_render(&game.midfield);
    score_render(&game.player1_score);
    score_render(&game.player2_score);
    player_render(&game.player1);
    player_render(&game.player2);
    ball_render(&game.ball);
    wall_render(&game.top_wall);
    wall_render(&game.bottom_wall);
}