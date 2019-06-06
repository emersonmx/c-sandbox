#ifndef PONG_APP_H
#define PONG_APP_H

#include <sdl2/engine.h>
#include <sdl2/sdl2_ttf.h>

#include "action.h"
#include "player.h"
#include "ball.h"
#include "wall.h"
#include "midfield.h"
#include "score.h"
#include "shade.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    BALL_OUT_OF_BOUNDS_SIGNAL, PLAY_BALL_SIGNAL, SIGNALS_SIZE
};

typedef struct App {
    EngineSettings settings;
    bool paused;

    TTF_Font* score_font;
    Uint32 event_id;

    Player player1;
    Player player2;
    Ball ball;
    Wall top_wall;
    Wall bottom_wall;
    MidField midfield;
    Score player1_score;
    Score player2_score;
    Shade shade;

    SDL_Rect play_area;
} App;


App* app_instance(void);

void app_initialize(void);
void app_finalize(void);
void app_process_events(SDL_Event* event);
void app_fixed_update(double delta);
void app_update(double delta);
void app_render(void);

void app_pause(void);
void app_unpause(void);

#ifdef __cplusplus
}
#endif

#endif /* PONG_APP_H */
