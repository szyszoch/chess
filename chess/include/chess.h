#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "log.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define STATE_QUIT 0
#define STATE_MENU 1

void Chess_Init();
void Chess_Destroy();
void Chess_Render();
void Chess_HandleEvent();
void Chess_Delay();
int Chess_State();

void Chess_State_Menu();