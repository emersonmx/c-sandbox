#include "sdl2.h"

#define TIMEOUT_EVENT 1

static Uint32 user_event;

Uint32 my_timer_callback(Uint32 interval, void* param);

int main(int argc, char* argv[])
{
    sdl2_initialize();

    SDL_Window* window = sdl2_create_window("Events", 800, 600);
    SDL_Renderer* renderer = sdl2_create_renderer(window);

    SDL_Event event;
    user_event = SDL_RegisterEvents(1);
    if (user_event == (Uint32)-1) {
        SDL_Log("Can't register user event.\n\tError: %s\n", SDL_GetError());
        return -1;
    }

    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    SDL_Log("Timeout in 5 seconds\n");
                    SDL_AddTimer(5000, my_timer_callback, NULL);
                }
            }
            if (event.type == user_event) {
                if (event.user.code == TIMEOUT_EVENT) {
                    SDL_Log("Event timeout!\n");
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    sdl2_destroy_renderer(renderer);
    sdl2_destroy_window(window);

    sdl2_finalize();
}

Uint32 my_timer_callback(Uint32 interval, void* param)
{
    SDL_Event myevent;
    SDL_memset(&myevent, 0, sizeof(myevent));
    myevent.type = user_event;
    myevent.user.code = TIMEOUT_EVENT;

    SDL_PushEvent(&myevent);

    return 0;
}
