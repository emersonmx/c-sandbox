#include "wall.h"

#include "object.h"

SDL_Rect wall_rect(Wall* wall)
{
    return object_rect(wall);
}

void wall_render(Wall* wall)
{
    object_render(wall);
}
