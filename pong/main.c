#include <utils/random.h>

#include "pong.h"

int main(void)
{
    randomize();

    Pong* game = pong_instance();

    game->settings = engine_default_settings();
    game->settings.window.title = "Pong";

    engine_set_init_func(pong_initialize);
    engine_set_process_events_func(pong_process_event);
    engine_set_fixed_update_func(pong_fixed_update);
    engine_set_render_func(pong_render);

    return engine_main_loop(game->settings);
}
