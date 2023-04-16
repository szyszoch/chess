#pragma once
#include <memory.h>
#include <string.h>
#include "renderer.h"

#define COLOR_WHITE (SDL_Color){255,255,255,255}
#define COLOR_BLACK (SDL_Color){0,0,0,255}

typedef struct InputBox InputBox;

InputBox* inputbox_create(SDL_Rect pos, unsigned int max_letters);
void inputbox_destroy(InputBox* inb);
void inputbox_render(InputBox* inb);
void inputbox_handle(InputBox* inb);
const char* inputbox_get_input(InputBox* inb);
void inputbox_update(InputBox* inb);
