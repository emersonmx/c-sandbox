#include <utils/random.h>

#include "app.h"

int main(void)
{
    randomize();

    App* app = app_instance();

    app->settings = engine_default_settings();
    app->settings.window.title = "Pong";

    engine_set_init_func(app_init);
    engine_set_quit_func(app_quit);
    engine_set_process_events_func(app_process_events);
    engine_set_fixed_update_func(app_fixed_update);
    engine_set_update_func(app_update);
    engine_set_render_func(app_render);

    engine_main(app->settings);
}
