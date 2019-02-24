#ifndef SDL2_SDL2_H
#define SDL2_SDL2_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

#ifdef __cplusplus
extern "C" {
#endif

bool initialize_sdl2(void);
void finalize_sdl2(void);

bool initialize_sdl2_ttf(void);
void finalize_sdl2_ttf(void);

SDL_Window* create_sdl2_window(const char* title, int width, int height);
SDL_Window* create_sdl2_window_with_flags(
    const char* title, int width, int height, Uint32 flags
);
void destroy_sdl2_window(SDL_Window* window);

SDL_Renderer* create_sdl2_renderer(SDL_Window* window);
void destroy_sdl2_renderer(SDL_Renderer* renderer);

#ifdef __cplusplus
}
#endif

#endif /* SDL2_SDL2_H */
