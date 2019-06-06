#include "app.h"

#include <utils/macros.h>

#include "utils.h"

#define WINDOW_WIDTH app.settings.window.width
#define WINDOW_HEIGHT app.settings.window.height
#define WINDOW_CENTER_X WINDOW_WIDTH/2.0
#define WINDOW_CENTER_Y WINDOW_HEIGHT/2.0

static App app;

App* app_instance(void)
{
    return &app;
}

void app_initialize(void)
{
    sdl2_ttf_initialize();

    app.paused = false;

    app.score_font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 32);
    if (!app.score_font) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s\n", TTF_GetError());
    }

    app.event_id = SDL_RegisterEvents(1);
    if (app.event_id == (Uint32)-1) {
        SDL_Log("Can't register app event\n\tError: %s\n", SDL_GetError());
        engine_quit_loop();
        return;
    }

    PlayerInputVelocityFunc* player_controls[2];
    player_controls[PLAYER1] = player_default_input_velocity_func;
    // player_controls[PLAYER2] = player_default_input_velocity_func;
    // player_controls[PLAYER1] = player_ia_input_velocity_func;
    player_controls[PLAYER2] = player_ia_input_velocity_func;

    app.player1 = (Player){
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
    app.player2 = (Player){
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

    app.ball = (Ball){
        .color = COLOR_WHITE,
        .rect = {WINDOW_CENTER_X, WINDOW_CENTER_Y, 10, 10},
        .position = {0},
        .play_delay = 1000,
    };
    ball_reset(&app.ball);
    ball_play_with_delay(&app.ball);

    app.top_wall = (Wall){
        .color = COLOR_WHITE,
        .rect = {0, 0, WINDOW_WIDTH, 10},
        .position = {WINDOW_CENTER_X, 5},
    };
    app.bottom_wall = (Wall){
        .color = COLOR_WHITE,
        .rect = {0, 0, WINDOW_WIDTH, 10},
        .position = {WINDOW_CENTER_X, WINDOW_HEIGHT - 5},
    };

    app.midfield = (MidField){
        .color = COLOR_WHITE,
        .rect = {0, 0, 4, 4},
        .position = {WINDOW_CENTER_X, WINDOW_CENTER_Y},
    };

    score_reset(&app.player1_score);
    score_reset(&app.player2_score);
    app.player1_score = (Score){
        .color = COLOR_WHITE,
        .position = {WINDOW_CENTER_X - 27, 35},
        .origin = {1, 0, 0},
    };
    app.player2_score = (Score){
        .color = COLOR_WHITE,
        .position = {WINDOW_CENTER_X + 27, 35},
        .origin = {0, 0, 0},
    };
    score_update_score(&app.player1_score, 0);
    score_update_score(&app.player2_score, 0);

    shade_init(&app.shade);

    app.play_area = (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
}

void app_finalize(void)
{
    TTF_CloseFont(app.score_font);
    app.score_font = NULL;

    sdl2_ttf_finalize();
}

void app_process_events(SDL_Event* event)
{
    if (event->type == SDL_QUIT) {
        engine_quit_loop();
    }
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            if (app.paused) {
                app_unpause();
            } else {
                app_pause();
            }
        }
    }

    action_process_events(event);

#ifdef DEBUG
    if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_r) {
            ball_reset(&app.ball);
            ball_play(&app.ball);
        }
    }
#endif

    if (event->type == app.event_id) {
        if (event->user.code == BALL_OUT_OF_BOUNDS_SIGNAL) {
#ifdef DEBUG
            printf("Ball out of bounds\n");
#endif
            uint8_t player_side = (uintptr_t) event->user.data1;
            if (player_side == PLAYER1) {
                score_update_score(
                    &app.player2_score, app.player2_score.value + 1
                );
            } else if (player_side == PLAYER2) {
                score_update_score(
                    &app.player1_score, app.player1_score.value + 1
                );
            } else {
                SDL_Log("WAT?! O.o\n");
            }

            ball_reset(&app.ball);
            ball_play_with_delay(&app.ball);
        }
        if (event->user.code == PLAY_BALL_SIGNAL) {
#ifdef DEBUG
            printf("Play ball\n");
#endif
            ball_play(&app.ball);
        }
    }
}

void app_fixed_update(double delta)
{
    if (app.paused) {
        return;
    }

    player_fixed_update(&app.player1, delta);
    player_fixed_update(&app.player2, delta);
    ball_fixed_update(&app.ball, delta);
}

void app_update(double delta)
{
    if (app.paused) {
        return;
    }

    shade_update(&app.shade, delta);
}

void app_render(void)
{
    midfield_render(&app.midfield);
    score_render(&app.player1_score);
    score_render(&app.player2_score);
    player_render(&app.player1);
    player_render(&app.player2);
    ball_render(&app.ball);
    wall_render(&app.top_wall);
    wall_render(&app.bottom_wall);
    shade_render(&app.shade);
}

void app_pause(void)
{
    app.paused = true;
    shade_show(&app.shade);
}

void app_unpause(void)
{
    app.paused = false;
    shade_hide(&app.shade);
}
