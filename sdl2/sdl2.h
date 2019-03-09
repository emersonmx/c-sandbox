#ifndef CSB_SDL2_SDL2_H
#define CSB_SDL2_SDL2_H

#include <stdbool.h>

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

bool sdl2_initialize(void);
void sdl2_finalize(void);

SDL_Window* sdl2_create_window(const char* title, int width, int height);
SDL_Window* sdl2_create_window_with_flags(
    const char* title, int width, int height, Uint32 flags
);
void sdl2_destroy_window(SDL_Window* window);

SDL_Renderer* sdl2_create_renderer(SDL_Window* window);
SDL_Renderer* sdl2_create_renderer_with_flags(SDL_Window* window, Uint32 flags);
void sdl2_destroy_renderer(SDL_Renderer* renderer);

#ifdef __cplusplus
}
#endif

#endif /* CSB_SDL2_SDL2_H*/
