#ifndef CSB_SDL2_ENGINE_H
#define CSB_SDL2_ENGINE_H

#include <sdl2/sdl2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void EngineInitFunc(void);
typedef void EngineQuitFunc(void);
typedef void EngineProcessEvents(SDL_Event* event);
typedef void EngineFixedUpdateFunc(double delta);
typedef void EngineUpdateFunc(double delta);
typedef void EngineRenderFunc(void);

typedef struct EngineSettings EngineSettings;
struct EngineSettings {
    struct {
        const char* title;
        int width;
        int height;
    } window;
    struct {
        SDL_Color clear_color;
        bool vsync;
    } renderer;
    struct {
        double fps;
    } physics;
};

typedef struct Engine Engine;


void engine_main(EngineSettings settings);
void engine_quit_loop(void);

EngineSettings engine_default_settings(void);
EngineSettings engine_settings(void);
SDL_Window* engine_window(void);
SDL_Renderer* engine_renderer(void);

void engine_set_init_func(EngineInitFunc func);
void engine_set_quit_func(EngineQuitFunc func);
void engine_set_process_events_func(EngineProcessEvents func);
void engine_set_fixed_update_func(EngineFixedUpdateFunc func);
void engine_set_update_func(EngineUpdateFunc func);
void engine_set_render_func(EngineRenderFunc func);

#ifdef __cplusplus
}
#endif

#endif /* CSB_SDL2_ENGINE_H */
