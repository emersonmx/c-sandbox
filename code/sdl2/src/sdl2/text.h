#ifndef CSB_SDL2_TEXT_H
#define CSB_SDL2_TEXT_H

#include <SDL_render.h>
#include <SDL_ttf.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Text {
    char* value;
    SDL_Color color;
    TTF_Font* font;
    SDL_Rect offset;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Text;

Text* text_new(void);
void text_delete(Text* text);

void text_update_texture(Text* text);
void text_clear(Text* text);

#ifdef __cplusplus
}
#endif

#endif /* CSB_SDL2_TEXT_H */
