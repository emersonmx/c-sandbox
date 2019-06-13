#include "render.h"

#include <sdl2/engine.h>

void renderer_draw_rect(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(
        engine_renderer(),
        color.r, color.g, color.b, color.a
    );
    SDL_RenderFillRect(engine_renderer(), &rect);
}
