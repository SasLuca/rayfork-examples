#include "platform.h"

const char* window_title = "rayfork - basic shapes";

int screen_width = 800;
int screen_height = 450;

rf_context ctx;
rf_render_batch batch;

extern void game_init(rf_gfx_backend_data* gfx_data)
{
    rf_init_context(&ctx);
    rf_init_gfx(screen_width, screen_height, gfx_data);

    batch = rf_create_default_render_batch(RF_DEFAULT_ALLOCATOR);
    rf_set_active_render_batch(&batch);

    rf_image image = rf_load_image_from_file_ez("path");
}

extern void game_update(const input_t* input)
{
    rf_begin();
    {
        rf_clear(RF_RAYWHITE);

        rf_draw_text("ome basic shapes available on rayfork", 20, 20, 20, RF_DARKGRAY);

        rf_draw_circle(screen_width / 4, 120, 35, RF_DARKBLUE);

        rf_draw_rectangle(screen_width / 4 * 2 - 60, 100, 120, 60, RF_RED);

        rf_draw_rectangle_outline((rf_rec) { screen_width / 4 * 2 - 40, 320, 80, 60 }, 0, RF_ORANGE);  // NOTE: Uses QUADS internally, not lines

        rf_draw_rectangle_gradient_h(screen_width / 4 * 2 - 90, 170, 180, 130, RF_MAROON, RF_GOLD);

        rf_draw_triangle((rf_vec2) { screen_width / 4 * 3, 80 },
                         (rf_vec2) { screen_width / 4 * 3 - 60, 150 },
                         (rf_vec2) { screen_width / 4 * 3 + 60, 150 }, RF_VIOLET);

        rf_draw_poly((rf_vec2) { screen_width / 4.0f * 3.0f, 320 }, 6, 80, 0, RF_BROWN);

        rf_draw_circle_gradient(screen_width / 4, 220, 60, RF_GREEN, RF_SKYBLUE);

        // NOTE: We draw all LINES based shapes together to optimize internal drawing,
        // this way, all LINES are rendered in a single draw pass
        rf_draw_line(18, 42, screen_width - 18, 42, RF_BLACK);

        rf_draw_circle_lines(screen_width / 4, 340, 80, RF_DARKBLUE);

        rf_draw_triangle_lines(
                (rf_vec2) { screen_width / 4 * 3, 160 },
                (rf_vec2) { screen_width / 4 * 3 - 20, 230 },
                (rf_vec2) { screen_width / 4 * 3 + 20, 230 },
                RF_DARKBLUE);
    }
    rf_end();
}

extern void game_window_resize(int width, int height)
{
    screen_width  = width;
    screen_height = height;

    rf_set_viewport(screen_width, screen_height);
}