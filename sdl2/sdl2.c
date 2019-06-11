#include "sdl2.h"

#include <utils/macros.h>

bool sdl2_initialize(void)
{
    return SDL_Init(SDL_INIT_EVERYTHING) == 0;
}

void sdl2_finalize(void)
{
    SDL_Quit();
}

SDL_Window* sdl2_create_window(const char* title, int width, int height)
{
    return sdl2_create_window_with_flags(
        title, width, height, SDL_WINDOW_SHOWN
    );
}

SDL_Window* sdl2_create_window_with_flags(
    const char* title, int width, int height, uint32_t flags
) {
    return SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        flags
    );
}

void sdl2_destroy_window(SDL_Window* window)
{
    RETURN_IF_NULL(window);
    SDL_DestroyWindow(window);
}

SDL_Renderer* sdl2_create_renderer(SDL_Window* window)
{
    RETURN_VALUE_IF_NULL(window, NULL);

    uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    return sdl2_create_renderer_with_flags(window, flags);
}

SDL_Renderer* sdl2_create_renderer_with_flags(
    SDL_Window* window, uint32_t flags
)
{
    RETURN_VALUE_IF_NULL(window, NULL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, flags);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return renderer;
}

void sdl2_destroy_renderer(SDL_Renderer* renderer)
{
    RETURN_IF_NULL(renderer);
    SDL_DestroyRenderer(renderer);
}

