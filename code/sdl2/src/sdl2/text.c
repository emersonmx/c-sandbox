#include "text.h"

#include <assert.h>

#include <SDL_ttf.h>

SDL_Texture* create_text(Text* text);

Text* text_new(void)
{
    Text* text = malloc(sizeof(Text));
    if (!text) {
        return NULL;
    }

    *text = (const Text){0};

    return text;
}

void text_delete(Text* text)
{
    if (!text) {
        return;
    }
    text_clear(text);
    free(text);
}

void text_update_texture(Text* text)
{
    assert(text);

    text->texture = create_text(text);
    SDL_QueryTexture(
        text->texture, NULL, NULL, &text->offset.w, &text->offset.h
    );
}

void text_clear(Text* text)
{
    assert(text);

    if (text->value != NULL) {
        free(text->value);
    }

    if (text->texture != NULL) {
        SDL_DestroyTexture(text->texture);
    }
}

SDL_Texture* create_text(Text* text)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(
        text->font,
        text->value,
        text->color
    );
    if (!surface) {
        return NULL;
    }

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(text->renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        return NULL;
    }

    return texture;
}
