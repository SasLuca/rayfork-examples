#pragma once

#define SCREEN_WIDTH  (800)
#define SCREEN_HEIGHT (450)

typedef struct input_data input_data;
struct input_data
{
    int left_pressed;
    int right_pressed;
    int s_pressed;
    int space_pressed;

    int c_pressed;
    int c_down;

    int r_pressed;
    int r_down;

    float mouse_scroll_y;
};

void on_init(void);
void on_frame(input_data);