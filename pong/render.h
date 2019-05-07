#ifndef PONG_RENDER_H
#define PONG_RENDER_H

#include <sdl2/sdl2.h>

#ifdef __cplusplus
extern "C" {
#endif

void renderer_draw_rect(SDL_Rect rect, SDL_Color color);

#ifdef __cplusplus
}
#endif

#endif /* PONG_RENDER_H */
