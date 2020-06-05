//Implementation of the geometric shapes example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"
#include "stdlib.h"
#include "stdio.h"

#define MAX_BUNNIES (50000)  // 50K bunnies limit

// This is the maximum amount of elements (quads) per batch
// NOTE: This value is defined in [rlgl] module and can be changed there
typedef struct bunny_t bunny_t;
struct bunny_t
{
    rf_vec2  position;
    rf_vec2  speed;
    rf_color color;
};

rf_context                 rf_ctx;
rf_renderer_memory_buffers rf_mem;
rf_default_font    default_font_mem;

rf_texture2d               bunny_texture;
bunny_t*                   bunnies;
int                        bunnies_count;

int random_value_in_range(int min, int max)
{
    if (min > max)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }

    return (rand() % (abs(max - min) + 1) + min);
}

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(&default_font_mem);

    bunny_texture = rf_load_texture_from_file(EXAMPLES_ASSETS_PATH "assets/wabbit_alpha.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);

    bunnies = (bunny_t*) malloc(MAX_BUNNIES * sizeof(bunny_t)); // Bunnies array
}

void on_frame(const input_data input)
{
    // Update
    if (input.left_mouse_button_pressed)
    {
        // Create more bunnies
        for (int i = 0; i < 100; i++)
        {
            if (bunnies_count < MAX_BUNNIES)
            {
                bunnies[bunnies_count].position = (rf_vec2) { (float) input.mouse_x, (float) input.mouse_y };
                bunnies[bunnies_count].speed.x  = (float) random_value_in_range(-250, 250) / 60.0f;
                bunnies[bunnies_count].speed.y  = (float) random_value_in_range(-250, 250) / 60.0f;
                bunnies[bunnies_count].color    = (rf_color) { random_value_in_range(50, 240), random_value_in_range(80, 240), random_value_in_range(100, 240), 255 };
                bunnies_count++;
            }
        }
    }

    // Update bunnies
    for (int i = 0; i < bunnies_count; i++)
    {
        bunnies[i].position.x += bunnies[i].speed.x;
        bunnies[i].position.y += bunnies[i].speed.y;

        if (((bunnies[i].position.x + bunny_texture.width / 2) > SCREEN_WIDTH) ||
            ((bunnies[i].position.x + bunny_texture.width / 2) < 0)) bunnies[i].speed.x *= -1;
        if (((bunnies[i].position.y + bunny_texture.height / 2) > SCREEN_HEIGHT) ||
            ((bunnies[i].position.y + bunny_texture.height / 2 - 40) < 0)) bunnies[i].speed.y *= -1;
    }

    // Draw
    rf_begin();

    rf_clear(RF_RAYWHITE);

    for (int i = 0; i < bunnies_count; i++)
    {
        // NOTE: When internal batch buffer limit is reached (MAX_BATCH_ELEMENTS),
        // a draw call is launched and buffer starts being filled again;
        // before issuing a draw call, updated vertex data from internal CPU buffer is send to GPU...
        // Process of sending data is costly and it could happen that GPU data has not been completely
        // processed for drawing while new data is tried to be sent (updating current in-use buffers)
        // it could generates a stall and consequently a frame drop, limiting the number of drawn bunnies
        rf_draw_texture(bunny_texture, (rf_vec2) { bunnies[i].position.x, bunnies[i].position.y }, 0, 1, bunnies[i].color);
    }

    rf_draw_rectangle(0, 0, SCREEN_WIDTH, 40, RF_BLACK);

    rf_draw_fps(10, 10);

    char text[1024];
    snprintf(text, sizeof(text), "bunnies: %i", bunnies_count);
    rf_draw_text(text, 120, 10, 20, RF_GREEN);

    snprintf(text, sizeof(text), "batched draw calls: %i", 1 + bunnies_count / RF_MAX_BATCH_ELEMENTS);
    rf_draw_text(text, 320, 10, 20, RF_MAROON);

    rf_end();
}