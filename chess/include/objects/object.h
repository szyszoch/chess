#pragma once
#include <stdbool.h>
#include "renderer.h"

typedef void (*void_func_ptr)();

typedef struct Object {
	bool hidden;
	bool frozen;
	SDL_Rect pos;
} Object;

#define COLOR_WHITE (SDL_Color){255,255,255,255} 
#define COLOR_BLACK (SDL_Color){0,0,0,255}

bool is_object_hover(Object* o);
bool is_object_clicked(Object* o);
void set_object_position(Object* o, int x, int y);
void set_object_position_and_dimensions(Object* o, int x, int y, int w, int h);
void hide_object(Object* o);
void freeze_object(Object* o);
void unfreeze_object(Object* o);
