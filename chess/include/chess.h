#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "log.h"
#include "button.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define STATE_QUIT 0
#define STATE_MENU 1

enum TEXTURE {
	TEXTURE_BLACK_BISHOP,
	TEXTURE_BLACK_KING,
	TEXTURE_BLACK_KNIGHT,
	TEXTURE_BLACK_PAWN,
	TEXTURE_BLACK_QUEEN,
	TEXTURE_BLACK_ROOK,
	TEXTURE_WHITE_BISHOP,
	TEXTURE_WHITE_KING,
	TEXTURE_WHITE_KNIGHT,
	TEXTURE_WHITE_PAWN,
	TEXTURE_WHITE_QUEEN,
	TEXTURE_WHITE_ROOK,
	TEXTURE_COUNT
};

void Chess_Init();
void Chess_Destroy();
void Chess_Render();
void Chess_HandleEvent();
void Chess_Delay();
int Chess_State();

void Chess_State_Menu();

