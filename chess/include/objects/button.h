#pragma once
#include "objects/object.h"
#include "objects/texture.h"

#define BUTTON_TEXT_COLOR (SDL_Color){ 240,240,240,255 }
#define BUTTON_BACKGROUND_COLOR (SDL_Color){ 40,40,40,255 }
#define BUTTON_HOVER_BACKGROUND_COLOR (SDL_Color){ 70,70,70,255 }

#define BUTTON_STATE_NORMAL 0
#define BUTTON_STATE_HOVER 1

#define COLOR_WHITE (SDL_Color){255,255,255,255} 
#define COLOR_BLACK (SDL_Color){0,0,0,255}

typedef void (*void_func_ptr)();
typedef struct Button Button;

Button* b_create(const char* title, SDL_Rect position, void_func_ptr func);
void b_destroy(Button* button);
void b_render(Button* button);
bool b_handle(Button* button);