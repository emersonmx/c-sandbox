#include "app.h"

#include "events.h"

static App app;

App* app_instance(void)
{
    return &app;
}

void app_init(void)
{
    sdl2_ttf_initialize();

    app.score_font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 32);
    if (!app.score_font) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s\n", TTF_GetError());
    }

    if (!events_init()) {
        SDL_Log("Can't register app event\n\tError: %s\n", SDL_GetError());
        engine_quit_loop();
        return;
    }

    game_init(&app.game);
}

void app_quit(void)
{
    game_quit(&app.game);

    events_quit();

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
