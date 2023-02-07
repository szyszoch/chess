#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "log.h"
#include "button.h"
#include "texture.h"
#include "board.h"

#define WINDOW_TITLE "Chess"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define STATE_QUIT 0
#define STATE_MENU 1
#define STATE_LOCALGAME 2
#define STATE_JOINGAME 3
#define STATE_CREATEGAME 4

typedef struct Chess {

	int state;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event events;
	Uint32 window_flags;

	Texture** texture;
	int ntexture;
	Button** button;
	int nbutton;
	Board** board;
	int nboard;

	int* chess_tex_index; // Index to textures of chess


} Chess;

void Chess_Init();
void Chess_Destroy();
void Chess_Render();
void Chess_HandleEvent();
void Chess_Delay();
int Chess_State();
void Chess_StateClean();

void Chess_State_Menu();
void Chess_State_LocalGame();

void Chess_Event_Exit();
void Chess_Event_GoToMenu();
void Chess_Event_GoToLocalGame();
void Chess_Event_GoToJoinGame();
void Chess_Event_GoToCreateGame();
