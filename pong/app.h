#ifndef PONG_APP_H
#define PONG_APP_H

#include <sdl2/engine.h>
#include <sdl2/sdl2_ttf.h>

#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct App {
    EngineSettings settings;

    TTF_Font* score_font;

    Game game;
} App;


App* app_instance(void);

void app_init(void);
void app_quit(void);
void app_process_events(SDL_Event* event);
void app_fixed_update(double delta);
void app_update(double delta);
void app_render(void);

#ifdef __cplusplus
}
#endif

#endif /* PONG_APP_H */
