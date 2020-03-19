// Implementation of the geometric shapes example from raylib using rayfork

#include "rayfork.h"
#include "glad.h"
#include "sokol_app.h"
#include "malloc.h"

#define SCREEN_WIDTH  (800)
#define SCREEN_HEIGHT (450)

rf_context rf_ctx;
rf_renderer_memory_buffers rf_mem;
rf_default_font_buffers default_font_mem;

void on_init(void)
{
    // Load opengl with glad
    gladLoadGL();

    // Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(&default_font_mem);
}

void on_frame(void)
{
    rf_begin();
    {
        rf_clear(RF_RAYWHITE);

        rf_draw_text("some basic shapes available on raylib", 20, 20, 20, RF_DARKGRAY);

        rf_draw_circle(SCREEN_WIDTH / 4, 120, 35, RF_DARKBLUE);

        rf_draw_rectangle(SCREEN_WIDTH / 4 * 2 - 60, 100, 120, 60, RF_RED);

        rf_draw_rectangle_outline((rf_rec) { SCREEN_WIDTH / 4 * 2 - 40, 320, 80, 60 }, 0, RF_ORANGE);  // NOTE: Uses QUADS internally, not lines

        rf_draw_rectangle_gradient_h(SCREEN_WIDTH / 4 * 2 - 90, 170, 180, 130, RF_MAROON, RF_GOLD);

        rf_draw_triangle((rf_vec2) { SCREEN_WIDTH / 4 * 3, 80 },
                         (rf_vec2) { SCREEN_WIDTH / 4 * 3 - 60, 150 },
                         (rf_vec2) { SCREEN_WIDTH / 4 * 3 + 60, 150 }, RF_VIOLET);

        rf_draw_poly((rf_vec2) { SCREEN_WIDTH / 4.0f * 3.0f, 320 }, 6, 80, 0, RF_BROWN);

        rf_draw_circle_gradient(SCREEN_WIDTH / 4, 220, 60, RF_GREEN, RF_SKYBLUE);

        // NOTE: We draw all LINES based shapes together to optimize internal drawing,
        // this way, all LINES are rendered in a single draw pass
        rf_draw_line(18, 42, SCREEN_WIDTH - 18, 42, RF_BLACK);

        rf_draw_circle_lines(SCREEN_WIDTH / 4, 340, 80, RF_DARKBLUE);

        rf_draw_triangle_lines(
                (rf_vec2) { SCREEN_WIDTH / 4 * 3, 160 },
                (rf_vec2) { SCREEN_WIDTH / 4 * 3 - 20, 230 },
                (rf_vec2) { SCREEN_WIDTH / 4 * 3 + 20, 230 },
                RF_DARKBLUE);
    }
    rf_end();
}