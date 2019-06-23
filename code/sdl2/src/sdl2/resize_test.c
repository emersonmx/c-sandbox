#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include <sdl2/sdl2.h>
#include <sdl2/sdl2_ttf.h>
#include <sdl2/text.h>
#include <utils/str.h>

typedef struct Engine {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
} Engine;

static Engine* engine = NULL;

void init(void);
void quit(void);
void load_assets(void);
void destroy_assets(void);

int main(void)
{
    init();

    SDL_Rect window_rect = {0};
    SDL_GetWindowSize(engine->window, &window_rect.w, &window_rect.h);

    SDL_Rect fill_rect = {5, 5, 790, 590};

    Text* text = text_new();
    text->font = engine->font;
    text->renderer = engine->renderer;
    text->color = (SDL_Color){0x7b, 0, 0x7b, SDL_ALPHA_OPAQUE};

    text_clear(text);
    text->value = str_format("%dx%d", window_rect.w, window_rect.h);
    text_update_texture(text);
    text->offset.x = window_rect.w/2 - text->offset.w/2;
    text->offset.y = window_rect.h/2 - text->offset.h/2;

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    window_rect.w = event.window.data1;
                    window_rect.h = event.window.data2;

                    fill_rect.w = window_rect.w - 10;
                    fill_rect.h = window_rect.h - 10;

                    text_clear(text);
                    text->value = str_format("%dx%d", window_rect.w, window_rect.h);
                    text_update_texture(text);
                    text->offset.x = window_rect.w/2 - text->offset.w/2;
                    text->offset.y = window_rect.h/2 - text->offset.h/2;
                }
            }
        }

        SDL_SetRenderDrawColor(engine->renderer, 0x1a, 0, 0x1a, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(engine->renderer);

        SDL_SetRenderDrawColor(engine->renderer, 0x30, 0, 0x30, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(engine->renderer, &fill_rect);

        SDL_RenderCopy(engine->renderer, text->texture, NULL, &text->offset);

        SDL_RenderPresent(engine->renderer);
    }

    text_delete(text);

    quit();
}

void init(void)
{
    engine = malloc(sizeof(Engine));
    if (!engine) {
        SDL_Log("Couldn't create app engine.");
        return;
    }

    *engine = (const Engine){0};

    if (!sdl2_initialize()) {
        SDL_Log("Couldn't start SDL.\n\tError: %s", SDL_GetError());
        return;
    }

    engine->window = sdl2_create_window_with_flags(
        "Resize Test", 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!engine->window) {
        SDL_Log("Couldn't create window.\n\tError: %s", SDL_GetError());
        return;
    }

    engine->renderer = sdl2_create_renderer(engine->window);
    if (!engine->renderer) {
        SDL_Log("Couldn't create renderer.\n\tError: %s", SDL_GetError());
        return;
    }

    if (!sdl2_ttf_initialize()) {
        SDL_Log("Couldn't initialize SDL TTF.\n\tError: %s", TTF_GetError());
        return;
    }

    load_assets();
}

void quit(void)
{
    destroy_assets();

    sdl2_ttf_finalize();
    sdl2_finalize();

    free(engine);
}

void load_assets(void)
{
    engine->font = TTF_OpenFont("./assets/fonts/Quicksand-Bold.ttf", 40);
    if (!engine->font) {
        SDL_Log("Couldn't load font.\n\tError: %s", TTF_GetError());
        return;
    }
}

void destroy_assets(void)
{
    if (!engine) {
        return;
    }

    TTF_CloseFont(engine->font);
    sdl2_destroy_renderer(engine->renderer);
    sdl2_destroy_window(engine->window);
}
