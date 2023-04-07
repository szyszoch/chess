#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <malloc.h>
#include <memory.h>
#include "log.h"

typedef union Color {
	SDL_Color color;
	Uint32 uint;
} Color;

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600
#define WINDOW_RECT (SDL_Rect){0,0,WINDOW_WIDTH,WINDOW_HEIGHT}
#define WINDOW_BACKGROUND_COLOR (SDL_Color){150, 150, 150, 255}

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Event event_handler;

bool init_window();
void destroy_window();
void set_window_default_background_color();
bool pressed_key(SDL_Scancode code);
bool pressed_quit();
void delay();