#ifndef RENDERER_H
#define RENDERER_H

#define HORIZONTAL_RESOLUTION 640
#define VERTICAL_RESOLUTION 480

typedef int (*screen_t)[HORIZONTAL_RESOLUTION][3];

screen_t start_screen(screen_t screen_ptr, volatile int* quit_sim_ptr, volatile int* evt_array_ptr);
void close_screen();		// deallocate memory and close the window
void draw_screen();

#endif // RENDERER_H
