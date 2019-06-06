#include "midfield.h"

#include "app.h"

void midfield_render(MidField* midfield)
{
    App* app = app_instance();
    int window_height = app->settings.window.height;
    int window_half_height = window_height/2.0f;

    int position_x = midfield->position[0] - midfield->rect.w/2.0f;
    int position_y = midfield->position[1] - midfield->rect.h/2.0f;
    int top = -window_half_height;
    int bottom = window_half_height;

    for (int step = top; step <= bottom; step += window_half_height/30.0f) {
        SDL_Rect rect = {
            position_x, position_y + step,
            midfield->rect.w, midfield->rect.h,
        };
        SDL_Color color = midfield->color;
        renderer_draw_rect(rect, color);
    }
}
