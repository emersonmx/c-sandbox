#ifndef CSB_GAMES_PONG_RENDER_H
#define CSB_GAMES_PONG_RENDER_H

#include <sdl2/sdl2.h>

#define object_render(O) { \
        SDL_Rect rect = (O)->rect; \
        rect.x = (O)->position[0] - rect.w/2.0f; \
        rect.y = (O)->position[1] - rect.h/2.0f; \
        SDL_Color color = (O)->color; \
        renderer_draw_rect(rect, color); \
    }

#ifdef __cplusplus
extern "C" {
#endif

void renderer_draw_rect(SDL_Rect rect, SDL_Color color);

#ifdef __cplusplus
}
#endif

#endif /* CSB_GAMES_PONG_RENDER_H */
