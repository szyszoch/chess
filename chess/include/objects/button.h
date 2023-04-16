#pragma once
#include "renderer.h"
#include "events.h"

#define BUTTON_TEXT_COLOR (SDL_Color){ 240,240,240,255 }
#define BUTTON_BACKGROUND_COLOR (SDL_Color){ 40,40,40,255 }
#define BUTTON_HOVER_BACKGROUND_COLOR (SDL_Color){ 70,70,70,255 }

#define BUTTON_STATE_NORMAL 0
#define BUTTON_STATE_HOVER 1

typedef void (*void_func_ptr)();
typedef struct Button Button;

Button* button_create(const char* title, SDL_Rect pos, void_func_ptr func);
void button_destroy(Button* bn);
void button_render(Button* bn);
void button_handle(Button* bn);
bool button_clicked(Button* bn);