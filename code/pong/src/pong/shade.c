#include "shade.h"

#include "app.h"
#include "render.h"
#include "object.h"

void shade_init(Shade* shade)
{
    EngineSettings settings = app_instance()->settings;
    int32_t width = settings.window.width;
    int32_t height = settings.window.height;

    *shade = (Shade){
        .color = {0, 0, 0, 200},
        .rect = {0, 0, width, height},
        .position = {width/2.0, height/2.0, 0},
        .visibility = false,
    };
}

void shade_show(Shade* shade)
{
    shade->visibility = true;
}

void shade_hide(Shade* shade)
{
    shade->visibility = false;
}

void shade_update(Shade* shade, double delta)
{
}

void shade_render(Shade* shade)
{
    if (!shade->visibility) {
        return;
    }

    object_render(shade);
}

