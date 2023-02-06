#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "log.h"

#define BUTTON_NORMAL 0
#define BUTTON_HOVER 1

typedef void (*void_func_ptr)();

typedef struct Button Button;

Button* Button_Init(SDL_Renderer* renderer, const char* font_path, int font_size, const char* title, SDL_Rect position, SDL_Color background_color, SDL_Color text_color);
void Button_Destroy(Button* button);
void Button_Render(Button* button);
void Button_Event(Button* button, SDL_Event* events);
void Button_SetEvent(Button* button, void_func_ptr function);

void Empty_Function();