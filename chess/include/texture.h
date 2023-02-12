#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <malloc.h>
#include "log.h"

typedef struct Texture Texture;

Texture* Texture_LoadFrom(SDL_Renderer* renderer, const char* path, SDL_Rect position);
Texture* Texture_CreateText(SDL_Renderer* renderer, const char* font_path, int font_size, const char* title, SDL_Color color,  int x, int y);
void Texture_Destroy(Texture* texture);
void Texture_Render(Texture* texture);
void Texture_ChangePosition(Texture* texture, int x, int y);
void Texture_Clean(Texture* texture);