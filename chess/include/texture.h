#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <malloc.h>
#include "log.h"

typedef struct Texture Texture;

Texture* Texture_Init(SDL_Renderer* renderer, const char* path, SDL_Rect position);
void Texture_Destroy(Texture* texture);
void Texture_Render(Texture* texture);