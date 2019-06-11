#include "app.h"

#include "shade.h"

static App app;

App* app_instance(void)
{
    return &app;
}

void app_initialize(void)
{
    sdl2_ttf_initialize();

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

    game_init(&app.game);
}

void app_finalize(void)
{
    game_quit(&app.game);

    TTF_CloseFont(app.score_font);
    app.score_font = NULL;

    sdl2_ttf_finalize();
}

void app_process_events(SDL_Event* event)
{
    game_process_events(&app.game, event);
}

void app_fixed_update(double delta)
{
    game_fixed_update(&app.game, delta);
}

void app_update(double delta)
{
    game_update(&app.game, delta);
}

void app_render(void)
{
    game_render(&app.game);
}
