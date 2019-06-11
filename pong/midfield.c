#include "midfield.h"

#include "app.h"
#include "render.h"

void midfield_render(MidField* midfield)
{
    App* app = app_instance();
    int32_t window_height = app->settings.window.height;
    int32_t window_half_height = window_height/2.0f;

    int32_t position_x = midfield->position[0] - midfield->rect.w/2.0f;
    int32_t position_y = midfield->position[1] - midfield->rect.h/2.0f;
    int32_t top = -window_half_height;
    int32_t bottom = window_half_height;

    for (
        int32_t step = top;
        step <= bottom;
        step += window_half_height/30.0f
    ) {
        SDL_Rect rect = {
            position_x, position_y + step,
            midfield->rect.w, midfield->rect.h,
        };
        SDL_Color color = midfield->color;
        renderer_draw_rect(rect, color);
    }
}
