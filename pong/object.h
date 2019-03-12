#ifndef CSB_GAMES_PONG_OBJECT_H
#define CSB_GAMES_PONG_OBJECT_H

#define object_rect(OBJ) \
    (SDL_Rect){ \
        (OBJ)->position[0] - (OBJ)->rect.w/2.0f, \
        (OBJ)->position[1] - (OBJ)->rect.h/2.0f, \
        (OBJ)->rect.w, \
        (OBJ)->rect.h, \
    }

#define object_render(OBJ) { \
        SDL_Rect rect = (OBJ)->rect; \
        rect.x = (OBJ)->position[0] - rect.w/2.0f; \
        rect.y = (OBJ)->position[1] - rect.h/2.0f; \
        SDL_Color color = (OBJ)->color; \
        renderer_draw_rect(rect, color); \
    }

#endif /* CSB_GAMES_PONG_OBJECT_H */
