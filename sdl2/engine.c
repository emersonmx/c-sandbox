#include "engine.h"

#include <sdl2/timer.h>
#include <utils/macros.h>

void default_init_func(void) {}
void default_quit_func(void) {}
void default_process_events_func(SDL_Event* event) {}
void default_fixed_update_func(double delta) {}
void default_update_func(double delta) {}
void default_render_func(void) {}

struct Engine {
    EngineSettings settings;
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool running;
    double physics_tick_count;

    EngineInitFunc* init_func;
    EngineQuitFunc* quit_func;
    EngineProcessEvents* process_events_func;
    EngineFixedUpdateFunc* fixed_update_func;
    EngineUpdateFunc* update_func;
    EngineRenderFunc* render_func;
};

static Engine engine = {
    .window = NULL,
    .renderer = NULL,

    .running = true,
    .physics_tick_count = 0.0,

    .init_func = default_init_func,
    .quit_func = default_quit_func,
    .process_events_func = default_process_events_func,
    .fixed_update_func = default_fixed_update_func,
    .update_func = default_update_func,
    .render_func = default_render_func,
};

static double fixed_update_delta(void);
static void initialize_engine(void);
static bool setup_window(void);
static bool setup_renderer(void);
static void finalize_engine(void);
static void destroy_renderer(void);
static void destroy_window(void);
static void process_events(void);
static void fixed_update(void);
static void update(double delta);
static void render(void);

void engine_main(EngineSettings settings)
{
    engine.settings = engine_default_settings();
    engine.settings = settings;

    atexit(finalize_engine);

    initialize_engine();

    double last_count = timer_get_ticks_in_seconds();
    double delta = fixed_update_delta();

    while (engine.running) {
        double now = timer_get_ticks_in_seconds();
        delta = now - last_count;
        last_count = now;
        engine.physics_tick_count += delta;

        process_events();
        fixed_update();
        update(delta);
        render();
    }
}

void engine_quit_loop(void)
{
    engine.running = false;
}

EngineSettings engine_default_settings(void)
{
    return (EngineSettings){
        .window = {
            "engine.Window",
            800, 600
        },
            .renderer = {
                .clear_color = {0, 0, 0, SDL_ALPHA_OPAQUE},
                .vsync = true
            },
            .physics = {
                .fps = 60.0
            }
    };
}

EngineSettings engine_settings(void)
{
    return engine.settings;
}

SDL_Window* engine_window(void)
{
    return engine.window;
}

SDL_Renderer* engine_renderer(void)
{
    return engine.renderer;
}

void engine_set_init_func(EngineInitFunc func)
{
    ASSERT_VALID_OBJECT(func);
    engine.init_func = func;
}

void engine_set_quit_func(EngineQuitFunc func)
{
    ASSERT_VALID_OBJECT(func);
    engine.quit_func = func;
}

void engine_set_process_events_func(EngineProcessEvents func)
{
    ASSERT_VALID_OBJECT(func);
    engine.process_events_func = func;
}

void engine_set_fixed_update_func(EngineFixedUpdateFunc func)
{
    ASSERT_VALID_OBJECT(func);
    engine.fixed_update_func = func;
}

void engine_set_update_func(EngineUpdateFunc func)
{
    ASSERT_VALID_OBJECT(func);
    engine.update_func = func;
}

void engine_set_render_func(EngineRenderFunc func)
{
    ASSERT_VALID_OBJECT(func);
    engine.render_func = func;
}

double fixed_update_delta(void)
{
    return 1.0 / engine.settings.physics.fps;
}

void initialize_engine(void)
{
    sdl2_initialize();

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);

    engine.running = setup_window() && setup_renderer();

    engine.init_func();
}

bool setup_window(void)
{
    engine.window = sdl2_create_window(
        engine.settings.window.title,
        engine.settings.window.width, engine.settings.window.height
    );
    if (!engine.window) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
            "Couldn't create SDL Window\n\tError: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool setup_renderer(void)
{
    uint32_t flags = SDL_RENDERER_ACCELERATED;
    if (engine.settings.renderer.vsync) {
        flags |= SDL_RENDERER_PRESENTVSYNC;
    }

    engine.renderer = sdl2_create_renderer_with_flags(engine.window, flags);
    if (!engine.renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
            "Couldn't create SDL Renderer\n\tError: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void finalize_engine(void)
{
    engine.quit_func();

    destroy_renderer();
    destroy_window();

    sdl2_finalize();
}

void destroy_renderer(void)
{
    sdl2_destroy_renderer(engine.renderer);
    engine.renderer = NULL;
}

void destroy_window(void)
{
    sdl2_destroy_window(engine.window);
    engine.window = NULL;
}

void process_events(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        engine.process_events_func(&event);
    }
}

void fixed_update(void)
{
    if (engine.physics_tick_count <= fixed_update_delta()) {
        return;
    }

    engine.fixed_update_func(fixed_update_delta());

    engine.physics_tick_count -= fixed_update_delta();
}

void update(double delta)
{
    engine.update_func(delta);
}

void render(void)
{
    SDL_Color color = engine.settings.renderer.clear_color;
    SDL_SetRenderDrawColor(engine.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(engine.renderer);

    engine.render_func();

    SDL_RenderPresent(engine.renderer);
}
