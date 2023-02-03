#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "log.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

void Chess_Init();
void Chess_Destroy();