#include "sdl2.h"

#include <utils/macros.h>

bool initialize_sdl2(void)
{
    return SDL_Init(SDL_INIT_EVERYTHING) == 0;
}

void finalize_sdl2(void)
{
    SDL_Quit();
}

bool initialize_sdl2_ttf(void)
{
    return TTF_Init() == 0;
}

void finalize_sdl2_ttf(void)
{
    TTF_Quit();
}

SDL_Window* create_sdl2_window(const char* title, int width, int height)
{
    return create_sdl2_window_with_flags(title, width, height, SDL_WINDOW_SHOWN);
}

SDL_Window* create_sdl2_window_with_flags(
    const char* title, int width, int height, Uint32 flags
) {
    return SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        flags
    );
}

void destroy_sdl2_window(SDL_Window* window)
{
    RETURN_IF_NULL(window);
    SDL_DestroyWindow(window);
}

SDL_Renderer* create_sdl2_renderer(SDL_Window* window)
{
    RETURN_VALUE_IF_NULL(window, NULL);

    return SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
}

void destroy_sdl2_renderer(SDL_Renderer* renderer)
{
    RETURN_IF_NULL(renderer);
    SDL_DestroyRenderer(renderer);
}

