#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"

#include "renderer.h"

int init();         // start SDL and create a window, returns 0 on error
int eventHandler(SDL_Event e);	// handle events
void draw();
int draw_thread(void* arg);
int poll_thread (void* arg);

const int SCREEN_WIDTH = HORIZONTAL_RESOLUTION*2, SCREEN_HEIGHT = VERTICAL_RESOLUTION*2;	// screen resolution

SDL_Window* window = NULL;		// window
SDL_Renderer* renderer = NULL;	// renderer

volatile static int quit_flag;
volatile static int draw_flag;

volatile static int draw_done;
volatile static int poll_done;

static screen_t screen;

int init() {	// start SDL and create a window, returns 0 on error
	quit_flag = 0;
	draw_flag = 0;
	screen = (screen_t)malloc(sizeof(int)*VERTICAL_RESOLUTION*HORIZONTAL_RESOLUTION*3);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {		// video init
        std::cout << "meepmop: " << SDL_GetError() << std::endl;
        return 0;
    }
    window = SDL_CreateWindow("yo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {							// window init
        std::cout << "meepmop: " << SDL_GetError() << std::endl;
        return 0;
    }
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {						// renderer init
		std::cout << "meepmop: " << SDL_GetError() << std::endl;
		return 0;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);	// white
	SDL_RenderClear(renderer);									// draw background
	SDL_RenderPresent(renderer);	// put the render onto the window

	poll_done = 0;
	SDL_CreateThread(poll_thread, "poll_thread", NULL);
	draw_done = 0;
	SDL_CreateThread(draw_thread, "draw_thread", NULL);

	return 1;
}

int poll_thread(void* arg) {
	SDL_Event e;	// event struct
	while (!quit_flag) {
		if (SDL_PollEvent(&e)) {	// poll for events
			if (eventHandler(e)) {
				close_screen();
				return 0;
			};
		}
	}
	poll_done = 1;
	return 0;
}

int eventHandler(SDL_Event e) {	// handle events
	if (e.type == SDL_QUIT) {	// quit event
		return 1;
	} else if(e.type == SDL_KEYDOWN) {	// keydown event
		switch(e.key.keysym.sym) {
			case SDLK_UP:				// up
				break;
			case SDLK_DOWN:				// down
				break;
			case SDLK_LEFT:				// left
				break;
			case SDLK_RIGHT:			// right
				break;
			case SDLK_BACKSPACE:		// backspace
			case SDLK_0:				// 0
				break;
			case SDLK_2:				// 1
				break;
			case SDLK_1:				// 2
				break;
			case SDLK_3:				// 3
				break;
			case SDLK_4:				// 4
				break;
			case SDLK_5:				// 5
				break;
			case SDLK_6:				// 6
				break;
			case SDLK_7:				// 7
				break;
			case SDLK_8:				// 8
				break;
			case SDLK_9:				// 9
				break;
			case SDLK_RETURN:			// enter
				break;
			case SDLK_BACKSLASH:		// backslash
				break;
			default:
				return 0;
		}
	}
	return 0;
}

screen_t start_screen() {
    if (!init()) return NULL;	// initialize the video, window, and renderer
    return screen;
}

void draw_screen() {
	draw_flag = 1;
	return;
}

int draw_thread(void* arg) {
	while (!quit_flag) {
		if (draw_flag) {
			draw();
			draw_flag = 0;
		}
	}
	draw_done = 1;
	return 0;
}

void draw() {
	int x;
	int y;
	for (y=0; y < VERTICAL_RESOLUTION; ++y) {
		for (x=0; x < HORIZONTAL_RESOLUTION; ++x) {
			SDL_SetRenderDrawColor(renderer, screen[y][x][0], screen[y][x][1], screen[y][x][2], 0xFF);	// highlight current position
			SDL_Rect drawUnit = {x*2, y*2, 2, 2};
			SDL_RenderFillRect(renderer, &drawUnit);
		}
	}
	SDL_RenderPresent(renderer);	// put the render onto the window
	return;
}

void close_screen() {		// deallocate memory and close the window
	quit_flag = 1;
	while (!poll_done) {}
	while (!draw_done) {}
	SDL_DestroyRenderer(renderer);	// free renderer
	renderer = NULL;
    SDL_DestroyWindow(window);		// free window
    window = NULL;
    SDL_Quit();						// quit
}
