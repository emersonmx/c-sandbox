#include <utils/random.h>

#include "game.h"

int main(void)
{
    randomize();

    Game* game = game_instance();

    game->settings = engine_default_settings();
    game->settings.window.title = "Game";

    engine_set_init_func(game_initialize);
    engine_set_quit_func(game_finalize);
    engine_set_process_events_func(game_process_events);
    engine_set_fixed_update_func(game_fixed_update);
    engine_set_render_func(game_render);

    engine_main(game->settings);
}
