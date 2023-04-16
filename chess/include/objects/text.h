#pragma once
#include <memory.h>
#include "renderer.h"
#include "events.h"

#define TEXT_COLOR (SDL_Color){0,0,0,255}
#define TEXT_BACKGROUND_COLOR (SDL_Color){255,255,255,255}
#define TEXT_BORDER_COLOR (SDL_Color){0,0,0,255}
#define TEXT_BORDER_SIZE 3
#define TEXT_SIZE 32

typedef struct Text Text;

Text* text_create(const char* title, SDL_Rect pos);
void text_destroy(Text* text);
void text_render(Text* text);