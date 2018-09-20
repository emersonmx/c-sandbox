#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>

SDL_Window* window = NULL;

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    window = SDL_CreateWindow(
        "Time Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        return false;
    }

    return true;
}

void quit()
{
    SDL_DestroyWindow(window);

    SDL_Quit();
}

int main() {
    atexit(quit);
    if (!init()) {
        return -1;
    }

    int delay = 1000;

    uint32_t start_low = SDL_GetTicks();
    SDL_Delay(delay);
    uint32_t end_low = SDL_GetTicks();

    uint64_t start_high = SDL_GetPerformanceCounter();
    SDL_Delay(delay);
    uint64_t end_high = SDL_GetPerformanceCounter();

    printf("%u\n", end_low - start_low);
    printf("%f\n", (end_high - start_high) / (double)SDL_GetPerformanceFrequency());

    return 0;
}
